void copy(int* f1, int* e1, int* f2) {
	while (f1 != e1) {
		*f2 = *f1;
		++f1;
		++f2;
	}
}

template<typename Iter>
void advance(Iter& p, int n) {
	while (n > 0) {
		++p;
		--n;
	}
	while (n < 0) {
		--p;
		++n;
	}
}