#include <iostream>
#include <vector>
#include <list>
#include <chrono>

using namespace std;

template<typename C>
	// requires Container<C>()
void sorted_insert(C& c, int val) {
	auto it = c.begin();
	while (it != c.end() && *it < val) ++it;
	c.insert(it, val);
}

int main() {
	srand(time(nullptr));
	for (unsigned long n = 2; n <= 1'000'000; n *= 3) {
		cout << "N: " << n << endl;
		vector<int> v{};
		chrono::steady_clock::time_point begin = 
			chrono::steady_clock::now();
		for (unsigned long i = 0; i < n; ++i) {
			sorted_insert(v, rand()%100);
			//v.push_back(rand()%100);
		}
		chrono::steady_clock::time_point end = 
			chrono::steady_clock::now();
		std::cout << "Vector time (sec) = " << 
			(std::chrono::duration_cast<std::chrono::microseconds>
			(end - begin).count()) /1000000.0 <<std::endl;

		list<int> l{};
		begin = chrono::steady_clock::now();
		for (unsigned long i = 0; i < n; ++i) {
			sorted_insert(l, rand()%100);
			//l.push_back(rand()%100);
		}
		end = chrono::steady_clock::now();
		std::cout << "List time (sec) = " << 
			(std::chrono::duration_cast<std::chrono::microseconds>
			(end - begin).count()) /1000000.0 <<std::endl;
	}

	return 0;
}