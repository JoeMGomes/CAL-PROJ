#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->setBackground("background.jpg");
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
	gv->removeNode(1);
	gv->addNode(2);
	gv->addEdge(0,0,2,EdgeType::UNDIRECTED);
	gv->setEdgeLabel(0,"Isto é uma aresta");
	gv->setVertexColor(2,"green");
	gv->setEdgeColor(0,"yellow");

}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->addNode(0,300,50);
	gv->addNode(1,318,58);
	gv->addNode(2,325,75);
	gv->addNode(3,318,93);
	gv->addNode(4,300,100);
	gv->addNode(5,282,93);
	gv->addNode(6,275,75);
	gv->addNode(7,282,58);
	gv->addNode(8,150,200);
	gv->addNode(9,300,200);
	gv->addNode(10,450,200);
	gv->addNode(11,300,400);
	gv->addNode(12,200,550);
	gv->addNode(13,400,550);
	gv->addEdge(0,0,1,EdgeType::UNDIRECTED);
	gv->addEdge(1,1,2,EdgeType::UNDIRECTED);
	gv->addEdge(2,2,3,EdgeType::UNDIRECTED);
	gv->addEdge(3,3,4,EdgeType::UNDIRECTED);
	gv->addEdge(4,4,5,EdgeType::UNDIRECTED);
	gv->addEdge(5,5,6,EdgeType::UNDIRECTED);
	gv->addEdge(6,6,7,EdgeType::UNDIRECTED);
	gv->addEdge(7,7,0,EdgeType::UNDIRECTED);
	gv->addEdge(8,4,9,EdgeType::UNDIRECTED);
	gv->addEdge(9,9,8,EdgeType::UNDIRECTED);
	gv->addEdge(10,9,10,EdgeType::UNDIRECTED);
	gv->addEdge(11,9,11,EdgeType::UNDIRECTED);
	gv->addEdge(12,11,12,EdgeType::UNDIRECTED);
	gv->addEdge(13,11,13,EdgeType::UNDIRECTED);
	for (int i=0;i<7;i++){
	sleep(1);
	gv->removeNode(12+i*4);
	gv->removeNode(13+i*4);
	gv->addNode(14+i*4,250,550);
	gv->addNode(15+i*4,350,550);
	gv->addEdge(14+i*4,11,14+i*4,EdgeType::UNDIRECTED);
	gv->addEdge(15+i*4,11,15+i*4,EdgeType::UNDIRECTED);
	gv->rearrange();
	sleep(1);
	gv->removeNode(14+i*4);
	gv->removeNode(15+i*4);
	gv->addNode(16+i*4,200,550);
	gv->addNode(17+i*4,400,550);
	gv->addEdge(16+i*4,11,16+i*4,EdgeType::UNDIRECTED);
	gv->addEdge(17+i*4,11,17+i*4,EdgeType::UNDIRECTED);
	gv->rearrange();}
}

void exercicio3()
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
	//exercicio1();
	//exercicio2();
	exercicio3();
	getchar();
	return 0;
}
