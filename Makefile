all: src/main.cpp src/connection.cpp src/edgetype.h src/graphviewer.cpp
	make main connection graphviewer
	g++ -g -o proj main.o connection.o graphviewer.o
main: src/main.cpp
	g++ -g -c src/main.cpp
connection: src/connection.cpp
	g++ -g -c src/connection.cpp
graphviewer: src/graphviewer.cpp
	g++ -g -c src/graphviewer.cpp
clean: 
	rm -f proj
	rm -f *.o
force:
	make clean
	make all