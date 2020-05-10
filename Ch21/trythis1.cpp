#include <vector>
#include <list>
#include <iostream>
#include <numeric>

using namespace std;

struct R {
	double unit_price;
	int units;
};

int main() {
	list<R> l {R{4.2,2},R{1.99,5}, R{10.50,1}};
	double accum = 0;
	accum = accumulate(l.begin(), l.end(), accum,
			[](double a, R r) 
			{return a + (r.unit_price*r.units);});
	cout << accum << endl;
	return 0;
}