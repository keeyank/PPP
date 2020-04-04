struct Stats {
	int max;
	int min;
	double mean;
	double median;
};

// Prints out contents of vec, as well as the label.
void print_vec(const string& label, const vector<int>& vec);
// Return a Stats for v
Stats get_stats(const vector<int>& v);
