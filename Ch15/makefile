objects = Graph.o Simple_window.o Window.o GUI.o main.o
exec_name = go

$(exec_name) : $(objects)
	g++ -o $(exec_name) $(objects) \
	-L/usr/local/lib -lfltk_images -ljpeg -lpng \
	-lz -lfltk -lpthread -framework Cocoa

Graph.o : Graph.cpp Graph.h Point.h fltk.h
	g++ -I/usr/local/include -D_LARGEFILE_SOURCE \
	-D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
	-c -std=c++17 Graph.cpp
Simple_window.o : Simple_window.cpp Simple_window.h GUI.h Window.h Graph.h Point.h fltk.h std_lib_facilities.h 
	g++ -I/usr/local/include -D_LARGEFILE_SOURCE \
	-D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
	-c -std=c++17 Simple_window.cpp
Window.o : Window.cpp Window.h Graph.h GUI.h fltk.h Point.h std_lib_facilities.h
	g++ -I/usr/local/include -D_LARGEFILE_SOURCE \
	-D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
	-c -std=c++17 Window.cpp
GUI.o : GUI.cpp GUI.h std_lib_facilities.h Window.h Graph.h Point.h fltk.h
	g++ -I/usr/local/include -D_LARGEFILE_SOURCE \
	-D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
	-c -std=c++17 GUI.cpp
main.o : graphing.cpp Window.h Graph.h GUI.h fltk.h Point.h std_lib_facilities.h
	g++ -I/usr/local/include -D_LARGEFILE_SOURCE \
	-D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT \
	-c -std=c++17 graphing.cpp -o main.o
clean : 
	rm $(exec_name) $(objects)