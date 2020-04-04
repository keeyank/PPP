
#include "Lines_window.h"
#include "Graph.h"

int main() 
try {
	Clock_window win{Point{100,100},600,400,"My window"};
	return gui_main();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
