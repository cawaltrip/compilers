//int times_two(int x);
int times_two(int x) {
	int ret = x * 2;
	return ret;
}

/*
Results:

decl-seq-2 (149002,2)
  simple-decl-1 (152001,3)
    322: int
    init-decl-1 (174001,2)
      direct-decl-5 (176005,4)
        258: times_two
        40: (
        param-decl-1 (187001,2)
          322: int
          258: x
        41: )
    59: ;
  func-decl-2 (188002,4)
    322: int
    direct-decl-5 (176005,4)
      258: times_two
      40: (
      param-decl-1 (187001,2)
        322: int
        258: f
      41: )
    cmpd-stmt-1 (141001,3)
      123: {
      stmt-seq-2 (142002,2)
        simple-decl-1 (152001,3)
          322: int
          init-decl-1 (174001,2)
            258: ret
            init-1 (190001,2)
              61: =
              mult-expr-2 (123002,3)
                258: f
                42: *
                259: 2
          59: ;
        jump-stmt-3 (147003,3)
          333: return
          258: ret
          59: ;
      125: }
*/