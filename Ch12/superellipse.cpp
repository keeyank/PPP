#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

const Point tl {200, 200};
constexpr int width {1000};
constexpr int height {1000};
const Point zero {width/2, height/2};

constexpr double err_factor = 0.001;

// Effectively constants - these should never change
int a, b, line_count;
double m, n;


// Check if (x, y) is a point on the superellipse
bool valid_coord(int x, int y) {
	double x_component = abs(x-zero.x)/((double)a);
	x_component = pow(x_component, m);
	double y_component = abs(y-zero.y)/((double)b);
	y_component = pow(y_component, n);
	return abs(x_component+y_component - 1) <= err_factor;
}

void generate_points(vector<Point>& points) {
	for (int i = 0; i < width; ++i) {
		for (int j = zero.y-1; j >= 0; --j) {
			if (valid_coord(i, j)) {
				points.push_back(Point{i, j});
			}
		}
	}
	for (int i = width-1; i >= 0; --i) {
		for (int j = zero.y; j < height; ++j) {
			if (valid_coord(i, j)) {
				points.push_back(Point{i, j});
			}
		}
	}
}

// void create_se(Closed_polyline& se, vector<Point>& points) {
// 	double skip_factor = points.size()/((double)line_count);
// 	if (skip_factor < 1) {skip_factor = 1;}
// 	for (double i = 0; i < points.size(); i += skip_factor) {
// 		se.add(points[(int)i]);
// 	}
// }

// Generate proper amount of lines into lines Vector_ref
void generate_lines(Vector_ref<Line>& ls, const vector<Point>& ps) {
	double skip_factor = ps.size()/((double)line_count);
	if (skip_factor < 1) {skip_factor = 1;}

	double i;
	for (i = skip_factor; i < ps.size(); i += skip_factor) {
		ls.push_back(new Line{ps[i-skip_factor], ps[i]}); 
		ls[ls.size()-1].set_color((int)i%256); 
	}
	ls.push_back(new Line{ps[i-skip_factor], ps[0]});
}

int main() 
try {
	Simple_window win {tl, width, height, "Canvas"};

	cout << "To create a superellipse, enter integer values "
			<< "for a, b, m, n, and N respectively.\n";
	cin >> a >> b >> m >> n >> line_count;

	if (!cin) {error("Bad input.");}

	vector<Point> points;
	generate_points(points);

	// Closed_polyline se;
	// se.set_color(Color::black);
	// create_se(se, points);

	Vector_ref<Line> se_lines;
	generate_lines(se_lines, points);

	// Attach lines to window
	for (int i = 0; i < se_lines.size(); ++i) {
		win.attach(se_lines[i]);
	}
	
	win.wait_for_button();

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