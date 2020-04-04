// Date type
namespace Chrono {
	enum class Month {
		jan=1, feb, mar, apr, may, jun, jul, 
		aug, sep, oct, nov, dec
	};

	class Date {
	public:
		class Invalid { };
		Date(int )
		Date(int y, Month m, int d);	
		int year() const {return y;}
		int month() const {return m+1;}
		int day() const {return d+1;}
		// Add n days to the current date
		void add_day(int n);
	private:
		bool is_valid();
		int y = 1998;
		int m = 1;
		int d = 15;
	};
}