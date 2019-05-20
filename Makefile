all: src/main.cpp src/connection.cpp src/edgetype.h src/graphviewer.cpp
	g++ -g -o proj src/main.cpp src/connection.cpp src/edgetype.h src/graphviewer.cpp
clean: 
	rm -f proj
force:
	make clean
	make all