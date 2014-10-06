#include <iostream>
using namespace std;

double myfunc(double xxxxxxxxxx, double y);
double goof(double);


int main()
{
double x, y;
	double z;
	z = myfunc(x, y);
	cout << "zed was " << z << endl;
	return 0;
}


double myfunc(double xxxxxxxxxx, double yyyyyyyyyy)
{
	xxxxxxxxxx = goof(2.0);
	return xxxxxxxxxx;
}

double goof(double branflakes)
{
    double bf2 = branflakes + 2.0;
    cout << "bf2 is " << bf2 << endl;
    return goof(bf2);
}
