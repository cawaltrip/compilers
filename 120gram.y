/*
 * 120gram.y
 * UIdaho CS-445 120++ Compiler
 * Bison-style grammar for 120++ language
 * 
 * Copyright (c) 1997 Sandro Sigala <ssigala@globalnet.it>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Grammar for 120++, a subset of C++ used in CS 120 at University of Idaho
 *
 * Adaptation by Clinton Jeffery, with help from Matthew Brown, Ranger
 * Adams, and Shea Newton.
 *
 * Based on Sandro Sigala's transcription of the ISO C++ 1996 draft standard.
 * 
 */

/*
 * ISO C++ parser.
 *
 * Based on the ISO C++ draft standard of December '96.
 */

/* TODO: Improve output, especially for error reporting */

%define parse.error verbose
%define parse.trace

%{

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdarg>
#include <utility>

#include "globals.hh"
#include "treenode.hh"
#include "typename.hh"
#include "120rules.hh"

extern int yylineno;
extern int yylex();
extern std::string yyfilename;
extern std::string yytext;
extern TypenameTable ident_table;

struct TreeNode *root;

struct TreeNode* alloc_tree(yyrule y, int num_kids, ...);
void add_typename(struct TreeNode *t, int cat);
static void unsupported_warn(std::string str = "");
static void unsupported_feature(std::string str = "");
static void yyerror(std::string s);
%}

%define api.value.type { struct TreeNode* }

%token IDENTIFIER INTEGER FLOATING CHARACTER STRING
%token TYPEDEF_NAME NAMESPACE_NAME CLASS_NAME ENUM_NAME TEMPLATE_NAME

%token NAMESPACE_STD

%token ELLIPSIS COLONCOLON DOTSTAR ADDEQ SUBEQ MULEQ DIVEQ MODEQ
%token XOREQ ANDEQ OREQ SL SR SREQ SLEQ EQ NOTEQ LTEQ GTEQ ANDAND OROR
%token PLUSPLUS MINUSMINUS ARROWSTAR ARROW

%token ASM AUTO BOOL BREAK CASE CATCH CHAR CLASS CONST CONST_CAST CONTINUE
%token DEFAULT DELETE DO DOUBLE DYNAMIC_CAST ELSE ENUM EXPLICIT EXPORT EXTERN
%token FALSE FLOAT FOR FRIEND GOTO IF INLINE INT LONG MUTABLE NAMESPACE NEW
%token OPERATOR PRIVATE PROTECTED PUBLIC REGISTER REINTERPRET_CAST RETURN
%token SHORT SIGNED SIZEOF STATIC STATIC_CAST STRUCT SWITCH TEMPLATE THIS
%token THROW TRUE TRY TYPEDEF TYPEID TYPENAME UNION UNSIGNED USING VIRTUAL
%token VOID VOLATILE WCHAR_T WHILE

%start translation_unit

%%

/*----------------------------------------------------------------------
 * Program entrance
 *----------------------------------------------------------------------*/

translation_unit:
	declaration_seq_opt 
		{ root = $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Lexical elements.
 *----------------------------------------------------------------------*/

literal:
	INTEGER
		{ $$ = $1; }
	| CHARACTER
		{ $$ = $1; }
	| FLOATING
		{ $$ = $1; }
	| STRING
		{ $$ = $1; }
	| TRUE
		{ $$ = $1; }
	| FALSE
		{ $$ = $1; }
	;
/*----------------------------------------------------------------------
 * Context-dependent identifiers.
 *----------------------------------------------------------------------*/

namespace_name:
	original_namespace_name 
		{ unsupported_feature(); }
	;

original_namespace_name:
	NAMESPACE_NAME
		{ unsupported_feature(); }
	;

/*----------------------------------------------------------------------
 * Expressions.
 *----------------------------------------------------------------------*/

primary_expression:
	literal
		{ $$ = $1; }
	| THIS
		{ $$ = $1; }
	| id_expression
		{ $$ = $1; }
	| '(' expression ')'
		{ unsupported_feature(); }
	;

id_expression:
	unqualified_id
		{ $$ = $1; }
	| qualified_id
		{ $$ = $1; }
	;

unqualified_id:
	IDENTIFIER
		{ $$ = $1; }
	| operator_function_id
		{ unsupported_feature(); }
	| conversion_function_id
		{ unsupported_feature(); }
	| '~' CLASS_NAME
		{ unsupported_feature(); }
	;

qualified_id:
	nested_name_specifier unqualified_id
		{ $$ = alloc_tree(QUALIFIED_ID_1, 2, $1, $2); }
	| nested_name_specifier TEMPLATE unqualified_id
		{ unsupported_feature(); }
	;

nested_name_specifier:
	CLASS_NAME COLONCOLON nested_name_specifier
		{ $$ = alloc_tree(NESTED_NAME_1, 3, $1, $2, $3); }
	| CLASS_NAME COLONCOLON
		{ $$ = alloc_tree(NESTED_NAME_2, 2, $1, $2); }
	| namespace_name COLONCOLON nested_name_specifier
		{ unsupported_feature(); }
	| namespace_name COLONCOLON
		{ unsupported_feature(); }

	;

postfix_expression:
	primary_expression
		{ $$ = $1; }
	| postfix_expression '[' expression ']'
		{ $$ = alloc_tree(POSTFIX_EXPR_2, 4, $1, $2, $3, $4); }
	| postfix_expression '(' expression_list_opt ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_3, 4, $1, $2, $3, $4); }
	| postfix_expression '.' id_expression
		{ $$ = alloc_tree(POSTFIX_EXPR_7, 3, $1, $2, $3); }
	| postfix_expression ARROW id_expression
		{ $$ = alloc_tree(POSTFIX_EXPR_11, 3, $1, $2, $3); }
	| postfix_expression PLUSPLUS
		{ $$ = alloc_tree(POSTFIX_EXPR_12, 2, $1, $2); }
	| postfix_expression MINUSMINUS
		{ $$ = alloc_tree(POSTFIX_EXPR_13, 2, $1, $2); }
	| postfix_expression '.' TEMPLATE COLONCOLON id_expression
		{ unsupported_feature(); }
	| postfix_expression '.' TEMPLATE id_expression
		{ unsupported_feature(); }
	| postfix_expression '.' COLONCOLON id_expression
		{ unsupported_feature(); }
	| postfix_expression ARROW TEMPLATE COLONCOLON id_expression
		{ unsupported_feature(); }
	| postfix_expression ARROW TEMPLATE id_expression
		{ unsupported_feature(); }
	| postfix_expression ARROW COLONCOLON id_expression
		{ unsupported_feature(); }
	| DYNAMIC_CAST '<' type_id '>' '(' expression ')'
		{ unsupported_feature(); }
	| STATIC_CAST '<' type_id '>' '(' expression ')'
		{ unsupported_feature(); }
	| REINTERPRET_CAST '<' type_id '>' '(' expression ')'
		{ unsupported_feature(); }
	| CONST_CAST '<' type_id '>' '(' expression ')'
		{ unsupported_feature(); }
	| TYPEID '(' expression ')'
		{ unsupported_feature(); }
	| TYPEID '(' type_id ')'
		{ unsupported_feature(); }
	;

expression_list:
	assignment_expression
		{ $$ = $1; }
	| expression_list ',' assignment_expression
		{ $$ = alloc_tree(EXPR_LIST_2, 3, $1, $2, $3); }
	;

unary_expression:
	postfix_expression
		{ $$ = $1; }
	| PLUSPLUS unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_2, 2, $1, $2); }
	| MINUSMINUS unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_3, 2, $1, $2); }
	| '*' unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_4, 2, $1, $2); }
	| '&' unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_5, 2, $1, $2); }
	| '+' unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_6, 2, $1, $2); }
	| '-' unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_7, 2, $1, $2); }
	| '!' unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_8, 2, $1, $2); }
	| '~' unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_9, 2, $1, $2); }
	| SIZEOF unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_10, 2, $1, $2); }
	| SIZEOF '(' type_id ')'
		{ $$ = alloc_tree(UNARY_EXPR_11, 4, $1, $2, $3, $4); }
	| new_expression
		{ $$ = $1; }
	| delete_expression
		{ $$ = $1; }
	;

new_expression:
	  NEW new_placement_opt new_type_id new_initializer_opt
	  	{ $$ = alloc_tree(NEW_EXPR_1, 4, $1, $2, $3, $4); }
	;

new_placement:
	'(' expression_list ')'
		{ $$ = alloc_tree(NEW_PLACEMENT_1, 3, $1, $2, $3); }
	;

new_type_id:
	type_specifier_seq new_declarator_opt
		{ $$ = alloc_tree(NEW_TYPE_ID_1, 2, $1, $2); }
	;

new_declarator:
	ptr_operator new_declarator_opt
		{ $$ = alloc_tree(NEW_DECL_1, 2, $1, $2); }
	| direct_new_declarator
		{ $$ = $1; }
	;

direct_new_declarator:
	'[' expression ']'
		{ $$ = alloc_tree(DIRECT_NEW_DECL_1, 3, $1, $2, $3); }
	| direct_new_declarator '[' constant_expression ']'
		{ $$ = alloc_tree(DIRECT_NEW_DECL_2, 4, $1, $2, $3, $4); }
	;

new_initializer:
	'(' expression_list_opt ')'
		{ $$ = alloc_tree(NEW_INIT_1, 3, $1, $2, $3); }
	;

delete_expression:
	  DELETE unary_expression
	  	{ $$ = alloc_tree(DELETE_EXPR_1, 2, $1, $2); }
	| DELETE '[' ']' unary_expression
		{ $$ = alloc_tree(DELETE_EXPR_3, 4, $1, $2, $3, $4); }
	;

pm_expression:
	unary_expression
		{ $$ = $1; }
	| pm_expression DOTSTAR unary_expression
		{ $$ = alloc_tree(PM_EXPR_2, 3, $1, $2, $3); }
	| pm_expression ARROWSTAR unary_expression
		{ $$ = alloc_tree(PM_EXPR_3, 3, $1, $2, $3); }
	;

multiplicative_expression:
	pm_expression
		{ $$ = $1; }
	| multiplicative_expression '*' pm_expression
		{ $$ = alloc_tree(MULT_EXPR_2, 3, $1, $2, $3); }
	| multiplicative_expression '/' pm_expression
		{ $$ = alloc_tree(MULT_EXPR_3, 3, $1, $2, $3); }
	| multiplicative_expression '%' pm_expression
		{ $$ = alloc_tree(MULT_EXPR_4, 3, $1, $2, $3); }
	;

additive_expression:
	multiplicative_expression
		{ $$ = $1; }
	| additive_expression '+' multiplicative_expression
		{ $$ = alloc_tree(ADD_EXPR_2, 3, $1, $2, $3); }
	| additive_expression '-' multiplicative_expression
		{ $$ = alloc_tree(ADD_EXPR_3, 3, $1, $2, $3); }
	;

shift_expression:
	additive_expression
		{ $$ = $1; }
	| shift_expression SL additive_expression
		{ $$ = alloc_tree(SHIFT_EXPR_2, 3, $1, $2, $3); }
	| shift_expression SR additive_expression
		{ $$ = alloc_tree(SHIFT_EXPR_3, 3, $1, $2, $3); }
	;

relational_expression:
	shift_expression
		{ $$ = $1; }
	| relational_expression '<' shift_expression
		{ $$ = alloc_tree(RELATIONAL_EXPR_2, 3, $1, $2, $3); }
	| relational_expression '>' shift_expression
		{ $$ = alloc_tree(RELATIONAL_EXPR_3, 3, $1, $2, $3); }
	| relational_expression LTEQ shift_expression
		{ $$ = alloc_tree(RELATIONAL_EXPR_4, 3, $1, $2, $3); }
	| relational_expression GTEQ shift_expression
		{ $$ = alloc_tree(RELATIONAL_EXPR_5, 3, $1, $2, $3); }
	;

equality_expression:
	relational_expression
		{ $$ = $1; }
	| equality_expression EQ relational_expression
		{ $$ = alloc_tree(EQ_EXPR_2, 3, $1, $2, $3); }
	| equality_expression NOTEQ relational_expression
		{ $$ = alloc_tree(EQ_EXPR_3, 3, $1, $2, $3); }
	;

and_expression:
	equality_expression
		{ $$ = $1; }
	| and_expression '&' equality_expression
		{ $$ = alloc_tree(AND_EXPR_2, 3, $1, $2, $3); }
	;

exclusive_or_expression:
	and_expression
		{ $$ = $1; }
	| exclusive_or_expression '^' and_expression
		{ $$ = alloc_tree(XOR_EXPR_2, 3, $1, $2, $3); }
	;

inclusive_or_expression:
	exclusive_or_expression
		{ $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression
		{ $$ = alloc_tree(OR_EXPR_2, 3, $1, $2, $3); }
	;

logical_and_expression:
	inclusive_or_expression
		{ $$ = $1; }
	| logical_and_expression ANDAND inclusive_or_expression
		{ $$ = alloc_tree(LOGICAL_AND_EXPR_2, 3, $1, $2, $3); }
	;

logical_or_expression:
	logical_and_expression
		{ $$ = $1; }
	| logical_or_expression OROR logical_and_expression
		{ $$ = alloc_tree(LOGICAL_OR_EXPR_2, 3, $1, $2, $3); }
	;

conditional_expression:
	logical_or_expression
		{ $$ = $1; }
	;

assignment_expression:
	conditional_expression
		{ $$ = $1; }
	| logical_or_expression assignment_operator assignment_expression
		{ $$ = alloc_tree(ASSIGN_EXPR_2, 3, $1, $2, $3); }
	;

assignment_operator:
	'='
		{ $$ = $1; }
	| MULEQ
		{ $$ = $1; }
	| DIVEQ
		{ $$ = $1; }
	| MODEQ
		{ $$ = $1; }
	| ADDEQ
		{ $$ = $1; }
	| SUBEQ
		{ $$ = $1; }
	| SREQ
		{ $$ = $1; }
	| SLEQ
		{ $$ = $1; }
	| ANDEQ
		{ $$ = $1; }
	| XOREQ
		{ $$ = $1; }
	| OREQ
		{ $$ = $1; }
	;

expression:
	assignment_expression
		{ $$ = $1; }
	| expression ',' assignment_expression
		{ $$ = alloc_tree(EXPRESSION_2, 3, $1, $2, $3); }
	;

constant_expression:
	conditional_expression
		{ $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Statements.
 *----------------------------------------------------------------------*/

statement:
	labeled_statement
		{ $$ = $1; }
	| expression_statement
		{ $$ = $1; }
	| compound_statement
		{ $$ = $1; }
	| selection_statement
		{ $$ = $1; }
	| iteration_statement
		{ $$ = $1; }
	| jump_statement
		{ $$ = $1; }
	| declaration_statement
		{ $$ = $1; }
	;

labeled_statement:
	CASE constant_expression ':' statement
		{ $$ = alloc_tree(LABELED_STMT_2, 4, $1, $2, $3, $4); }
	| DEFAULT ':' statement
		{ $$ = alloc_tree(LABELED_STMT_3, 3, $1, $2, $3); }
	;

expression_statement:
	expression_opt ';'
		{ $$ = alloc_tree(EXPR_STMT_1, 2, $1, $2); }
	;

compound_statement:
	'{' statement_seq_opt '}'
		{ $$ = alloc_tree(COMPOUND_STMT_1, 3, $1, $2, $3); }
	;

statement_seq:
	statement
		{ $$ = $1; }
	| statement_seq statement
		{ $$ = alloc_tree(STMT_SEQ_2, 2, $1, $2); }
	;

selection_statement:
	IF '(' condition ')' statement
		{ $$ = alloc_tree(SELECTION_STMT_1, 5, $1, $2, $3, $4, $5); }
	| IF '(' condition ')' statement ELSE statement
		{ $$ = alloc_tree(SELECTION_STMT_2, 7,
			$1, $2, $3, $4, $5, $6, $7); }
	| SWITCH '(' condition ')' statement
		{ $$ = alloc_tree(SELECTION_STMT_3, 5, $1, $2, $3, $4, $5); }
	;

condition:
	expression
		{ $$ = $1; }
	| type_specifier_seq declarator '=' assignment_expression
		{ $$ = alloc_tree(CONDITION_2, 4, $1, $2, $3, $4); }
	;

iteration_statement:
	WHILE '(' condition ')' statement
		{ $$ = NULL; unsupported_feature(); }
	| DO statement WHILE '(' expression ')' ';'
		{ $$ = NULL; unsupported_feature(); }
	| FOR '(' for_init_statement condition_opt ';' expression_opt 
		')' statement
			{ $$ = alloc_tree(ITER_STMT_3, 8,
				$1, $2, $3, $4, $5, $6, $7, $8); }
	;

for_init_statement:
	expression_statement
		{ $$ = $1; }
	| simple_declaration
		{ $$ = $1; }
	;

jump_statement:
	BREAK ';'
		{ $$ = alloc_tree(JUMP_STMT_1, 2, $1, $2); }
	| CONTINUE ';'
		{ $$ = alloc_tree(JUMP_STMT_2, 2, $1, $2); }
	| RETURN expression_opt ';'
		{ $$ = alloc_tree(JUMP_STMT_3, 3, $1, $2, $3); }
	;

declaration_statement:
	block_declaration
		{ $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Declarations.
 *----------------------------------------------------------------------*/

declaration_seq:
	declaration
		{ $$ = $1; }
	| declaration_seq declaration
		{ $$ = alloc_tree(DECL_SEQ_2, 2, $1, $2); }
	;

declaration:
	block_declaration
		{ $$ = $1; }
	| function_definition
		{ $$ = $1; }
	;

block_declaration:
	simple_declaration
		{ $$ = $1; }
	;

simple_declaration:
	decl_specifier_seq init_declarator_list ';'
	  	{ $$ = alloc_tree(SIMPLE_DECL_1, 3, $1, $2, $3); }
	|  decl_specifier_seq ';'
		{ $$ = alloc_tree(SIMPLE_DECL_2, 2, $1, $2); }
	;

decl_specifier:
	type_specifier
		{ $$ = $1; }
	;

decl_specifier_seq:
	decl_specifier
	  	{ $$ = $1; }
	| decl_specifier_seq decl_specifier
		{ $$ = alloc_tree(DECL_SPEC_SEQ_2, 2, $1, $2); }
	; 

type_specifier:
	simple_type_specifier
		{ $$ = $1; }
	| class_specifier
		{ $$ = $1; }
	| elaborated_type_specifier
		{ $$ = $1; }
	;

simple_type_specifier:
	CLASS_NAME
		{ $$ = $1; }
	| nested_name_specifier CLASS_NAME
		{ $$ = alloc_tree(SIMPLE_TYPE_SPEC_2, 2, $1, $2); }
	| CHAR
		{ $$ = $1; }
	| BOOL
		{ $$ = $1; }
	| SHORT
		{ $$ = $1; }
	| INT
		{ $$ = $1; }
	| LONG
		{ $$ = $1; }
	| SIGNED
		{ $$ = $1; }
	| UNSIGNED
		{ $$ = $1; }
	| FLOAT
		{ $$ = $1; }
	| DOUBLE
		{ $$ = $1; }
	| VOID
		{ $$ = $1; }
	;

elaborated_type_specifier:
	  class_key COLONCOLON nested_name_specifier IDENTIFIER
	  	{ $$ = alloc_tree(ELAB_TYPE_SPEC_1, 4, $1, $2, $3, $4); }
	| class_key COLONCOLON IDENTIFIER
		{ $$ = alloc_tree(ELAB_TYPE_SPEC_2, 3, $1, $2, $3); }
	;

/*----------------------------------------------------------------------
 * Declarators.
 *----------------------------------------------------------------------*/

init_declarator_list:
	init_declarator
		{ $$ = $1; }
	| init_declarator_list ',' init_declarator
		{ $$ = alloc_tree(INIT_DECL_LIST_2, 3, $1, $2, $3); }
	;

init_declarator:
	declarator initializer_opt
		{ $$ = alloc_tree(INIT_DECL_1, 2, $1, $2); }
	;

declarator:
	direct_declarator
		{ $$ = $1; }
	| ptr_operator declarator
		{ $$ = alloc_tree(DECLARATOR_2, 2, $1, $2); }
	;

direct_declarator:
	declarator_id
	  	{ $$ = $1; }
	| direct_declarator '(' parameter_declaration_clause ')'
		{ $$ = alloc_tree(DIRECT_DECL_2, 4, $1, $2, $3, $4); }
	| CLASS_NAME '(' parameter_declaration_clause ')'
		{ $$ = alloc_tree(DIRECT_DECL_3, 4, $1, $2, $3, $4); }
	| CLASS_NAME COLONCOLON declarator_id 
		'(' parameter_declaration_clause ')'
		{ $$ = alloc_tree(DIRECT_DECL_4, 6, $1, $2, $3, $4, $5, $6); }
	| CLASS_NAME COLONCOLON CLASS_NAME '(' parameter_declaration_clause ')'
		{ $$ = alloc_tree(DIRECT_DECL_5, 6, $1, $2, $3, $4, $5, $6); }
	| direct_declarator '[' constant_expression_opt ']'
		{ $$ = alloc_tree(DIRECT_DECL_6, 4, $1, $2, $3, $4); }
	| '(' declarator ')'
		{ $$ = alloc_tree(DIRECT_DECL_7, 3, $1, $2, $3); }
	;

ptr_operator:
	'*'
		{ $$ = $1; }
	| '&'
		{ $$ = $1; }
	| nested_name_specifier '*'
		{ $$ = alloc_tree(PTR_OP_4, 2, $1, $2); }
	| COLONCOLON nested_name_specifier '*'
		{ $$ = alloc_tree(PTR_OP_6, 3, $1, $2, $3); }
	;

declarator_id:
	  id_expression
	  	{ $$ = $1; }
	| COLONCOLON id_expression
		{ $$ = alloc_tree(DECL_ID_2, 2, $1, $2); }
	| COLONCOLON nested_name_specifier CLASS_NAME
		{ $$ = alloc_tree(DECL_ID_3, 3, $1, $2, $3); }
	| COLONCOLON CLASS_NAME
		{ $$ = alloc_tree(DECL_ID_4, 2, $1, $2); }
	;

type_id:
	type_specifier_seq abstract_declarator_opt
		{ $$ = alloc_tree(TYPE_ID_1, 2, $1, $2); }
	;

type_specifier_seq:
	type_specifier type_specifier_seq_opt
		{ $$ = alloc_tree(TYPE_SPEC_SEQ_1, 2, $1, $2); }
	;

abstract_declarator:
	ptr_operator abstract_declarator_opt
		{ $$ = alloc_tree(ABSTRACT_DECL_1, 2, $1, $2); }
	| direct_abstract_declarator
		{ $$ = $1; }
	;

direct_abstract_declarator:
	direct_abstract_declarator '(' parameter_declaration_clause ')' 
	  	{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_1, 4, $1, $2, $3, $4); }
	| '(' parameter_declaration_clause ')'
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_2, 3, $1, $2, $3); }
	| direct_abstract_declarator '[' constant_expression_opt ']'
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_3, 4, $1, $2, $3, $4); }
	| '[' constant_expression_opt ']'
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_4, 3, $1, $2, $3); }
	| '(' abstract_declarator ')'
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_5, 3, $1, $2, $3); }

parameter_declaration_clause:
	parameter_declaration_list
		{ $$ = $1; }
	| %empty
		{ $$ = NULL; } /* epsilon */
	;

parameter_declaration_list:
	parameter_declaration
		{ $$ = $1; }
	| parameter_declaration_list ',' parameter_declaration
		{ $$ = alloc_tree(PARAM_DECL_LIST_2, 3, $1, $2, $3); }
	;

parameter_declaration:
	decl_specifier_seq declarator
		{ $$ = alloc_tree(PARAM_DECL_1, 2, $1, $2); }
	| decl_specifier_seq declarator '=' assignment_expression
		{ $$ = alloc_tree(PARAM_DECL_2, 4, $1, $2, $3, $4); }
	| decl_specifier_seq abstract_declarator_opt
		{ $$ = alloc_tree(PARAM_DECL_3, 2, $1, $2); }
	| decl_specifier_seq abstract_declarator_opt '=' assignment_expression
		{ $$ = alloc_tree(PARAM_DECL_4, 4, $1, $2, $3, $4); }
	;

function_definition:
	  declarator ctor_initializer_opt function_body
	  	{ $$ = alloc_tree(FUNC_DECL_1, 3, $1, $2, $3); }
	| decl_specifier_seq declarator ctor_initializer_opt function_body
		{ $$ = alloc_tree(FUNC_DECL_2, 4, $1, $2, $3, $4); }
	;

function_body:
	compound_statement
		{ $$ = $1; }
	;

initializer:
	'=' initializer_clause
		{ $$ = alloc_tree(INITIALIZER_1, 2, $1, $2); }
	| '(' expression_list ')'
		{ $$ = alloc_tree(INITIALIZER_2, 3, $1, $2, $3); }
	;

initializer_clause:
	assignment_expression
		{ $$ = $1; }
	| '{' initializer_list COMMA_opt '}'
		{ $$ = alloc_tree(INITIALIZER_CLAUSE_2, 4, $1, $2, $3, $4); }
	| '{' '}'
		{ $$ = alloc_tree(INITIALIZER_CLAUSE_3, 2, $1, $2); }
	;

initializer_list:
	initializer_clause
		{ $$ = $1; }
	| initializer_list ',' initializer_clause
		{ $$ = alloc_tree(INITIALIZER_LIST_2, 3, $1, $2, $3); }
	;

/*----------------------------------------------------------------------
 * Classes.
 *----------------------------------------------------------------------*/

class_specifier:
	class_head '{' member_specification_opt '}'
		{ $$ = alloc_tree(CLASS_SPECIFIER_1, 4, $1, $2, $3, $4); }
	;

class_head:
	  class_key IDENTIFIER
	  	{ $$ = alloc_tree(CLASS_HEAD_1, 2, $1, $2);
	  		add_typename($2, CLASS_NAME); }
	| class_key nested_name_specifier IDENTIFIER
		{ $$ = alloc_tree(CLASS_HEAD_3, 3, $1, $2, $3);
			add_typename($3, CLASS_NAME); }
	;

class_key:
	CLASS
		{ $$ = $1; }
	| STRUCT
		{ $$ = $1; }
	;

member_specification:
	member_declaration member_specification_opt
		{ $$ = alloc_tree(MEMBER_SPEC_1, 2, $1, $2); 
			unsupported_warn(); }
	| access_specifier ':' member_specification_opt
		{ $$ = alloc_tree(MEMBER_SPEC_2, 3, $1, $2, $3);
			unsupported_warn(); }
	;

member_declaration:
	  decl_specifier_seq member_declarator_list ';'
	  	{ $$ = alloc_tree(MEMBER_DECL_1, 3, $1, $2, $3); }
	| decl_specifier_seq ';'
		{ $$ = alloc_tree(MEMBER_DECL_2, 2, $1, $2); }
	| member_declarator_list ';'
		{ $$ = alloc_tree(MEMBER_DECL_3, 2, $1, $2); }
	| ';'
		{ $$ = $1; }
	| function_definition SEMICOLON_opt
		{ $$ = alloc_tree(MEMBER_DECL_5, 2, $1, $2); }
	| qualified_id ';'
		{ $$ = alloc_tree(MEMBER_DECL_6, 2, $1, $2); }
	;

member_declarator_list:
	member_declarator
		{ $$ = $1; }
	| member_declarator_list ',' member_declarator
		{ $$ = alloc_tree(MEMBER_DECL_LIST_2, 3, $1, $2, $3); }
	;

member_declarator:
	declarator
		{ $$ = $1; }
	| declarator constant_initializer
		{ $$ = alloc_tree(MEMBER_DECLARATOR_2, 2, $1, $2); }
	| IDENTIFIER ':' constant_expression
		{ $$ = alloc_tree(MEMBER_DECLARATOR_3, 3, $1, $2, $3); }
	;

constant_initializer:
	'=' constant_expression
		{ $$ = alloc_tree(CONST_INITIALIZER_1, 2, $1, $2); }
	;

access_specifier:
	PRIVATE
		{ $$ = $1; unsupported_warn(); }
	| PROTECTED
		{ $$ = $1; unsupported_warn(); }
	| PUBLIC
		{ $$ = $1; unsupported_warn(); }
	;

/*----------------------------------------------------------------------
 * Special member functions.
 *----------------------------------------------------------------------*/

conversion_function_id:
	OPERATOR conversion_type_id
		{ unsupported_feature(); }
	;

conversion_type_id:
	type_specifier_seq conversion_declarator_opt
		{ unsupported_feature(); }
	;

conversion_declarator:
	ptr_operator conversion_declarator_opt
		{ unsupported_feature(); }
	;

ctor_initializer:
	':' mem_initializer_list
		{ $$ = alloc_tree(CTOR_INIT_1, 2, $1, $2); }
	;

mem_initializer_list:
	mem_initializer
		{ $$ = $1; }
	| mem_initializer ',' mem_initializer_list
		{ $$ = alloc_tree(MEM_INIT_LIST_2, 3, $1, $2, $3); }
	;

mem_initializer:
	mem_initializer_id '(' expression_list_opt ')'
		{ $$ = alloc_tree(MEM_INIT_1, 4, $1, $2, $3, $4); }
	;

mem_initializer_id:
	  COLONCOLON nested_name_specifier CLASS_NAME
	  	{ $$ = alloc_tree(MEM_INIT_ID_1, 3, $1, $2, $3); }
	| COLONCOLON CLASS_NAME
		{ $$ = alloc_tree(MEM_INIT_ID_2, 2, $1, $2); }
	| nested_name_specifier CLASS_NAME
		{ $$ = alloc_tree(MEM_INIT_ID_3, 2, $1, $2); }
	| CLASS_NAME
		{ $$ = $1; }
	| IDENTIFIER
		{ $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Overloading.
 *----------------------------------------------------------------------*/

operator_function_id:
	OPERATOR operator_function_id_opt
		{ unsupported_feature(); }
	;

/*----------------------------------------------------------------------
 * Epsilon (optional) definitions.
 *----------------------------------------------------------------------*/

declaration_seq_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| declaration_seq
		{ $$ = $1; }
	;

expression_list_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| expression_list
		{ $$ = $1; }
	;

new_placement_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| new_placement
		{ $$ = $1; }
	;

new_initializer_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| new_initializer
		{ $$ = $1; }
	;

new_declarator_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| new_declarator
		{ $$ = $1; }
	;

expression_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| expression
		{ $$ = $1; }
	;

statement_seq_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| statement_seq
		{ $$ = $1; }
	;

condition_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| condition
		{ $$ = $1; }
	;

initializer_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| initializer
		{ $$ = $1; }
	;

constant_expression_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| constant_expression
		{ $$ = $1; }
	;

abstract_declarator_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| abstract_declarator
		{ $$ = $1; }
	;

type_specifier_seq_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| type_specifier_seq
		{ $$ = $1; }
	;

ctor_initializer_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| ctor_initializer
		{ $$ = $1; }
	;

COMMA_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| ','
		{ $$ = $1; }
	;

member_specification_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| member_specification
		{ $$ = $1; }
	;

SEMICOLON_opt:
	%empty
		{ $$ = NULL; } /* epsilon */
	| ';'
		{ $$ = $1; }
	;

conversion_declarator_opt:
	%empty
		{ unsupported_feature(); } /* epsilon */
	| conversion_declarator
		{ unsupported_feature(); }
	;

operator_function_id_opt:
	%empty
		{ unsupported_feature(); } /* epsilon */
	| operator_function_id
		{ unsupported_feature(); }
	;

%%

void add_typename(struct TreeNode *t, int cat) {
	std::stringstream ss;
	ss << "Adding " << t->t->get_text();
	ss << " as a (" << cat << ") to lookup table...";
	std::clog << ss.str() << std::endl;

	if(!ident_table.insert(t->t->get_text(), cat)) {
		yyerror("token already in identifier lookup table");
	}
}

struct TreeNode* alloc_tree(yyrule y, int num_kids, ...) {
	va_list vakid;

	struct TreeNode *t = new struct TreeNode();
	if(!t) {
		std::cerr << "TreeNode: Cannot allocate memory." << std::endl;
		exit(EXIT_FAILURE);
	}
	t->prod_num = y;
	t->prod_text = get_production_text(y);
	t->num_kids = num_kids;
	t->s = NULL;

	va_start(vakid, num_kids);

	for(int i = 0; i < num_kids; ++i) {
		t->kids[i] = va_arg(vakid, struct TreeNode*);
	}

	va_end(vakid);
	return t;
}
static void unsupported_warn(std::string str) {
	if(str.empty()) {
		str = "120++ operation not implemented yet";
	}
	std::stringstream ss;
	ss << "120++ Warning: Semantic: ";
	ss << yyfilename << ":" << yylineno << ": ";
	ss << str << " before '" << yylval->t->get_text() << "' token";
	std::cerr << ss.str() << std::endl;
}
static void unsupported_feature(std::string str) {
	if(str.empty())
		str = "C++ operation not supported in 120++";
	std::stringstream s;
	s << yyfilename << ":" << yylineno << ": ";
	s << str << " before '" << yylval->t->get_text() << "' token";

	std::cerr << s.str() << std::endl;
	
	exit(EXIT_UNSUPPORTED);
}

static void yyerror(std::string str) {
	std::stringstream s;
	s << yyfilename << ":" << yylineno << ": ";
	s << str << " before '" << yylval->t->get_text() << "' token"; 
	s << std::endl;

	std::cerr << s.str();
	exit(EXIT_SYNTAX_ERROR);
}

