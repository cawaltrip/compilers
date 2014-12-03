int foobar(char c);

int main() {
  int x;
  int y = foobar('w');
}

int foobar(char c) {
	return c;
}

/*
Results:

func-decl-2 (188002,4)
  322: int
  direct-decl-5 (176005,4)
    258: foobar
    40: (
    param-decl-1 (187001,2)
      300: char
      258: c
    41: )
  cmpd-stmt-1 (141001,3)
    123: {
    jump-stmt-3 (147003,3)
      333: return
      258: c
      59: ;
    125: }
*/