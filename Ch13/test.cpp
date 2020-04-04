#include "Simple_window.h"
#include "Graph.h"
#include <time.h>

using namespace Graph_lib;

int main() 
try {
	Simple_window win {Point{200,200}, 600, 500, "test"};

	// Exercise 1
	// Arc a {Point{300, 150}, 100, 0, 180};
	// Arc b {Point{40, 200}, 35, 0, 300};
	// Arc c {Point{400, 400}, 100, 275, 330};

	// win.attach(a);
	// win.attach(b);
	// win.attach(c);
	// win.wait_for_button();

	// // Exercise 2
	// Box a {Point{200, 200}, 100};
	// a.set_color(Color::blue);
	// Box b {Point{20, 20}, 40};
	// b.set_style(Line_style{Line_style::dashdotdot, 3});

	// win.attach(a);
	// win.attach(b);

	// // Exercise 15 - uses magic constants
	// Vector_ref<Right_triangle> grid;
	// for (int i = 0; i < 500; i += 50) {
	// 	for (int j = 0; j < 600; j += 50) {
	// 		Point p1 {j, i};
	// 		Point p2 {j+50, i};
	// 		Point p3 {j+50, i+50};
	// 		grid.push_back(new Right_triangle{p1, p2, p3});
	// 		grid[grid.size()-1].set_fill_color(Color::black);
	// 		win.attach(grid[grid.size()-1]);
	// 	}
	// }
	// win.wait_for_button();

	// Exercise 17
	// Poly p; // This gives a compile-error, because the default constructor
			   // is protected. Only used implicitly by Hexagon's constructor

	// Vector_ref<Hexagon> grid;
	// int h_width = 16;
	// int h_height = 16;
	// srand(time(NULL));

	// for (int i = 0; i < 600; i += h_height/2) {
	// 	int disp = h_width/2 + h_width/4;
	// 	int j_start = ((i/(h_height/2))%2)*disp;
	// 	for (int j = j_start; j < 500; j += 3*(h_width/2)) {
	// 		grid.push_back(new Hexagon {Point{j, i}, h_width, h_height});
	// 		Hexagon& curr_hex = grid[grid.size()-1];
	// 		curr_hex.set_fill_color(rand()%256);
	// 		curr_hex.set_color(rand()%256);
	// 		win.attach(curr_hex);
	// 	}
	// }

	// // Exercise 4, 5
	// Circle c {Point{100,100}, 50};
	// Circle c2 {nw(c), 50};
	// win.attach(c2); win.attach(c);

	// Exercise 12
	Point zero {250, 250};
	int radius = 200; 

	Circle c {zero, radius};
	win.attach(c);
	c.set_color(Color::blue);

	int r_size = 10;
	double step = .1;

	for (double i = 0; i < 2*3.14; i += step) {
		Point curr {(int)(zero.x + radius*cos(i) - r_size/2), 
					(int)(zero.y - radius*sin(i) - r_size/2)};
		Rectangle r {curr, r_size, r_size};
		r.set_fill_color(Color::cyan);
		win.attach(r);
		win.wait_for_button();
	}

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
	return 1;
}
