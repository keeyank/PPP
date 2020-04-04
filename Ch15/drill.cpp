
#include "Simple_window.h"
#include "Graph.h"

class Person {
public:
	Person(string name, int age); 
	Person() { }

	string name() const {return nam;}
	int age() const {return ag;}

private:
	string nam = "DEFAULT";
	int ag = -1;
	static constexpr int a_max = 140;
};

bool illegal_name(const string& s) {
	static const string illegal = ";:\"'!@#$%^&*()";
	/*
	Note: This returns true when the following double exist statement
	is satisfied:
	There exists a c in s such that there exists a bad in illegal 
	such that c == bad
	It returns false when the negation of the above is true
	For all c in s, it is true that (for all bad in illegal, 
	c != bad)
	*/
	for (char c : s) {
		for (char bad : illegal) {
			if (c == bad) {
				return true;
			}
		}
	}
	return false;
}

Person::Person(string name, int age) :
			nam{name}, ag{age} 
	{
		if (nam == "" || illegal_name(nam)) 
			{error("Bad name!");}
		if (ag < 0 || ag > a_max) 
			{error("Bad age!");}
	}

// Helper functions 
ostream& operator<<(ostream& os, const Person& p) {
	return os << p.name() << ' ' << p.age();
}

istream& operator>>(istream& is, Person& p) {
	string name; 
	int age;
	is >> name >> age;
	if (!is) {return is;}
	Person tmp {name, age};
	p = tmp;
	return is;
}

int main() 
try {
	// Part 1

	constexpr int win_width = 600;
	constexpr int win_height = 600;

	constexpr int xlength = 400;
	constexpr int ylength = 400;

	constexpr int xstart = (win_width-400)/2;
	constexpr int ystart = win_height - (win_height-400)/2;
	constexpr Point orig {win_width/2, win_height/2};

	constexpr int pixels_per_unit = 20;
	constexpr int xscale = pixels_per_unit;
	constexpr int yscale = pixels_per_unit;

	constexpr int x_notch_count = xlength/xscale;
	constexpr int y_notch_count = ylength/yscale;

	Simple_window win {Point{200, 200}, win_width, 
						win_height, "Test"};

	Axis xaxis {Axis::x, Point{xstart, orig.y}, xlength, 
			x_notch_count, "1 == 20 pixels"};
	Axis yaxis {Axis::y, Point{orig.x, ystart}, ylength,
			y_notch_count, "1 == 20 pixels"};
	xaxis.set_color(Color::dark_magenta);
	yaxis.set_color(Color::dark_magenta);

	win.attach(xaxis);
	win.attach(yaxis);

	// Part 2
	constexpr int rleft = -10;
	constexpr int rright = 10;

	Function one {[](double){return 1.;}, rleft, rright, orig, 
					400, xscale, yscale};
	Function slope {[](double d){return d/2;}, rleft, rright, 
					orig, 400, xscale, yscale};
	Text slope_label {Point{xstart, orig.y + 6*yscale}, "x/2"};
	Function sqr {[](double d){return d*d;}, rleft, rright,
					orig, 400, xscale, yscale};
	Function cose {cos, rleft, rright, orig, 400, xscale, yscale};
	cose.set_color(Color::blue);
	Function scose {[](double d){return cos(d) + d/2;}, rleft,
					rright, orig, 400, xscale, yscale};


	win.attach(one);
	win.attach(slope);
	win.attach(slope_label);
	win.attach(sqr);
	win.attach(cose);
	win.attach(scose);

	// Part 3
	Person goger {"Goger", 14};
	cout << goger << endl;

	cout << "give: " << endl;
	Person yogert;
	cin >> yogert;
	cout << yogert << endl;

	const Person brogert {"Brogert", 21};
	cout << brogert.age() << brogert.name() << endl;
	cout << brogert << endl;

	//win.wait_for_button();
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
