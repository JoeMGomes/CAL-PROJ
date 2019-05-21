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

int Point::getID() {
    return this->id;
}

int Point::getNum(){
    return num;
}
int Point::getX() {
    return this->x;
}
int Point::getY() {
    return this->y;
}

double Point::getDist() {
    return this->dist;
}

Point* Point::getPath(){
	return this->path;
}

std::vector<Road* > Point::getRoads(){
	return this->roads;
}

void Point::setDist(double dist){
	this->dist = dist;
}

void Point::setPath(Point * path){
	this->path = path;
}

bool Point::operator<(Point & p)const {
	return this->dist < p.getDist();
}

bool Point::equals(Point & p)const{
	return this->id == p.getID();
}

void Point::addRoad(Road * r){
    this->roads.push_back(r);
}