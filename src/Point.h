#ifndef SRC_POINT_H_
#define SRC_POINT_H_
#include <vector>
#include "Road.h"

class Road;

class Point {//Node(?) can change it later
private:
	int id;
	int x;
	int y;
	std::vector<Road* > roads;
public:
	Point();
	Point(int id, int x, int y);
	int getID();
	int getX();
	int getY();
};

#endif /* SRC_POINT_H_ */
