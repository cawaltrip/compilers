char plain_char;
char* char_ptr;

char* char_ptr_function();

char* char_ptr_function() {
	int x = 5;
	char *my_string = "Hi there";
	return my_string;
}

int non_ptr_function(int prm1) {
	int x = 3;
	return prm1;
}