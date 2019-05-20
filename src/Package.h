#include "Point.h"

#ifndef SRC_PACKAGE_H_
#define SRC_PACKAGE_H_

class Package {
private:
	int identifier; //is this the best option?
	Point *PickUpPoint; //??
	Point * DeliveryPoint;
public:
	Package(int id, Point PUP, Point DP);
	int getIdentifier(){
		return this->identifier;
	}
};




#endif /* SRC_PACKAGE_H_ */
