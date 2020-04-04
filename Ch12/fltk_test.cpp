#include "Simple_window.h"
#include "Graph.h"

int main() 
try {
	using namespace Graph_lib;

	Point tl {200,200};
	Simple_window win {tl, 600, 400, "Canvas"};

	// // Exercise 1
	// Rectangle r {Point{100,100}, 100, 30};
	// r.set_color(Color::blue);
	// Polygon p;
	// p.add(Point{5, 5});
	// p.add(Point{30, 5});
	// p.add(Point{30, 20});
	// p.add(Point{5, 20});
	// p.set_color(Color::red);
	// win.attach(p);
	// win.attach(r);

	// // Exercise 2
	// Text t {Point{110,115}, "monky!"};
	// t.set_color(Color::black);
	// win.attach(t);
	// win.wait_for_button();

	// // Exercise 4
	// int sqr_size = 30;
	// int tile_count = 3;
	// Point begin_loc = {200, 200};
	// vector<Rectangle> sqrs;
	// for (int i = 0; i < tile_count; ++i) {
	// 	for (int j = 0; j < tile_count; ++j) {
	// 		Point loc {begin_loc.x + j*sqr_size, 
	// 					begin_loc.y + i*sqr_size};
	// 		Rectangle r {loc, sqr_size-1, sqr_size-1};
	// 		r.set_color(Color::black);
	// 		win.attach(r);
	// 		win.wait_for_button();
	// 	}
	// }

	// // Exercise 3
	// Open_polyline k_line;
	// k_line.add(Point{300, 200});
	// k_line.add(Point{300, 300});
	// Open_polyline k_dash;
	// k_dash.add(Point{350, 200});
	// k_dash.add(Point{300, 250});
	// k_dash.add(Point{350, 300});
	// win.attach(k_line);
	// win.attach(k_dash);
	// win.wait_for_button();

	// // Exercise 5

	// int rect_width = (3./4.)*x_max();
	// int rect_height = (2./3.)*y_max();
	// int pos_x = (1./8.)*x_max();
	// int pos_y = (1./6.)*y_max();

	// Rectangle rect {Point{pos_x, pos_y}, rect_width, rect_height};
	// rect.set_fill_color(Color::red);
	// win.attach(rect);

	// int x_increase = 136;
	// int rect2_width = (1./2.)*x_max()+x_increase;
	// int rect2_height = (4./9.)*y_max();
	// int pos2_x = (1./4.)*x_max()-x_increase/2;
	// int pos2_y = (5./18.)*y_max();
	// Rectangle rect2 {Point{pos2_x, pos2_y}, 
	// 					rect2_width, rect2_height};
	// rect2.set_fill_color(Color::green);
	// win.attach(rect2);

	// win.wait_for_button();

	// Exercise 6

	// Running this line of code will make the window, but it's so big
	// that the "next" button clips outside the screen!
	// Simple_window win2 {tl, x_max()+40, y_max()+400, "Too big!"};
	// win2.wait_for_button();

	// This rectangle will be drawn, but clipped by the window edges
	// If you expand the window, you can see the full guy!
	Rectangle guy {Point{5, 300}, 800, 300};
	guy.set_fill_color(Color::green);
	win.attach(guy);
	win.wait_for_button();

	// Drill
	// Axis xa {Axis::x, Point{20, 300}, 280, 10, "x axis"};
	// win.attach(xa);
	// win.set_label("Canvas #2");
	// win.wait_for_button();

	// Axis ya {Axis::y, Point{20, 300}, 280, 10, "y axis"};
	// ya.set_color(Color::cyan);
	// ya.label.set_color(Color::dark_red);
	// win.attach(ya);
	// win.set_label("Canvas #3");
	// win.wait_for_button();

	// Function sine {sin, 0, 100, Point{20,150}, 1000, 50, 50};
	// win.attach(sine);
	// win.set_label("Canvas #4");
	// win.wait_for_button();

	// sine.set_color(Color::blue);
	// Polygon poly;
	// poly.add(Point{300, 200});
	// poly.add(Point{350, 100});
	// poly.add(Point{450, 200});
	// poly.add(Point{500, 200});
	// poly.set_color(Color::red);
	// poly.set_style(Line_style::dash);
	// win.attach(poly);
	// win.set_label("Canvas #5");
	// win.wait_for_button();

	// Rectangle r {Point{200,200}, 100, 50};
	// win.attach(r);
	// win.set_label("Canvas #6");
	// win.wait_for_button();

	// r.set_fill_color(Color::yellow);
	// poly.set_fill_color(Color::green);
	// poly.set_style(Line_style(Line_style::dash, 6));
	// win.set_label("Canvas #7");
	// win.wait_for_button();

	// Text t {Point{5,5}, "ok now get redy for monkey!"};
	// win.attach(t);
	// win.set_label("Canvas #8");
	// win.wait_for_button();

	// t.set_font(Font::times_bold);
	// t.set_font_size(20);
	// win.set_label("Canvas #9");
	// win.wait_for_button();

	// Image ii {Point{100,50}, "funny_monkey.jpg"};
	// win.attach(ii);
	// win.set_label("Canvas #10");
	// win.wait_for_button();


	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << '.' << endl;
	return 1;
}
catch (...) {
	cerr << "Error: Unknown exception." << endl;
	return 2;
}