objects = room.o cave.o controller.o main.o
wump : $(objects)
	g++ -o wump $(objects)

room.o : room.cpp room.h constants.h
	g++ -std=c++17 -c room.cpp
cave.o : cave.cpp cave.h room.h vector_set.h constants.h
	g++ -std=c++17 -c cave.cpp
controller.o : controller.cpp controller.h cave.h room.h vector_set.h constants.h
	g++ -std=c++17 -c controller.cpp
main.o : main.cpp controller.h cave.h room.h vector_set.h constants.h
	g++ -std=c++17 -c main.cpp 
clean:
	rm wump $(objects)