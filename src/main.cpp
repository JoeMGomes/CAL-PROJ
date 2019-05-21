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
void menuUser();
void menuBase();

//Variaveis globais because fuck it

struct nodeEdge{
    std::vector<Point *> points;
    std::vector<Road *> roads;
} typedef nodeEdge_t;

GraphViewer *gv;
nodeEdge_t mainMap;

Point * findPoint(int id) {

    for(auto p : mainMap.points) {
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
        mainMap.points.push_back(new Point(id, x - xOffset, y - yOffset));
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

        mainMap.roads.push_back(r1);
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

void displayMap(nodeEdge_t graph) {

    for(auto p : graph.points) {
        gv->addNode(p->getID(), p->getX(), p->getY());
        // gv->setVertexLabel(p->getID(), "cenas");
    }

    for(auto e : graph.roads) {
        gv->addEdge(e->getID(),e->getSource()->getID(),e->getDest()->getID(), EdgeType::UNDIRECTED);
        //gv->setEdgeLabel(e->getID(),to_string( e->getWeight()));
    }
}

void dijkstra(int sourceID, int destID) {
    cout << "Startin dijkstra\n";
    Point * source = findPoint(sourceID);
    Point * dest = findPoint(destID);
    double oldDistance;

    for(auto p : mainMap.points) {
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

nodeEdge_t getPath(int sourceID, int destID) {

    nodeEdge_t ret;

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
    ret.points = path;

    return ret;
}
void AdicionaEncomenda() {
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
			menuUser();
			break;
		case 2:
			break;
		case 3:
			cout << "The program will end now!" << endl;
			exit(0);
		default:
			cout << "Sorry, not a valid choice. Choose again." << endl;
			menuBase();
			break;
	}
}

void menuUser() {
    cout << endl;
    cout << " _______________________________________________________________________" << endl;
    cout << "|                         Chose one option                              |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|      1 - Ask for a delivery                                           |" << endl;
    cout << "|      2 - Random delivery                                              |" << endl;
    cout << "|      3 - Exit                                                         |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|_______________________________________________________________________|" << endl;

    int opcao;
    cin >> opcao;
    if (cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');}
    switch(opcao) {
        case 1:{
            int source,dest;
            while (true){
                cout<<"Source:";cin>>source;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    continue;}
                cout<<"Destination:";cin>>dest;
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    continue;}
                break;}
            initMap();
            readMap("Fafe");
            dijkstra(source,dest);
            vector<Road * > r;
            displayMap(getPath(source,dest), r);
            break;}
        case 2:{
            initMap();
            readMap("Fafe");
            srand(time(NULL));
            int source=points[rand()%points.size()]->getID(),dest=points[rand()%points.size()]->getID();
            cout<<"Origin: "<<source<<endl<<"Destination: "<<dest<<endl;
            dijkstra(source,dest);
            vector<Road * > r;
            vector<Point *> p;
            p=getPath(source,dest);
            for (long unsigned int i=0;i<p.size();i++){
                if (i==0||i==p.size()-1)
                    gv->setVertexColor(points[i]->getID(),"yellow");
                else gv->setVertexColor(points[i]->getID(),"green");
            }
            displayMap(points,roads);

            break;}
        case 3: 
            menuBase();
            break;
    }
}

int main() {
	menuBase();

    getchar();//porque?
    return 0;
}


