#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Point.h"
#include "Road.h"
#ifdef linux
#else
#include <Windows.h>
#endif

//Variaveis globais because fuck it
GraphViewer *gv;
std::vector<Point*> points;
std::vector<Road* > roads;

Point * findPoint(int id){

	for(auto p : points){
		if(p->getID() == id){
			return p;
		}
	}
}

void readMap(string cityName) {
	GraphViewer *gv = new GraphViewer(1000, 700, false);
	gv->createWindow(1000, 700);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(1, 1, 1);
	gv->addNode(2, 30, 30);
	gv->addNode(3, 800, 600);
	ifstream file;

	string nodeFile = "T09/" + cityName + "/T09_nodes_X_Y_" + cityName + ".txt";
	file.open(nodeFile);

	if (!file) {
		cout << "Failed to open node file\n";
		exit(1);
	}

	string line;
	int temp;
	double id, x, y;
	int xOffset = 0, yOffset = 0;

	getline(file, line);
	sscanf(line.c_str(), "%d", &temp); //numNos

	while (getline(file, line) && temp != 0) {
		cout << temp << endl;
		sscanf(line.c_str(), "(%lf, %lf, %lf)", &id, &x, &y);
		if (xOffset == 0 && yOffset == 0) {
			xOffset = x;
			yOffset = y;
		}
		points.push_back(new Point(id, x - xOffset, y - yOffset));
		temp--;
	}
	cout << "Completed reading nodes\n";
	file.close();

	string edgeFile = "T09/" + cityName + "/T09_edges_" + cityName + ".txt";

	file.open(edgeFile);

	if (!file) {
		cout << "Failed to open edge file\n";
		exit(1);
	}
	getline(file, line);
	sscanf(line.c_str(), "%d", &temp);
	id = 0;
	while (getline(file, line) && temp != 0) {
		cout << temp << endl;
		sscanf(line.c_str(), "(%lf, %lf)", &x, &y);

		roads.push_back(new Road(id, findPoint(x), findPoint(y)));
		temp--;
		id++;
	}

	file.close();
	cout << "Completed edge reading\n";
	gv->rearrange();

}

void initMap() {
	gv = new GraphViewer(1000, 700, false);
	gv->createWindow(1000, 700);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
}

void displayMap(){

}

int main() {
	initMap();
	readMap("Porto");
	displayMap();
	getchar();
	return 0;
}
