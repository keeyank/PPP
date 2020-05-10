#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <numeric>

using namespace std;

struct Item {
	string name;
	int id;
	double val;
};

istream& operator>>(istream& is, Item& i) {
	return is >> i.name >> i.id >> i.val;
}

ostream& operator<<(ostream& os, const Item& i) {
	return os << "(" << i.name << "," << i.id 
		<< "," << fixed << setprecision(2) 
		<< i.val << ")" << defaultfloat;
}

struct Item_cmp1 {
	bool operator()(const Item& i1, const Item& i2) {
		return i1.name < i2.name;
	}
};

struct Item_cmp2 {
	bool operator()(const Item& i1, const Item& i2) {
		return i1.id > i2.id;
	}
};

template<typename Key, typename Val>
void print_map(const map<Key, Val>& m) {
	for (const pair<Key, Val>& p : m) {
		cout << p.first << ": " << p.second << endl;
	}
}

void read_to_map(map<string,int>& m) {
	while (true) {
		string s;
		int i;
		cin >> s >> i;
		if (!cin) return;
		m[s] = i;
	}
}

struct map_add {
	int operator()(int a, const pair<string,int>& p) {
		return a + p.second;
	}
};

int main() {
	// {
	// ifstream ifs {"items.txt"};

	// istream_iterator<Item> ii {ifs};
	// istream_iterator<Item> eos;

	// ostream_iterator<Item> oi {cout, "\n"};


	
	// vector<Item> v{ii, eos};

	// sort(v.begin(), v.end(), Item_cmp1{});
	// sort(v.begin(), v.end(), Item_cmp2{});
	// sort(v.begin(), v.end(), 
	// 	[](Item& i1, Item& i2){return i1.val > i2.val;});

	// v.insert(v.begin(), Item{"horse-shoe",99,12.34});
	// v.insert(v.end(), Item{"Canon S400", 9988, 22.12});
	// //copy(v.begin(), v.end(), oi);	

	// vector<Item>::iterator itr =  find_if(v.begin(), v.end(),
	// 		[](Item& i) {return i.name == "horse-shoe";});
	// itr = v.erase(itr);
	// itr = v.erase(itr);
	// itr = find_if(v.begin(), v.end(), 
	// 		[](Item& i) {return i.id == 9988;});
	// itr = v.erase(itr);
	// //itr = v.erase(itr); // Segfault - attempted to erase end()
	// copy(v.begin(), v.end(), oi);
	

	// list<Item> v{ii, eos};

	// // // Uh oh, sort doesn't work for lists (requires random-access-iterator)
	// // sort(v.begin(), v.end(), Item_cmp1{});
	// // sort(v.begin(), v.end(), Item_cmp2{});
	// // sort(v.begin(), v.end(), 
	// // 	[](Item& i1, Item& i2){return i1.val > i2.val;});

	// v.insert(v.begin(), Item{"horse-shoe",99,12.34});
	// v.insert(v.end(), Item{"Canon S400", 9988, 22.12});
	// //copy(v.begin(), v.end(), oi);	

	// list<Item>::iterator itr =  find_if(v.begin(), v.end(),
	// 		[](Item& i) {return i.name == "horse-shoe";});
	// itr = v.erase(itr);
	// itr = v.erase(itr);
	// itr = find_if(v.begin(), v.end(), 
	// 		[](Item& i) {return i.id == 9988;});
	// itr = v.erase(itr);
	// //itr = v.erase(itr); // Segfault - attempted to erase end()
	// copy(v.begin(), v.end(), oi);
	// }
	/* 2 */
	// {
	// map<string, int> msi;
	// msi["tom"] = 21;
	// msi["msi"] = 194;
	// msi.insert(pair<string,int>{"wego",13013});
	// msi.insert(make_pair("starlo",43));
	// msi["blinker"] = -23;
	// // All of these have equivelant functionality
	// // see https://en.cppreference.com/w/cpp/container/map/operator_at
	// //print_map(msi);

	// msi.erase("tom");
	// msi.erase("blinker");
	// //print_map(msi);

	// //read_to_map(msi);
	// //print_map(msi);


	// /* MAKE SURE THAT b IS CONST!!! it doesn't work otherwise */
	// int accum = 0;
	// accum = accumulate(msi.begin(), msi.end(), accum, 
	// 		[](int a, const pair<string,int>& b)
	// 		{return a + b.second;});
	// cout << accum << endl;

	// map<int, string> mis;
	// for (const pair<string,int>& p : msi) {
	// 	mis[p.second] = p.first;
	// }
	// print_map(mis);
	// }

	/* 3 */
	{
		ifstream ifs{"data.txt"};
		istream_iterator<double> ii {ifs};
		istream_iterator<double> eos;
		vector<double> vd {ii, eos};

		ostream_iterator<double> oi {cout, "\n"};
		//copy(vd.begin(), vd.end(), oi);

		vector<int> vi {vd.begin(), vd.end()}; // Copy will implicitly
			// convert doubles to ints
		auto it1 = vi.begin();
		auto it2 = vd.begin();
		while (it1 != vi.end()) {
			cout << *it1 << '\t' << *it2 << endl;
			++it1; ++it2;
		}

		double accum = 0;
		accum = accumulate(vd.begin(), vd.end(), accum);
		cout << accum << endl;
		int accum2 = 0;
		accum2 = accumulate(vi.begin(), vi.end(), accum2);
		cout << accum2 << endl;
		cout << accum - accum2 << endl;
		reverse(vd.begin(), vd.end());
		//copy(vd.begin(), vd.end(), oi);

		double mean = accum/vd.size();
		cout << mean << endl;

		vector<double> vd2(vd.size());
		copy_if(vd.begin(), vd.end(), vd2.begin(), 
			[&](double d){return d>mean;});
		sort(vd2.begin(), vd2.end());
		copy(vd2.begin(), vd2.end(), oi);
	}

	return 0;
}