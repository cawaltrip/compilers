/* Token type.  */
#ifndef YY_PRODUCTION_RULES
#define YY_PRODUCTION_RULES

#include <string>

typedef struct yyrule { 
	int num;
	std::string text;
	yyrule(int n, std::string s) : num(n), text(s) { }
} yyrule;

const struct yyrule START_RULE(10000,"START");

const struct yyrule TYPEDEF_NAME_1(11001, "typedef-name");
const struct yyrule NAMESPACE_NAME_1(11002, "namespace-name");
const struct yyrule ORIG_NAMESPACE_NAME_1(11003, "orig-namespace-name");
const struct yyrule CLASS_NAME_1(11004, "class-name");
const struct yyrule ENUM_NAME_1(11005, "enum-name");
const struct yyrule TEMPLATE_NAME_1(11006, "template-name");

/* Lexical Elements */
const struct yyrule IDENTIFIER_1(12001, "id");

const struct yyrule LITERAL_1(13001,"int-literal");
const struct yyrule LITERAL_2(13002,"char-lit");
const struct yyrule LITERAL_3(13003,"float-lit");
const struct yyrule LITERAL_4(13004,"string-lit");
const struct yyrule LITERAL_5(13005,"bool-lit");

const struct yyrule INTEGER_LITERAL_1(14001,"int-val");
const struct yyrule CHARACTER_LITERAL_1(14002,"char-val");
const struct yyrule FLOATING_LITERAL_1(14003,"float-val");
const struct yyrule STRING_LITERAL_1(14004,"string-val");
const struct yyrule BOOLEAN_LITERAL_1(14005,"bool-val");

/* Expressions */
const struct yyrule PRIMARY_EXPRESSION_1(15001,"prim-expr-lit");
const struct yyrule PRIMARY_EXPRESSION_2(15002,"prim-expr-THIS");
const struct yyrule PRIMARY_EXPRESSION_3(15003,"prim-expr-()");
const struct yyrule PRIMARY_EXPRESSION_4(15004,"prim-expr-idexpr");

const struct yyrule ID_EXPRESSION_1(16001,"idexpr-unqual");
const struct yyrule ID_EXPRESSION_2(16002,"idexpr-qual");

const struct yyrule UNQUALIFIED_ID_1(17001,"unqual-id");
const struct yyrule UNQUALIFIED_ID_2(17002,"unqual-funcid");
const struct yyrule UNQUALIFIED_ID_3(17003,"unqual-conv-funcid");
const struct yyrule UNQUALIFIED_ID_4(17004,"unqual-~class");

const struct yyrule QUALIFIED_ID_1(18001,"qual-nontemplate");
const struct yyrule QUALIFIED_ID_2(18002,"qual-template");

const struct yyrule NESTED_NAME_1(18001,"nestedname-class1");
const struct yyrule NESTED_NAME_2(18002,"nestedname-namespace1");
const struct yyrule NESTED_NAME_3(18003,"nestedname-class2");
const struct yyrule NESTED_NAME_4(18004,"nestedname-namespace2");

const struct yyrule POSTFIX_EXPR_1(19001,"postfix-primary");
const struct yyrule POSTFIX_EXPR_2(19002,"postfix-[]");
const struct yyrule POSTFIX_EXPR_3(19003,"postfix-()");
const struct yyrule POSTFIX_EXPR_4(19004,"postfix-template1");
const struct yyrule POSTFIX_EXPR_5(19005,"postfix-template2");
const struct yyrule POSTFIX_EXPR_6(19006,"postfix-::");
const struct yyrule POSTFIX_EXPR_7(19007,"postfix-.idexpr");
const struct yyrule POSTFIX_EXPR_8(19008,"postfix");
const struct yyrule POSTFIX_EXPR_9(19009,"postfix");
const struct yyrule POSTFIX_EXPR_10(19010,"postfix");
const struct yyrule POSTFIX_EXPR_11(19011,"postfix");
const struct yyrule POSTFIX_EXPR_12(19012,"postfix");
const struct yyrule POSTFIX_EXPR_13(19013,"postfix");
const struct yyrule POSTFIX_EXPR_14(19014,"postfix");
const struct yyrule POSTFIX_EXPR_15(19015,"postfix");
const struct yyrule POSTFIX_EXPR_16(19016,"postfix");
const struct yyrule POSTFIX_EXPR_17(19017,"postfix");
const struct yyrule POSTFIX_EXPR_18(19018,"postfix");
const struct yyrule POSTFIX_EXPR_19(19018,"postfix");

const struct yyrule EXPR_LIST_1(20001,"expr-list1");
const struct yyrule EXPR_LIST_2(20002,"expr-list2");

const struct yyrule UNARY_EXPR_1(21001,"unary-expr");
const struct yyrule UNARY_EXPR_2(21002,"unary-expr");
const struct yyrule UNARY_EXPR_3(21003,"unary-expr");
const struct yyrule UNARY_EXPR_4(21004,"unary-expr");
const struct yyrule UNARY_EXPR_5(21005,"unary-expr");
const struct yyrule UNARY_EXPR_6(21006,"unary-expr");
const struct yyrule UNARY_EXPR_7(21007,"unary-expr");
const struct yyrule UNARY_EXPR_8(21008,"unary-expr");
const struct yyrule UNARY_EXPR_9(21009,"unary-expr");
const struct yyrule UNARY_EXPR_10(21010,"unary-expr");

const struct yyrule UNARY_OP_1(22001,"unary-op");
const struct yyrule UNARY_OP_2(22002,"unary-op");
const struct yyrule UNARY_OP_3(22003,"unary-op");
const struct yyrule UNARY_OP_4(22004,"unary-op");

const struct yyrule NEW_EXPR_1(23001,"new-expr");
const struct yyrule NEW_EXPR_2(23002,"new-expr");
const struct yyrule NEW_EXPR_3(23003,"new-expr");
const struct yyrule NEW_EXPR_4(23004,"new-expr");

const struct yyrule NEW_PLACEMENT_1(24001,"new-placement");

const struct yyrule NEW_TYPE_ID_1(25001,"new-type");

const struct yyrule NEW_DECL_1(26001,"new-decl");
const struct yyrule NEW_DECL_2(26002,"new-decl");

const struct yyrule DIRECT_NEW_DECL_1(27001,"direct-new-decl");
const struct yyrule DIRECT_NEW_DECL_2(27002,"direct-new-decl");

const struct yyrule NEW_INIT_1(28001,"new-init");

const struct yyrule DELETE_EXPR_1(29001,"delete-expr");
const struct yyrule DELETE_EXPR_2(29002,"delete-expr");
const struct yyrule DELETE_EXPR_3(29003,"delete-expr");
const struct yyrule DELETE_EXPR_4(29004,"delete-expr");

const struct yyrule CAST_EXPR_1(30001,"cast-expr");
const struct yyrule CAST_EXPR_2(30002,"cast-expr");

const struct yyrule PM_EXPR_1(31001,"pm-expr");
const struct yyrule PM_EXPR_2(31002,"pm-expr");
const struct yyrule PM_EXPR_3(31003,"pm-expr");

const struct yyrule MULT_EXPR_1(32001,"mult-expr");
const struct yyrule MULT_EXPR_2(32002,"mult-expr");
const struct yyrule MULT_EXPR_3(32003,"mult-expr");
const struct yyrule MULT_EXPR_4(32004,"mult-expr");

const struct yyrule ADD_EXPR_1(33001,"add-expr");
const struct yyrule ADD_EXPR_2(33002,"add-expr");
const struct yyrule ADD_EXPR_3(33003,"add-expr");

const struct yyrule SHIFT_EXPR_1(34001,"shift-expr");
const struct yyrule SHIFT_EXPR_2(34002,"shift-expr");
const struct yyrule SHIFT_EXPR_3(34003,"shift-expr");

const struct yyrule RELATIONAL_EXPR_1(35001,"relational-expr");
const struct yyrule RELATIONAL_EXPR_2(35002,"relational-expr");
const struct yyrule RELATIONAL_EXPR_3(35003,"relational-expr");
const struct yyrule RELATIONAL_EXPR_4(35004,"relational-expr");
const struct yyrule RELATIONAL_EXPR_5(35005,"relational-expr");

const struct yyrule EQ_EXPR_1(36001,"equality-expr");
const struct yyrule EQ_EXPR_2(36002,"equality-expr");
const struct yyrule EQ_EXPR_3(36003,"equality-expr");

const struct yyrule AND_EXPR_1(37001,"and-expr");
const struct yyrule AND_EXPR_2(37002,"and-expr");

const struct yyrule XOR_EXPR_1(38001,"xor-expr");
const struct yyrule XOR_EXPR_2(38002,"xor-expr");

const struct yyrule OR_EXPR_1(39001,"or-expr");
const struct yyrule OR_EXPR_2(39002,"or-expr");

const struct yyrule LOGICAL_AND_EXPR_1(40001,"land-expr");
const struct yyrule LOGICAL_AND_EXPR_2(40002,"land-expr");

const struct yyrule LOGICAL_OR_EXPR_1(41001,"lor-expr");
const struct yyrule LOGICAL_OR_EXPR_2(41002,"lor-expr");

const struct yyrule CONDITIONAL_EXPR_1(42001,"cond-expr");
const struct yyrule CONDITIONAL_EXPR_2(42002,"cond-expr");

const struct yyrule ASSIGN_EXPR_1(43001,"assignment");
const struct yyrule ASSIGN_EXPR_2(43002,"assignment");
const struct yyrule ASSIGN_EXPR_3(43003,"assignment");

const struct yyrule ASSIGN_OP_1(44001,"assign-op");
const struct yyrule ASSIGN_OP_2(44002,"assign-op");
const struct yyrule ASSIGN_OP_3(44003,"assign-op");
const struct yyrule ASSIGN_OP_4(44004,"assign-op");
const struct yyrule ASSIGN_OP_5(44005,"assign-op");
const struct yyrule ASSIGN_OP_6(44006,"assign-op");
const struct yyrule ASSIGN_OP_7(44007,"assign-op");
const struct yyrule ASSIGN_OP_8(44008,"assign-op");
const struct yyrule ASSIGN_OP_9(44009,"assign-op");
const struct yyrule ASSIGN_OP_10(44010,"assign-op");
const struct yyrule ASSIGN_OP_11(44011,"assign-op");

const struct yyrule EXPRESSION_1(45001,"expression");
const struct yyrule EXPRESSION_2(45002,"expression");

const struct yyrule CONSTANT_EXPRESSION_1(46001,"const-expr");

/* Statements */

const struct yyrule STMT_1(47001,"statement");
const struct yyrule STMT_2(47002,"statement");
const struct yyrule STMT_3(47003,"statement");
const struct yyrule STMT_4(47004,"statement");
const struct yyrule STMT_5(47005,"statement");
const struct yyrule STMT_6(47006,"statement");
const struct yyrule STMT_7(47007,"statement");
const struct yyrule STMT_8(47008,"statement");

const struct yyrule LABELED_STMT_1(48001,"labeled-stmt");
const struct yyrule LABELED_STMT_2(48002,"labeled-stmt");
const struct yyrule LABELED_STMT_3(48003,"labeled-stmt");

const struct yyrule EXPR_STMT_1(49001,"expr-stmt");

const struct yyrule COMPOUND_STMT_1(50001,"cmpd-stmt");

const struct yyrule STMT_SEQ_1(51001,"stmt-seq");
const struct yyrule STMT_SEQ_2(51002,"stmt-seq");

const struct yyrule SELECTION_STMT_1(52001,"selection-stmt");
const struct yyrule SELECTION_STMT_2(52002,"selection-stmt");
const struct yyrule SELECTION_STMT_3(52003,"selection-stmt");

const struct yyrule CONDITION_1(53001,"conditional");
const struct yyrule CONDITION_2(53002,"conditional");

const struct yyrule ITER_STMT_1(54001,"iter-stmt");
const struct yyrule ITER_STMT_2(54002,"iter-stmt");
const struct yyrule ITER_STMT_3(54003,"iter-stmt");
const struct yyrule ITER_STMT_4(54004,"iter-stmt");

const struct yyrule FOR_INIT_STMT_1(55001,"for-stmt");
const struct yyrule FOR_INIT_STMT_2(55002,"for-stmt");

const struct yyrule JUMP_STMT_1(56001,"jump-stmt");
const struct yyrule JUMP_STMT_2(56002,"jump-stmt");
const struct yyrule JUMP_STMT_3(56003,"jump-stmt");
const struct yyrule JUMP_STMT_4(56004,"jump-stmt");

const struct yyrule DECL_STMT_1(57001,"decl-stmt");

/* Declarations */

const struct yyrule DECL_SEQ_1(142001,"decl-seq");
const struct yyrule DECL_SEQ_2(142002,"decl-seq");

/* 143000 for decl */
/* 144000 for block-decl */

const struct yyrule SIMPLE_DECL_1(145001,"simple-decl");
const struct yyrule SIMPLE_DECL_2(145002,"simple-decl");

/* 146000 for block-decl */

const struct yyrule DECL_SPEC_SEQ_1(147001,"decl-spec-seq");
const struct yyrule DECL_SPEC_SEQ_2(147002,"decl-spec-seq");

/* 148000 for block-decl */
/* 149000 for block-decl */

const struct yyrule SIMPLE_TYPE_SPEC_1(150001,"simp-typespec");
const struct yyrule SIMPLE_TYPE_SPEC_2(150002,"simp-typespec");

/* 151000 for typename */

const struct yyrule ELAB_TYPE_SPEC_1(152001,"elab-typespec");
const struct yyrule ELAB_TYPE_SPEC_2(152002,"elab-typespec");
const struct yyrule ELAB_TYPE_SPEC_3(152003,"elab-typespec");
const struct yyrule ELAB_TYPE_SPEC_4(152004,"elab-typespec");
const struct yyrule ELAB_TYPE_SPEC_5(152005,"elab-typespec");
const struct yyrule ELAB_TYPE_SPEC_6(152006,"elab-typespec");
const struct yyrule ELAB_TYPE_SPEC_7(152007,"elab-typespec");

const struct yyrule ENUM_TYPE_SPEC_1(153001,"enum-spec");

const struct yyrule ENUM_LIST_1(154001,"enum-list");

const struct yyrule ENUM_DEFINITION_1(155001,"enum-def");

/* 156000 for enumerator */

/* 157000 for namespace-definition */
/* 158000 for named-namespace */

const struct yyrule ORIG_NAMESPACE_DEF_1(159001,"orig-namespc-def");

const struct yyrule EXT_NAMESPACE_DEF_1(160001,"ext-namespc-def");

const struct yyrule UNNAMED_NAMESPACE_DEF_1(161001,"unnamed-namespc-def");

/* 162000 for namespace-body */

const struct yyrule NAMESPACE_ALIAS_DEF_1(163001,"namespc-alias-def");

const struct yyrule QUAL_NAMESPACE_SPEC_1(164001,"qual-namespc-spec");
const struct yyrule QUAL_NAMESPACE_SPEC_2(164002,"qual-namespc-spec");
const struct yyrule QUAL_NAMESPACE_SPEC_3(164003,"qual-namespc-spec");
const struct yyrule QUAL_NAMESPACE_SPEC_4(164004,"qual-namespc-spec");


const struct yyrule USING_DECL_1(165001,"using-def");
const struct yyrule USING_DECL_2(165002,"using-def");
const struct yyrule USING_DECL_3(165003,"using-def");
const struct yyrule USING_DECL_4(165004,"using-def");
const struct yyrule USING_DECL_5(165005,"using-def");

const struct yyrule USING_DIRECTIVE_1(166001,"using-dir");
const struct yyrule USING_DIRECTIVE_2(166002,"using-dir");
const struct yyrule USING_DIRECTIVE_3(166003,"using-dir");
const struct yyrule USING_DIRECTIVE_4(166004,"using-dir");

const struct yyrule ASM_DEF_1(167001,"asm-def");

const struct yyrule LINKAGE_SPEC_1(167001,"linkage-spec");
const struct yyrule LINKAGE_SPEC_2(167002,"linkage-spec");




/* Declarators */

const struct yyrule INIT_DECL_LIST_1(58001,"init-decl-list");
const struct yyrule INIT_DECL_LIST_2(58002,"init-decl-list");

const struct yyrule INIT_DECL_1(59001,"init-decl");

const struct yyrule DECL_1(60001,"decl");
const struct yyrule DECL_2(60002,"decl");

const struct yyrule DIRECT_DECL_1(61001,"direct-decl");
const struct yyrule DIRECT_DECL_2(61002,"direct-decl");
const struct yyrule DIRECT_DECL_3(61003,"direct-decl");
const struct yyrule DIRECT_DECL_4(61004,"direct-decl");
const struct yyrule DIRECT_DECL_5(61005,"direct-decl");
const struct yyrule DIRECT_DECL_6(61006,"direct-decl");
const struct yyrule DIRECT_DECL_7(61007,"direct-decl");

const struct yyrule PTR_OP_1(62001,"ptr-op");
const struct yyrule PTR_OP_2(62002,"ptr-op");
const struct yyrule PTR_OP_3(62003,"ptr-op");
const struct yyrule PTR_OP_4(62004,"ptr-op");
const struct yyrule PTR_OP_5(62005,"ptr-op");
const struct yyrule PTR_OP_6(62006,"ptr-op");
const struct yyrule PTR_OP_7(62007,"ptr-op");

const struct yyrule CV_QUAL_SEQ_1(63001,"cv-qual-seq");
const struct yyrule CV_QUAL_SEQ_2(63002,"cv-qual-seq");

const struct yyrule CV_QUAL_1(64001,"cv-qual");

const struct yyrule DECL_ID_1(65001,"decl-id");
const struct yyrule DECL_ID_2(65002,"decl-id");
const struct yyrule DECL_ID_3(65003,"decl-id");
const struct yyrule DECL_ID_4(65004,"decl-id");

const struct yyrule TYPE_ID_1(66001,"type-id");

const struct yyrule TYPE_SPEC_SEQ_1(67001,"typespec-seq");

const struct yyrule ABSTRACT_DECL_1(68001,"abstract-decl");
const struct yyrule ABSTRACT_DECL_2(68002,"abstract-decl");

const struct yyrule DIRECT_ABSTRACT_DECL_1(69001,"dir-abst-decl");
const struct yyrule DIRECT_ABSTRACT_DECL_2(69002,"dir-abst-decl");
const struct yyrule DIRECT_ABSTRACT_DECL_3(69003,"dir-abst-decl");
const struct yyrule DIRECT_ABSTRACT_DECL_4(69004,"dir-abst-decl");
const struct yyrule DIRECT_ABSTRACT_DECL_5(69005,"dir-abst-decl");
const struct yyrule DIRECT_ABSTRACT_DECL_6(69006,"dirparam-decl-clause);

const struct yyrule PARAM_DECL_CLAUSE_1(70001,"param-decl-clause");
const struct yyrule PARAM_DECL_CLAUSE_2(70002,"param-decl-clause");
const struct yyrule PARAM_DECL_CLAUSE_3(70003,"param-decl-clause");
const struct yyrule PARAM_DECL_CLAUSE_4(70004,"param-decl-clause");
const struct yyrule PARAM_DECL_CLAUSE_5(70005,"param-decl-clause");

const struct yyrule PARAM_DECL_LIST_1(71001,"param-decl-list");
const struct yyrule PARAM_DECL_LIST_2(71002,"param-decl-list");

const struct yyrule PARAM_DECL_1(72001,"param-decl");
const struct yyrule PARAM_DECL_2(72002,"param-decl");
const struct yyrule PARAM_DECL_3(72003,"param-decl");
const struct yyrule PARAM_DECL_4(72004,"param-decl");

const struct yyrule FUNC_DEF_1(73001,"func-decl");
const struct yyrule FUNC_DEF_2(73002,"func-decl");
const struct yyrule FUNC_DEF_3(73003,"func-decl");
const struct yyrule FUNC_DEF_4(73004,"func-decl");

const struct yyrule FUNC_BODY_1(74001,"func-body");

const struct yyrule INITIALIZER_1(75001,"init");
const struct yyrule INITIALIZER_2(75002,"init");

const struct yyrule INITIALIZER_CLAUSE_1(76001,"init-clause");
const struct yyrule INITIALIZER_CLAUSE_2(76002,"init-clause");
const struct yyrule INITIALIZER_CLAUSE_3(76003,"init-clause");

const struct yyrule INITIALIZER_LIST_1(77001,"init-list");
const struct yyrule INITIALIZER_LIST_2(77002,"init-list");

/* Classes */

const struct yyrule CLASS_SPECIFIER_1(78001,"class-spec");

const struct yyrule CLASS_HEAD_1(79001,"class-head");
const struct yyrule CLASS_HEAD_2(79002,"class-head");
const struct yyrule CLASS_HEAD_3(79003,"class-head");
const struct yyrule CLASS_HEAD_4(79004,"class-head");

const struct yyrule CLASS_KEY_1(80001,"class-key");
const struct yyrule CLASS_KEY_2(80002,"class-key");
const struct yyrule CLASS_KEY_3(80003,"class-key");

const struct yyrule MEMBER_SPEC_1(81001,"member-spec");
const struct yyrule MEMBER_SPEC_2(81002,"member-spec");

const struct yyrule MEMBER_DECL_1(82001,"member-decl");
const struct yyrule MEMBER_DECL_2(82002,"member-decl");
const struct yyrule MEMBER_DECL_3(82003,"member-decl");
const struct yyrule MEMBER_DECL_4(82004,"member-decl");
const struct yyrule MEMBER_DECL_5(82005,"member-decl");
const struct yyrule MEMBER_DECL_6(82006,"member-decl");
const struct yyrule MEMBER_DECL_7(82007,"member-decl");
const struct yyrule MEMBER_DECL_8(82008,"member-decl");

const struct yyrule MEMBER_DECL_LIST_1(83001,"member-decl-list");
const struct yyrule MEMBER_DECL_LIST_2(83002,"member-decl-list");

const struct yyrule MEMBER_DECLARATOR_1(84001,"member-declr");
const struct yyrule MEMBER_DECLARATOR_2(84002,"member-declr");
const struct yyrule MEMBER_DECLARATOR_3(84003,"member-declr");
const struct yyrule MEMBER_DECLARATOR_4(84004,"member-declr");

const struct yyrule PURE_SPECIFIER_1(85001,"pure-spec");

const struct yyrule CONST_INITIALIZER_1(86001,"const-init");

/* Derived Classes */

const struct yyrule BASE_CLAUSE_1(87001,"base-clause");

const struct yyrule BASE_SPECIFIER_LIST_1(88001,"base-spec-list");
const struct yyrule BASE_SPECIFIER_LIST_2(88002,"base-spec-list");

const struct yyrule BASE_SPECIFIER_1(89001,"base-spec");
const struct yyrule BASE_SPECIFIER_2(89002,"base-spec");
const struct yyrule BASE_SPECIFIER_3(89003,"base-spec");
const struct yyrule BASE_SPECIFIER_4(89004,"base-spec");
const struct yyrule BASE_SPECIFIER_5(89005,"base-spec");
const struct yyrule BASE_SPECIFIER_6(89006,"base-spec");
const struct yyrule BASE_SPECIFIER_7(89007,"base-spec");
const struct yyrule BASE_SPECIFIER_8(89008,"base-spec");
const struct yyrule BASE_SPECIFIER_9(89009,"base-spec");
const struct yyrule BASE_SPECIFIER_10(89010,"base-spec");
const struct yyrule BASE_SPECIFIER_11(89011,"base-spec");
const struct yyrule BASE_SPECIFIER_12(89012,"base-spec");

const struct yyrule ACCESS_SPECIFIER_1(90001,"access-spec");
const struct yyrule ACCESS_SPECIFIER_2(90002,"access-spec");
const struct yyrule ACCESS_SPECIFIER_3(90003,"access-spec");

/* Special Member Functions */

const struct yyrule CONV_FUNC_ID_1(91001,"conv-func-id");

const struct yyrule CONV_TYPE_ID_1(92001,"conv-type-id");

const struct yyrule CONV_DECLARATOR_1(93001,"conv-declr");

const struct yyrule CTOR_INIT_1(94001,"ctor-init");

const struct yyrule MEM_INIT_LIST_1(95001,"mem-init-list");
const struct yyrule MEM_INIT_LIST_2(95002,"mem-init-list");

const struct yyrule MEM_INIT_1(96001,"mem-init");

const struct yyrule MEM_INIT_ID_1(97001,"mem-init-id");
const struct yyrule MEM_INIT_ID_2(97002,"mem-init-id");
const struct yyrule MEM_INIT_ID_3(97003,"mem-init-id");
const struct yyrule MEM_INIT_ID_4(97004,"mem-init-id");
const struct yyrule MEM_INIT_ID_5(97005,"mem-init-id");

/* Overloading */
const struct yyrule OP_FUNC_ID_1(98001,"op-func-id");

const struct yyrule OP_1(99001,"operator");
const struct yyrule OP_2(99002,"operator");
const struct yyrule OP_3(99003,"operator");
const struct yyrule OP_4(99004,"operator");
const struct yyrule OP_5(99005,"operator");
const struct yyrule OP_6(99006,"operator");
const struct yyrule OP_7(99007,"operator");
const struct yyrule OP_8(99008,"operator");
const struct yyrule OP_9(99009,"operator");
const struct yyrule OP_10(99010,"operator");
const struct yyrule OP_11(99011,"operator");
const struct yyrule OP_12(99012,"operator");
const struct yyrule OP_13(99013,"operator");
const struct yyrule OP_14(99014,"operator");
const struct yyrule OP_15(99015,"operator");
const struct yyrule OP_16(99016,"operator");
const struct yyrule OP_17(99017,"operator");
const struct yyrule OP_18(99018,"operator");
const struct yyrule OP_19(99019,"operator");
const struct yyrule OP_20(99020,"operator");
const struct yyrule OP_21(99021,"operator");
const struct yyrule OP_22(99022,"operator");
const struct yyrule OP_23(99023,"operator");
const struct yyrule OP_24(99024,"operator");
const struct yyrule OP_25(99025,"operator");
const struct yyrule OP_26(99026,"operator");
const struct yyrule OP_27(99027,"operator");
const struct yyrule OP_28(99028,"operator");
const struct yyrule OP_29(99029,"operator");
const struct yyrule OP_30(99030,"operator");
const struct yyrule OP_31(99031,"operator");
const struct yyrule OP_32(99032,"operator");
const struct yyrule OP_33(99033,"operator");
const struct yyrule OP_34(99034,"operator");
const struct yyrule OP_35(99035,"operator");
const struct yyrule OP_36(99036,"operator");
const struct yyrule OP_37(99037,"operator");
const struct yyrule OP_38(99038,"operator");
const struct yyrule OP_39(99039,"operator");
const struct yyrule OP_40(99040,"operator");
const struct yyrule OP_41(99041,"operator");
const struct yyrule OP_42(99042,"operator");

/* Templates */

const struct yyrule TEMPLATE_DECL_1(100001,"template-decl");

const struct yyrule TEMPLATE_PARAM_LIST_1(101001,"tpl-param-list");
const struct yyrule TEMPLATE_PARAM_LIST_2(101002,"tpl-param-list");

const struct yyrule TEMPLATE_PARAM_1(102001,"tpl-param");
const struct yyrule TEMPLATE_PARAM_2(102002,"tpl-param");

const struct yyrule TYPE_PARAM_1(103001,"type-param");
const struct yyrule TYPE_PARAM_2(103002,"type-param");
const struct yyrule TYPE_PARAM_3(103003,"type-param");
const struct yyrule TYPE_PARAM_4(103004,"type-param");
const struct yyrule TYPE_PARAM_5(103005,"type-param");
const struct yyrule TYPE_PARAM_6(103006,"type-param");

const struct yyrule TEMPLATE_ID_1(104001,"template-id");

const struct yyrule TEMPLATE_ARG_LIST_1(105001,"tpl-arg-list");
const struct yyrule TEMPLATE_ARG_LIST_2(105002,"tpl-arg-list");

const struct yyrule TEMPLATE_ARG_1(106001,"tpl-arg");
const struct yyrule TEMPLATE_ARG_2(106002,"tpl-arg");
const struct yyrule TEMPLATE_ARG_3(106003,"tpl-arg");

const struct yyrule EXPLICIT_INSTANTIATION_1(107001,"expl-instant");

const struct yyrule EXPLICIT_SPECIALIZATION_1(108001,"expl-special");

/* Exception Handling */
const struct yyrule TRY_BLOCK_1(109001,"try-block");

const struct yyrule FUNC_TRY_BLOCK_1(110001,"try-func-block");

const struct yyrule HANDLER_SEQ_1(111001,"handler-seq");

const struct yyrule HANDLER_1(112001,"handler");

const struct yyrule EXCEPTION_DECL_1(113001,"exception-decl");
const struct yyrule EXCEPTION_DECL_2(113002,"exception-decl");
const struct yyrule EXCEPTION_DECL_3(113003,"exception-decl");
const struct yyrule EXCEPTION_DECL_4(113004,"exception-decl");

const struct yyrule THROW_EXPR_1(114001,"throw-expr");

const struct yyrule EXCEPTION_SPEC_1(115001,"exception-spec");

const struct yyrule TYPE_ID_LIST_1(116001,"type-id-list");
const struct yyrule TYPE_ID_LIST_2(116002,"type-id-list");

/* Epsilon defintions */

const struct yyrule DECL_SEQ_OPT_1(117001,"decl-seq-opt");
const struct yyrule NESTED_NAME_SPEC_OPT_1(118001,"nested-name-spec-opt");
const struct yyrule EXPR_LIST_OPT_1(119001,"expr-list-opt");
const struct yyrule SCOPE_RESOLUTION_OPT_1(120001,"scope-res-opt");
const struct yyrule NEW_PLACEMENT_OPT_1(121001,"new-plcmt-opt");
const struct yyrule NEW_INIT_OPT_1(122001,"new-init-opt");
const struct yyrule NEW_DECL_OPT_1(123001,"new-decl-opt");
const struct yyrule EXPR_OPT_1(124001,"expr-opt");
const struct yyrule STMT_SEQ_OPT_1(125001,"stmt-seq-opt");
const struct yyrule COND_OPT_1(126001,"cond-opt");
const struct yyrule ENUM_LIST_OPT_1(127001,"enum-list-opt");
const struct yyrule INIT_OPT_1(128001,"init-opt");
const struct yyrule CONST_EXPR_OPT_1(129001,"const-expr-opt");
const struct yyrule ABSTRACT_DECL_OPT_1(130001,"abstract-decl-opt");
const struct yyrule TYPE_SPEC_SEQ_OPT_1(131001,"type-spec-seq-opt");
const struct yyrule DIRECT_ABSTRACT_DECL_OPT_1(132001,"direct-abst-decl-opt");
const struct yyrule CTOR_INIT_OPT_1(133001,"ctor-init-opt");
const struct yyrule COMMA_OPT_1(134001,"comma-opt");
const struct yyrule MEMBER_SPEC_OPT_1(135001,"member-spec-opt");
const struct yyrule SEMICOLON_OPT_1(136001,"semicolon-opt");
const struct yyrule CONVERSION_DECL_OPT_1(137001,"conv-decl-opt");
const struct yyrule EXPORT_OPT_1(138001,"export-opt");
const struct yyrule HANDLER_SEQ_OPT_1(139001,"handler-seq-opt");
const struct yyrule ASSIGN_EXPR_OPT_1(140001,"assign-expr-opt");
const struct yyrule TYPE_ID_LIST_OPT_1(141001,"type-id-list-opt");



#endif /* YY_PRODUCTION_RULES */