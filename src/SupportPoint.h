#include "Package.h"
#include "Vehicle.h"
#include <vector>
using namespace std;

#ifndef SRC_SUPPORTPOINT_H_
#define SRC_SUPPORTPOINT_H_

class SupportPoint{
private:
	int identifier; //think if we wanna use names or ids
	int x;
	int y;
	vector<Package> PackagesToDelivery;
	vector<Vehicle> Fleet;
public:
	SupportPoint();
	SupportPoint(int id, int x, int y);
	void addPackage(Package p); //so later we can drop packages
	void removePackage(Package p); //so we can delivery them, i guess :')
	void addVehicle(Vehicle v);
	void removeVehicle(Vehicle v);
	int getIdentifer();
};




#endif /* SRC_SUPPORTPOINT_H_ */
