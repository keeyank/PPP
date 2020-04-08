#include "vector_set.h"

// // Testing
// int main() {
// 	Vector_set<int> vi;
// 	vi.insert(1); vi.insert(3); vi.insert(3);
// 	vi.insert(2); vi.insert(11);
// 	cout << vi << endl;
// 	cout << vi.in(1) << vi.in(2) << vi.in(3) << vi.in(4) << vi.in(5) << endl;
// 	cout << vi.in(-1) << vi.in(23) << vi.in(11) << vi.in(1111) << endl;
// 	for (int i = 0; i < 10; ++i) {
// 		cout << vi.get_rand() << ' ';
// 	}
// 	vi.remove(1);
// 	vi.remove(0);
// 	cout << endl;
// 	cout << vi << endl;
// 	vi.remove(2);
// 	vi.insert(12);
// 	cout << vi << endl;
// 	vi.remove(3);
// 	vi.remove(11);
// 	cout << vi << endl;
// 	vi.remove(12);
// 	cout << vi << endl;
// 	for (int i = 0; i < 20; ++i) {
// 		vi.insert(i);
// 	}
// 	vi.remove(11);
// 	vi.remove(1);
// 	vi.remove(19);
// 	vi.remove(0);
// 	if (!vi.in(1) && vi.in(18) && vi.in(17))
// 		cout << vi << endl;
// 	return 0;
// }