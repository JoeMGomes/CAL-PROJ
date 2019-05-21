#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SupportPoint.h"
#include "Package.h"

#include "Point.h"
#include "Road.h"
#include "MutablePriorityQueue.h"
#ifdef linux
#else
#include <Windows.h>
#endif

//Variaveis globais because fuck it
GraphViewer *gv;
std::vector<Point*> points;
std::vector<Road* > roads;
vector<Package> PackagesToDelivery;
vector<Vehicle> Fleet;

void menuUser();

Point * findPoint(int id) {

    for(auto p : points) {
        if(p->getID() == id) {
            cout << "got it\n";
            return p;
        }
    }
    return nullptr;
}

void readMap(string cityName) {

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

void displayMap(vector<Point *> p, vector<Road *> r) {

    for(auto p : p) {
        gv->addNode(p->getID(), p->getX(), p->getY());
       // gv->setVertexLabel(p->getID(), "cenas");

        gv->setVertexColor(p->getID(),RED);
    }

    for(auto e : r) {
        gv->addEdge(e->getID(),e->getSource()->getID(),e->getDest()->getID(), EdgeType::UNDIRECTED);
        //gv->setEdgeLabel(e->getID(),to_string( e->getWeight()));
    }
}

void dijkstra(int sourceID, int destID) {
    cout << "Startin dijkstra\n";
    Point * source = findPoint(sourceID);
    Point * dest = findPoint(destID);
    double oldDistance;

    for(auto p : points) {
        p->setDist(SIZE_MAX);
        p->setPath(nullptr);
        p->queueIndex = 0;
    }

    source->setDist(0);

    MutablePriorityQueue q;
    q.insert(source);

    while(!q.empty()) {

        source = q.extractMin();

        if(source->equals(*dest)) {
            break;
        }

        for(auto e : source->getRoads()) {
            oldDistance = e->getDest()->getDist();

            if(e->getDest()->getDist() > source->getDist() + e->getWeight()) {
                e->getDest()->setDist(source->getDist() + e->getWeight());
                e->getDest()->setPath(source);
                if(oldDistance == SIZE_MAX) {
                    q.insert(e->getDest());
                } else {
                    q.decreaseKey(e->getDest());
                }
            }
        }
    }
            cout << "Found path\n";

}

std::vector<Point *> getPath(int sourceID, int destID) {

    vector<Point *> path;
    Point * dest = findPoint(destID);
    Point * source = dest->getPath();

    while(source != nullptr) {
        path.push_back(source);
        source = source->getPath();
    }

    path.reserve(path.size());
    cout << "Ret path\n";
    return path;
}
void AdicionaEncomenda(){
	Package pacote;
	Point* Source;
	Point* Delivery;
	int source;
	int delivery;
	cout << "ID of the source point?" << endl;
	cin >> source;
	cout << "ID of the delivery point?" << endl;
	cin >> delivery;
	Source = findPoint(source);
	Delivery = findPoint(delivery);
	pacote.setPickUpPoint(Source);
	pacote.setDeliveryPoint(Delivery);
	PackagesToDelivery.push_back(pacote);
}
void menuControler(){
				cout << endl;
				cout << " _______________________________________________________________________" << endl;
				cout << "|                         Chose one option                              |" << endl;
				cout << "|                                                                       |" << endl;
				cout << "|      1 - See the map                                                  |" << endl;
				cout << "|      2 - See pick up points                                           |" << endl;
				cout << "|      3 - See delivery points                                          |" << endl;
				cout << "|      4 - See vehicle path to satisfy packages                         |" << endl;
				cout << "|                                                                       |" << endl;
				cout << "|_______________________________________________________________________|" << endl;

				int opcao;
				cin >> opcao;
				switch(opcao){
				case 1:{
					  displayMap(points,roads);
					break;
				}
				case 2:{
					break;
				}
				case 3:{
					break;
				}
				case 4:{
					break;
				}

				}

}
void menuBase(){
		cout << endl;
		cout << " _______________________________________________________________________" << endl;
		cout << "|                         Chose one option                              |" << endl;
		cout << "|                                                                       |" << endl;
		cout << "|      1 - I am a user                                                  |" << endl;
		cout << "|      2 - Control of the company                                       |" << endl;
		cout << "|      3 - Exit                                                         |" << endl;
		cout << "|                                                                       |" << endl;
		cout << "|_______________________________________________________________________|" << endl;

		int opcao;
		cin >> opcao;

		switch(opcao){
		case 1:
		{
			menuUser();
			break;
		}
		case 2:
		{
			menuControler();
			break;
		}
		case 3:
		{
			cout << "The program will end now!" << endl;
			break;
		}
		default: {
			cout << "Sorry, not a Valid Choice. \n"
			<< "Choose again.\n";
			/*Sleep(3000);
			system("CLS");
			menuBase(); */ //eclipse es burro ou eu sou burra
			break;
		}
		}
}
void menuUser(){
			cout << endl;
			cout << " _______________________________________________________________________" << endl;
			cout << "|                         Chose one option                              |" << endl;
			cout << "|                                                                       |" << endl;
			cout << "|      1 - Ask for a delivery                                           |" << endl;
			cout << "|      2 - Exit                                                         |" << endl;
			cout << "|                                                                       |" << endl;
			cout << "|                                                                       |" << endl;
			cout << "|_______________________________________________________________________|" << endl;

	int opcao;
	cin >> opcao;

	switch(opcao){
	case 1:
	{
		AdicionaEncomenda();
		break;
	}
	case 2:{
		menuBase();
		break;
	}
	}
}

int main() {
	initMap();
	readMap("Fafe");
	menuBase();


    //dijkstra(402328721, 1238420455);
    std::vector<Road * > r;
    //displayMap(getPath(402328721,1238420455), r);

   // displayMap(points,roads);


    getchar();
    return 0;
}


