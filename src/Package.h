#include "Point.h"

#ifndef SRC_PACKAGE_H_
#define SRC_PACKAGE_H_

class Package {
private:
	int identifier; //is this the best option?
	Point *PickUpPoint; //??
	Point *DeliveryPoint;
public:
	Package();
	Package(int id, Point* PUP, Point* DP);
	void setPickUpPoint(Point* PUP);
	void setDeliveryPoint(Point* DP);
	Point* getPickUpPoint()const;
	Point* getDeliveryPoint()const;
	int getIdentifier();
};




#endif /* SRC_PACKAGE_H_ */
