#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int w = 8;

int main() {
	ifstream ifs {"test.txt"};
	int alnum = 0;
	int alpha = 0;
	int cntrl = 0;
	int graph = 0;
	int lower = 0;
	int print = 0;
	int space = 0;
	int upper = 0;


	for (char c; ifs.get(c);) {
		alnum += isalnum(c);
		alpha += isalpha(c);
		cntrl += iscntrl(c);
		graph += isgraph(c);
		lower += islower(c);
		print += isprint(c);
		space += isspace(c);
		upper += isupper(c);
	}

	ofstream ofs {"test.txt", ios_base::app};
	ofs << "\n\nalnum: " << alnum << endl
		<< "alpha: " << alpha << endl
		<< "cntrl: " << cntrl << endl
		<< "graph: " << graph << endl
		<< "lower: " << lower << endl
		<< "print: " << print << endl
		<< "space: " << space << endl
		<< "upper: " << upper << endl;

	return 0;
}