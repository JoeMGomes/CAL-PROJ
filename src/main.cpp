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
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(80000, 80000);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(1, 1, 1);
	gv->addNode(2, 1000, 1000);
	gv->addNode(3, 10000, 10000);
	gv->addNode(4, 100000, 100000);
	ifstream file;
	file.open("T09/Porto/T09_nodes_X_Y_Porto.txt");
	//f.open("nos.txt");

	if (!file) {
		cout << "Failed to open node file\n";
		exit(1);
	}

	string line;
	int numNos;
	double id, x, y;
	getline(file,line);
	sscanf(line.c_str(), "%d",&numNos);

	while (getline(file,line) && numNos != 0) {
		cout << numNos << endl;
		sscanf(line.c_str(),"(%lf, %lf, %lf)", &id, &x,&y);
		gv->addNode(id, x, y);
		numNos--;
	}
	cout << "Completed reading " << numNos << "nodes\n";//vai dar sempre 0, é estupido
	file.close();

	//gv->rearrange();

	/*f.open("arestas.txt");

	if (!f){
		cout << "Failed to open edge file\n";
		exit(1);
	}

	f >> numNos;
	cout << numNos << endl;
	while (!f.eof()) {
		f >> c;
		f >> x;
		f >> c;
		f >> y;
		f >> c;
		gv->addEdge(id, x, y, EdgeType::UNDIRECTED);
	}
	f.close();
	cout << "Completed edge reading\n";*/
}

int main() {
	inicia();
	getchar();
	return 0;
}
