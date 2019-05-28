#ifndef SRC_POINT_H_
#define SRC_POINT_H_
#include <vector>
#include "Road.h"

class Road;

enum typeOfPoint{NORMAL, SOURCE, DELIVERY, PATH};

class Point {
	private:
		int id;
		int x;
		int y;
		double dist;
		enum typeOfPoint type; 
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
		typeOfPoint getType();
		void setType(typeOfPoint t);
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
