#include "SupportPoint.h"

SupportPoint::SupportPoint(){
	this->identifier = 0;
	this->x = 0;
	this->y = 0;

}

SupportPoint::SupportPoint(int id, int x, int y){
	this->identifier = id;
	this->x = x;
	this->y = y;
}

void SupportPoint::addPackage(Package p){
	PackagesToDelivery.push_back(p);
}

void SupportPoint::removePackage(Package p){
	for (unsigned int i = 0; i < PackagesToDelivery.size(); i++){
		if (PackagesToDelivery[i].getIdentifier() == p.getIdentifier()) {
			PackagesToDelivery.erase(PackagesToDelivery.begin()+i);
		}
		else{
			//idk
		}
	}
}

void SupportPoint::addVehicle(Vehicle v){
	Fleet.push_back(v);
}

void SupportPoint::removeVehicle(Vehicle v){
	for (unsigned int i = 0; i < Fleet.size(); i++){
		if (Fleet[i].getIdentifier() == v.getIdentifier()) {
			Fleet.erase(Fleet.begin()+i);
		}
		else{
			//idk
		}
	}
}
