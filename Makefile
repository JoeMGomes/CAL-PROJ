CC= g++
LIBS = 
OBJ = src/graphviewer.o src/connection.o src/Package.o src/Point.o src/Road.o src/main.o

CFLAGS = -g -Wall -Wextra -MMD #-Werror

all: proj 

%.o: %.cpp
		$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

proj: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf src/*.d
	rm -rf src/*.o
	rm -rf proj