/*
 * 120++.cc
 * UIdaho CS-445 120++ Compiler
 * Main driver for the 120++ Compiler
 * 
 * Copyright (C) 2014 Chris Waltrip <walt2178@vandals.uidaho.edu>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h> /* chdir() */
#include <libgen.h> /* dirname and basename */
#include <boost/program_options.hpp> /* command line arguments parser */

#include "exception.hh"
#include "globals.hh"
#include "lex.yy.h"
#include "token.hh"
#include "120gram.tab.h"
#include "treenode.hh"
#include "semantic.hh"
#include "typename.hh"

extern int yyparse();
extern int yydebug;
extern TreeNode *root;

using namespace std;
using namespace boost;
namespace po = boost::program_options;

Token *yytoken;
string yyfilename;
TypenameTable ident_table;
SemanticAnalyzer sa;
string config_file = "testing.cfg";

/* Move command line parsing to its own function.  Returns file list */
vector<string> parse_command_line(int argc, char *argv[]);

/*
 * The main driver of the compiler.  Parses the command line for all 
 * options and files to compile.  Then iterates through each of the
 * input files, creating parse trees and symbols tables for each.  Then
 * the compiler will perform any necessary type checking and will eventually
 * make its way to the intermediate code generation and final code generation
 * stages.
 *
 * The program options parser code is adapted from the Boost Library example
 * code included with the library and is distributed under the Boost Software
 * License, Version 1.0.  A copy of this license can be found at:
 * http://www.boost.org/LICENSE_1_0.txt
 *
 * TODO:
 *   - Error checking/handling
 */

int main(int argc, char *argv[]) {
	vector<string> file_list;
	FILE *fp;

	/* Parse the command line options */
	try {
		file_list = parse_command_line(argc, argv);	
	} catch(EHaltCommandLineParse e) {
		return(EXIT_FAILURE);
	}

	/* Parse files */
	for(size_t i = 0; i < file_list.size(); ++i) {
		char *tmp1 = strdup(file_list[i].c_str());
		char *tmp2 = strdup(tmp1);
		yyfilename.assign(basename(tmp1));
		chdir(dirname(tmp2));
		free(tmp1);
		free(tmp2);

		if((fp = fopen(yyfilename.c_str(), "r")) != NULL) {
			yyin = fp;
			yypush_buffer_state(yy_create_buffer(yyin, 
							YY_BUF_SIZE));
			int ret = yyparse();
			fclose(fp);
			yylineno = 1;

			if(!ret) {
				if(PRINT_PARSE_TREES) {
					print_tree(root);
					cout << endl;
				}
			sa.add_tree(root, ident_table);
			}
		} else {
			clog << "Cannot find include file: '";
			clog << yyfilename << "'" << endl;
		}
	}
	sa.check_semantics();
	//sa.print_all_tables();

	return(EXIT_SUCCESS);
}

vector<string> parse_command_line(int argc, char *argv[]) {
	/* Setup command line parser */
	try {
		/* File list to return if successful */
		vector<string> vl;

		/* Basic options don't execute compiler */
		po::options_description basic_opts("Basic Options");
		basic_opts.add_options()
			("help,h", "    print this help and exit");

		/* Compiler options control how the compiler operates */
		po::options_description compiler_opts(
						"Compiler Configurations");
		compiler_opts.add_options()
			("verbose,v", "   print additional logging messages")
			("tree,t", "   print abstract syntax tree") 
			("parser_debug,p", "   print parser debug information");
		po::options_description hidden_opts("Hidden Options");
		hidden_opts.add_options()
			("input,I", po::value< vector<string> >(),
						"specify input files");

		po::options_description cmd_opts;
		cmd_opts.add(basic_opts).add(compiler_opts).add(hidden_opts);
		po::options_description config_file_opts;
		config_file_opts.add(compiler_opts).add(hidden_opts);
		po::options_description visible_opts;
		visible_opts.add(basic_opts).add(compiler_opts);
		po::positional_options_description positional_opts;
		positional_opts.add("input", -1);

		po::variables_map vm;

		ifstream ifs(config_file.c_str());
		store(po::parse_config_file(ifs, config_file_opts), vm);
		po::notify(vm);

		store(po::command_line_parser(argc,argv).options(
						cmd_opts).positional(
						positional_opts).run(), vm);
		po::notify(vm);

		/* 
		 * Verify that the correct options are present.  If the 
		 * options are present, then verify their validity.  The most
		 * important part here is to make sure that all the filenames
		 * passed in as positional arguments actually exist.  The only
		 * other option that must be set is the print level; the print
		 * level determines what type of parse tree to print out and
		 * sets global flags appropriately.
		 */
		stringstream help_msg;
		help_msg << "Usage: 120 [options] input_file_1 ";
		help_msg << "input_file_2 ... input_file_n" << endl;
		help_msg << visible_opts;		

		if(vm.count("help")) {
			cout << help_msg.str();
			throw EHaltCommandLineParse();
		}

		if(!vm.count("verbose")) {
			streambuf *null_log = NULL;
			clog.rdbuf(null_log);
		}

		if(vm.count("tree")) {
			PRINT_PARSE_TREES = true;
		}

		if(vm.count("parser_debug")) {
			yydebug = 1;
		} else {
			yydebug = 0;
		}

		if(vm.count("input")) {
			/* Verify the filenames exist */
			vl = vm["input"].as< vector<string> >();
			vector<string>::size_type sz = vl.size();
			FILE *fp;

			for(size_t i = 0; i < sz; ++i) {
				if((fp = fopen(vl[i].c_str(), "r")) == NULL) {
					cerr << "Invalid filename: " << vl[i];
					cerr << endl;
					cerr << help_msg.str();
					throw EHaltCommandLineParse();
				} else {
					fclose(fp);
					clog << "Filename found: " << vl[i];
					clog << endl;
				}
			}
		} else {
			cerr << "No input files specified." << endl;
			cerr << help_msg.str();
			throw EHaltCommandLineParse();
		}

		return vl;
	} catch(EHaltCommandLineParse e) {
		throw EHaltCommandLineParse();
	} catch(std::exception& e) {
		cerr << "120++: General error: " << e.what() << endl;
		throw EHaltCommandLineParse();
	}
}