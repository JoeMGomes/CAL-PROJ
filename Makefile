all: src/main.cpp src/connection.cpp src/edgetype.h src/graphviewer.cpp src/Road.cc src/Point.cpp
	g++ -g -o proj src/main.cpp src/connection.cpp src/edgetype.h src/graphviewer.cpp src/Road.cpp src/Point.cpp
clean: 
	rm -f proj
force:
	make clean
	make all