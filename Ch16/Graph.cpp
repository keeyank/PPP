#include "Graph.h"
#include<map>

namespace Graph_lib {

Shape::Shape(initializer_list<Point> lst) {
	for (Point p : lst) {
		add(p);
	}
}

void Shape::draw_lines() const
{
	if (color().visibility() && 1<points.size())	// draw sole pixel?
		for (unsigned int i=1; i<points.size(); ++i)
			fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);
}

void Shape::draw() const
{
	Fl_Color oldc = fl_color();
	// there is no good portable way of retrieving the current style
	fl_color(lcolor.as_int());
	fl_line_style(ls.style(),ls.width());
	draw_lines();
	fl_color(oldc);	// reset color (to pevious) and style (to default)
	fl_line_style(0);
}

void Group::add(Shape& s) {
	vs.push_back(s);
}

void Group::move(int dx, int dy) {
	for (int i = 0; i < vs.size(); ++i) {
		vs[i].move(dx, dy);
	}
}

void Group::set_color(Color col) {
	lcolor = col;
	for (int i = 0; i < vs.size(); ++i) {
		vs[i].set_color(col);
	}
}

void Group::set_fill_color(Color col) {
	fcolor = col;
	for (int i = 0; i < vs.size(); ++i) {
		vs[i].set_fill_color(col);
	}
}

void Group::set_style(Line_style sty) {
	ls = sty;
	for (int i = 0; i < vs.size(); ++i) {
		vs[i].set_style(sty);
	}
}

void Group::draw_lines() const {
	for (int i = 0; i < vs.size(); ++i) {
		vs[i].draw();
	}
}

// does two lines (p1,p2) and (p3,p4) intersect?
// if se return the distance of the intersect point as distances from p1
inline pair<double,double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel) 
{
    double x1 = p1.x;
    double x2 = p2.x;
	double x3 = p3.x;
	double x4 = p4.x;
	double y1 = p1.y;
	double y2 = p2.y;
	double y3 = p3.y;
	double y4 = p4.y;

	double denom = ((y4 - y3)*(x2-x1) - (x4-x3)*(y2-y1));
	if (denom == 0){
		parallel= true;
		return pair<double,double>(0,0);
	}
	parallel = false;
	return pair<double,double>( ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/denom,
								((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3))/denom);
}


//intersection between two line segments
//Returns true if the two segments intersect,
//in which case intersection is set to the point of intersection
bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection){
   bool parallel;
   pair<double,double> u = line_intersect(p1,p2,p3,p4,parallel);
   if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
   intersection.x = p1.x + u.first*(p2.x - p1.x);
   intersection.y = p1.y + u.first*(p2.y - p1.y);
   return true;
} 

Poly::Poly(initializer_list<Point> ps) :
			Shape{ps}
{
	if (number_of_points() <= 2) {
		error("Poly::Poly: Less than 3 points");
	}
	if (number_of_points() == 3) {
		if (point(0)== point(1) || 
			point(0) == point(2) || 
			point(1) == point(2)) {
			error("Poly::Poly: Some points are the same");
		}
	}
	// number_of_points() > 3
	for (int i = 3; i < number_of_points(); ++i) {
		Point ignore {0,0};
		if (line_segment_intersect(point(i), point(i-1),
									point(i-2), point(i-3),
									ignore)) {
			error("Poly::Poly: Some points intersect");
		}
	}
}

void Poly::draw_lines() const {
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_begin_complex_polygon();
		for(int i=0; i<number_of_points(); ++i){
			fl_vertex(point(i).x, point(i).y);
		}
		fl_end_complex_polygon();
		fl_color(color().as_int());	// reset color
	}
	if (color().visibility()) {
		Shape::draw_lines();
		fl_line(point(0).x, point(0).y, point(number_of_points()-1).x,
				point(number_of_points()-1).y);
	}
}

void Polygon::add(Point p)
{
	int np = number_of_points();

	if (1<np) {	// check that thenew line isn't parallel to the previous one
		if (p==point(np-1)) error("polygon point equal to previous point");
		bool parallel;
		line_intersect(point(np-1),p,point(np-2),point(np-1),parallel);
		if (parallel)
			error("two polygon points lie in a straight line");
	}

	for (int i = 1; i<np-1; ++i) {	// check that new segment doesn't interset and old point
		Point ignore{0,0};
		if (line_segment_intersect(point(np-1),p,point(i-1),point(i),ignore))
			error("intersect in polygon");
	}
	

	Closed_polyline::add(p);
}

void Polygon::draw_lines() const
{
		if (number_of_points() < 3) error("less than 3 points in a Polygon");
		Closed_polyline::draw_lines();
}

void Open_polyline::draw_lines() const
{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i=0; i<number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}
		
		if (color().visibility())
			Shape::draw_lines();
}


void Closed_polyline::draw_lines() const
{
	Open_polyline::draw_lines();
		
	if (color().visibility())	// draw closing line:
		fl_line(point(number_of_points()-1).x,point(number_of_points()-1).y,point(0).x,point(0).y);
}
void Shape::move(int dx, int dy)
{
	for (unsigned int i = 0; i<points.size(); ++i) {
		points[i].x+=dx;
		points[i].y+=dy;
	}
}

void Lines::draw_lines() const
{
//	if (number_of_points()%2==1) error("odd number of points in set of lines");
	if (color().visibility())
		for (int i=1; i<number_of_points(); i+=2)
			fl_line(point(i-1).x,point(i-1).y,point(i).x,point(i).y);
}

void Text::draw_lines() const
{
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(),fnt_sz);
	fl_draw(lab.c_str(), point(0).x, point(0).y);
	fl_font(ofnt,osz);
}

Function::Function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale)
// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
// x coordinates are scaled by xscale and y coordinates scaled by yscale
{
	if (r2-r1<=0) error("bad graphing range");
	if (count<=0) error("non-positive graphing count");
	double dist = (r2-r1)/count;
	double r = r1;
	for (int i = 0; i<count; ++i) {
		add(Point{xy.x+int(r*xscale),xy.y-int(f(r)*yscale)});
		r += dist;
	}
}

void Rectangle::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x,point(0).y,w,h);
		fl_color(color().as_int());	// reset color
	}
	if (color().visibility()) {	// edge on top of fill
		fl_color(color().as_int());
		fl_rect(point(0).x,point(0).y,w,h);
	}
}

void Striped_rectangle::draw_lines() const {
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		constexpr int step = 4;
		constexpr int stripe_width = 2;
		for (int i = 0; i < width(); i += step) {
			fl_rectf(point(0).x+i, point(0).y, stripe_width, height());
		}
		fl_color(color().as_int());
	}

	if (color().visibility()) {	// edge on top of fill
		fl_color(color().as_int());
		fl_rect(point(0).x,point(0).y,width(),height());
	}
}

Axis::Axis(Orientation d, Point xy, int length, int n, string lab)
	:label(Point{0,0},lab)
{
	if (length<0) error("bad axis length");
	switch (d){
	case Axis::x:
		{	Shape::add(xy);	// axis line
			Shape::add(Point{xy.x+length,xy.y});	// axis line
			if (1<n) {
				int dist = length/n;
				int x = xy.x+dist;
				for (int i = 0; i<n; ++i) {
					notches.add(Point{x,xy.y},Point{x,xy.y-5});
				x += dist;
			}
		}
		// label under the line
		label.move(length/3,xy.y+20);
		break;
	}
	case Axis::y:
		{	Shape::add(xy);	// a y-axis goes up
			Shape::add(Point{xy.x,xy.y-length});
			if (1<n) {
			int dist = length/n;
			int y = xy.y-dist;
			for (int i = 0; i<n; ++i) {
				notches.add(Point{xy.x,y},Point{xy.x+5,y});
				y -= dist;
			}
		}
		// label at top
		label.move(xy.x-10,xy.y-length-10);
		break;
	}
	case Axis::z:
		error("z axis not implemented");
	}
}

void Axis::draw_lines() const
{
	Shape::draw_lines();	// the line
	notches.draw();	// the notches may have a different color from the line
	label.draw();	// the label may have a different color from the line
}


void Axis::set_color(Color c)
{
	Shape::set_color(c);
	notches.set_color(c);
	label.set_color(c);
}

void Axis::move(int dx, int dy)
{
	Shape::move(dx,dy);
	notches.move(dx,dy);
	label.move(dx,dy);
}

void Circle::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,r+r-1,r+r-1,0,360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,r+r,r+r,0,360);
	}
}

void Striped_circle::draw_lines() const {
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());

		constexpr int step = 4;
		constexpr int stripe_width = 2;
		int i_start = center().x - radius();
		int i_end = center().x + radius();
		for (int i = i_start; i < i_end; i += step) {

			int x = i - center().x;
			int line_height = pow(radius(),2) - pow(x, 2);
			line_height = 2*sqrt(line_height);
			int line_height_start = center().y - line_height/2;
			fl_rectf(i+radius(), line_height_start+radius(), 
					stripe_width, line_height);
		}
		fl_color(color().as_int());
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(center().x,center().y,2*radius(),2*radius(),0,360);
	}
}

void Arc::draw_lines() const
{
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,r+r,r+r,deg1,deg2);
	}
}

void Ellipse::draw_lines() const
{
	if (fill_color().visibility()) {	// fill
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,w+w-1,h+h-1,0,360);
		fl_color(color().as_int());	// reset color
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,w+w,h+h,0,360);
	}
}

void Box::draw_lines() const
{
	fl_color(color().as_int());
	fl_line_style(style().style(), style().width());

	// Draw lines
	fl_line(center.x+wh/2, center.y+wh/2 - edge_size, 
			center.x+wh/2, center.y-wh/2 + edge_size);
	fl_line(center.x+wh/2 - edge_size, center.y-wh/2,
			center.x-wh/2 + edge_size, center.y-wh/2);
	fl_line(center.x-wh/2, center.y-wh/2 + edge_size,
			center.x-wh/2, center.y+wh/2 - edge_size);
	fl_line(center.x-wh/2 + edge_size, center.y+wh/2,
			center.x+wh/2 - edge_size, center.y+wh/2);

	// Draw arcs
	fl_arc(center.x+wh/2 - 2*edge_size+1, center.y-wh/2,
			2*edge_size, 2*edge_size, 0, 90);
	fl_arc(center.x-wh/2, center.y-wh/2,
			2*edge_size, 2*edge_size, 90, 180);
	fl_arc(center.x-wh/2, center.y+wh/2 - 2*edge_size+1,
			2*edge_size, 2*edge_size, 180, 270);
	fl_arc(center.x+wh/2 - 2*edge_size+1, center.y+wh/2 - 2*edge_size+1,
			2*edge_size, 2*edge_size, 270, 360);

}

bool valid_right_triangle(Point p1, Point p2, Point p3) {
	bool x_valid = (p1.x == p2.x && p1.x != p3.x) ||
					(p1.x == p3.x && p1.x != p2.x) ||
					(p2.x == p3.x && p2.x != p1.x);
	bool y_valid = (p1.y == p2.y && p1.y != p3.y) ||
					(p1.y == p3.y && p1.y != p2.y) ||
					(p2.y == p3.y && p2.y != p1.y);
	return x_valid && y_valid;
}

Right_triangle::Right_triangle(Point p1, Point p2, Point p3) : 
			Poly{p1, p2, p3}
{
	string bad = "Right_triangle::Right_triangle: Invalid right triangle";
	if (p1 == p2 || p1 == p3) {
		throw runtime_error(bad);
	}
	if (!valid_right_triangle(p1, p2, p3)) {
		throw runtime_error(bad);;
	}
}

Hexagon::Hexagon(Point c, int w, int h) {
	if (w%4 != 0 || h%4 != 0) {
		error("Hexagon::Hexagon: Width and height must be divisible by 4");
	}
	add(Point{c.x-w/2, c.y});
	add(Point{c.x-w/4, c.y-h/2});
	add(Point{c.x+w/4, c.y-h/2});
	add(Point{c.x+w/2, c.y});
	add(Point{c.x+w/4, c.y+h/2});
	add(Point{c.x-w/4, c.y+h/2});
}

void draw_mark(Point xy, char c)
{
	static const int dx = 4;
	static const int dy = 4;
	string m(1,c);
	fl_draw(m.c_str(),xy.x-dx,xy.y+dy);
}

void Marked_polyline::draw_lines() const
{
	Open_polyline::draw_lines();
	for (int i=0; i<number_of_points(); ++i) 
		draw_mark(point(i),mark[i%mark.size()]);
}
/*
void Marks::draw_lines() const
{
	for (int i=0; i<number_of_points(); ++i) 
		fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
}
*/


/* Complex shapes */

void draw_txt(Point p, string txt, Color c, int fnt, int fnt_sz) {
	if (c.visibility()) { // Ensure proper color 
		fl_color(c.as_int()); // before drawing
	}
	fl_font(fnt, fnt_sz);
	fl_draw(txt.c_str(), p.x, p.y);
	fl_font(fl_font(), fl_size());
}


// Look at notebook for explanation on why this works
// (or look up how to represent a binary tree as an array)
void Binary_tree::gen_bt() {
	add(Point{-1,-1});
	add(orig);

	double disp_x = width/4;
	int curr_y = orig.y + l_height;
	int next_lev = 4;
	for (int i = 2; i < pow(2, levs); ++i) {

		if (i == next_lev) { 
			next_lev *= 2;
			disp_x /= 2;
			curr_y += l_height;
		}

		int p = i/2; // parent index
		int curr_x; 
		if (i%2 == 0) { // Left child
			curr_x = point(p).x - (int)disp_x;
		}
		else { // Right child
			curr_x = point(p).x + (int)disp_x;
		}
		Point node {curr_x, curr_y};
		add(node);
	}
}

void Binary_tree::gen_lbls() {
	for (int i = 0; i < number_of_points(); ++i) {
		lbls.push_back("");
	}
}

Binary_tree::Binary_tree(Point origin, int levels, 
		int tree_width, int line_height, int node_width, 
		int node_height) :
		orig{origin}, levs{levels}, width{tree_width},
		l_height{line_height},
		n_width{node_width}, n_height{node_height}
{
	if (levels <= 1) {error("Levels must be greater than 1");}
	gen_bt();
	gen_lbls();
}

void Binary_tree::draw_edge(Point c, Point p) const {
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_line(c.x, c.y, p.x, p.y);
	}
}

void Binary_tree::draw_node(Point n) const {
	if (fill_color().visibility()) {
		fl_color(fill_color().as_int());
		fl_pie(n.x-(n_width/2), n.y-(n_height/2),
				n_width-1,n_height-1,0,360);
		fl_color(color().as_int());
	}
	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(n.x-(n_width/2), n.y-(n_height/2), 
				n_width, n_height,0,360);
	}
}

void Binary_tree::draw_lines() const {
	// edges drawn before nodes
	for (int i = 2; i < number_of_points(); ++i) {
		draw_edge(point(i), point(i/2));
	}
	for (int i = 1; i < number_of_points(); ++i) {
		draw_node(point(i));

		Point txtpos {point(i).x - n_width/2 + 1, 
						point(i).y + n_height/4};
		draw_txt(txtpos, lbls[i], color(), fnt, fnt_sz);
	}
}

void Binary_tree::set_label(int i, string label) {
	if (i < 1 || i >= number_of_points()) {
		// Index 0 is a dummy index 
		error("Binary_tree::set_label: Index does not"
				" correspond to a node.");
	}
	lbls[i] = label;
}

string Binary_tree::label(int i) const {
	if (i < 1 || i >= number_of_points()) {
		// Index 0 is a dummy index 
		error("Binary_tree::label: Index does not"
				" correspond to a node.");
	}
	return lbls[i];
}

void draw_rect(Point p, int w, int h, Color col, Color fcol) {
	if (fcol.visibility()) {
		fl_color(fcol.as_int());
		fl_rectf(p.x, p.y, w, h);
		fl_color(col.as_int());	
	}
	if (col.visibility()) {	
		fl_color(col.as_int());
		fl_rect(p.x, p.y, w, h);
	}
}

Binary_tree_sqr::Binary_tree_sqr(Point origin, int levels, 
		int tree_width, int line_height, int node_width, 
		int node_height) :
		Binary_tree{origin, levels, tree_width, 
					line_height, node_width, node_height}
		{ }

void Binary_tree_sqr::draw_node(Point p) const {
	draw_rect(Point{p.x-n_width/2, p.y-n_height/2}, n_width, 
				n_height, color(), fill_color());
}

// Bar Graph //

Bar_graph::Bar_graph(Point origin, int xlength, int ylength, 
			int yscale, int yoffset, string name) :
			xlen{xlength}, ylen{ylength}, scale{yscale},
			yoff{yoffset}, 
			nam {Point{0,0}, name} // Use Text's constructor for nam
{ 
	nam.move(origin.x + xlen/2, origin.y + 50);
	Shape::add(origin);
}

void Bar_graph::draw_bars() const {
	int n = vals.size();
	if (n <= 0) {
		return;
	}

	double width = xlen/n;
	double xcurr = point(0).x; // point(0) is origin of graph
	for (int i = 0; i < n; ++i) {
		double ycurr = point(0).y - vals[i]*scale;
		draw_rect(Point{(int)xcurr, (int)ycurr}, width, 
					vals[i]*scale, color(), fill_color());

		xcurr += width;
	}
}

void Bar_graph::draw_axes() const {
	// Some hard-coded values here, but it's ok
	// x axis
	fl_line_style(0,2);
	Point orig = point(0);
	fl_line(orig.x, orig.y, orig.x + xlen, orig.y);

	// y axis
	fl_line(orig.x, orig.y, orig.x, orig.y - ylen);
	for (int y = 0; y < ylen; y += scale*yoff) {
		fl_line(orig.x, orig.y - y, 
			orig.x-4, orig.y - y);
	}
}

void Bar_graph::draw_lbls() const {
	// There are some magic constants in this code.
	Point orig = point(0);

	// x axis
	for (int i = 0; i < vals.size(); ++i) {
		int x = i * xlen/vals.size();
		draw_txt(Point{orig.x+x, orig.y+30}, lbls[i],
					color(), fnt, fnt_sz);
	}

	// y axis
	for (int y = 0; y < ylen; y += yoff*scale) {
		ostringstream oss;
		oss << setw(3) << y/scale;
		draw_txt(Point{orig.x-30, orig.y-y+4}, oss.str(), 
					color(), fnt, fnt_sz);
	}
}

void Bar_graph::draw_lines() const {
	draw_bars();
	draw_axes();
	draw_lbls();
	nam.draw();
}

Clock::Clock(Point center, int radius)
	: ctr{center}, r{radius},
	base{ctr, r},
	s_hand{ctr, Point{ctr.x+r, ctr.y}}
{ 
	if (r < 0) {error("Clock::Clock: Bad radius");}
}

void Clock::draw_lines() const {
	base.draw();
	s_hand.draw();
}

std::map<string,Suffix::Encoding> suffix_map;

int init_suffix_map()
{
	suffix_map["jpg"] = Suffix::jpg;
	suffix_map["JPG"] = Suffix::jpg;
	suffix_map["jpeg"] = Suffix::jpg;
	suffix_map["JPEG"] = Suffix::jpg;
	suffix_map["gif"] = Suffix::gif;
	suffix_map["GIF"] = Suffix::gif;
	suffix_map["bmp"] = Suffix::bmp;
	suffix_map["BMP"] = Suffix::bmp;
	return 0;
}

Suffix::Encoding get_encoding(const string& s)
		// try to deduce type from file name using a lookup table
{
	static int x = init_suffix_map();

	string::const_iterator p = find(s.begin(),s.end(),'.');
	if (p==s.end()) return Suffix::none;	// no suffix

	string suf(p+1,s.end());
	return suffix_map[suf];
}

bool can_open(const string& s)
            // check if a file named s exists and can be opened for reading
{
	ifstream ff(s.c_str());
	return static_cast<bool>(ff);
}


// somewhat overelaborate constructor
// because errors related to image files can be such a pain to debug
Image::Image(Point xy, string s, Suffix::Encoding e)
	:w(0), h(0), fn(xy,"")
{
	add(xy);

	if (!can_open(s)) {
		fn.set_label("cannot open \""+s+'\"');
		p = new Bad_image(30,20);	// the "error image"
		return;
	}

	if (e == Suffix::none) e = get_encoding(s);
	
	switch(e) {
	case Suffix::jpg:
		p = new Fl_JPEG_Image(s.c_str());
		break;
	case Suffix::gif:
		p = new Fl_GIF_Image(s.c_str());
		break;
//	case Suffix::bmp:
//		p = new Fl_BMP_Image(s.c_str());
//		break;
	default:	// Unsupported image encoding
		fn.set_label("unsupported file type \""+s+'\"');
		p = new Bad_image(30,20);	// the "error image"
	}
}

void Image::draw_lines() const
{
	if (fn.label()!="") fn.draw_lines();

	if (w&&h)
		p->draw(point(0).x,point(0).y,w,h,cx,cy);
	else
		p->draw(point(0).x,point(0).y);
}

// Helper functions 
Point nw(Rectangle& r) {
	Point center = r.point(0);
	int w = r.width();
	int h = r.height();
	return Point{center.x-(w/2), center.y-(h/2)};
}

Point nw(Circle& c) {
	Point center = c.center();
	int r = c.radius();
	return Point{center.x-r, center.y-r};
}

} // Graph