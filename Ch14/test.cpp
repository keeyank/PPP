
#include "Simple_window.h"
#include "Graph.h"

int main() {
	Simple_window win{Point{0,0}, 600, 400, "test"};

	// // Exercise 2
	// Circle c {Point{0,0}, 50};
	// // Circle c2 {c}; // Compile error (very helpful one too!)
	// Circle c2 {Point{0,0}, 25};
	// // c2 = c; // Compile error - copy assignment deleted

	// Exercise 3 (see drill.cpp)
	// Tells you that the class is abstract and gives a compile error

	// // Exercise 4
	// Immobile_circle ic {Point{50,50}, 50};
	// Shape& ics = ic;
	// ics.move(400,400); // does nothing
	// win.attach(ics);

	// Circle c {Point{50, 50}, 50};
	// Shape& cs = c;
	// cs.move(300, 300);
	// win.attach(cs);
	// win.wait_for_button();

	// // Exercise 5
	// Striped_rectangle sr {Point{20, 20}, 200, 300};
	// sr.set_fill_color(Color::magenta);
	// sr.set_color(Color::dark_blue);
	// win.attach(sr);

	// // Exercise 6
	// Striped_circle sc {Point{50, 50}, 200};
	// sc.set_fill_color(Color::red);
	// sc.set_color(Color::black);
	// win.attach(sc);

	// // Exercise 9
	// Circle c {Point{100,100}, 40};
	// Rectangle r {Point{40, 30}, 30, 50};
	// Line l {Point{100, 20}, Point{400, 400}};
	// Group g;
	// g.add(c);
	// g.add(r);
	// g.add(l);
	// g.set_fill_color(Color::dark_red);
	// win.attach(g);
	// win.wait_for_button();

	// g.move(200, 0);
	// g.set_color(Color::black);
	// win.wait_for_button();

	// g.move(-100, 100);
	// g.set_fill_color(Color::cyan);
	// g.set_style(Line_style::dashdot);
	// c.set_fill_color(Color::black);
	// win.wait_for_button();

	// Shape& s = g;
	// s.move(0, 150);
	// win.wait_for_button();

	// Exercise 12
	Binary_tree bt {Point{300,20}, 7, 500, 40};
	bt.set_fill_color(Color::cyan);
	bt.set_color(Color::dark_red);
	if (bt.color().as_int() == Color::dark_red) {
		cout << "Color is dark red!\n";
	}
	win.attach(bt);
	win.wait_for_button();

	// The default shape's move works for binary tree!
	// Amazing!!!
	bt.move(-15, 0);
	win.wait_for_button();
	bt.set_style(Line_style{Line_style::dot, 3});
	bt.move(0, 80);
	win.wait_for_button();
	bt.set_color(Color::invisible);
	win.wait_for_button();

	win.detach(bt);
	Binary_tree_sqr bts {Point{300, 200}, 5, 450, 30, 20, 16};
	bts.set_color(Color::dark_blue);
	win.attach(bts);
	win.wait_for_button();

	win.detach(bts);
	bts.set_fill_color(Color::blue);
	Binary_tree& bt2 = bts;
	bt2.move(-15, 10);
	win.attach(bt2);
	win.wait_for_button();

	win.detach(bt2);
	win.attach(bts);
	win.wait_for_button(); // Nothing should change!

	for (int i = 1; i < bts.number_of_points(); ++i) {
		ostringstream oss;
		oss << i;
		bts.set_label(i, oss.str());
	}
	bts.set_color(Color::black);
	win.wait_for_button();


	
	return 0;
}
