#include "Package.h"
using namespace std;

int Package::getIdentifier(){
		return this->identifier;
	}
Package::Package(){
	this->identifier = 0;
	this->PickUpPoint = nullptr;
	this->DeliveryPoint = nullptr;
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

void Package::setIdentifier(int ID){
	this->identifier = ID;
}

Point * Package::getDeliveryPoint()const{
	return this->DeliveryPoint;
}
Point * Package::getPickUpPoint()const{
	return this->PickUpPoint;
}

