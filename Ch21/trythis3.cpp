#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <numeric>
#include <string>
#include <functional>
#include <fstream>

using namespace std;

int main() {
	ifstream is {"words.txt"};
	ofstream os {"words_out.txt"};

	istream_iterator<string> ii {is};
	istream_iterator<string> eos;
	ostream_iterator<string> oo {os, "\n"};

	vector<string> b {ii, eos};
	// vector<string> b(1); BADBADBADBADBADBAD
	// copy(ii, eos, b.begin()); NOTGOOD!!!
	sort(b.begin(), b.end());
	copy(b.begin(), b.end(), oo);
	return 0;
}