#include "Point.h"

Point::Point() {
	this->x = 0;
	this->y = 0;
	this->id = 0;
}

Point::Point(int id, int x, int y) {
	this->x = x;
	this->y = y;
	this->id = id;
}

int Point::getID(){
	return this->id;
}
