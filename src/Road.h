#ifndef ROAD_H_
#define ROAD_H_
#include "Point.h"

class Point;

class Road {
private:
	double weight;
	int id;
	Point* source;
	Point* dest;
public:
	Road(int id, Point * source, Point* dest);


};








#endif




