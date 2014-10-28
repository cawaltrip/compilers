/*
 * Grammar for 120++, a subset of C++ used in CS 120 at University of Idaho
 *
 * Adaptation by Clinton Jeffery, with help from Matthew Brown, Ranger
 * Adams, and Shea Newton.
 *
 * Based on Sandro Sigala's transcription of the ISO C++ 1996 draft standard.
 * 
 */

/*	$Id: parser.y,v 1.3 1997/11/19 15:13:16 sandro Exp $	*/

/*
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
 * ISO C++ parser.
 *
 * Based on the ISO C++ draft standard of December '96.
 */

/* TODO: Improve output, especially for error reporting */



%{
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdarg>
#include <utility>

#include "treenode.hh"
#include "lookup.hh"
#include "120rules.hh"

extern int yylineno;
extern int yylex();
extern std::string yyfilename;
extern std::string yytext;

LookupTable ident_table;

struct TreeNode *root;
struct TreeNode* alloc_tree(const struct yyrule y, int num_kids, ...);
void add_typename(struct TreeNode *t, int cat);

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
 * Context-dependent identifiers.
 *----------------------------------------------------------------------*/

typedef_name:
	/* identifier */
	TYPEDEF_NAME 
		{ $$ = $1; }
	;

namespace_name:
	original_namespace_name 
		{ $$ = NULL; unsupported_feature(); }
	;

original_namespace_name:
	/* identifier */
	NAMESPACE_NAME
		{ $$ = NULL; unsupported_feature(); }
	;

class_name:
	/* identifier */
	CLASS_NAME
		{ $$ = $1; }
	| template_id
		{ $$ = $1; }
	;

enum_name:
	/* identifier */
	ENUM_NAME
		{ $$ = NULL; unsupported_feature(); }
	;

template_name:
	/* identifier */
	TEMPLATE_NAME
		{ $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Lexical elements.
 *----------------------------------------------------------------------*/

identifier:
	IDENTIFIER 
		{ $$ = $1; }
	;

literal:
	integer_literal
		{ $$ = $1; }
	| character_literal
		{ $$ = $1; }
	| floating_literal
		{ $$ = $1; }
	| string_literal
		{ $$ = $1; }
	| boolean_literal
		{ $$ = $1; }
	;

integer_literal:
	INTEGER
		{ $$ = $1; }
	;

character_literal:
	CHARACTER
		{ $$ = $1; }
	;

floating_literal:
	FLOATING
		{ $$ = $1; }
	;

string_literal:
	STRING
		{ $$ = $1; }
	;

boolean_literal:
	TRUE
		{ $$ = $1; }
	| FALSE
		{ $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Translation unit.
 *----------------------------------------------------------------------*/

translation_unit:
	declaration_seq_opt { root = $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Expressions.
 *----------------------------------------------------------------------*/

primary_expression:
	literal
		{ $$ = $1; }
	| THIS
		{ $$ = $1; }
	| '(' expression ')'
		{ $$ = alloc_tree(PRIMARY_EXPRESSION_1, 3, $1, $2, $3); }
	| id_expression
		{ $$ = $1; }
	;

id_expression:
	unqualified_id
		{ $$ = $1; }
	| qualified_id
		{ $$ = $1; }
	;

unqualified_id:
	identifier
		{ $$ = $1; }
	| operator_function_id
		{ $$ = $1; }
	| conversion_function_id
		{ $$ = $1; }
	| '~' class_name
		{ $$ = alloc_tree(UNQUALIFIED_ID_4, 2, $1, $2); }
	;

qualified_id:
	nested_name_specifier unqualified_id
		{ $$ = alloc_tree(QUALIFIED_ID_1, 2, $1, $2); }
	| nested_name_specifier TEMPLATE unqualified_id
		{ $$ = alloc_tree(QUALIFIED_ID_2, 3, $1, $2, $3); }
	;

nested_name_specifier:
	class_name COLONCOLON nested_name_specifier
		{ $$ = alloc_tree(NESTED_NAME_1, 3, $1, $2, $3); }
	| namespace_name COLONCOLON nested_name_specifier
		{ $$ = alloc_tree(NESTED_NAME_2, 3, $1, $2, $3); }
	| class_name COLONCOLON
		{ $$ = alloc_tree(NESTED_NAME_3, 2, $1, $2); }
	| namespace_name COLONCOLON
		{ $$ = alloc_tree(NESTED_NAME_4, 2, $1, $2); }
	;

postfix_expression:
	primary_expression
		{ $$ = $1; }
	| postfix_expression '[' expression ']'
		{ $$ = alloc_tree(POSTFIX_EXPR_2, 4, $1, $2, $3, $4); }
	| postfix_expression '(' expression_list_opt ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_3, 4, $1, $2, $3, $4); }
	| postfix_expression '.' TEMPLATE COLONCOLON id_expression
		{ $$ = NULL; unsupported_feature(); }
	| postfix_expression '.' TEMPLATE id_expression
		{ $$ = NULL; unsupported_feature(); }
	| postfix_expression '.' COLONCOLON id_expression
		{ $$ = alloc_tree(POSTFIX_EXPR_6, 4, $1, $2, $3, $4); }
	| postfix_expression '.' id_expression
		{ $$ = alloc_tree(POSTFIX_EXPR_7, 3, $1, $2, $3); }
	| postfix_expression ARROW TEMPLATE COLONCOLON id_expression
		{ $$ = NULL; unsupported_feature(); }
	| postfix_expression ARROW TEMPLATE id_expression
		{ $$ = NULL; unsupported_feature(); }
	| postfix_expression ARROW COLONCOLON id_expression
		{ $$ = alloc_tree(POSTFIX_EXPR_10, 4, $1, $2, $3, $4); }
	| postfix_expression ARROW id_expression
		{ $$ = alloc_tree(POSTFIX_EXPR_11, 3, $1, $2, $3); }
	| postfix_expression PLUSPLUS
		{ $$ = alloc_tree(POSTFIX_EXPR_12, 2, $1, $2); }
	| postfix_expression MINUSMINUS
		{ $$ = alloc_tree(POSTFIX_EXPR_13, 2, $1, $2); }
	| DYNAMIC_CAST '<' type_id '>' '(' expression ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_14, 7,
			$1, $2, $3, $4, $5, $6, $7); }
	| STATIC_CAST '<' type_id '>' '(' expression ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_15, 7,
			$1, $2, $3, $4, $5, $6, $7); }
	| REINTERPRET_CAST '<' type_id '>' '(' expression ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_16, 7,
			$1, $2, $3, $4, $5, $6, $7); }
	| CONST_CAST '<' type_id '>' '(' expression ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_17, 7,
			$1, $2, $3, $4, $5, $6, $7); }
	| TYPEID '(' expression ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_18, 4, $1, $2, $3, $4); }
	| TYPEID '(' type_id ')'
		{ $$ = alloc_tree(POSTFIX_EXPR_19, 4, $1, $2, $3, $4); }
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
	| PLUSPLUS cast_expression
		{ $$ = alloc_tree(UNARY_EXPR_2, 2, $1, $2); }
	| MINUSMINUS cast_expression
		{ $$ = alloc_tree(UNARY_EXPR_3, 2, $1, $2); }
	| '*' cast_expression
		{ $$ = alloc_tree(UNARY_EXPR_4, 2, $1, $2); }
	| '&' cast_expression
		{ $$ = alloc_tree(UNARY_EXPR_5, 2, $1, $2); }
	| unary_operator cast_expression
		{ $$ = alloc_tree(UNARY_EXPR_6, 2, $1, $2); }
	| SIZEOF unary_expression
		{ $$ = alloc_tree(UNARY_EXPR_7, 2, $1, $2); }
	| SIZEOF '(' type_id ')'
		{ $$ = alloc_tree(UNARY_EXPR_8, 4, $1, $2, $3, $4); }
	| new_expression
		{ $$ = $1; }
	| delete_expression
		{ $$ = $1; }
	;

unary_operator:
	  '+'
	  	{ $$ = $1; }
	| '-'
		{ $$ = $1; }
	| '!'
		{ $$ = $1; }
	| '~'
		{ $$ = $1; }
	;

new_expression:
	  NEW new_placement_opt new_type_id new_initializer_opt
	  	{ $$ = alloc_tree(NEW_EXPR_1, 4, $1, $2, $3, $4); }
	| COLONCOLON NEW new_placement_opt new_type_id new_initializer_opt
		{ $$ = alloc_tree(NEW_EXPR_2, 5, $1, $2, $3, $4, $5); }
	| NEW new_placement_opt '(' type_id ')' new_initializer_opt
		{ $$ = alloc_tree(NEW_EXPR_3, 6, $1, $2, $3, $4, $5, $6); }
	| COLONCOLON NEW new_placement_opt '(' type_id ')' new_initializer_opt
		{ $$ = alloc_tree(NEW_EXPR_4, 7, $1, $2, $3, $4, $5, $6, $7); }
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
	  DELETE cast_expression
	  	{ $$ = alloc_tree(DELETE_EXPR_1, 2, $1, $2); }
	| COLONCOLON DELETE cast_expression
		{ $$ = alloc_tree(DELETE_EXPR_2, 3, $1, $2, $3); }
	| DELETE '[' ']' cast_expression
		{ $$ = alloc_tree(DELETE_EXPR_3, 4, $1, $2, $3, $4); }
	| COLONCOLON DELETE '[' ']' cast_expression
		{ $$ = alloc_tree(DELETE_EXPR_4, 5, $1, $2, $3, $4, $5); }
	;

cast_expression:
	unary_expression
		{ $$ = $1; }
	| '(' type_id ')' cast_expression
		{ $$ = alloc_tree(CAST_EXPR_2, 4, $1, $2, $3, $4); }
	;

pm_expression:
	cast_expression
		{ $$ = $1; }
	| pm_expression DOTSTAR cast_expression
		{ $$ = alloc_tree(PM_EXPR_2, 3, $1, $2, $3); }
	| pm_expression ARROWSTAR cast_expression
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
	| logical_or_expression  '?' expression ':' assignment_expression
		{ $$ = alloc_tree(CONDITIONAL_EXPR_2, 5, $1, $2, $3, $4, $5); }
	;

assignment_expression:
	conditional_expression
		{ $$ = $1; }
	| logical_or_expression assignment_operator assignment_expression
		{ $$ = alloc_tree(ASSIGN_EXPR_2, 3, $1, $2, $3); }
	| throw_expression
		{ $$ = $1; }
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
	| try_block
		{ $$ = NULL; unsupported_feature(); }
	;

labeled_statement:
	identifier ':' statement
		{ $$ = alloc_tree(LABELED_STMT_1, 3, $1, $2, $3); }
	| CASE constant_expression ':' statement
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
	| GOTO identifier ';'
		{ $$ = NULL; unsupported_feature(); }
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
	| template_declaration
		{ $$ = $1; }
	| explicit_instantiation
		{ $$ = $1; }
	| explicit_specialization
		{ $$ = $1; }
	| linkage_specification
		{ $$ = $1; }
	| namespace_definition
		{ $$ = $1; }
	;

block_declaration:
	simple_declaration
		{ $$ = $1; }
	| asm_definition
		{ $$ = $1; }
	| namespace_alias_definition
		{ $$ = $1; }
	| using_declaration
		{ $$ = $1; }
	| using_directive
		{ $$ = $1; }
	;

simple_declaration:
	  decl_specifier_seq init_declarator_list ';'
	  	{ $$ = alloc_tree(SIMPLE_DECL_1, 3, $1, $2, $3); }
	|  decl_specifier_seq ';'
		{ $$ = alloc_tree(SIMPLE_DECL_2, 2, $1, $2); }
	;

decl_specifier:
	storage_class_specifier
		{ $$ = $1; }
	| type_specifier
		{ $$ = $1; }
	| function_specifier
		{ $$ = $1; }
	| FRIEND
		{ $$ = $1; }
	| TYPEDEF
		{ $$ = $1; }
	;

decl_specifier_seq:
	  decl_specifier
	  	{ $$ = $1; }
	| decl_specifier_seq decl_specifier
		{ $$ = alloc_tree(DECL_SPEC_SEQ_2, 2, $1, $2); }
	;

storage_class_specifier:
	AUTO
		{ $$ = NULL; unsupported_feature(); }
	| REGISTER
		{ $$ = NULL; unsupported_feature(); }
	| STATIC
		{ $$ = $1; }
	| EXTERN
		{ $$ = NULL; unsupported_feature(); }
	| MUTABLE
		{ $$ = NULL; unsupported_feature(); }
	;

function_specifier:
	INLINE
		{ $$ = NULL; unsupported_feature(); }
	| VIRTUAL
		{ $$ = NULL; unsupported_feature(); }
	| EXPLICIT
		{ $$ = NULL; unsupported_feature(); }
	;

type_specifier:
	simple_type_specifier
		{ $$ = $1; }
	| class_specifier
		{ $$ = $1; }
	| enum_specifier
		{ $$ = $1; }
	| elaborated_type_specifier
		{ $$ = $1; }
	| cv_qualifier
		{ $$ = $1; }
	;

simple_type_specifier:
	  type_name
	  	{ $$ = $1; }
	| nested_name_specifier type_name
		{ $$ = alloc_tree(SIMPLE_TYPE_SPEC_1, 2, $1, $2); }
	| COLONCOLON nested_name_specifier_opt type_name
		{ $$ = alloc_tree(SIMPLE_TYPE_SPEC_2, 3, $1, $2, $3); }
	| CHAR
		{ $$ = $1; }
	| WCHAR_T
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

type_name:
	class_name
		{ $$ = $1; }
	| enum_name
		{ $$ = NULL; unsupported_feature(); }
	| typedef_name
		{ $$ = $1; }
	;

elaborated_type_specifier:
	  class_key COLONCOLON nested_name_specifier identifier
	  	{ $$ = alloc_tree(ELAB_TYPE_SPEC_1, 4, $1, $2, $3, $4); }
	| class_key COLONCOLON identifier
		{ $$ = alloc_tree(ELAB_TYPE_SPEC_2, 3, $1, $2, $3); }
	| ENUM COLONCOLON nested_name_specifier identifier
		{ $$ = NULL; unsupported_feature(); }
	| ENUM COLONCOLON identifier
		{ $$ = NULL; unsupported_feature(); }
	| ENUM nested_name_specifier identifier
		{ $$ = NULL; unsupported_feature(); }
	| TYPENAME COLONCOLON_opt nested_name_specifier identifier
		{ $$ = alloc_tree(ELAB_TYPE_SPEC_6, 4, $1, $2, $3, $4); }
	| TYPENAME COLONCOLON_opt nested_name_specifier identifier 
	'<' template_argument_list '>'
		{ $$ = NULL; unsupported_feature(); }
	;

enum_specifier:
	ENUM identifier '{' enumerator_list_opt '}'
		{ $$ = NULL; unsupported_feature(); }
	;

enumerator_list:
	enumerator_definition
		{ $$ = $1; }
	| enumerator_list ',' enumerator_definition
		{ $$ = NULL; unsupported_feature(); }
	;

enumerator_definition:
	enumerator
		{ $$ = NULL; unsupported_feature(); }
	| enumerator '=' constant_expression
		{ $$ = NULL; unsupported_feature(); }
	;

enumerator:
	identifier
		{ $$ = NULL; unsupported_feature(); }
	;

namespace_definition:
	named_namespace_definition
		{ $$ = NULL; unsupported_feature(); }
	| unnamed_namespace_definition
		{ $$ = NULL; unsupported_feature(); }
	;

named_namespace_definition:
	original_namespace_definition
		{ $$ = NULL; unsupported_feature(); }
	| extension_namespace_definition
		{ $$ = NULL; unsupported_feature(); }
	;

original_namespace_definition:
	NAMESPACE identifier '{' namespace_body '}'
		{ $$ = NULL; unsupported_feature(); }
	;

extension_namespace_definition:
	NAMESPACE original_namespace_name '{' namespace_body '}'
		{ $$ = NULL; unsupported_feature(); }
	;

unnamed_namespace_definition:
	NAMESPACE '{' namespace_body '}'
		{ $$ = NULL; unsupported_feature(); }
	;

namespace_body:
	declaration_seq_opt
		{ $$ = NULL; unsupported_feature(); }
	;

namespace_alias_definition:
	NAMESPACE identifier '=' qualified_namespace_specifier ';'
		{ $$ = NULL; unsupported_feature(); }
	;

qualified_namespace_specifier:
	  COLONCOLON nested_name_specifier namespace_name
	  	{ $$ = NULL; unsupported_feature(); }
	| COLONCOLON namespace_name
		{ $$ = NULL; unsupported_feature(); }
	| nested_name_specifier namespace_name
		{ $$ = NULL; unsupported_feature(); }
	| namespace_name
		{ $$ = NULL; unsupported_feature(); }
	;

using_declaration:
	  USING TYPENAME COLONCOLON nested_name_specifier unqualified_id ';'
	  	{ $$ = alloc_tree(USING_DECL_1, 6, $1, $2, $3, $4, $5, $6); }
	| USING TYPENAME nested_name_specifier unqualified_id ';'
		{ $$ = alloc_tree(USING_DECL_2, 5, $1, $2, $3, $4, $5); }
	| USING COLONCOLON nested_name_specifier unqualified_id ';'
		{ $$ = alloc_tree(USING_DECL_3, 5, $1, $2, $3, $4, $5); }
	| USING nested_name_specifier unqualified_id ';'
		{ $$ = alloc_tree(USING_DECL_4, 4, $1, $2, $3, $4); }
	| USING COLONCOLON unqualified_id ';'
		{ $$ = alloc_tree(USING_DECL_5, 4, $1, $2, $3, $4); }
	;

using_directive:
	USING NAMESPACE COLONCOLON nested_name_specifier namespace_name ';'
		{ $$ = NULL; unsupported_feature(); }
	| USING NAMESPACE COLONCOLON namespace_name ';'
		{ $$ = NULL; unsupported_feature(); }
	| USING NAMESPACE nested_name_specifier namespace_name ';'
		{ $$ = NULL; unsupported_feature(); }
	| USING NAMESPACE namespace_name ';'
		{ $$ = NULL; unsupported_feature(); }
	;

asm_definition:
	ASM '(' string_literal ')' ';'
		{ $$ = NULL; unsupported_feature(); }
	;

linkage_specification:
	EXTERN string_literal '{' declaration_seq_opt '}'
		{ $$ = NULL; unsupported_feature(); }
	| EXTERN string_literal declaration
		{ $$ = NULL; unsupported_feature(); }
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
		{ $$ = alloc_tree(DECL_2, 2, $1, $2); }
	;

direct_declarator:
	  declarator_id
	  	{ $$ = $1; }
	| direct_declarator '(' parameter_declaration_clause ')' 
	cv_qualifier_seq exception_specification
		{ $$ = alloc_tree(DIRECT_DECL_2, 6, $1, $2, $3, $4, $5, $6); }
	| direct_declarator '(' parameter_declaration_clause ')' 
	cv_qualifier_seq
		{ $$ = alloc_tree(DIRECT_DECL_3, 5, $1, $2, $3, $4, $5); }
	| direct_declarator '(' parameter_declaration_clause ')' 
	exception_specification
		{ $$ = alloc_tree(DIRECT_DECL_4, 5, $1, $2, $3, $4, $5); }
	| direct_declarator '(' parameter_declaration_clause ')'
		{ $$ = alloc_tree(DIRECT_DECL_5, 4, $1, $2, $3, $4); }
	| direct_declarator '[' constant_expression_opt ']'
		{ $$ = alloc_tree(DIRECT_DECL_6, 4, $1, $2, $3, $4); }
	| '(' declarator ')'
		{ $$ = alloc_tree(DIRECT_DECL_7, 3, $1, $2, $3); }
	;

ptr_operator:
	'*'
		{ $$ = $1; }
	| '*' cv_qualifier_seq
		{ $$ = alloc_tree(PTR_OP_2, 2, $1, $2); }
	| '&'
		{ $$ = $1; }
	| nested_name_specifier '*'
		{ $$ = alloc_tree(PTR_OP_4, 2, $1, $2); }
	| nested_name_specifier '*' cv_qualifier_seq
		{ $$ = alloc_tree(PTR_OP_5, 3, $1, $2, $3); }
	| COLONCOLON nested_name_specifier '*'
		{ $$ = alloc_tree(PTR_OP_6, 3, $1, $2, $3); }
	| COLONCOLON nested_name_specifier '*' cv_qualifier_seq
		{ $$ = alloc_tree(PTR_OP_7, 4, $1, $2, $3, $4); }
	;

cv_qualifier_seq:
	cv_qualifier
		{ $$ = $1; }
	| cv_qualifier cv_qualifier_seq
		{ $$ = alloc_tree(CV_QUAL_SEQ_2, 2, $1, $2); }
	;

cv_qualifier:
	CONST
		{ $$ = $1; }
	| VOLATILE
		{ $$ = NULL; unsupported_feature(); }
	;

declarator_id:
	  id_expression
	  	{ $$ = $1; }
	| COLONCOLON id_expression
		{ $$ = alloc_tree(DECL_ID_2, 2, $1, $2); }
	| COLONCOLON nested_name_specifier type_name
		{ $$ = alloc_tree(DECL_ID_3, 3, $1, $2, $3); }
	| COLONCOLON type_name
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
	  direct_abstract_declarator_opt '(' parameter_declaration_clause ')' 
	  cv_qualifier_seq exception_specification
	  	{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_1, 6,
	  		$1, $2, $3, $4, $5, $6); }
	| direct_abstract_declarator_opt '(' parameter_declaration_clause ')' 
	cv_qualifier_seq
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_2, 5,
			$1, $2, $3, $4, $5); }
	| direct_abstract_declarator_opt '(' parameter_declaration_clause ')' 
	exception_specification
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_3, 5,
			$1, $2, $3, $4, $5); }
	| direct_abstract_declarator_opt '(' parameter_declaration_clause ')'
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_4, 4, $1, $2, $3, $4); }
	| direct_abstract_declarator_opt '[' constant_expression_opt ']'
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_5, 4, $1, $2, $3, $4); }
	| '(' abstract_declarator ')'
		{ $$ = alloc_tree(DIRECT_ABSTRACT_DECL_6, 3, $1, $2, $3); }
	;

parameter_declaration_clause:
	  parameter_declaration_list ELLIPSIS
	  	{ $$ = NULL; unsupported_feature(); }
	| parameter_declaration_list
		{ $$ = $1; }
	| ELLIPSIS
		{ $$ = NULL; unsupported_feature(); }
	| %empty
		{ $$ = NULL; } /* epsilon */
	| parameter_declaration_list ',' ELLIPSIS
		{ $$ = NULL; unsupported_feature(); }
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
	  	{ $$ = alloc_tree(FUNC_DEF_1, 3, $1, $2, $3); }
	| decl_specifier_seq declarator ctor_initializer_opt function_body
		{ $$ = alloc_tree(FUNC_DEF_2, 4, $1, $2, $3, $4); }
	| declarator function_try_block
		{ $$ = alloc_tree(FUNC_DEF_3, 2, $1, $2); }
	| decl_specifier_seq declarator function_try_block
		{ $$ = alloc_tree(FUNC_DEF_4, 3, $1, $2, $3); }
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
	  class_key identifier
	  	{ $$ = alloc_tree(CLASS_HEAD_1, 2, $1, $2);
	  		add_typename($2, CLASS_NAME); }
	| class_key identifier base_clause
		{ $$ = alloc_tree(CLASS_HEAD_2, 3, $1, $2, $3);
			add_typename($2, CLASS_NAME); }
	| class_key nested_name_specifier identifier
		{ $$ = alloc_tree(CLASS_HEAD_3, 3, $1, $2, $3);
			add_typename($3, CLASS_NAME);  }
	| class_key nested_name_specifier identifier base_clause
		{ $$ = alloc_tree(CLASS_HEAD_4, 4, $1, $2, $3, $4);
			add_typename($3, CLASS_NAME); }
	;

class_key:
	CLASS
		{ $$ = $1; }
	| STRUCT
		{ $$ = $1; }
	| UNION
		{ $$ = $1; } /* TODO: Find out if we support unions. */
	;

member_specification:
	member_declaration member_specification_opt
		{ $$ = alloc_tree(MEMBER_SPEC_1, 2, $1, $2); }
	| access_specifier ':' member_specification_opt
		{ $$ = alloc_tree(MEMBER_SPEC_2, 3, $1, $2, $3); }
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
	| using_declaration
		{ $$ = $1; }
	| template_declaration
		{ $$ = $1; }
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
	| declarator pure_specifier
		{ $$ = alloc_tree(MEMBER_DECLARATOR_2, 2, $1, $2); }
	| declarator constant_initializer
		{ $$ = alloc_tree(MEMBER_DECLARATOR_3, 2, $1, $2); }
	| identifier ':' constant_expression
		{ $$ = alloc_tree(MEMBER_DECLARATOR_4, 3, $1, $2, $3); }
	;

/*
 * This rule need a hack for working around the ``= 0'' pure specifier.
 * 0 is returned as an ``INTEGER'' by the lexical analyzer but in this
 * context is different.
 */
pure_specifier:
	'=' '0'
		{ $$ = alloc_tree(PURE_SPECIFIER_1, 2, $1, $2); }
	;

constant_initializer:
	'=' constant_expression
		{ $$ = alloc_tree(CONST_INITIALIZER_1, 2, $1, $2); }
	;

/*----------------------------------------------------------------------
 * Derived classes.
 *----------------------------------------------------------------------*/

base_clause:
	':' base_specifier_list
		{ $$ = alloc_tree(BASE_CLAUSE_1, 2, $1, $2); }
	;

base_specifier_list:
	base_specifier
		{ $$ = $1; }
	| base_specifier_list ',' base_specifier
		{ $$ = alloc_tree(BASE_SPECIFIER_LIST_2, 3, $1, $2, $3); }
	;

base_specifier:
	  COLONCOLON nested_name_specifier class_name
	  	{ $$ = alloc_tree(BASE_SPECIFIER_1, 3, $1, $2, $3); }
	| COLONCOLON class_name
		{ $$ = alloc_tree(BASE_SPECIFIER_2, 2, $1, $2); }
	| nested_name_specifier class_name
		{ $$ = alloc_tree(BASE_SPECIFIER_3, 2, $1, $2); }
	| class_name
		{ $$ = $1; }
	| VIRTUAL access_specifier COLONCOLON nested_name_specifier_opt 
	class_name
		{ $$ = NULL; unsupported_feature(); }
	| VIRTUAL access_specifier nested_name_specifier_opt class_name
		{ $$ = NULL; unsupported_feature(); }
	| VIRTUAL COLONCOLON nested_name_specifier_opt class_name
		{ $$ = NULL; unsupported_feature(); }
	| VIRTUAL nested_name_specifier_opt class_name
		{ $$ = NULL; unsupported_feature(); }
	| access_specifier VIRTUAL COLONCOLON nested_name_specifier_opt 
	class_name
		{ $$ = alloc_tree(BASE_SPECIFIER_9, 5, $1, $2, $3, $4, $5); }
	| access_specifier VIRTUAL nested_name_specifier_opt class_name
		{ $$ = alloc_tree(BASE_SPECIFIER_10, 4, $1, $2, $3, $4); }
	| access_specifier COLONCOLON nested_name_specifier_opt class_name
		{ $$ = alloc_tree(BASE_SPECIFIER_11, 4, $1, $2, $3, $4); }
	| access_specifier nested_name_specifier_opt class_name
		{ $$ = alloc_tree(BASE_SPECIFIER_12, 3, $1, $2, $3); }
	;

access_specifier:
	PRIVATE
		{ $$ = $1; }
	| PROTECTED
		{ $$ = NULL; unsupported_feature(); }
	| PUBLIC
		{ $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Special member functions.
 *----------------------------------------------------------------------*/

conversion_function_id:
	OPERATOR conversion_type_id
		{ $$ = alloc_tree(CONV_FUNC_ID_1, 2, $1, $2); }
	;

conversion_type_id:
	type_specifier_seq conversion_declarator_opt
		{ $$ = alloc_tree(CONV_TYPE_ID_1, 2, $1, $2); }
	;

conversion_declarator:
	ptr_operator conversion_declarator_opt
		{ $$ = alloc_tree(CONV_DECLARATOR_1, 2, $1, $2); }
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
	  COLONCOLON nested_name_specifier class_name
	  	{ $$ = alloc_tree(MEM_INIT_ID_1, 3, $1, $2, $3); }
	| COLONCOLON class_name
		{ $$ = alloc_tree(MEM_INIT_ID_2, 2, $1, $2); }
	| nested_name_specifier class_name
		{ $$ = alloc_tree(MEM_INIT_ID_3, 2, $1, $2); }
	| class_name
		{ $$ = $1; }
	| identifier
		{ $$ = $1; }
	;

/*----------------------------------------------------------------------
 * Overloading.
 *----------------------------------------------------------------------*/

operator_function_id:
	OPERATOR operator
		{ $$ = alloc_tree(OP_FUNC_ID_1, 2, $1, $2); }
	;

operator:
	NEW
		{ $$ = $1; }
	| DELETE
		{ $$ = $1; }
	| NEW '[' ']'
		{ $$ = alloc_tree(OP_3, 3, $1, $2, $3); }
	| DELETE '[' ']'
		{ $$ = alloc_tree(OP_4, 3, $1, $2, $3); }
	| '+'
		{ $$ = $1; }
	| '_'
		{ $$ = $1; }
	| '*'
		{ $$ = $1; }
	| '/'
		{ $$ = $1; }
	| '%'
		{ $$ = $1; }
	| '^'
		{ $$ = $1; }
	| '&'
		{ $$ = $1; }
	| '|'
		{ $$ = $1; }
	| '~'
		{ $$ = $1; }
	| '!'
		{ $$ = $1; }
	| '='
		{ $$ = $1; }
	| '<'
		{ $$ = $1; }
	| '>'
		{ $$ = $1; }
	| ADDEQ
		{ $$ = $1; }
	| SUBEQ
		{ $$ = $1; }
	| MULEQ
		{ $$ = $1; }
	| DIVEQ
		{ $$ = $1; }
	| MODEQ
		{ $$ = $1; }
	| XOREQ
		{ $$ = $1; }
	| ANDEQ
		{ $$ = $1; }
	| OREQ
		{ $$ = $1; }
	| SL
		{ $$ = $1; }
	| SR
		{ $$ = $1; }
	| SREQ
		{ $$ = $1; }
	| SLEQ
		{ $$ = $1; }
	| EQ
		{ $$ = $1; }
	| NOTEQ
		{ $$ = $1; }
	| LTEQ
		{ $$ = $1; }
	| GTEQ
		{ $$ = $1; }
	| ANDAND
		{ $$ = $1; }
	| OROR
		{ $$ = $1; }
	| PLUSPLUS
		{ $$ = $1; }
	| MINUSMINUS
		{ $$ = $1; }
	| ','
		{ $$ = $1; }
	| ARROWSTAR
		{ $$ = $1; }
	| ARROW
		{ $$ = $1; }
	| '(' ')'
		{ $$ = alloc_tree(OP_41, 2, $1, $2); }
	| '[' ']'
		{ $$ = alloc_tree(OP_42, 2, $1, $2); }
	;

/*----------------------------------------------------------------------
 * Templates.
 *----------------------------------------------------------------------*/

template_declaration:
	EXPORT_opt TEMPLATE '<' template_parameter_list '>' declaration
		{ $$ = NULL; unsupported_feature(); }
	;

template_parameter_list:
	template_parameter
		{ $$ = NULL; unsupported_feature(); }
	| template_parameter_list ',' template_parameter
		{ $$ = NULL; unsupported_feature(); }
	;

template_parameter:
	type_parameter
		{ $$ = NULL; unsupported_feature(); }
	| parameter_declaration
		{ $$ = NULL; unsupported_feature(); }
	;

type_parameter:
	  CLASS identifier
	  	{ $$ = alloc_tree(TYPE_PARAM_1, 2, $1, $2); }
	| CLASS identifier '=' type_id
		{ $$ = alloc_tree(TYPE_PARAM_2, 4, $1, $2, $3, $4); }
	| TYPENAME identifier
		{ $$ = alloc_tree(TYPE_PARAM_3, 2, $1, $2); }
	| TYPENAME identifier '=' type_id
		{ $$ = alloc_tree(TYPE_PARAM_4, 4, $1, $2, $3, $4); }
	| TEMPLATE '<' template_parameter_list '>' CLASS identifier
		{ $$ = NULL; unsupported_feature(); }
	| TEMPLATE '<' template_parameter_list '>' 
	CLASS identifier '=' template_name
		{ $$ = NULL; unsupported_feature(); }
	;

template_id:
	template_name '<' template_argument_list '>'
		{ $$ = NULL; unsupported_feature(); }
	;

template_argument_list:
	template_argument
		{ $$ = NULL; unsupported_feature(); }
	| template_argument_list ',' template_argument
		{ $$ = NULL; unsupported_feature(); }
	;

template_argument:
	assignment_expression
		{ $$ = NULL; unsupported_feature(); }
	| type_id
		{ $$ = NULL; unsupported_feature(); }
	| template_name
		{ $$ = NULL; unsupported_feature(); }
	;

explicit_instantiation:
	TEMPLATE declaration
		{ $$ = NULL; unsupported_feature(); }
	;

explicit_specialization:
	TEMPLATE '<' '>' declaration
		{ $$ = NULL; unsupported_feature(); }
	;

/*----------------------------------------------------------------------
 * Exception handling.
 *----------------------------------------------------------------------*/

try_block:
	TRY compound_statement handler_seq
		{ $$ = NULL; unsupported_feature(); }
	;

function_try_block:
	TRY ctor_initializer_opt function_body handler_seq
		{ $$ = NULL; unsupported_feature(); }
	;

handler_seq:
	handler handler_seq_opt
		{ $$ = NULL; unsupported_feature(); }
	;

handler:
	CATCH '(' exception_declaration ')' compound_statement
		{ $$ = NULL; unsupported_feature(); }
	;

exception_declaration:
	type_specifier_seq declarator
		{ $$ = NULL; unsupported_feature(); }
	| type_specifier_seq abstract_declarator
		{ $$ = NULL; unsupported_feature(); }
	| type_specifier_seq
		{ $$ = NULL; unsupported_feature(); }
	| ELLIPSIS
		{ $$ = NULL; unsupported_feature(); }
	;

throw_expression:
	THROW assignment_expression_opt
		{ $$ = NULL; unsupported_feature(); }
	;

exception_specification:
	THROW '(' type_id_list_opt ')'
		{ $$ = NULL; unsupported_feature(); }
	;

type_id_list:
	type_id
		{ $$ = $1; }
	| type_id_list ',' type_id
		{ $$ = NULL; unsupported_feature(); }
	;

/*----------------------------------------------------------------------
 * Epsilon (optional) definitions.
 *----------------------------------------------------------------------*/

declaration_seq_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| declaration_seq
		{ $$ = $1; }
	;

nested_name_specifier_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| nested_name_specifier
		{ $$ = $1; }
	;

expression_list_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| expression_list
		{ $$ = $1; }
	;

COLONCOLON_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| COLONCOLON
		{ $$ = $1; }
	;

new_placement_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| new_placement
		{ $$ = $1; }
	;

new_initializer_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| new_initializer
		{ $$ = $1; }
	;

new_declarator_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| new_declarator
		{ $$ = $1; }
	;

expression_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| expression
		{ $$ = $1; }
	;

statement_seq_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| statement_seq
		{ $$ = $1; }
	;

condition_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| condition
		{ $$ = $1; }
	;

enumerator_list_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| enumerator_list
		{ $$ = $1; }
	;

initializer_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| initializer
		{ $$ = $1; }
	;

constant_expression_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| constant_expression
		{ $$ = $1; }
	;

abstract_declarator_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| abstract_declarator
		{ $$ = $1; }
	;

type_specifier_seq_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| type_specifier_seq
		{ $$ = $1; }
	;

direct_abstract_declarator_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| direct_abstract_declarator
		{ $$ = $1; }
	;

ctor_initializer_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| ctor_initializer
		{ $$ = $1; }
	;

COMMA_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| ','
		{ $$ = $1; }
	;

member_specification_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| member_specification
		{ $$ = $1; }
	;

SEMICOLON_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| ';'
		{ $$ = $1; }
	;

conversion_declarator_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| conversion_declarator
		{ $$ = $1; }
	;

EXPORT_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| EXPORT
		{ $$ = $1; }
	;

handler_seq_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| handler_seq
		{ $$ = $1; }
	;

assignment_expression_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| assignment_expression
		{ $$ = $1; }
	;

type_id_list_opt:
	%empty
		{ $$ = NULL; }/* epsilon */
	| type_id_list
		{ $$ = $1; }
	;

%%

void add_typename(struct TreeNode *t, int cat) {
	if(!ident_table.insert(t->t->get_text(), cat)) {
		yyerror("token already in identifier lookup table");
	}
}

struct TreeNode* alloc_tree(struct yyrule y, int num_kids, ...) {
	va_list vakid;
	/* 
	 * TODO: Need to alloc size of kids seperately (causes a segfault
	 * when printing if not handled there).
	 */
	struct TreeNode *t = new struct TreeNode();
	if(!t) {
		std::cerr << "TreeNode: Cannot allocate memory." << std::endl;
		exit(1);
	}
	t->prod_num = y.num;
	t->prod_text = y.text;
	t->num_kids = num_kids;

	va_start(vakid, num_kids);
	if(num_kids > 1) {
		for(int i = 0; i < num_kids; ++i) {
			t->kids[i] = va_arg(vakid, struct TreeNode*);
		}
	}
	va_end(vakid);
	return t;
}

static void unsupported_feature(std::string str) {
	if(str.empty())
		str = "C++ operation not supported in 120++";
	std::stringstream s;
	s << yyfilename << ":" << yylineno << ": ";
	s << str << " before '" << yylval->t->get_text() << "' token";
	s << std::endl;

	std::cerr << s.str();
	exit(3); /* return 3 is unsupported feature detected */

}

static void yyerror(std::string str) {
	std::stringstream s;
	s << yyfilename << ":" << yylineno << ": ";
	s << str << " before '" << yylval->t->get_text() << "' token"; 
	s << std::endl;

	std::cerr << s.str();
	exit(2);
}

