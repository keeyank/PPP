#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

#include "print_vec.h"

vector<int> get_totals(const vector<int>& p, const vector<int>& w) {
	if (p.size() != w.size())
		throw runtime_error("Bad size.");

	vector<int> tot(p.size());
	for (int i = 0; i < p.size(); ++i) {
		tot[i] = p[i]*w[i];
	}

	return tot;
}

int main() 
try {
	vector<int> prices;
	vector<int> weights;
	cout << "Give those prices!\n";
	for (int tmp; cin >> tmp;) {
		if (tmp <= 0)
			break;
		prices.push_back(tmp);
	}
	cout << "Give those weights!\n";
	for (int tmp; cin >> tmp;) {
		if (tmp <= 0)
			break;
		weights.push_back(tmp);
	}

	vector<int> totals = get_totals(prices, weights);

	print_vec("Total price: ", totals)

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}