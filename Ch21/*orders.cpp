#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <numeric>

using namespace std;

/* 
The main stuff you want to review is in main function
*/

/*********************************************************/

struct Purchase {
	string name = "DEFAULT";
	double unit_price = -1;
	int count = -1;
};

istream& operator>>(istream& is, Purchase& p) {
	Purchase tmp;
	is >> tmp.name >> tmp.unit_price >> tmp.count;
	if (is) p = tmp;
	return is;
}

ostream& operator<<(ostream& os, const Purchase& p) {
	return os << p.name << ' ' << p.unit_price << ' ' << p.count;
}

/*********************************************************/

struct Order {
	string name = "DEFAULT";
	string address = "DEFAULT";
	vector<Purchase> data;
};

void eat_space(istream& is) {
	char c = ' ';
	while (is && isspace(c)) is.get(c);
	if (is) is.putback(c);
}

istream& operator>>(istream& is, Order& o) {
	char c = 0; 
	eat_space(is);
	is.get(c);
	if (c != '{') is.clear(ios_base::failbit);


	Order tmp;
	is >> tmp.name >> tmp.address;
	eat_space(is);
	is.get(c);
	if (c != '{') is.clear(ios_base::failbit);

	while (is && c != '}') {
		Purchase p;
		is >> p;
		tmp.data.push_back(p);

		eat_space(is);
		is.get(c);
		if (c != '}') is.putback(c);
	}

	eat_space(is);
	is.get(c);
	if (c != '}') is.clear(ios_base::failbit);

	if (is) o = tmp;
	return is;
}

ostream& operator<<(ostream& os, const Order& o) {
	os << "{\n\t" << o.name << "\n\t" << o.address << "\n\t{";
	for (const Purchase& p : o.data) {
		os << "\n\t\t" << p;
	}
	return os << "\n\t}\n}";
}

/*********************************************************/

struct Order_cmp {
	bool operator()(const Order& a, const Order& b) const {
		return a.name < b.name;
	}
};

// Accumlate within accumulate, accumulateception LOL
double Order_sum(double sum, const Order& o) {
	return accumulate(o.data.begin(), o.data.end(), sum, 
		[](double sum, const Purchase& p)
		{return sum + p.unit_price*p.count;});
}

/*********************************************************/

int main() {

	// File 1
	ifstream ifs {"orders_data.txt"};
	ofstream ofs {"orders_data_out.txt"};
	istream_iterator<Order> ii {ifs};
	istream_iterator<Order> eos;
	ostream_iterator<Order> oi {ofs, "\n"};

	vector<Order> v {ii, eos};
	sort(v.begin(), v.end(), Order_cmp{});
	copy(v.begin(), v.end(), oi);

	// File 2
	ifstream ifs2 {"orders_data2.txt"};
	istream_iterator<Order> ii2 {ifs2};
	ostream_iterator<Order> oi2 {cout, "\n"};

	list<Order> l {ii2, eos};
	l.sort(Order_cmp{});
	copy(l.begin(), l.end(), oi2);

	// Merge files
	ofstream merge_ofs {"orders_merged_data_out.txt"};
	ostream_iterator<Order> merge_oi {merge_ofs, "\n"};
	merge(v.begin(), v.end(), l.begin(), l.end(), 
			merge_oi, Order_cmp{});

	vector<Order> v2 (v.size() + l.size());
	merge(v.begin(), v.end(), l.begin(), l.end(),
			v2.begin(), Order_cmp{});
	// Alternatively, we could have used an input_iterator with 
	// orders_merged_data_out.txt to get the data into v2

	double accum = 0;
	accum = accumulate(v2.begin(), v2.end(), accum, Order_sum);
	cout << accum << endl;
	return 0;
}