/* 
 * This is a test file of a full-fledged program
 * to test my 120++ compiler.
 */

#include <string>
#include <iostream>

using namespace std;

int ret_five(float y);

class cat {
private:
	string name;
	int number_of_legs;
public:
	void meow();
	void eat();
	string get_name(float foo);
};

int main() {
	cat Momo;
	int x;
	float z = 7.7;

	cout << "My kitty is in this program!" << endl;
	//cout << ret_five(z); << endl;
	ret_five(z);

	return 0;
}

int ret_five(float y) {
	y += 3; // Does nothing
	return 5;
}