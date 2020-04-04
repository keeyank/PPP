#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


int main() 
try {
	string s;
	cin >> s;
	int n = s.size();
	int num = 0;
	for (int i = 0; i < n; ++i) {
		int j = n-i-1;
		num += (s[i]-'0') * pow(10,j);
		cout << num << '\n';
	}
	cout << num << '\n';
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