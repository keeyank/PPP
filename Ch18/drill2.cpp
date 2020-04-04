#include <iostream>
#include <vector>

using namespace std;

vector<int> gv {1,2,4,8,16};

void f(const vector<int>& v) {
	vector<int> lv(v.size());
	lv = gv;
	for (int i = 0; i < lv.size(); ++i) {
		cout << lv[i] << ' ';
	}
	cout << endl;
	vector<int> lv2 {v};
	for (int i = 0; i < lv2.size(); ++i) {
		cout << lv2[i] << ' ';
	}
	cout << endl;
}

int main() {
	f(gv);
	f(vector<int> {1,2,3,4,5,6,7,8,9,10});
	return 0;
}



