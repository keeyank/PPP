
class Vector {
	Vector(int n)
		: sz{n}, elem{new int[n]}
	{
		for (int i = 0; i < sz; ++i) {
			elem[i] = 0;
		}
	}

	~Vector() {
		delete[] elem;
	}

private:
	int sz;
	int* elem;
};