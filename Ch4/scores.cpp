#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {

	cout << "Enter the names and scores\n";

	// Populate vectors
	vector<string> names;
	vector<double> scores;
	string temp_name;
	int temp_score;
	while (cin >> temp_name >> temp_score) {
		if (temp_name == "NoName") {
			break;
		}

		names.push_back(temp_name);
		scores.push_back(temp_score);
	}

	// Check for uniqueness
	vector<string> names_sorted = names;
	sort(names_sorted.begin(), names_sorted.end());
	for (int i = 1; i < names_sorted.size(); ++i) {
		if (names_sorted[i] == names_sorted[i-1]) {
			cout << "Error: Duplicate name detected!\n";
			return 0;
		}
	}

	// Print vectors
	cout << "{";
	for (int i = 0; i < names.size(); i++) {
		cout << "(" << names[i] << "," << scores[i] << "), ";
	}
	cout << "\b\b}\n";

	cout << "Enter a name\n";
	string name_query;
	cin >> name_query;

	// Search for name and score
	int i = 0;
	bool name_found = false;
	while (i < names.size() && !name_found) {
		if (name_query == names[i]) {
			cout << names[i] << ", " << scores[i] << '\n';
			name_found = true;
		}
		++i;
	}
	if (!name_found) {
		cout << "Name not found.\n";
	}

	cout << "Enter a score\n";
	int score_query;
	cin >> score_query;

	// Search for any names with specified score
	i = 0;
	bool score_found = false;
	while (i < scores.size()) {
		if (scores[i] == score_query) {
			cout << names[i] << ", " << scores[i] << '\n';
			score_found = true;
		}
		++i;
	}
	if (!score_found) {
		cout << "Score not found.\n";
	}

	return 0;
}