#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

constexpr int w = 6;

int main() {
	ifstream ifs {"test.txt"};
	ofstream ofs {"16.txt"};

	vector<int> v;
	int i;
	while (true) {
		ifs >> i;
		if (ifs.eof()) {break;}
		else if (ifs.bad()) {return 1;}
		else if (ifs.fail()) {
			ifs.clear();
			ifs.get(); // Eat next char
			continue;
		}
		v.push_back(i);
	}

	sort(v.begin(), v.end());
	int count = 0;
	for (int i = 0; i < v.size(); ++i) {
		++count;
		if (i == v.size()-1 || v[i] != v[i+1]) {
			ofs << setw(w) << v[i] << ' ' 
				<< setw(w) << count << endl;
			count = 0;
		}
	}
	return 0;
}