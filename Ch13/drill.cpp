#include "Graph.h"
#include "Simple_window.h"

using namespace Graph_lib;

constexpr int win_width = 800;
constexpr int win_height = 1000;
constexpr Point tl {200, 200};

constexpr int grid_wh = 800;

constexpr int grid_xy = 100;

int main() {
	Simple_window win {tl, win_width, win_height, "Drill"};

	// Grid
	Lines grid;
	grid.set_color(Color::black);
	for (int i = 0; i <= grid_wh; i += grid_xy) {
		grid.add(Point{i, 0}, Point{i, grid_wh});
		grid.add(Point{0, i}, Point{grid_wh, i});
	}

	// Diagonal squares
	Vector_ref<Rectangle> rects;
	for (int i = 0; i < grid_wh; i += grid_xy) {
		rects.push_back(
			new Rectangle{Point{i, i}, grid_xy+1, grid_xy+1});
		rects[rects.size()-1].set_fill_color(Color::red);
		rects[rects.size()-1].set_color(Color::invisible);
		win.attach(rects[rects.size()-1]);
	}

	// Uh oh, monkey time!!
	Image fonkey {Point{400, 200}, "funny_monkey.jpg"};
	fonkey.set_mask(Point{0,0}, 200, 200);
	win.attach(fonkey);

	Image fonkey2 {Point{200, 500}, "funny_monkey.jpg"};
	fonkey2.set_mask(Point{0,0}, 200, 200);
	win.attach(fonkey2);

	Image fonkey3 {Point{0, 500}, "funny_monkey.jpg"};
	fonkey3.set_mask(Point{0,0}, 200, 200);
	win.attach(fonkey3);

	win.attach(grid);

	// Big gorilla come to get monkey
	Image gorel {Point{01,01}, "gorla.jpg"};
	gorel.set_mask(Point{150,80}, 99, 99);
	win.attach(gorel);
	for (int i = 0; i < 8; ++i) {
		win.wait_for_button();
		gorel.move(100, 0); 
		win.wait_for_button();
		gorel.move(0, 100); 
	}

	return 0;
}
