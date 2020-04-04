#include "Simple_window.h"
#include "Graph.h"

void read_to_graph(ifstream& ifs, Bar_graph& bg) {
	int label_i;
	int val;
	while (true) {
		ifs >> label_i >> val;
		if (!ifs) {
			return;
		}

		ostringstream label;
		label << label_i;
		bg.add(val, label.str());
	}
}

int main() 
try {
	Simple_window win{Point{200,200}, 600, 600, "ok"};

	Bar_graph bg {Point{50, 450}, 500, 400, 14, 5, "Heights"};
	bg.set_color(Color::black);
	bg.set_fill_color(Color::dark_cyan);
	win.attach(bg);

	ifstream ifs {"data.txt"};
	read_to_graph(ifs, bg);


	win.wait_for_button();
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
