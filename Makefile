CC= g++
LIBS = 
OBJ = src/graphviewer.o src/connection.o src/Package.o src/Point.o src/Road.o src/SupportPoint.o src/Vehicle.o src/main.o
<<<<<<< HEAD
CFLAGS = -g -Wall -Wextra  #-MMD
=======
CFLAGS = -g -Wall -Wextra -MMD #-Werror
>>>>>>> 2cd984f6008dc232649359de56413de0989422f7
all: proj 

%.o: %.cpp
		$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

proj: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf src/*.d
	rm -rf src/*.o
	rm -rf proj