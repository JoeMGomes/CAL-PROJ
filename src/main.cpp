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
		gv->addNode(id, 25*(x/100-5670), 25*(y/100-45872));
		numNos--;
	}
	cout << "Completed reading nodes\n";
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
