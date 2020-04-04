#include "Lines_window.h"

using namespace Graph_lib;

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{xy,w,h,title},
	next_button{Point{x_max()-150,0}, 70, 20, "Next point",
		[](Address, Address pw) {reference_to<Lines_window>(pw).next();}},
	quit_button{Point{x_max()-70,0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Lines_window>(pw).quit();}},
	next_x{Point{x_max()-310,0}, 50, 20, "next x:"},
	next_y{Point{x_max()-210,0}, 50, 20, "next y:"},
	xy_out{Point{100,0}, 100, 20, "current (x,y):"},
	color_menu{Point{x_max()-70,30},70,20,Menu::vertical,"color"},
	menu_button{Point{x_max()-80,30}, 80, 20, "Color menu",
		[](Address, Address pw) 
			{reference_to<Lines_window>(pw).menu_pressed();}},
	lmenu{Point{x_max()-70, 100}, 70, 20, Menu::vertical, "line"},
	lmenu_btn{Point{x_max()-70, 100}, 70, 20, "Line menu",
		[](Address, Address pw)
			{reference_to<Lines_window>(pw).lmenu_pressed();}}

{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");
	color_menu.attach(new Button{Point{0,0},0,0,"red",
		[](Address, Address pw) 
			{reference_to<Lines_window>(pw).red_pressed();}});
	color_menu.attach(new Button{Point{0,0},0,0,"blue",
		[](Address, Address pw) 
			{reference_to<Lines_window>(pw).blue_pressed();}});
	color_menu.attach(new Button{Point{0,0},0,0,"black",
		[](Address, Address pw) 
			{reference_to<Lines_window>(pw).black_pressed();}});
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);

	lmenu.attach(new Button{Point{0,0},0,0,"dash",
		[](Address, Address pw)
			{reference_to<Lines_window>(pw).dash_pressed();}});
	lmenu.attach(new Button{Point{0,0},0,0,"dot",
		[](Address, Address pw)
			{reference_to<Lines_window>(pw).dot_pressed();}});
	lmenu.attach(new Button{Point{0,0},0,0,"dashdot",
		[](Address, Address pw)
			{reference_to<Lines_window>(pw).dashdot_pressed();}});
	attach(lmenu);
	lmenu.hide();
	attach(lmenu_btn);
	attach(lines);
}

void Lines_window::quit() {
	Fl_Window::hide();
}

void Lines_window::next() {
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{x,y});

	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

My_window::My_window(Point xy, int w, int h, string title)
	: Window{xy, w, h, title},
	btn_quit{Point{w-70,0}, 70, 20, "Quit",
		[](Address,Address pw){reference_to<My_window>(pw).quit();}}
{
	attach(btn_quit);
}

Point Rand_window::randloc() {
	srand(time(NULL));
	int x = rand() % (x_max() - btn_w);
	int y = rand() % (y_max() - btn_h);
	return Point{x, y};
}

Rand_window::Rand_window(Point xy, int w, int h, string title)
	: My_window{xy, w, h, title},
	btn {randloc(), btn_w, btn_h, "-__=", 
		[](Address, Address pw) 
			{reference_to<Rand_window>(pw).btn_press();}}
{
	cout << btn.loc.x << ' ' << btn.loc.y;
	attach(btn);
}

void Rand_window::btn_press() {
	btn.move(randloc().x-btn.loc.x, randloc().y-btn.loc.y);
	//redraw();
}

Shapes_window::Shapes_window(Point xy, int w, int h, string title)
	: My_window{xy, w, h, title},
	menu {Point{w-70,40}, 70, 20, Menu::vertical, "Shapes"},
	xin {Point{w-230,0}, 70, 20, "x"},
	yin {Point{w-140,0}, 70, 20, "y"},
	btn_tri {Point{0,0}, 70, 20, "Triangle",
		[](Address, Address pw)
			{reference_to<Shapes_window>(pw).tri_press();}},
	tri {Point{0,0}, Point{0,50}, Point{50, 50}}
{
	menu.attach(new Button{Point{0,0}, 0, 0, "Square",
		[](Address, Address pw)
			{reference_to<Shapes_window>(pw).sqr_press();}});
	menu.attach(new Button{Point{0,0}, 0, 0, "Circle",
		[](Address, Address pw)
			{reference_to<Shapes_window>(pw).circ_press();}});
	menu.attach(new Button{Point{0,0}, 0, 0, "Hexagon",
		[](Address, Address pw)
			{reference_to<Shapes_window>(pw).hex_press();}});
	attach(menu);
	attach(xin);
	attach(yin);
	attach(btn_tri);
	attach(tri);
}

void Shapes_window::sqr_press() {
	int x = xin.get_int();
	int y = yin.get_int();
	shapes.push_back(new Rectangle{Point{x,y}, 80, 80});
	attach(shapes[shapes.size()-1]);
	redraw();
}

void Shapes_window::circ_press() {
	int x = xin.get_int();
	int y = yin.get_int();
	shapes.push_back(new Circle{Point{x,y}, 40});
	attach(shapes[shapes.size()-1]);
	redraw();
}

void Shapes_window::hex_press() {
	int x = xin.get_int();
	int y = yin.get_int();
	shapes.push_back(new Hexagon{Point{x,y}, 80, 80});
	attach(shapes[shapes.size()-1]);
	redraw();
}

void Shapes_window::tri_press() {
	ostringstream oss;
	oss << xin.get_string() << ' ' << yin.get_string();
	istringstream iss {oss.str()};
	int x, y;
	iss >> x >> y;
	if (!iss) {throw runtime_error("Bad!!!");}
	tri.move(x, y);
	redraw();
}

Clock_window::Clock_window(Point xy, int w, int h, string title) 
	: My_window {xy, w, h, title},
	c {Point{w/2,h/2},100},
	begin {Point{0,0}, 70, 20, "Begin",
		[](Address, Address pw)
			{reference_to<Clock_window>(pw).tick();}}
{
	attach(c);
	attach(begin);
}

void Clock_window::tick() {
	clock_t scurr;
	clock_t sprev = clock();
	while(true) {
		scurr = clock();
		if ((scurr - sprev)/CLOCKS_PER_SEC >= 1) {
			sprev = scurr;
			cout << "tick" << end;
		}
	}
}




