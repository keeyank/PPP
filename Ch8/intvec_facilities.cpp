#include <vector>
#include <iostream>
#include <string>

using namespace std;

#include "intvec_facilities.h"

void print_vec(const string& label, const vector<int>& vec) {
	cout << label << "{";
	for (int i = 0; i < vec.size(); ++i) {
		cout << vec[i];
		if (i != vec.size()-1) 
			cout << ", ";
	}
	cout << "}\n";

	return;
}

int maxv(const vector<int>& v) {
	int max = v[0];
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] > max) {
			max = v[i];
		}
	}
	return max;
}

int minv(const vector<int>& v) {
	int max = v[0];
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] < max) {
			max = v[i];
		}
	}
	return max;
}

double median(vector<int> v) {
	sort(v.begin(), v.end());

	if (v.size()%2 == 0) {
		int index = v.size()/2;
		return (v[index] + v[index-1])/2.0;
	}

	else { // v.size()%2 == 1
		int index = v.size()/2;
		return v[index];
	}
}

double mean(const vector<int>& v) {
	int sum = 0;
	for (const int& elem : v) {
		sum += elem;
	}
	return (double)sum/v.size();
}

Stats get_stats(const vector<int>& v) {
	if (v.size() == 0)
		throw runtime_error("maxv: Vector cannot be empty.");
	return Stats {maxv(v), minv(v), mean(v), median(v)};
}