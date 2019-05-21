all: src/main.cpp src/connection.cpp src/edgetype.h src/graphviewer.cpp src/MutablePriorityQueue.h src/Road.cpp src/Point.cpp
	make main connection graphviewer road point
	g++ -g -o proj main.o connection.o graphviewer.o
main: src/main.cpp
	g++ -g -c src/main.cpp
connection: src/connection.cpp
	g++ -g -c src/connection.cpp
graphviewer: src/graphviewer.cpp
	g++ -g -c src/graphviewer.cpp
road: src/Road.cpp
	g++ -g -c src/Road.cpp
point: src/Point.cpp
	g++ -g -c src/Point.cpp
clean: 
	rm -f proj
	rm -f *.o
force:
	make clean
	make all