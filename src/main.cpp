#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "SupportPoint.h"

#include "graphviewer.h"
#include "SupportPoint.h"
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

Point * findPoint(int id) {

    for(auto p : points) {
        if(p->getID() == id) {
            return p;
        }
    }
    cout << "Point not found\n";
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
        Point * source = findPoint(x);
        Point * dest = findPoint(y);
        Road * r1 = new Road(id,source, dest);
        Road * r2 = new Road(id,dest, source);//Se merdar o problema é o id

        source->addRoad(r1);
        dest->addRoad(r2);

        roads.push_back(r1);
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

void displayMap(vector<Point *> vecp, vector<Road *> r) {

    for(auto p : vecp) {
        gv->addNode(p->getID(), p->getX(), p->getY());
        // gv->setVertexLabel(p->getID(), "cenas");
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
        cout << "antes\n";

        if(source->equals(*dest)) {
            break;
        }
        cout << "depois\n";

        cout << source->getRoads().at(0)->getID() << endl;

        for(auto e : source->getRoads()) {
            oldDistance = e->getDest()->getDist();
            cout << e->getID();
            if(e->getDest()->getDist() > source->getDist() + e->getWeight()) {
                e->getDest()->setDist(source->getDist() + e->getWeight());
                e->getDest()->setPath(source);
                cout << source->getID();
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

    path.push_back(dest);
    while(source != nullptr) {
        path.push_back(source);
        cout << source->getID() << endl;
        source = source->getPath();
    }

    path.reserve(path.size());
    cout << "Ret path\n";
    return path;
}
void AdicionaEncomenda() {

}
void menuUser() {
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

    switch(opcao) {
    case 1:
    {
        break;
    }
    case 2: {
        break;
    }
    }
}
void menuBase(){
	SupportPoint pontoApoio;
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
        if (cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
        }
		switch(opcao){
		case 1:
		{
			menuUser();
			break;
		}
		case 2:
		{
			break;		}
		case 3:
		{
			cout << "The program will end now!" << endl;
			exit(0);
		}
		default: {
			cout << "Sorry, not a valid choice. Choose again." << endl;
			/*Sleep(3000);
			system("CLS");*/
			menuBase();  //eclipse es burro ou eu sou burra//tu es burra
			break;
		}
		}
}
int main() {
	menuBase();
    initMap();
    readMap("Fafe");

    displayMap(points,roads);
    dijkstra(1238420328, 1238420266);
    
    //std::vector<Road * > r;
    //displayMap(getPath(402328721,1238420455), r);

    getchar();//porque?
    return 0;
}


