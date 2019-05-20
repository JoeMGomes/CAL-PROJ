#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#ifdef linux
#else
#include <Windows.h>
#endif

void inicia() {
	GraphViewer *gv = new GraphViewer(1000, 700, false);
	gv->createWindow(1000, 700);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(1, 1, 1);
	gv->addNode(2, 30, 30);
	gv->addNode(3, 800, 600);
	ifstream file;
	file.open("T09/Fafe/T09_nodes_X_Y_Fafe.txt");

	if (!file) {
		cout << "Failed to open node file\n";
		exit(1);
	}

	string line;
	int temp;
	double id, x, y;
	getline(file,line);
	sscanf(line.c_str(), "%d",&temp);

	while (getline(file,line) && temp != 0) {
		cout << temp << endl;
		sscanf(line.c_str(),"(%lf, %lf, %lf)", &id, &x,&y);
		gv->addNode(id, 25*(x/100-5670), 25*(y/100-45872));
		temp--;
	}
	cout << "Completed reading nodes\n";
	file.close();

	file.open("T09/Fafe/T09_edges_Fafe.txt");

	if (!file) {
		cout << "Failed to open edge file\n";
		exit(1);
	}
	getline(file,line);
	sscanf(line.c_str(), "%d",&temp);
	id=0;
	while (getline(file,line) && temp != 0) {
		cout << temp << endl;
		sscanf(line.c_str(),"(%lf, %lf)", &x,&y);
		gv->addEdge(id, x, y, EdgeType::UNDIRECTED);
		temp--;
		id++;
	}

	file.close();
	cout << "Completed edge reading\n";
	gv->rearrange();

}

int main() {
	inicia();
	getchar();
	return 0;
}
