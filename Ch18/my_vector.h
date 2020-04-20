class Vector {
public:
	explicit Vector(unsigned long n);

	Vector(std::initializer_list<int> lst);

	Vector(const Vector& v);

	Vector(Vector&& v);

	~Vector() {
		delete[] elem;
	}

	Vector& operator=(const Vector& v);

	Vector& operator=(Vector&& v);

	int size() const {
		return sz;
	}

	int operator[](unsigned long n) const {
		return elem[n];
	}

	int& operator[] (unsigned long n) {
		return elem[n];
	}

private:
	unsigned long sz;
	int* elem;
};

Vector::Vector(unsigned long n)
	: sz{n}, elem{new int[n]}
{
	for (int i = 0; i < sz; ++i) elem[i] = 0;
}

Vector::Vector(std::initializer_list<int> lst)
	: sz{lst.size()}, elem{new int[sz]}
{
	std::copy(lst.begin(), lst.end(), elem);
}

Vector::Vector(const Vector& v) 
	: sz{v.sz}, elem{new int[sz]}
{
	std::copy(v.elem, v.elem + sz, elem);
}

Vector::Vector(Vector&& v) 
	: sz{v.sz}, elem{v.elem}
{
	v.sz = 0;
	v.elem = nullptr;
}

Vector& Vector::operator=(const Vector& v) {
	int* p = new int[v.sz];
	std::copy(v.elem, v.elem + v.sz, p);
	delete[] elem;
	elem = p;
	sz = v.sz;
	return *this;
}

Vector& Vector::operator=(Vector&& v) {
	delete[] elem;
	sz = v.sz;
	elem = v.elem;
	v.sz = 0;
	v.elem = 0;
	return *this;
}







