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
	double dist;
	int num; //1 e para source, 2 e para delivery
	
	Point * path;

	std::vector<Road* > roads;
public:

	//tem de ser publico
	int queueIndex;

	Point();
	Point(int id, int x, int y);
	int getID();
	int getX();
	int getY();
	int getNum();
	double getDist();
	Point * getPath();
	std::vector<Road*> getRoads();

	void setDist(double dist);
	void setPath(Point * path);
	void addRoad(Road * r);

	bool operator<(Point & p) const;

	bool equals (Point & p) const;
};

#endif /* SRC_POINT_H_ */
