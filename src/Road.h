#ifndef ROAD_H_
#define ROAD_H_
#include "Point.h"
#include <cmath>

class Point;

class Road {
private:
	double weight;
	int id;
	Point* source;
	Point* dest;
public:
	Road(int id, Point * source, Point* dest);
	void autoWeight();
	int getID();
	double getWeight();
	Point *getSource();
	Point *getDest();
};

#endif




