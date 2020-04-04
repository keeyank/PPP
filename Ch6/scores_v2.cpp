#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// This is (almost) an ordered pair from the set S x R.
// However, the comparisons for ordered pairs aren't normally defined 
// this way, so it's not actually an ordered pair.
class Name_value {
public:
	string name;
	double val;
	friend bool operator<(const Name_value &l, const Name_value &r) {
		return l.name < r.name;
	}
	friend bool operator==(const Name_value &l, const Name_value &r) {
		return l.name == r.name;
	}
	string tostring() {
		return "(" + name + "," + to_string(val) + ")";
	}
};



int main() 
try {

	cout << "Enter the names and scores\n";

	// Populate vectors
	vector<Name_value> nvs;
	string tmp_name;
	double tmp_val;
	while (cin >> tmp_name >> tmp_val) {
		if (tmp_name == "NoName")
			break;
		Name_value nv {tmp_name, tmp_val};
		nvs.push_back(nv);
	}
	if (!cin) 
		throw runtime_error("Invalid input.");

	// Check for uniqueness
	vector<Name_value> nvs_sorted = nvs;
	sort(nvs_sorted.begin(), nvs_sorted.end());
	for (int i = 1; i < nvs_sorted.size(); ++i) {
		if (nvs_sorted[i] == nvs_sorted[i-1]) 
			throw runtime_error("Duplicate name detected.");
	}

	// Print vectors
	cout << "{";
	for (Name_value nv : nvs) {
		cout << nv.tostring() << ", ";
	}
	cout << "\b\b}\n";

	cout << "Enter a name\n";
	string name_query;
	cin >> name_query;

	// Search for name and score
	int i = 0;
	bool name_found = false;
	while (i < nvs.size() && !name_found) {
		if (name_query == nvs[i].name) {
			cout << nvs[i].tostring() << '\n';
			name_found = true;
		}
		++i;
	}
	if (!name_found) {
		cout << "Name not found.\n";
	}

	cout << "Enter a score\n";
	float score_query;
	cin >> score_query;

	// Search for any names with specified score
	i = 0;
	bool score_found = false;
	while (i < nvs.size()) {
		if (nvs[i].val == score_query) {
			cout << nvs[i].tostring() << '\n';
			score_found = true;
		}
		++i;
	}
	if (!score_found) {
		cout << "Score not found.\n";
	}

	return 0;
}
catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
}
catch (...) {
    cerr << "exception \n";
    return 2;
}