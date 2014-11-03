/* 120rules.hh
 * Defines all of the production rules that can be used as well as a method
 * for looking up what the human-readable text of a production rule is.
 * 
 * UIdaho CS445 120++ Compiler
 * author: Chris Waltrip <walt2178@vandals.uidaho.edu>
 */

#ifndef _120_RULES_HH_
#define _120_RULES_HH_

#include <string>
#include <sstream>

/*
 * Any enumeration that isn't specifically numbered is auto-incremented,
 * so instead of specifying each of the rules, only the first rule of a
 * production rule set is given.  Each rule set is incremented by 1000 
 * to make searching stripping the base rule set and specific rule
 * numbers easier.
 */
enum yyrule {

	/* Start Statement */
	START_RULE 				= 100000,

	/* Named Types */

	TYPEDEF_NAME_1 				= 101001, 
		ORIG_NAMESPACE_NAME_1,
		CLASS_NAME_1,
		ENUM_NAME_1,
		TEMPLATE_NAME_1,
	
	/* Lexical Elements */

	IDENTIFIER_1 				= 102001,
	LITERAL_1 				= 103001,
		LITERAL_2,
		LITERAL_3,
		LITERAL_4,
		LITERAL_5,
	INTEGER_LITERAL_1 			= 104001,
		CHARACTER_LITERAL_1,
		FLOATING_LITERAL_1,
		STRING_LITERAL_1,
		BOOLEAN_LITERAL_1,
	PRIMARY_EXPRESSION_1 			= 105001,
		PRIMARY_EXPRESSION_2,
		PRIMARY_EXPRESSION_3,
		PRIMARY_EXPRESSION_4,
	ID_EXPRESSION_1				= 106001,
		ID_EXPRESSION_2,
	UNQUALIFIED_ID_1			= 107001,
		UNQUALIFIED_ID_2,
		UNQUALIFIED_ID_3,
		UNQUALIFIED_ID_4,
	QUALIFIED_ID_1				= 108001,
		QUALIFIED_ID_2,
	NESTED_NAME_1				= 109001,
		NESTED_NAME_2,
		NESTED_NAME_3,
		NESTED_NAME_4,
	POSTFIX_EXPR_1				= 110001,
		POSTFIX_EXPR_2,
		POSTFIX_EXPR_3,
		POSTFIX_EXPR_4,
		POSTFIX_EXPR_5,
		POSTFIX_EXPR_6,
		POSTFIX_EXPR_7,
		POSTFIX_EXPR_8,
		POSTFIX_EXPR_9,
		POSTFIX_EXPR_10,
		POSTFIX_EXPR_11,
		POSTFIX_EXPR_12,
		POSTFIX_EXPR_13,
		POSTFIX_EXPR_14,
		POSTFIX_EXPR_15,
		POSTFIX_EXPR_16,
		POSTFIX_EXPR_17,
		POSTFIX_EXPR_18,
		POSTFIX_EXPR_19,
	EXPR_LIST_1				= 111001,
		EXPR_LIST_2,
	UNARY_EXPR_1				= 112001,
		UNARY_EXPR_2,
		UNARY_EXPR_3,
		UNARY_EXPR_4,
		UNARY_EXPR_5,
		UNARY_EXPR_6,
		UNARY_EXPR_7,
		UNARY_EXPR_8,
		UNARY_EXPR_9,
		UNARY_EXPR_10,
	UNARY_OP_1				= 113001,
		UNARY_OP_2,
		UNARY_OP_3,
		UNARY_OP_4,
	NEW_EXPR_1				= 114001,
		NEW_EXPR_2,
		NEW_EXPR_3,
		NEW_EXPR_4,
	NEW_PLACEMENT_1				= 115001,
	NEW_TYPE_ID_1				= 116001,
	NEW_DECL_1				= 117001,
		NEW_DECL_2,
	DIRECT_NEW_DECL_1			= 118001,
		DIRECT_NEW_DECL_2,
	NEW_INIT_1				= 119001,
	DELETE_EXPR_1				= 120001,
		DELETE_EXPR_2,
		DELETE_EXPR_3,
		DELETE_EXPR_4,
	CAST_EXPR_1				= 121001,
		CAST_EXPR_2,
	PM_EXPR_1				= 122001,
		PM_EXPR_2,
		PM_EXPR_3,
	MULT_EXPR_1				= 123001,
		MULT_EXPR_2,
		MULT_EXPR_3,
		MULT_EXPR_4,
	ADD_EXPR_1				= 124001,
		ADD_EXPR_2,
		ADD_EXPR_3,
	SHIFT_EXPR_1				= 125001,
		SHIFT_EXPR_2,
		SHIFT_EXPR_3,
	RELATIONAL_EXPR_1			= 126001,
		RELATIONAL_EXPR_2,
		RELATIONAL_EXPR_3,
		RELATIONAL_EXPR_4,
		RELATIONAL_EXPR_5,
	EQ_EXPR_1				= 127001,
		EQ_EXPR_2,
		EQ_EXPR_3,
	AND_EXPR_1				= 128001,
		AND_EXPR_2,
	XOR_EXPR_1				= 129001,
		XOR_EXPR_2,
	OR_EXPR_1				= 130001,
		OR_EXPR_2,
	LOGICAL_AND_EXPR_1			= 131001,
		LOGICAL_AND_EXPR_2,
	LOGICAL_OR_EXPR_1			= 132001,
		LOGICAL_OR_EXPR_2,
	CONDITIONAL_EXPR_1			= 133001,
		CONDITIONAL_EXPR_2,
	ASSIGN_EXPR_1				= 134001,
		ASSIGN_EXPR_2,
		ASSIGN_EXPR_3,
	ASSIGN_OP_1				= 135001,
		ASSIGN_OP_2,
		ASSIGN_OP_3,
		ASSIGN_OP_4,
		ASSIGN_OP_5,
		ASSIGN_OP_6,
		ASSIGN_OP_7,
		ASSIGN_OP_8,
		ASSIGN_OP_9,
		ASSIGN_OP_10,
		ASSIGN_OP_11,
	EXPRESSION_1				= 136001,
		EXPRESSION_2,
	CONSTANT_EXPRESSION_1			= 137001,

	/* Statements */

	STMT_1					= 138001,
		STMT_2,
		STMT_3,
		STMT_4,
		STMT_5,
		STMT_6,
		STMT_7,
		STMT_8,
	LABELED_STMT_1				= 139001,
		LABELED_STMT_2,
		LABELED_STMT_3,
	EXPR_STMT_1				= 140001,
	COMPOUND_STMT_1				= 141001,
	STMT_SEQ_1				= 142001,
		STMT_SEQ_2,
	SELECTION_STMT_1			= 143001,
		SELECTION_STMT_2,
		SELECTION_STMT_3,
	CONDITION_1				= 144001,
		CONDITION_2,
	ITER_STMT_1				= 145001,
		ITER_STMT_2,
		ITER_STMT_3,
		ITER_STMT_4,
	FOR_INIT_STMT_1				= 146001,
		FOR_INIT_STMT_2,
	JUMP_STMT_1				= 147001,
		JUMP_STMT_2,
		JUMP_STMT_3,
		JUMP_STMT_4,
	DECL_STMT_1				= 148001,
	
	/* Declarations */

	DECL_SEQ_1				= 149001,
		DECL_SEQ_2,
	SIMPLE_DECL_1				= 150001,
		SIMPLE_DECL_2,
	DECL_SPEC_SEQ_1				= 151001,
		DECL_SPEC_SEQ_2,
	SIMPLE_TYPE_SPEC_1			= 152001,
		SIMPLE_TYPE_SPEC_2,
	ELAB_TYPE_SPEC_1			= 153001,
		ELAB_TYPE_SPEC_2,
		ELAB_TYPE_SPEC_3,
		ELAB_TYPE_SPEC_4,
		ELAB_TYPE_SPEC_5,
		ELAB_TYPE_SPEC_6,
		ELAB_TYPE_SPEC_7,
	ENUM_TYPE_SPEC_1			= 154001,
	ENUM_LIST_1				= 155001,
	ENUM_DEFINITION_1			= 156001,
	ORIG_NAMESPACE_DEF_1			= 157001,
	EXT_NAMESPACE_DEF_1			= 158001,
	UNNAMED_NAMESPACE_DEF_1			= 159001,
	NAMESPACE_ALIAS_DEF_1			= 160001,
	QUAL_NAMESPACE_SPEC_1			= 161001,
		QUAL_NAMESPACE_SPEC_2,
		QUAL_NAMESPACE_SPEC_3,
		QUAL_NAMESPACE_SPEC_4,
	USING_DECL_1				= 162001,
		USING_DECL_2,
		USING_DECL_3,
		USING_DECL_4,
		USING_DECL_5,
	USING_DIRECTIVE_1			= 163001,
		USING_DIRECTIVE_2,
		USING_DIRECTIVE_3,
		USING_DIRECTIVE_4,
	ASM_DEF_1				= 164001,
	LINKAGE_SPEC_1				= 165001,
		LINKAGE_SPEC_2,

	/* Declarators */

	INIT_DECL_LIST_1			= 166001,
		INIT_DECL_LIST_2,
	INIT_DECL_1				= 167001,
	DECL_1					= 168001,
		DECL_2,
	DIRECT_DECL_1				= 169001,
		DIRECT_DECL_2,
		DIRECT_DECL_3,
		DIRECT_DECL_4,
		DIRECT_DECL_5,
		DIRECT_DECL_6,
		DIRECT_DECL_7,
	PTR_OP_1				= 170001,
		PTR_OP_2,
		PTR_OP_3,
		PTR_OP_4,
		PTR_OP_5,
		PTR_OP_6,
		PTR_OP_7,
	CV_QUAL_SEQ_1				= 171001,
		CV_QUAL_SEQ_2,
	CV_QUAL_1				= 172001,
	DECL_ID_1				= 173001,
		DECL_ID_2,
		DECL_ID_3,
		DECL_ID_4,
	TYPE_ID_1				= 174001,
	TYPE_SPEC_SEQ_1				= 175001,
	ABSTRACT_DECL_1				= 176001,
		ABSTRACT_DECL_2,
	DIRECT_ABSTRACT_DECL_1			= 177001,
		DIRECT_ABSTRACT_DECL_2,	
		DIRECT_ABSTRACT_DECL_3,
		DIRECT_ABSTRACT_DECL_4,
		DIRECT_ABSTRACT_DECL_5,
		DIRECT_ABSTRACT_DECL_6,
	PARAM_DECL_CLAUSE_1			= 178001,
		PARAM_DECL_CLAUSE_2,
		PARAM_DECL_CLAUSE_3,
		PARAM_DECL_CLAUSE_4,
		PARAM_DECL_CLAUSE_5,
	PARAM_DECL_LIST_1			= 179001,
		PARAM_DECL_LIST_2,
	PARAM_DECL_1				= 180001,
		PARAM_DECL_2,
		PARAM_DECL_3,
		PARAM_DECL_4,
	FUNC_DEF_1				= 181001,
		FUNC_DEF_2,
		FUNC_DEF_3,
		FUNC_DEF_4,
	FUNC_BODY_1				= 182001,
	INITIALIZER_1				= 183001,
		INITIALIZER_2,
	INITIALIZER_CLAUSE_1			= 184001,
		INITIALIZER_CLAUSE_2,
		INITIALIZER_CLAUSE_3,
	INITIALIZER_LIST_1			= 185001,
		INITIALIZER_LIST_2,
	CLASS_SPECIFIER_1			= 186001,
	CLASS_HEAD_1				= 187001,
		CLASS_HEAD_2,
		CLASS_HEAD_3,
		CLASS_HEAD_4,
	CLASS_KEY_1				= 188001,
		CLASS_KEY_2,
		CLASS_KEY_3,
	MEMBER_SPEC_1				= 189001,
		MEMBER_SPEC_2,
	MEMBER_DECL_1				= 190001,
		MEMBER_DECL_2,
		MEMBER_DECL_3,
		MEMBER_DECL_4,
		MEMBER_DECL_5,
		MEMBER_DECL_6,
		MEMBER_DECL_7,
		MEMBER_DECL_8,
	MEMBER_DECL_LIST_1			= 191001,
		MEMBER_DECL_LIST_2,
	MEMBER_DECLARATOR_1			= 192001,
		MEMBER_DECLARATOR_2,
		MEMBER_DECLARATOR_3,
		MEMBER_DECLARATOR_4,
	PURE_SPECIFIER_1			= 193001,
	CONST_INITIALIZER_1			= 194001,
	
	/* Derived Classes */

	BASE_CLAUSE_1				= 195001,
	BASE_SPECIFIER_LIST_1			= 196001,
		BASE_SPECIFIER_LIST_2,
	BASE_SPECIFIER_1			= 197001,
		BASE_SPECIFIER_2,
		BASE_SPECIFIER_3,
		BASE_SPECIFIER_4,
		BASE_SPECIFIER_5,
		BASE_SPECIFIER_6,
		BASE_SPECIFIER_7,
		BASE_SPECIFIER_8,
		BASE_SPECIFIER_9,
		BASE_SPECIFIER_10,
		BASE_SPECIFIER_11,
		BASE_SPECIFIER_12,
	ACCESS_SPECIFIER_1			= 198001,
		ACCESS_SPECIFIER_2,
		ACCESS_SPECIFIER_3,
	
	/* Special Member Functions */

	CONV_FUNC_ID_1				= 199001,
	CONV_TYPE_ID_1				= 200001,
	CONV_DECLARATOR_1			= 201001,
	CTOR_INIT_1				= 202001,
	MEM_INIT_LIST_1				= 203001,
		MEM_INIT_LIST_2,
	MEM_INIT_1				= 204001,
	MEM_INIT_ID_1				= 205001,
		MEM_INIT_ID_2,
		MEM_INIT_ID_3,
		MEM_INIT_ID_4,
		MEM_INIT_ID_5,

	/* Overloading */

	OP_FUNC_ID_1				= 206001,
	OP_1					= 207001,
		OP_2,
		OP_3,
		OP_4,
		OP_5,
		OP_6,
		OP_7,
		OP_8,
		OP_9,
		OP_10,
		OP_11,
		OP_12,
		OP_13,
		OP_14,
		OP_15,
		OP_16,
		OP_17,
		OP_18,
		OP_19,
		OP_20,
		OP_21,
		OP_22,
		OP_23,
		OP_24,
		OP_25,
		OP_26,
		OP_27,
		OP_28,
		OP_29,
		OP_30,
		OP_31,
		OP_32,
		OP_33,
		OP_34,
		OP_35,
		OP_36,
		OP_37,
		OP_38,
		OP_39,
		OP_40,
		OP_41,
		OP_42,
	
	/* Templates */

	TEMPLATE_DECL_1				= 208001,
	TEMPLATE_PARAM_LIST_1			= 209001,
		TEMPLATE_PARAM_LIST_2,
	TEMPLATE_PARAM_1			= 210001,
		TEMPLATE_PARAM_2,
	TYPE_PARAM_1				= 211001,
		TYPE_PARAM_2,
		TYPE_PARAM_3,
		TYPE_PARAM_4,
		TYPE_PARAM_5,
		TYPE_PARAM_6,
	TEMPLATE_ID_1				= 212001,
	TEMPLATE_ARG_LIST_1			= 213001,
		TEMPLATE_ARG_LIST_2,
	TEMPLATE_ARG_1				= 214001,
		TEMPLATE_ARG_2,
		TEMPLATE_ARG_3,
	EXPLICIT_INSTANTIATION_1		= 215001,
	EXPLICIT_SPECIALIZATION_1		= 216001,

	/* Exception Handling */

	TRY_BLOCK_1				= 217001,
	FUNC_TRY_BLOCK_1			= 218001,
	HANDLER_SEQ_1				= 219001,
	HANDLER_1				= 220001,
	EXCEPTION_DECL_1			= 221001,
		EXCEPTION_DECL_2,
		EXCEPTION_DECL_3,
		EXCEPTION_DECL_4,
	THROW_EXPR_1				= 222001,
	EXCEPTION_SPEC_1			= 223001,
	TYPE_ID_LIST_1				= 224001,
		TYPE_ID_LIST_2,

	/* Epsilon definitions */

	DECL_SEQ_OPT_1				= 225001,
	NESTED_NAME_SPEC_OPT_1			= 226001,
	EXPR_LIST_OPT_1				= 227001,
	SCOPE_RESOLUTION_OPT_1			= 228001,
	NEW_PLACEMENT_OPT_1			= 229001,
	NEW_INIT_OPT_1				= 230001,
	NEW_DECL_OPT_1				= 231001,
	EXPR_OPT_1				= 232001,
	STMT_SEQ_OPT_1				= 233001,
	COND_OPT_1				= 234001,
	ENUM_LIST_OPT_1				= 235001,
	INIT_OPT_1				= 236001,
	CONST_EXPR_OPT_1			= 237001,
	ABSTRACT_DECL_OPT_1			= 238001,
	TYPE_SPEC_SEQ_OPT_1			= 239001,
	DIRECT_ABSTRACT_DECL_OPT_1		= 240001,
	CTOR_INIT_OPT_1				= 241001,
	COMMA_OPT_1				= 242001,
	MEMBER_SPEC_OPT_1			= 243001,
	SEMICOLON_OPT_1				= 244001,
	CONVERSION_DECL_OPT_1			= 245001,
	EXPORT_OPT_1				= 246001,
	HANDLER_SEQ_OPT_1			= 247001,
	ASSIGN_EXPR_OPT_1			= 248001,
	TYPE_ID_LIST_OPT_1			= 249001,
};

static std::string get_production_text(const unsigned int num) {
	unsigned int base = num / 1000;
	unsigned int rule = num % 1000;
	std::stringstream s;
	switch(base) {

		case 100:
			s << "START";
			break;
		case 101:
			s << "name-";
			switch(rule) {
				case 1: s << "typedef"; break;
				case 2: s << "namespace"; break;
				case 3: s << "orig-namespace"; break;
				case 4: s << "class"; break;
				case 5: s << "enum"; break;
				case 6: s << "template"; break;
			}
			break;
		case 102:
			s << "ident";
			break;
		case 103:
			s << "lit-";
			switch(rule) {
				case 1: s << "int"; break;
				case 2: s << "char"; break;
				case 3: s << "float"; break;
				case 4: s << "string"; break;
				case 5: s << "bool"; break;
			}
			break;
		case 104:
			s << "val-";
			switch(rule) {
				case 1: s << "int"; break;
				case 2: s << "char"; break;
				case 3: s << "float"; break;
				case 4: s << "string"; break;
				case 5: s << "bool"; break;
			}
			break;
		case 105:
			s << "pri-expr-";
			switch(rule) {
				case 1: s << "lit"; break;
				case 2: s << "THIS"; break;
				case 3: s << "()"; break;
				case 4: s << "idexpr"; break;
			}
			break;
		case 106:
			s << "idexpr-";
			switch(rule) {
				case 1: s << "unqual"; break;
				case 2: s << "qual"; break;
			}
			break;
		case 107:
			s << "unqual";
			s << "-";
			switch(rule) {
				case 1: s << "id"; break;
				case 2: s << "funcid"; break;
				case 3: s << "conv-funcid"; break;
				case 4: s << "~class"; break;
			}
			break;
		case 108:
			s << "qual";
			switch(rule) {
				case 1: s << "-nontemplate"; break;
				case 2: s << "-template"; break;
			}
			break;
		case 109:
			s << "nestedname-";
			switch(rule) {
				case 1: s << "class1"; break;
				case 2: s << "namespace1"; break;
				case 3: s << "class2"; break;
				case 4: s << "namespace2"; break;
			}			
			break;
		case 110:
			s << "postfix";
			switch(rule) {
				case 1: s << "-primary"; break;
				case 2: s << "-[]"; break;
				case 3: s << "-()"; break;
				case 4: s << "-template1"; break;
				case 5: s << "-template2"; break;
				case 6: s << "-::"; break;
				case 7: s << "-.idexpr"; break;
				default: s << "-" << rule; break;
			}
			break;
		case 111:
			s << "expr-list";
			switch(rule) {
				case 1: s << "-1"; break;
				case 2: s << "-2"; break;
			}
			break;
		case 112:
			s << "unary-expr-" << rule;
			break;
		case 113:
			s << "unary-op-" << rule;
			break;
		case 114:
			s << "new-expr-" << rule;
			break;
		case 115:
			s << "new-placement-" << rule;
			break;
		case 116:
			s << "new-type-" << rule;
			break;
		case 117:
			s << "new-decl-" << rule;
			break;
		case 118:
			s << "direct-new-decl-" << rule;
			break;
		case 119:
			s << "new-init-" << rule;
			break;
		case 120:
			s << "delete-expr-" << rule;
			break;
		case 121:
			s << "cast-expr-" << rule;
			break;
		case 122:
			s << "pm-expr-" << rule;
			break;
		case 123:
			s << "mult-expr-" << rule;
			break;
		case 124:
			s << "add-expr-" << rule;
			break;
		case 125:
			s << "shift-expr-" << rule;
			break;
		case 126:
			s << "relational-expr-" << rule;
			break;
		case 127:
			s << "eq-expr-" << rule;
			break;
		case 128:
			s << "and-expr-" << rule;
			break;
		case 129:
			s << "xor-expr-" << rule;
			break;
		case 130:
			s << "or-expr-" << rule;
			break;
		case 131:
			s << "land-expr-" << rule;
			break;
		case 132:
			s << "lor-" << rule;
			break;
		case 133:
			s << "cond-expr-" << rule;
			break;
		case 134:
			s << "assign-expr-" << rule;
			break;
		case 135:
			s << "assign-op-" << rule;
			break;
		case 136:
			s << "expr-" << rule;
			break;
		case 137:
			s << "const-expr-" << rule;
			break;
		case 138:
			s << "stmt-" << rule;
			break;
		case 139:
			s << "labeled-stmt-" << rule;
			break;
		case 140:
			s << "expr-stmt-" << rule;
			break;
		case 141:
			s << "cmpd-stmt-" << rule;
			break;
		case 142:
			s << "stmt-seq-" << rule;
			break;
		case 143:
			s << "select-stmt-" << rule;
			break;
		case 144:
			s << "cond-" << rule;
			break;
		case 145:
			s << "iter-stmt-" << rule;
			break;
		case 146:
			s << "for-stmt-" << rule;
			break;
		case 147:
			s << "jump-stmt-" << rule;
			break;
		case 148:
			s << "decl-stmt-" << rule;
			break;
		case 149:
			s << "decl-seq-" << rule;
			break;
		case 150:
			s << "simple-decl-" << rule;
			break;
		case 151:
			s << "decl-spec-seq-" << rule;
			break;
		case 152:
			s << "simp-typespec-" << rule;
			break;
		case 153:
			s << "elab-typespec-" << rule;
			break;
		case 154:
			s << "enum-spec-" << rule;
			break;
		case 155:
			s << "enum-list-" << rule;
			break;
		case 156:
			s << "enum-def-" << rule;
			break;
		case 157:
			s << "orig-nspace-def-" << rule;
			break;
		case 158:
			s << "ext-nspace-def-" << rule;
			break;
		case 159:
			s << "unnamed-nspace-def-" << rule;
			break;
		case 160:
			s << "nspace-alias-def-" << rule;
			break;
		case 161:
			s << "qual-nspace-spec-" << rule;
			break;
		case 162:
			s << "using-def-" << rule;
			break;
		case 163:
			s << "using-dir-" << rule;
			break;
		case 164:
			s << "asm-def-" << rule;
			break;
		case 165:
			s << "-" << rule;
			break;
		case 166:
			s << "init-decl-list-" << rule;
			break;
		case 167:
			s << "init-decl-" << rule;
			break;
		case 168:
			s << "decl-" << rule;
			break;
		case 169:
			s << "direct-decl-" << rule;
			break;
		case 170:
			s << "ptr-op-" << rule;
			break;
		case 171:
			s << "cv-qual-seq-" << rule;
			break;
		case 172:
			s << "cv-qual-" << rule;
			break;
		case 173:
			s << "decl-id-" << rule;
			break;
		case 174:
			s << "type-id-" << rule;
			break;
		case 175:
			s << "typespec-seq-" << rule;
			break;
		case 176:
			s << "abstract-decl-" << rule;
			break;
		case 177:
			s << "direct-abstract-decl-" << rule;
			break;
		case 178:
			s << "param-decl-clause-" << rule;
			break;
		case 179:
			s << "param-decl-list-" << rule;
			break;
		case 180:
			s << "param-decl-" << rule;
			break;
		case 181:
			s << "func-decl-" << rule;
			break;
		case 182:
			s << "func-body-" << rule;
			break;
		case 183:
			s << "init-" << rule;
			break;
		case 184:
			s << "init-clause-" << rule;
			break;
		case 185:
			s << "init-list-" << rule;
			break;
		case 186:
			s << "class-spec-" << rule;
			break;
		case 187:
			s << "class-head-" << rule;
			break;
		case 188:
			s << "class-key-" << rule;
			break;
		case 189:
			s << "member-spec-" << rule;
			break;
		case 190:
			s << "member-decl-" << rule;
			break;
		case 191:
			s << "member-decl-list-" << rule;
			break;
		case 192:
			s << "member-declarator-" << rule;
			break;
		case 193:
			s << "pure-spec-" << rule;
			break;
		case 194:
			s << "const-init-" << rule;
			break;
		case 195:
			s << "base-clause-" << rule;
			break;
		case 196:
			s << "base-spec-list-" << rule;
			break;
		case 197:
			s << "base-spec-" << rule;
			break;
		case 198:
			s << "access-spec-" << rule;
			break;
		case 199:
			s << "conv-func-id-" << rule;
			break;
		case 200:
			s << "conv-type-id-" << rule;
			break;
		case 201:
			s << "conv-declarator-" << rule;
			break;
		case 202:
			s << "ctor-init-" << rule;
			break;
		case 203:
			s << "mem-init-list-" << rule;
			break;
		case 204:
			s << "mem-init-" << rule;
			break;
		case 205:
			s << "mem-init-id-" << rule;
			break;
		case 206:
			s << "op-func-id-" << rule;
			break;
		case 207:
			s << "operator-" << rule;
			break;
		case 208:
			s << "template-decl-" << rule;
			break;
		case 209:
			s << "tmpl-param-list-" << rule;
			break;
		case 210:
			s << "tmpl-param-" << rule;
			break;
		case 211:
			s << "type-param-" << rule;
			break;
		case 212:
			s << "template-id-" << rule;
			break;
		case 213:
			s << "tmpl-arg-list-" << rule;
			break;
		case 214:
			s << "template-arg-" << rule;
			break;
		case 215:
			s << "explicit-instanciation-" << rule;
			break;
		case 216:
			s << "explicit-specialization-" << rule;
			break;
		case 217:
			s << "try-block-" << rule;
			break;
		case 218:
			s << "try-function-block-" << rule;
			break;
		case 219:
			s << "handler-seq-" << rule;
			break;
		case 220:
			s << "handler-" << rule;
			break;
		case 221:
			s << "exception-decl-" << rule;
			break;
		case 222:
			s << "throw-expr-" << rule;
			break;
		case 223:
			s << "exception-spec-" << rule;
			break;
		case 224:
			s << "type-id-list-" << rule;
			break;
		case 225:
			s << "decl-seq-opt-" << rule;
			break;
		case 226:
			s << "nested-name-spec-opt-" << rule;
			break;
		case 227:
			s << "expr-list-opt-" << rule;
			break;
		case 228:
			s << "scope-res-opt-" << rule;
			break;
		case 229:
			s << "new-placement-opt-" << rule;
			break;
		case 230:
			s << "new-init-opt-" << rule;
			break;
		case 231:
			s << "new-decl-opt-" << rule;
			break;
		case 232:
			s << "expr-opt-" << rule;
			break;
		case 233:
			s << "stmt-seq-opt-" << rule;
			break;
		case 234:
			s << "cond-opt-" << rule;
			break;
		case 235:
			s << "enum-list-opt-" << rule;
			break;
		case 236:
			s << "init-opt-" << rule;
			break;
		case 237:
			s << "const-expr-opt-" << rule;
			break;
		case 238:
			s << "abstract-decl-opt-" << rule;
			break;
		case 239:
			s << "type-spec-seq-opt-" << rule;
			break;
		case 240:
			s << "direct-abstract-decl-opt-" << rule;
			break;
		case 241:
			s << "ctor-init-opt-" << rule;
			break;
		case 242:
			s << "comma-opt-" << rule;
			break;
		case 243:
			s << "member-spec-opt-" << rule;
			break;
		case 244:
			s << "semicolon-opt-" << rule;
			break;
		case 245:
			s << "conv-decl-opt-" << rule;
			break;
		case 246:
			s << "export-opt-" << rule;
			break;
		case 247:
			s << "handler-seq-opt-" << rule;
			break;
		case 248:
			s << "assign-expr-opt-" << rule;
			break;
		case 249:
			s << "type-id-list-opt-" << rule;
			break;
		default:
			s << "NO RULE FOUND";
	}
	return s.str();
}


#endif /* _120_RULES_HH_ */