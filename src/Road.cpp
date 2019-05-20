#include "Road.h"
#include "math.h"

Road::Road(int id, Point * source, Point* dest){
    this->id = id;
    this->source = source;
    this->dest = dest;
    autoWeight();
}

int Road::getID(){
    return this->id;
}

Point* Road::getSource(){
    return this->source;
}

Point* Road::getDest(){
    return this->dest;
}

void Road::autoWeight(){
    double xDiff = dest->getX() - source->getX();
    double yDiff = dest->getY() - source->getY();
    this->weight = sqrt(xDiff*xDiff + yDiff*yDiff);
}

double Road::getWeight(){
    return this->weight;
}