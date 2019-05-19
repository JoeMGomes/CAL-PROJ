#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <Windows.h>

void inicia() {
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(800, 800);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(1, 1, 2);

	ifstream file;
	file.open("testeNodes.txt");
	//f.open("nos.txt");

	if (!file) {
		cout << "Failed to open node file\n";
		exit(1);
	}

	string line;
	int id, numNos;
	double x, y;
	getline(file,line);
	sscanf(line.c_str(), "%d",&numNos);

	while (getline(file,line) && numNos != 0) {
		cout << numNos << endl;
		sscanf(line.c_str(),"(%d, %lf, %lf)", &id, &x,&y);
		gv->addNode(id, x, y);
		numNos--;
	}
	cout << "Completed reading " << numNos << "nodes\n";
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
