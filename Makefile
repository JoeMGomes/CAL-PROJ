.PHONY: all clean
all: proj

CFLAGS = -Wall -Wextra -Werror
OBJECTS = graphviewer.o connection.o Package.o Point.o Road.o SupportPoint.o Vehicle.o main.o

proj: $(OBJECTS)
	@g++ $(CFLAGS) -pedantic $(OBJECTS) -o proj

main.o: src/graphviewer.h src/Point.h src/Road.h src/MutablePriorityQueue.h
graphviewer.o: src/graphviewer.h src/connection.h src/edgetype.h
connection.o: src/connection.h
Package.o: src/Point.h
Point.o: src/Point.h src/Road.h
Road.o: src/Road.h src/Point.h
SupportPoint.o: src/SupportPoint.h src/Package.h src/Vehicle.h
Vehicle.o: src/Vehicle.h

clean:
	@rm -f proj $(OBJECTS)
