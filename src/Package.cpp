#include "Package.h"
using namespace std;

int Package::getIdentifier(){
		return this->identifier;
	}
Package::Package(){
	this->identifier = 0;
	Point* pup;
	Point* dp;
	this->PickUpPoint = pup;
	this->DeliveryPoint = dp;
}
Package::Package(int id, Point* PUP, Point* DP){
	this->identifier = id;
	this->PickUpPoint = PUP;
	this->DeliveryPoint = DP;
}

void Package::setPickUpPoint(Point* PUP){
	this->PickUpPoint = PUP;

}

void Package::setDeliveryPoint(Point* DP){
	this->DeliveryPoint = DP;

}
