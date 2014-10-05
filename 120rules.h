/* Token type.  */
#ifndef YY_PRODUCTION_RULES
#define YY_PRODUCTION_RULES

#include <string>

typedef struct yyrule { 
	int num;
	std::string text;
	yyrule(int n, std::string s) : num(n), text(s) { }
} yyrule;

const struct yyrule START_RULE(10000,"Start Symbol");

const struct yyrule TYPEDEF_NAME_1(11001, "Typedef Name");
const struct yyrule NAMESPACE_NAME_1(11002, "Namespace Name");
const struct yyrule ORIG_NAMESPACE_NAME_1(11003, "Orig. Namespace Name");
const struct yyrule CLASS_NAME_1(11004, "Class Name");
const struct yyrule ENUM_NAME_1(11005, "Enumerated Name");
const struct yyrule TEMPLATE_NAME_1(11006, "Template Name");

/* Lexical Elements */
const struct yyrule IDENTIFIER_1(12001, "Identifier");

const struct yyrule LITERAL_1(13001,"Integer Literal");
const struct yyrule LITERAL_2(13002,"Character Literal");
const struct yyrule LITERAL_3(13003,"Floating Literal");
const struct yyrule LITERAL_4(13004,"String Literal");
const struct yyrule LITERAL_5(13005,"Boolean Literal");

const struct yyrule INTEGER_LITERAL_1(14001,"Integer Literal Value");
const struct yyrule CHARACTER_LITERAL_1(14002,"Character Literal Value");
const struct yyrule FLOATING_LITERAL_1(14003,"Floating Literal Value");
const struct yyrule STRING_LITERAL_1(14004,"String Literal Value");
const struct yyrule BOOLEAN_LITERAL_1(14005,"Boolean Literal Value");

/* Expressions */
const struct yyrule PRIMARY_EXPRESSION_1(15001,"Primary - Literal");
const struct yyrule PRIMARY_EXPRESSION_2(15002,"Primary - THIS");
const struct yyrule PRIMARY_EXPRESSION_3(15003,"Primary - Parens");
const struct yyrule PRIMARY_EXPRESSION_4(15004,"Primary - ID expression");

const struct yyrule ID_EXPRESSION_1(16001,"ID Expression - Unqualified");
const struct yyrule ID_EXPRESSION_2(16002,"ID Expression - Qualified");

const struct yyrule UNQUALIFIED_ID_1(17001,"Unqualified - Identifier");
const struct yyrule UNQUALIFIED_ID_2(17002,"Unqualified - Operator Func ID");
const struct yyrule UNQUALIFIED_ID_3(17003,"Unqualified - Conversion Func ID");
const struct yyrule UNQUALIFIED_ID_4(17004,"Unqualified - ~ClassName");

const struct yyrule QUALIFIED_ID_1(18001,"Qualified - Non-template");
const struct yyrule QUALIFIED_ID_2(18002,"Qualified - Template");

const struct yyrule NESTED_NAME_1(18001,"Nested name: Class 1");
const struct yyrule NESTED_NAME_2(18002,"Nested name: Namespace 1");
const struct yyrule NESTED_NAME_3(18003,"Nested name: Class 2");
const struct yyrule NESTED_NAME_4(18004,"Nested name: Namespace 2");

const struct yyrule POSTFIX_EXP_1(19001,"Postix Expr: 1");
const struct yyrule POSTFIX_EXP_2(19002,"Postix Expr: 2");
const struct yyrule POSTFIX_EXP_3(19003,"Postix Expr: 3");
const struct yyrule POSTFIX_EXP_4(19004,"Postix Expr: 4");
const struct yyrule POSTFIX_EXP_5(19005,"Postix Expr: 5");
const struct yyrule POSTFIX_EXP_6(19006,"Postix Expr: 6");
const struct yyrule POSTFIX_EXP_7(19007,"Postix Expr: 7");
const struct yyrule POSTFIX_EXP_8(19008,"Postix Expr: 8");
const struct yyrule POSTFIX_EXP_9(19009,"Postix Expr: 9");
const struct yyrule POSTFIX_EXP_10(19000,"Postix Expr: 10");
const struct yyrule POSTFIX_EXP_11(19001,"Postix Expr: 11");
const struct yyrule POSTFIX_EXP_12(19002,"Postix Expr: 12");
const struct yyrule POSTFIX_EXP_13(19003,"Postix Expr: 13");
const struct yyrule POSTFIX_EXP_14(19004,"Postix Expr: 14");
const struct yyrule POSTFIX_EXP_15(19005,"Postix Expr: 15");
const struct yyrule POSTFIX_EXP_16(19006,"Postix Expr: 16");
const struct yyrule POSTFIX_EXP_17(19007,"Postix Expr: 17");
const struct yyrule POSTFIX_EXP_18(19008,"Postix Expr: 18");

const struct yyrule EXP_LIST_1(20001,"Placeholder");
const struct yyrule EXP_LIST_2(20002,"Placeholder");

const struct yyrule UNARY_EXP_1(21001,"Placeholder");
const struct yyrule UNARY_EXP_2(21002,"Placeholder");
const struct yyrule UNARY_EXP_3(21003,"Placeholder");
const struct yyrule UNARY_EXP_4(21004,"Placeholder");
const struct yyrule UNARY_EXP_5(21005,"Placeholder");
const struct yyrule UNARY_EXP_6(21006,"Placeholder");
const struct yyrule UNARY_EXP_7(21007,"Placeholder");
const struct yyrule UNARY_EXP_8(21008,"Placeholder");
const struct yyrule UNARY_EXP_9(21009,"Placeholder");
const struct yyrule UNARY_EXP_10(21010,"Placeholder");

const struct yyrule UNARY_OP_1(22001,"Placeholder");
const struct yyrule UNARY_OP_2(22002,"Placeholder");
const struct yyrule UNARY_OP_3(22003,"Placeholder");
const struct yyrule UNARY_OP_4(22004,"Placeholder");

const struct yyrule NEW_EXP_1(23001,"Placeholder");
const struct yyrule NEW_EXP_2(23002,"Placeholder");
const struct yyrule NEW_EXP_3(23003,"Placeholder");
const struct yyrule NEW_EXP_4(23004,"Placeholder");

const struct yyrule NEW_PLACEMENT_1(24001,"Placeholder");

const struct yyrule NEW_TYPE_ID_1(25001,"Placeholder");

const struct yyrule NEW_DECL_1(26001,"Placeholder");
const struct yyrule NEW_DECL_2(26002,"Placeholder");

const struct yyrule DIRECT_NEW_DECL_1(27001,"Placeholder");
const struct yyrule DIRECT_NEW_DECL_2(27002,"Placeholder");

const struct yyrule NEW_INIT_1(28001,"Placeholder");

const struct yyrule DELETE_EXP_1(29001,"Placeholder");
const struct yyrule DELETE_EXP_2(29002,"Placeholder");
const struct yyrule DELETE_EXP_3(29003,"Placeholder");
const struct yyrule DELETE_EXP_4(29004,"Placeholder");

const struct yyrule CAST_EXP_1(30001,"Placeholder");
const struct yyrule CAST_EXP_2(30002,"Placeholder");

const struct yyrule PM_EXP_1(31001,"Placeholder");
const struct yyrule PM_EXP_2(31002,"Placeholder");
const struct yyrule PM_EXP_3(31003,"Placeholder");

const struct yyrule MULT_EXP_1(32001,"Placeholder");
const struct yyrule MULT_EXP_2(32002,"Placeholder");
const struct yyrule MULT_EXP_3(32003,"Placeholder");
const struct yyrule MULT_EXP_4(32004,"Placeholder");

const struct yyrule ADD_EXP_1(33001,"Placeholder");
const struct yyrule ADD_EXP_2(33002,"Placeholder");
const struct yyrule ADD_EXP_3(33003,"Placeholder");

const struct yyrule SHIFT_EXP_1(34001,"Placeholder");
const struct yyrule SHIFT_EXP_2(34002,"Placeholder");
const struct yyrule SHIFT_EXP_3(34003,"Placeholder");

const struct yyrule RELATIONAL_EXP_1(35001,"Placeholder");
const struct yyrule RELATIONAL_EXP_2(35002,"Placeholder");
const struct yyrule RELATIONAL_EXP_3(35003,"Placeholder");
const struct yyrule RELATIONAL_EXP_4(35004,"Placeholder");
const struct yyrule RELATIONAL_EXP_5(35005,"Placeholder");

const struct yyrule EQ_EXP_1(36001,"Placeholder");
const struct yyrule EQ_EXP_2(36002,"Placeholder");
const struct yyrule EQ_EXP_3(36003,"Placeholder");

const struct yyrule AND_EXP_1(37001,"Placeholder");
const struct yyrule AND_EXP_2(37002,"Placeholder");

const struct yyrule XOR_EXP_1(38001,"Placeholder");
const struct yyrule XOR_EXP_2(38002,"Placeholder");

const struct yyrule OR_EXP_1(39001,"Placeholder");
const struct yyrule OR_EXP_2(39002,"Placeholder");

const struct yyrule LOGICAL_AND_EXP_1(40001,"Placeholder");
const struct yyrule LOGICAL_AND_EXP_2(40002,"Placeholder");

const struct yyrule LOGICAL_OR_EXP_1(41001,"Placeholder");
const struct yyrule LOGICAL_OR_EXP_2(41002,"Placeholder");

const struct yyrule CONDITIONAL_EXP_1(42001,"Placeholder");
const struct yyrule CONDITIONAL_EXP_2(42002,"Placeholder");

const struct yyrule ASSIGN_EXP_1(43001,"Placeholder");
const struct yyrule ASSIGN_EXP_2(43002,"Placeholder");
const struct yyrule ASSIGN_EXP_3(43003,"Placeholder");

const struct yyrule ASSIGN_OP_1(44001,"Placeholder");
const struct yyrule ASSIGN_OP_2(44002,"Placeholder");
const struct yyrule ASSIGN_OP_3(44003,"Placeholder");
const struct yyrule ASSIGN_OP_4(44004,"Placeholder");
const struct yyrule ASSIGN_OP_5(44005,"Placeholder");
const struct yyrule ASSIGN_OP_6(44006,"Placeholder");
const struct yyrule ASSIGN_OP_7(44007,"Placeholder");
const struct yyrule ASSIGN_OP_8(44008,"Placeholder");
const struct yyrule ASSIGN_OP_9(44009,"Placeholder");
const struct yyrule ASSIGN_OP_10(44010,"Placeholder");
const struct yyrule ASSIGN_OP_11(44011,"Placeholder");

const struct yyrule EXPRESSION_1(45001,"Placeholder");
const struct yyrule EXPRESSION_2(45002,"Placeholder");

const struct yyrule CONSTANT_EXPRESSION_1(46001,"Placeholder");

/* Statements */

const struct yyrule STMT_1(47001,"Placeholder");
const struct yyrule STMT_2(47002,"Placeholder");
const struct yyrule STMT_3(47003,"Placeholder");
const struct yyrule STMT_4(47004,"Placeholder");
const struct yyrule STMT_5(47005,"Placeholder");
const struct yyrule STMT_6(47006,"Placeholder");
const struct yyrule STMT_7(47007,"Placeholder");
const struct yyrule STMT_8(47008,"Placeholder");

const struct yyrule LABELED_STMT_1(48001,"Placeholder");
const struct yyrule LABELED_STMT_2(48002,"Placeholder");
const struct yyrule LABELED_STMT_3(48003,"Placeholder");

const struct yyrule EXPR_STMT_1(49001,"Placeholder");

const struct yyrule COMPOUND_STMT_1(50001,"Placeholder");

const struct yyrule STMT_SEQ_1(51001,"Placeholder");
const struct yyrule STMT_SEQ_2(51002,"Placeholder");

const struct yyrule SELECTION_STMT_1(52001,"Placeholder");
const struct yyrule SELECTION_STMT_2(52002,"Placeholder");
const struct yyrule SELECTION_STMT_3(52003,"Placeholder");

const struct yyrule CONDITION_1(53001,"Placeholder");
const struct yyrule CONDITION_2(53002,"Placeholder");

const struct yyrule ITER_STMT_1(54001,"Placeholder");
const struct yyrule ITER_STMT_2(54002,"Placeholder");
const struct yyrule ITER_STMT_3(54003,"Placeholder");
const struct yyrule ITER_STMT_4(54004,"Placeholder");

const struct yyrule FOR_INIT_STMT_1(55001,"Placeholder");
const struct yyrule FOR_INIT_STMT_2(55002,"Placeholder");

const struct yyrule JUMP_STMT_1(56001,"Placeholder");
const struct yyrule JUMP_STMT_2(56002,"Placeholder");
const struct yyrule JUMP_STMT_3(56003,"Placeholder");
const struct yyrule JUMP_STMT_4(56004,"Placeholder");

const struct yyrule DECL_STMT_1(57001,"Placeholder");

/* Declarations */

const struct yyrule INIT_DECL_LIST_1(58001,"Placeholder");
const struct yyrule INIT_DECL_LIST_2(58002,"Placeholder");

const struct yyrule INIT_DECL_1(59001,"Placeholder");

const struct yyrule DECL_1(60001,"Placeholder");
const struct yyrule DECL_2(60002,"Placeholder");

const struct yyrule DIRECT_DECL_1(61001,"Placeholder");
const struct yyrule DIRECT_DECL_2(61002,"Placeholder");
const struct yyrule DIRECT_DECL_3(61003,"Placeholder");
const struct yyrule DIRECT_DECL_4(61004,"Placeholder");
const struct yyrule DIRECT_DECL_5(61005,"Placeholder");
const struct yyrule DIRECT_DECL_6(61006,"Placeholder");
const struct yyrule DIRECT_DECL_7(61007,"Placeholder");

const struct yyrule PTR_OP_1(62001,"Placeholder");
const struct yyrule PTR_OP_2(62002,"Placeholder");
const struct yyrule PTR_OP_3(62003,"Placeholder");
const struct yyrule PTR_OP_4(62004,"Placeholder");
const struct yyrule PTR_OP_5(62005,"Placeholder");
const struct yyrule PTR_OP_6(62006,"Placeholder");
const struct yyrule PTR_OP_7(62007,"Placeholder");

const struct yyrule CV_QUAL_SEQ_1(63001,"Placeholder");
const struct yyrule CV_QUAL_SEQ_2(63002,"Placeholder");

const struct yyrule CV_QUAL_1(64001,"Placeholder");

const struct yyrule DECL_ID_1(65001,"Placeholder");
const struct yyrule DECL_ID_2(65002,"Placeholder");
const struct yyrule DECL_ID_3(65003,"Placeholder");
const struct yyrule DECL_ID_4(65004,"Placeholder");

const struct yyrule TYPE_ID_1(66001,"Placeholder");

const struct yyrule TYPE_SPECIFIER_SEQ_1(67001,"Placeholder");

const struct yyrule ABSTRACT_DECL_1(68001,"Placeholder");
const struct yyrule ABSTRACT_DECL_2(68002,"Placeholder");

const struct yyrule DIRECT_ABSTRACT_DECL_1(69001,"Placeholder");
const struct yyrule DIRECT_ABSTRACT_DECL_2(69002,"Placeholder");
const struct yyrule DIRECT_ABSTRACT_DECL_3(69003,"Placeholder");
const struct yyrule DIRECT_ABSTRACT_DECL_4(69004,"Placeholder");
const struct yyrule DIRECT_ABSTRACT_DECL_5(69005,"Placeholder");
const struct yyrule DIRECT_ABSTRACT_DECL_6(69006,"Placeholder");

const struct yyrule PARAM_DECL_CLAUSE_1(70001,"Placeholder");
const struct yyrule PARAM_DECL_CLAUSE_2(70002,"Placeholder");
const struct yyrule PARAM_DECL_CLAUSE_3(70003,"Placeholder");
const struct yyrule PARAM_DECL_CLAUSE_4(70004,"Placeholder");
const struct yyrule PARAM_DECL_CLAUSE_5(70005,"Placeholder");

const struct yyrule PARAM_DECL_LIST_1(71001,"Placeholder");
const struct yyrule PARAM_DECL_LIST_2(71002,"Placeholder");

const struct yyrule PARAM_DECL_1(72001,"Placeholder");
const struct yyrule PARAM_DECL_2(72002,"Placeholder");
const struct yyrule PARAM_DECL_3(72003,"Placeholder");
const struct yyrule PARAM_DECL_4(72004,"Placeholder");

const struct yyrule FUNC_DEF_1(73001,"Placeholder");
const struct yyrule FUNC_DEF_2(73002,"Placeholder");
const struct yyrule FUNC_DEF_3(73003,"Placeholder");
const struct yyrule FUNC_DEF_4(73004,"Placeholder");

const struct yyrule FUNC_BODY_1(74001,"Placeholder");

const struct yyrule INITIALIZOR_1(75001,"Placeholder");
const struct yyrule INITIALIZOR_2(75002,"Placeholder");

const struct yyrule INITIALIZOR_CLAUSE_1(76001,"Placeholder");
const struct yyrule INITIALIZOR_CLAUSE_2(76002,"Placeholder");
const struct yyrule INITIALIZOR_CLAUSE_3(76003,"Placeholder");

const struct yyrule INITIALIZOR_LIST_1(77001,"Placeholder");
const struct yyrule INITIALIZOR_LIST_2(77002,"Placeholder");

/* Classes */

const struct yyrule CLASS_SPECIFIER_1(78001,"Placeholder");

const struct yyrule CLASS_HEAD_1(79001,"Placeholder");
const struct yyrule CLASS_HEAD_2(79002,"Placeholder");
const struct yyrule CLASS_HEAD_3(79003,"Placeholder");
const struct yyrule CLASS_HEAD_4(79004,"Placeholder");

const struct yyrule CLASS_KEY_1(80001,"Placeholder");
const struct yyrule CLASS_KEY_2(80002,"Placeholder");
const struct yyrule CLASS_KEY_3(80003,"Placeholder");

const struct yyrule MEMBER_SPEC_1(81001,"Placeholder");
const struct yyrule MEMBER_SPEC_2(81002,"Placeholder");

const struct yyrule MEMBER_DECLARATION_1(82001,"Placeholder");
const struct yyrule MEMBER_DECLARATION_2(82002,"Placeholder");
const struct yyrule MEMBER_DECLARATION_3(82003,"Placeholder");
const struct yyrule MEMBER_DECLARATION_4(82004,"Placeholder");
const struct yyrule MEMBER_DECLARATION_5(82005,"Placeholder");
const struct yyrule MEMBER_DECLARATION_6(82006,"Placeholder");
const struct yyrule MEMBER_DECLARATION_7(82007,"Placeholder");
const struct yyrule MEMBER_DECLARATION_8(82008,"Placeholder");

const struct yyrule MEMBER_DECL_LIST_1(83001,"Placeholder");
const struct yyrule MEMBER_DECL_LIST_2(83002,"Placeholder");

const struct yyrule MEMBER_DECLARATOR_1(84001,"Placeholder");
const struct yyrule MEMBER_DECLARATOR_2(84002,"Placeholder");
const struct yyrule MEMBER_DECLARATOR_3(84003,"Placeholder");
const struct yyrule MEMBER_DECLARATOR_4(84004,"Placeholder");

const struct yyrule PURE_SPECIFIER_1(85001,"Placeholder");

const struct yyrule CONST_INITIALIZOR_1(86001,"Placeholder");

/* Derived Classes */

const struct yyrule BASE_CLAUSE_1(87001,"Placeholder");

const struct yyrule BASE_SPECIFIER_LIST_1(88001,"Placeholder");
const struct yyrule BASE_SPECIFIER_LIST_2(88002,"Placeholder");

const struct yyrule BASE_SPECIFIER_1(89001,"Placeholder");
const struct yyrule BASE_SPECIFIER_2(89002,"Placeholder");
const struct yyrule BASE_SPECIFIER_3(89003,"Placeholder");
const struct yyrule BASE_SPECIFIER_4(89004,"Placeholder");
const struct yyrule BASE_SPECIFIER_5(89005,"Placeholder");
const struct yyrule BASE_SPECIFIER_6(89006,"Placeholder");
const struct yyrule BASE_SPECIFIER_7(89007,"Placeholder");
const struct yyrule BASE_SPECIFIER_8(89008,"Placeholder");
const struct yyrule BASE_SPECIFIER_9(89009,"Placeholder");
const struct yyrule BASE_SPECIFIER_10(89010,"Placeholder");
const struct yyrule BASE_SPECIFIER_11(89011,"Placeholder");
const struct yyrule BASE_SPECIFIER_12(89012,"Placeholder");

const struct yyrule ACCESS_SPECIFIER_1(90001,"Placeholder");
const struct yyrule ACCESS_SPECIFIER_2(90002,"Placeholder");
const struct yyrule ACCESS_SPECIFIER_3(90003,"Placeholder");

/* Special Member Functions */

const struct yyrule CONV_FUNC_ID_1(91001,"Placeholder");

const struct yyrule CONV_TYPE_ID_1(92001,"Placeholder");

const struct yyrule CONV_DECLARATOR_1(93001,"Placeholder");

const struct yyrule CTOR_INIT_(94001,"Placeholder");

const struct yyrule MEM_INIT_LIST_1(95001,"Placeholder");
const struct yyrule MEM_INIT_LIST_2(95002,"Placeholder");

const struct yyrule MEM_INIT_1(96001,"Placeholder");

const struct yyrule MEM_INIT_ID_1(97001,"Placeholder");
const struct yyrule MEM_INIT_ID_2(97002,"Placeholder");
const struct yyrule MEM_INIT_ID_3(97003,"Placeholder");
const struct yyrule MEM_INIT_ID_4(97004,"Placeholder");
const struct yyrule MEM_INIT_ID_5(97005,"Placeholder");

/* Overloading */
const struct yyrule OP_FUNC_ID_1(98001,"Placeholder");

const struct yyrule OP_1(99001,"Placeholder");
const struct yyrule OP_2(99002,"Placeholder");
const struct yyrule OP_3(99003,"Placeholder");
const struct yyrule OP_4(99004,"Placeholder");
const struct yyrule OP_5(99005,"Placeholder");
const struct yyrule OP_6(99006,"Placeholder");
const struct yyrule OP_7(99007,"Placeholder");
const struct yyrule OP_8(99008,"Placeholder");
const struct yyrule OP_9(99009,"Placeholder");
const struct yyrule OP_10(99010,"Placeholder");
const struct yyrule OP_11(99011,"Placeholder");
const struct yyrule OP_12(99012,"Placeholder");
const struct yyrule OP_13(99013,"Placeholder");
const struct yyrule OP_14(99014,"Placeholder");
const struct yyrule OP_15(99015,"Placeholder");
const struct yyrule OP_16(99016,"Placeholder");
const struct yyrule OP_17(99017,"Placeholder");
const struct yyrule OP_18(99018,"Placeholder");
const struct yyrule OP_19(99019,"Placeholder");
const struct yyrule OP_20(99020,"Placeholder");
const struct yyrule OP_21(99021,"Placeholder");
const struct yyrule OP_22(99022,"Placeholder");
const struct yyrule OP_23(99023,"Placeholder");
const struct yyrule OP_24(99024,"Placeholder");
const struct yyrule OP_25(99025,"Placeholder");
const struct yyrule OP_26(99026,"Placeholder");
const struct yyrule OP_27(99027,"Placeholder");
const struct yyrule OP_28(99028,"Placeholder");
const struct yyrule OP_29(99029,"Placeholder");
const struct yyrule OP_30(99030,"Placeholder");
const struct yyrule OP_31(99031,"Placeholder");
const struct yyrule OP_32(99032,"Placeholder");
const struct yyrule OP_33(99033,"Placeholder");
const struct yyrule OP_34(99034,"Placeholder");
const struct yyrule OP_35(99035,"Placeholder");
const struct yyrule OP_36(99036,"Placeholder");
const struct yyrule OP_37(99037,"Placeholder");
const struct yyrule OP_38(99038,"Placeholder");
const struct yyrule OP_39(99039,"Placeholder");
const struct yyrule OP_40(99040,"Placeholder");
const struct yyrule OP_41(99041,"Placeholder");
const struct yyrule OP_42(99042,"Placeholder");

/* Templates */

const struct yyrule TEMPLATE_DECL_1(100001,"Placeholder");

const struct yyrule TEMPLATE_PARAM_LIST_1(101001,"Placeholder");
const struct yyrule TEMPLATE_PARAM_LIST_2(101002,"Placeholder");

const struct yyrule TEMPLATE_PARAM_1(102001,"Placeholder");
const struct yyrule TEMPLATE_PARAM_2(102002,"Placeholder");

const struct yyrule TYPE_PARAM_1(103001,"Placeholder");
const struct yyrule TYPE_PARAM_2(103002,"Placeholder");
const struct yyrule TYPE_PARAM_3(103003,"Placeholder");
const struct yyrule TYPE_PARAM_4(103004,"Placeholder");
const struct yyrule TYPE_PARAM_5(103005,"Placeholder");
const struct yyrule TYPE_PARAM_6(103006,"Placeholder");
const struct yyrule TYPE_PARAM_7(103007,"Placeholder");

const struct yyrule TEMPLATE_ID_1(104001,"Placeholder");

const struct yyrule TEMPLATE_ARG_LIST_1(105001,"Placeholder");
const struct yyrule TEMPLATE_ARG_LIST_2(105002,"Placeholder");

const struct yyrule TEMPLATE_ARG_1(106001,"Placeholder");
const struct yyrule TEMPLATE_ARG_2(106002,"Placeholder");
const struct yyrule TEMPLATE_ARG_3(106003,"Placeholder");

const struct yyrule EXPLICIT_INSTANTIATION_1(107001,"Placeholder");

const struct yyrule EXPLICIT_SPECIALIZATION_1(108001,"Placeholder");

/* Exception Handling */
const struct yyrule TRY_BLOCK_1(109001,"Placeholder");

const struct yyrule FUNC_TRY_BLOCK_1(110001,"Placeholder");

const struct yyrule HANDLER_SEQ_1(111001,"Placeholder");

const struct yyrule HANDLER_1(112001,"Placeholder");

const struct yyrule EXCEPTION_DECL_1(113001,"Placeholder");
const struct yyrule EXCEPTION_DECL_2(113002,"Placeholder");
const struct yyrule EXCEPTION_DECL_3(113003,"Placeholder");
const struct yyrule EXCEPTION_DECL_4(113004,"Placeholder");

const struct yyrule THROW_EXPR_1(114001,"Placeholder");

const struct yyrule EXCEPTION_SPEC_1(115001,"Placeholder");

const struct yyrule TYPE_ID_LIST_1(116001,"Placeholder");
const struct yyrule TYPE_ID_LIST_2(116002,"Placeholder");

/* Epsilon defintions */

const struct yyrule DECL_SEQ_OPT_1(117001,"Placeholder");
const struct yyrule NESTED_NAME_SPEC_OPT_1(118001,"Placeholder");
const struct yyrule EXPR_LIST_OPT_1(119001,"Placeholder");
const struct yyrule SCOPE_RESOLUTION_OPT_1(120001,"Placeholder");
const struct yyrule NEW_PLACEMENT_OPT_1(121001,"Placeholder");
const struct yyrule NEW_INIT_OPT_1(122001,"Placeholder");
const struct yyrule NEW_DECL_OPT_1(123001,"Placeholder");
const struct yyrule EXPR_OPT_1(124001,"Placeholder");
const struct yyrule STMT_SEQ_OPT_1(125001,"Placeholder");
const struct yyrule COND_OPT_1(126001,"Placeholder");
const struct yyrule ENUM_LIST_OPT_1(127001,"Placeholder");
const struct yyrule INIT_OPT_1(128001,"Placeholder");
const struct yyrule CONST_EXPR_OPT_1(129001,"Placeholder");
const struct yyrule ABSTRACT_DECL_OPT_1(130001,"Placeholder");
const struct yyrule TYPE_SPEC_SEQ_OPT_1(131001,"Placeholder");
const struct yyrule DIRECT_ABSTRACT_DECL_OPT_1(132001,"Placeholder");
const struct yyrule CTOR_INIT_OPT_1(133001,"Placeholder");
const struct yyrule COMMA_OPT_1(134001,"Placeholder");
const struct yyrule MEMBER_SPEC_OPT1(135001,"Placeholder");
const struct yyrule SEMICOLON_OPT_1(136001,"Placeholder");
const struct yyrule CONVERSION_DECL_OPT_1(137001,"Placeholder");
const struct yyrule EXPORT_OPT_1(138001,"Placeholder");
const struct yyrule HANDLER_SEQ_OPT_1(139001,"Placeholder");
const struct yyrule ASSIGN_EXPR_OPT_1(140001,"Placeholder");
const struct yyrule TYPE_ID_LIST_OPT_1(141001,"Placeholder");



#endif /* YY_PRODUCTION_RULES */