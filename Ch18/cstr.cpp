#include <iostream>

using namespace std;

void const_ptr_test(const int* ptr) {
	++ptr; // Compiles!
	//++*ptr; // Error - ptr is const
			// (means you can't write to the object it points to)
	// Moral of the story: const pointers protect the object they point to,
	// and that general area in memory (you can't set any pointers equal to
	// them and dereference those either, try it!)
	// Basically, it works just like doing a const reference argument
}

int str_len(const char* s) {
	int count = 0;
	while (s[count]) ++count;
	return count;
}

void print_string_rep(const char* s) {
	cout << endl;
	for (int i = 0; i < str_len(s) + 1; ++i) {
		cout << (int)s[i] << ' ';
	}
	cout << endl;
}

char* strdup(const char* orig) { 
	char* copy = new char[str_len(orig)+1]; // +1 for null terminator
				// The +1 is VERY IMPORTANT!!! It works without the
				// +1, but you need it to add the null terminator
				// and ensure it is a c-style string.
	const char* ocurr = orig;
	char* ccurr = copy;
	while (*ocurr != 0) {
		*ccurr = *ocurr;
		++ccurr;
		++ocurr;
	}
	*ccurr = 0; // Don't forget null terminator!
	return copy;
}

int strcmp(const char* s1, const char* s2) {
	while (*s1 != 0 && *s2 != 0) {
		if (*s1 < *s2) 
			{return -1;}
		if (*s1 > *s2)
			{return 1;}
		++s1;
		++s2;
	}
	if (*s1 == 0 && *s2 != 0) 
		{return -1;}
	if (*s2 == 0 && *s1 != 0) 
		{return 1;}
	return 0; 
}

bool find(const char* big, const char* small) {
	const char* bcurr_main = big;
	while (*bcurr_main != 0) {
		const char* bcurr = bcurr_main;
		const char* scurr = small;

		bool found = true;
		while (*scurr != 0 && *bcurr != 0) {
			if (*scurr != *bcurr) 
				{found = false;}
			++scurr;
			++bcurr;
		}
		if (*bcurr == 0 && *scurr != 0) 
			{found = false;}

		if (found) 
			{return true;}

		++bcurr_main;
	}

	return false;
}

int main() {
	constexpr int max = 128;

	// // Exercise 2
	// char big[max];
	// cin.getline(big, max);
	// for (char s[max]; cin.getline(s, max);) {
	// 	if (find(big, s)) cout << "Found!\n";
	// 	else cout << "Not found.\n";
	// }


	// // Exercise 1
	// for (char s[max]; cin.getline(s, max);) {

	// 	char* copy = strdup(s);
	// 	cout << copy << endl;

	// 	print_string_rep(s);
	// 	print_string_rep(copy);

	// 	delete[] copy; // NEVER FORGET THIS
	// }

	// // Exercise 3
	// char s1[max];
	// char s2[max];
	// while (true) {
	// 	cin.getline(s1, max);
	// 	cin.getline(s2, max);
	// 	if (!cin)
	// 		break;

	// 	int cmp = strcmp(s1, s2);
	// 	switch (cmp) {
	// 		case 1:
	// 			cout << "First string is lexicographically larger.\n";
	// 			break;
	// 		case -1:
	// 			cout << "First string is lexicographically smaller.\n";
	// 			break;
	// 		case 0:
	// 			cout << "Both strings are the same size.\n";
	// 			break;
	// 	}	
	// }

	// // Exercise 4
	// int x = 4;
	// char uhoh[] {"abc"};
	// uhoh[3] = 'd'; // Remove null-terminator (this is bad!!!)
	// // This didn't do anything - the next portion in stack memory
	// // must have just so happened to also be 0.
	// // (actually, it was 4 - corresponding to part of x I think)
	// uhoh[4] = 'e'; // This overwrites our x!!!! it is 101 now
	// uhoh[5] = 'f'; // This overwrites x even more!!! Now it's 26213

	// char a = 'a';
	// double y = 148.2;

	// char* dup = strdup(uhoh);

	// cout << "Duplicate: " << dup 
	// 	<< "\nUhoh: " << uhoh
	// 	<< "\nx: " << x
	// 	<< "\na: " << a
	// 	<< "\ny: " << y << endl;

	// char* bad = new char[19] {"This array is bad!"};
	// char* cool = new char[17] {"OOOOOOhhhhkay!!!"};
	// for (int i = 18; bad[i] == 0; ++i) {
	// 	bad[i] = '!';
	// }

	// dup = strdup(bad);

	// cout << "Duplicate: " << dup  
	// << "\nbad: " << bad // Since null-terminator is gone, this
	// 				// prints out bad, and then cool!
	// 				// Same with dup
	// << "\ncool: " << cool << endl;

	// delete[] bad;
	// delete[] cool;

	return 0;
}



