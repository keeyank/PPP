#include <fstream>

struct File_handle {
	File_handle(string name)
		: f{fopen(name)}

private:
	FILE* f;
}

int main() 
try {


	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
	return 1;
}

