
#include "Simple_window.h"
#include "Graph.h"

constexpr double pi = 3.141592653589793238462643383279502884;

double cs_addsqr(double d) {
	return pow(sin(d),2) + pow(cos(d),2);
}

double leib(int n) {
	double sum = 0;
	for (int i = 0; i < n; ++i) {
		double a = 1./(2*i + 1);
		sum = (i%2 == 0) ? sum+a : sum-a;
	}
	return sum;
}

int main() 
try {
	// // Part 1

	constexpr int win_width = 900;
	constexpr int win_height = 900;

	// constexpr int xlength = 500;
	// constexpr int ylength = 500;

	// constexpr int xstart = (win_width-xlength)/2;
	// constexpr int ystart = win_height - (win_height-ylength)/2;
	// constexpr Point orig {win_width/2, win_height/2};

	// constexpr int pixels_per_unit = 25;
	// constexpr int xscale = pixels_per_unit;
	// constexpr int yscale = pixels_per_unit;

	// constexpr int x_notch_count = xlength/xscale;
	// constexpr int y_notch_count = ylength/yscale;

	Simple_window win {Point{200, 200}, win_width, 
						win_height, "Test"};

	// Axis xaxis {Axis::x, Point{xstart, orig.y}, xlength, 
	// 		x_notch_count, "1 == 25 pixels"};
	// Axis yaxis {Axis::y, Point{orig.x, ystart}, ylength,
	// 		y_notch_count, "1 == 25 pixels"};
	// xaxis.set_color(Color::dark_magenta);
	// yaxis.set_color(Color::dark_magenta);

	// win.attach(xaxis);
	// win.attach(yaxis);

	// constexpr int rleft = -10;
	// constexpr int rright = 10;
	// constexpr int acc = 500; // accuracy

	// // Exercise 4
	// Function cose {cos, rleft, rright, orig, acc, xscale, yscale};
	// cose.set_color(Color::blue);
	// Function sine {sin, rleft, rright, orig, acc, xscale, yscale};
	// sine.set_color(Color::red);
	// Function csadd {[](double d){return sin(d)+cos(d);}, rleft,
	// 				rright, orig, acc, xscale, yscale};
	// csadd.set_color(Color::cyan);
	// Function cssqr {cs_addsqr, rleft, rright, orig, 
	// 				acc, xscale, yscale};

	// win.attach(cose);
	// win.attach(sine);
	// win.attach(csadd);
	// win.attach(cssqr);

	// // Exercise 5
	// Function pidiv4 {[](double){return pi/4;}, rleft, rright, orig,
	// 					acc, xscale, yscale};

	// win.attach(pidiv4);
	// win.wait_for_button();

	// for (int n = 0; n < 30; ++n) {
	// 	Line approx {Point{xstart, orig.y-(int)(leib(n)*yscale)},
	// 				 Point{xstart+xlength, orig.y-(int)(leib(n)*yscale)}};
	// 	win.attach(approx);
	// 	win.wait_for_button();
	// 	win.detach(approx);
	// }

	Bar_graph bg {{100, 500}, 200, 300, 20, 1};

	win.attach(bg);

	bg.add(3, "0-5");
	bg.add(12, "6-8");
	bg.add(15, "9-11");
	bg.add(8, "12-15");
	bg.add(4, "16-18");
	win.wait_for_button();
	bg.move(-50, 50);
	win.wait_for_button();
	bg.set_fill_color(Color::yellow);
	win.wait_for_button();

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
