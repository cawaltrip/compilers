#include <iostream>
#include <string>

using namespace std;

int times_two(int x);

int main(int argc, char argv) {
  char *my_string = "Hello world!";
  long long_var;
  short short_var = 2;
  //cout << my_string << endl;

  float f = pi();
  short_var = 2 + times_two(short_var);

  return 0;
}

float pi() {
  return 3.14159;
}

int times_two(int z) {
	int ret = z * 2;
	return ret;
}