#include "Vehicle.h"

Vehicle::Vehicle(){
	this->identifier = 0;
}

Vehicle::Vehicle(int id){
	this->identifier = id;
}
int Vehicle::getIdentifier(){
	return this->identifier;
}


