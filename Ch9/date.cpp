#include <iostream>
#include <string>

#include "date.h"

using namespace std;

namespace Chrono {

	// Member functions
	// Implementation notes: We represent the months and days from
	// [0, 11] rather than [1, 12] - this simplifies modular arithmetic
	// when adding days. We convert back and forth to account for this
	// discrepenancy in the implementation and interface, which is why 
	// there are +1s and -1s in some areas (e.g., initializing m {mm-1})
	Date::Date(int yy, Month mm, int dd)
		: y{yy}, m{int(mm)-1}, d{dd-1}
		{
			if (!is_valid()) 
				throw Invalid{};
		}

	void Date::add_day(int d_to_add) {
		if (d_to_add < 0)
			throw runtime_error("add_day: Negative d_to_add disallowed.");

		int d_new = (d_to_add+d)%31;
		int m_to_add = (d_to_add+d)/31;
		int m_new = (m_to_add+m)%12;
		int y_to_add = (m_to_add+m)/12;
		
		d = d_new;
		m = m_new;
		y += y_to_add;
	}

	bool Date::is_valid() { 
		// Assume y is valid
		if (m < 0 || m > 11)
			return false;
		if (d < 0 || d > 30) 
			return false;
		return true;
	}


	// Helper Functions 
	ostream& operator<<(ostream& os, const Date& d) {
		return os << '(' << d.year()
				<< ',' << d.month()
				<< ',' << d.day() << ')';
	}

}

int main() {
	using Chrono::Month;
	Chrono::Date today{2020, Month::jan, 24};
	today.add_day(10);
	const Chrono::Date tomorrow{2020, Month::jan, 25};
	//tomorrow.add_day(4); // Compiler error!
	cout << today << endl;
}
