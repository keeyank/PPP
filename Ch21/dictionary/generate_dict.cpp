#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <utility>

using namespace std;

/*********************************************************/

const map<string, pair<string,string>> contractions {
	{"don't", {"do", "not"}},
	{"isn't", {"is", "not"}},
	{"shouldn't", {"should", "not"}},
	{"can't", {"can", "not"}},
	{"won't", {"will", "not"}},
	{"musn't", {"must", "not"}},
	{"willn't", {"will", "not"}},
	{"shan't", {"shall", "not"}},
	{"wouldn't", {"would", "not"}},
	{"couldn't", {"could", "not"}},
	{"doesn't", {"does", "not"}},
	{"that's", {"that", "is"}},
	{"that'll", {"that", "will"}},
	{"that'd", {"that", "would"}},
	{"it's", {"it", "is"}},
	{"it'd", {"it", "would"}},
	{"it'll", {"it", "will"}},
	{"i'll", {"i", "will"}},
	{"i'd", {"i", "would"}},
	{"i'm", {"i", "am"}},
	{"you're", {"you", "are"}},
	{"you'd", {"you", "would"}},
	{"you'll", {"you", "will"}},
	{"she's", {"she", "is"}},
	{"she'd", {"she", "would"}},
	{"she'll", {"she", "will"}},
	{"he's", {"he", "is"}},
	{"he'd", {"he", "would"}},
	{"he'll", {"he", "will"}},
	{"they're", {"they", "are"}},
	{"they'd", {"they", "would"}},
	{"they'll", {"they", "will"}},
	{"we're", {"we", "are"}},
	{"we'd", {"we", "would"}},
	{"we'll", {"we", "will"}},
	{"this'll", {"this", "will"}},
	{"that'll", {"that", "will"}},
	{"there's", {"there", "is"}},
};

/*********************************************************/

/* 
First pass converts to lowercase, omits spaces and punct, and
expands contractions. Does not omit apostrophe.
*/
list<string> generate_intermed_pass1(ifstream& ifs) {
	list<string> im {""}; // intermediary list representing file
	char c {};

	// First Pass ()
	while (ifs.get(c)) {
		if (isalnum(c) || c == '\'') {
			c = tolower(c);
			im.back() += c;
		}
		else if (im.back() != "") { // && !isalnum(c) && c != '\''
			auto contr = contractions.find(im.back());
			if (contr != contractions.end()) {
				*(--im.end()) = contr->second.first;
				im.push_back(contr->second.second);
			}
			im.push_back("");
		}
	}

	if (im.back() == "") im.erase(--im.end());
	return im;
}

/*
Second pass. Remove's apostrophe, and adds each apostrophe-less string
to the set of all words.
*/
list<string> generate_intermed_pass2(const list<string>& old_im) {
	list<string> im {""};
	for (const string& s : old_im) {
		for (const char& c : s) {
			if (c != '\'') im.back() += c;
			else if (im.back() != "") im.push_back("");
		}
		if (im.back() != "") im.push_back("");
	}
	im.erase(--im.end());
	return im;
}

/* 
generate intermediary list holding words for further 
processing. Requires 2 full passes of the data in ifs.
*/
list<string> generate_intermed(ifstream& ifs) {
	list<string> intermed = generate_intermed_pass1(ifs);
	return generate_intermed_pass2(intermed);
}

/*
Generate the map based on ls.
*/
map<string, int> generate_map(list<string>& ls) {
	map<string, int> m;
	for (string word : ls) ++m[word];
	return m;
}

/*
Generate dictionary file based on dict map
(AKA, move our in-memory data structure onto the disk).
Put this in file called dict.txt
*/
void generate_dict(map<string, int> m) {
	ofstream ofs {"dict.txt"};
	for (const pair<string, int>& p : m) {
		ofs << p.first << ": " << p.second << endl;
	}
}

/*********************************************************/

int main() {
	ifstream ifs {"input.txt"};
	list<string> intermed {generate_intermed(ifs)};
	map<string, int> dict = generate_map(intermed);
	generate_dict(dict);

	return 0;
}