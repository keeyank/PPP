
#include "GUI.h"

using namespace Graph_lib;

struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);

private:
	// Data
	Open_polyline lines;
	
	// Widgets
	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;
	Menu color_menu;
	Button menu_button;
	Menu lmenu;
	Button lmenu_btn;

	void change(Color c) {lines.set_color(c);}
	void hide_menu() {color_menu.hide(); menu_button.show();}

	// Invoked by callbacks
	void red_pressed() {change(Color::red); hide_menu();}
	void blue_pressed() {change(Color::blue); hide_menu();}
	void black_pressed() {change(Color::black); hide_menu();}
	void menu_pressed() {menu_button.hide(); color_menu.show();}

	void dash_pressed() {
		lines.set_style(Line_style::dash);
		lmenu.hide();
		lmenu_btn.show();
	}
	void dot_pressed() {
		lines.set_style(Line_style::dot);
		lmenu.hide();
		lmenu_btn.show();
	}
	void dashdot_pressed() {
		lines.set_style(Line_style::dashdot);
		lmenu.hide();
		lmenu_btn.show();
	}
	void lmenu_pressed() {lmenu_btn.hide(); lmenu.show();} 

	void next();
	void quit();
};

struct My_window : Window {
	My_window(Point xy, int w, int h, string title);

private:
	Button btn_quit;

	void quit() {Fl_Window::hide();}
};

struct Rand_window : My_window {
	Rand_window(Point xy, int w, int h, string title);
private:
	Button btn;
	static constexpr int btn_w = 30;
	static constexpr int btn_h = 30;

	void btn_press();
	Point randloc();
};

struct Shapes_window : My_window {
	Shapes_window(Point xy, int w, int h, string title);
private:
	Menu menu;
	Vector_ref<Shape> shapes;
	In_box xin;
	In_box yin;

	Button btn_tri;
	Right_triangle tri;

	void sqr_press();
	void circ_press();
	void hex_press();

	void tri_press();
};

struct Clock_window : My_window {
	Clock_window(Point xy, int w, int h, string title);
private:
	Button begin;
	Clock c;
	void tick();
};


