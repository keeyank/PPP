#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

/*
Some false starts:
We can't do this by simply switching the int and string
in map<string, int> because the integer keys won't be unique.
There will be a lot of words with frequency 1, 2, etc. Plus,
every word starts out with frequency 0.

We can't add a Map_cmp function object (or functor) because
the comparison used by the Map class only involves the key, not
the pair<key, val>. Makes sense too, because you may update the
val (how would it keep the map sorted then?) but you can't update
the key.

What we could do is copy the map into a vector and sort the vector
with respect to the integer counts. We can't sort a map because
it uses a bidirectional iterator.
*/

// struct Map_cmp {
// 	bool operator()(const string& a, 
// 			const string& b) const
// 	{
// 		return a < b;
// 	}
// };

int main() {
	ifstream ifs {"words.txt"};
	ofstream ofs {"words_out.txt"};

	map<string, int> m;

	for (string tmp; ifs >> tmp;) {
		++m[tmp];
	}

	vector<pair<string, int>> v(m.size());
	copy(m.begin(), m.end(), v.begin());
	sort(v.begin(), v.end(), 
		[](const pair<string,int>& a, const pair<string,int>& b)
		{return a.second > b.second;});

	for (const auto& p : v) {
		ofs << p.second << ": " << p.first << endl;
	}

	return 0;
}