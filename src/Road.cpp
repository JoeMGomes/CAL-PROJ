#include "Road.h"

Road::Road(int id, Point * source, Point* dest){
    this->id = id;
    this->source = source;
    this->dest = dest;
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