#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <numeric>
#include <string>
#include <functional>

using namespace std;

struct Price {
	double operator()(const pair<string,double>& a, 
			const pair<string,double>& b) 
	{
		return a.second * b.second;
	}
};

int main() {
	map<string, double> dow_price {
		{"MMM", 81.86},
		{"AA", 34.69},
		{"MO", 54.45}
	};
	map<string, double> dow_weight {
		{"MMM", 5.8549},
		{"AA", 2.4808},
		{"MO", 3.8940}
	};
	map<string, string> dow_name {
		pair<string, string>{"MMM", "3M Co."},
		pair<string, string>{"AA", "Alcoa Inc."},
		pair<string, string>{"MO", "Altria Group Inc."}
	};

	double alcoa_price = dow_price["AA"];
	cout << alcoa_price << endl;
	cout << dow_price.find("MO")->second << endl;

	for (const pair<string,double>& p : dow_price) {
		string name = p.first;
		cout << name << '\t' << p.second << '\t'
			<< dow_name[name] << endl;
	}

	double total = 0;
	total = inner_product(dow_price.begin(), dow_price.end(), 
			dow_weight.begin(), total, plus<double>{}, Price{});

	cout << total << endl;

	return 0;
}