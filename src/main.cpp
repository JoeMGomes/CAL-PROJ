#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <Windows.h>





void inicia()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	ifstream f;
	f.open("nos.txt");
	if (!f) exit(1);
	int id,x,y;
	char c;
	while(!f.eof()){
		f>>id;f>>c;f>>x;f>>c;f>>y;
		gv->addNode(id,x,y);
	}
	f.close();

	f.open("arestas.txt");
	if (!f) exit(1);
	while(!f.eof()){
		f>>id;f>>c;f>>x;f>>c;f>>y;
		gv->addEdge(id,x,y,EdgeType::UNDIRECTED);
	}
	f.close();
}


int main() {
	inicia();
	getchar();
	return 0;
}
