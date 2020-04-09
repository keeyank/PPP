objects = room.o cave.o
wump : $(objects)
	g++ -o wump $(objects)

room.o : room.cpp room.h constants.h
	g++ -std=c++17 -c room.cpp
cave.o : cave.cpp cave.h room.h vector_set.h constants.h
	g++ -std=c++17 -c cave.cpp
clean:
	rm wump room.o cave.o