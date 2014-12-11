#include <string>
#include <iostream>

using namespace std;

int ret_five(float y);

class cat {
private:
	string name;
	int number_of_legs;
public:
	cat(int legs) {
		this->number_of_legs = legs;
	}
	void meow();
	void eat();
	string get_name(float foo);
};

int main() {
	cat Momo(4);
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