#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "SupportPoint.h"
#include "Package.h"

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

struct nodeEdge {
    std::vector<Point *> points;
    std::vector<Road *> roads;
    int lenght;

} typedef nodeEdge_t;

bool compSL(nodeEdge_t i,nodeEdge_t j) {
    return i.lenght < j.lenght;
}

GraphViewer *gv;
nodeEdge_t mainMap;
vector<Vehicle> Fleet;
vector<vector<Package>> PackagesToDelivery; // add comentario que eu nao sei o que é esta merda
Point * centralPoint;

std::vector<nodeEdge_t *> nearestNeighbour(std::vector<Package *> packages);

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
        mainMap.points.push_back(new Point(id,  x -xOffset, yOffset -y));
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
    centralPoint = findPoint(1052802810);

}

void initMap() {
    gv = new GraphViewer(1000, 700, false);
    gv->createWindow(1000, 700);
    gv->defineVertexColor("black");
    gv->defineEdgeColor("black");
}

void updateColors(nodeEdge_t graph, int color) {
    string cor = "";
    if (color == 1) cor = "RED";
    if (color == 2) cor = "PINK";
    if (color == 3) cor = "BLUE";
    if (color == 4) cor = "LIGH_GRAY"; //sim, tou a limitar o numero de carrinhas a 4 */

    for (long unsigned int i=1; i<graph.points.size(); i++) {
        if (graph.points[i]->getType()==DELIVERY)
            gv->setVertexColor(graph.points[i]->getID(),"YELLOW");
        else if (graph.points[i]->getType()==SOURCE)
            gv->setVertexColor(graph.points[i]->getID(),"ORANGE");
        else gv->setVertexColor(graph.points[i]->getID(),"GREEN");
    }
    for (long unsigned int i=0; i<graph.roads.size(); i++) {
        gv->setEdgeColor(graph.roads[i]->getID(), cor);
    }
    
}

void displayMap(nodeEdge_t graph) {
    for(auto p : graph.points) {
        gv->addNode(p->getID(), p->getX(), p->getY());
        /*if (p->getType()==DELIVERY) gv->setVertexColor(p->getID(),ORANGE);
        else if (p->getType()==SOURCE) gv->setVertexColor(p->getID(),YELLOW);
        else if (p->getType()==PATH) gv->setVertexColor(p->getID(),GREEN);*/

        // gv->setVertexLabel(p->getID(), "cenas");
    }
    for(auto e : graph.roads) {
        gv->addEdge(e->getID(),e->getSource()->getID(),e->getDest()->getID(), EdgeType::UNDIRECTED);
        //gv->setEdgeLabel(e->getID(),to_string( e->getWeight()));
    }
    gv->rearrange();
}

void dijkstra(int sourceID, int destID) {
    cout << "Startin dijkstra\n";
    cout << sourceID<<"\t"<<destID<<endl;
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

}

nodeEdge_t getPath(/*int sourceID, */int destID) {

    nodeEdge_t ret;
    int x=0;
    vector<Point *> path;
    vector<Road *> roads, temp;
    Point * dest = findPoint(destID);
    Point * source = dest->getPath();

    path.push_back(dest);
    // dest->setType(DELIVERY);
    while(source != nullptr) {
        temp=dest->getRoads();
        //source->setType(PATH);
        path.push_back(source);
        for (unsigned int i=0; i<temp.size(); i++)
            if (temp[i]->getDest()==source) {
                roads.push_back(temp[i]);
                x+=temp[i]->getWeight();
            }
        dest = source;
        source = source->getPath();
    }
    //path[path.size()-1]->setType(SOURCE);
    path.reserve(path.size());
    cout << "Ret path\n";
    ret.points = path;
    ret.roads = roads;
    ret.lenght = x;
    if (x==0) cout<<"Couldn't find path.\n";
    return ret;
}

void AdicionaEncomenda(int source, int delivery) {
    Package pacote;
    Point* Source;
    Point* Delivery;
    //int source=source;//26130574;
    //int delivery=dest;//=26130608;
    cout << "ID of the source point?" << endl;
    //cin >> source;
    cout << "ID of the delivery point?" << endl;
    //cin >> delivery;
    Source = findPoint(source);
    Delivery = findPoint(delivery);
    if(Source != nullptr && Delivery != nullptr) {
        Source->setType(SOURCE);
        Delivery->setType(DELIVERY);
        pacote.setPickUpPoint(Source);
        pacote.setDeliveryPoint(Delivery);
        PackagesToDelivery[0].push_back(pacote);
        cout << "Your order has been added" << endl;
        //cout<<pacote->getPickUpPoint()->getID()<<"\t"<<pacote->getDeliveryPoint()->getID()<<endl;

    }
    else cout << "Your order hasn't been added." << endl << "Please check is the points ID's are correct" << endl;

}

void distributePackages(int n){
    vector<Package> vec;
    float angle, divangle=360/n;
    cout<<"Divangle:"<<divangle;
    for (int i=1;i<=n;i++){
        PackagesToDelivery.push_back(vec);
    }
    cout << "SIZE" << PackagesToDelivery[0].size();
    for (long unsigned i=0;i<PackagesToDelivery[0].size();i++){
        angle = -180 / M_PI *atan2(PackagesToDelivery[0][i].getPickUpPoint()->getY()-centralPoint->getY(),PackagesToDelivery[0][i].getPickUpPoint()->getX()- centralPoint->getX());
        if (angle<0) angle+=360;
        cout<<"\t"<<angle;
        PackagesToDelivery[ceil(angle/divangle)].push_back(PackagesToDelivery[0][i]);
    }
    
}

void menuControler() {
    cout << endl;
    cout << " _______________________________________________________________________" << endl;
    cout << "|                         Chose one option                              |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|      1- See the map                                                   |" << endl;
    cout << "|      2- See vehicle path to satisfy packages                          |" << endl;
    cout << "|      3- Exit                                                          |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|_______________________________________________________________________|" << endl;

    int opcao;
    cin >> opcao;
    switch(opcao) {
    case 1: {
        cout << "The red points represent pickup points and the green ones represent delivery points." << endl;
        displayMap(mainMap);
        break;
    }
    case 2: {
        break;
    }
    case 3: {
        break;
    }
    default:
        break;
    }
}

void menuBase() {
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

    switch(opcao) {
    case 1: {
        menuUser();
        break;
    }
    case 2: {
        menuControler();
        break;
    }
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
    cout << "|      1 - New Order                                                    |" << endl;
    cout << "|      2 - Exit                                                         |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|                                                                       |" << endl;
    cout << "|_______________________________________________________________________|" << endl;

    int opcao;
    cin >> opcao;

    switch(opcao) {
    case 1: {
        AdicionaEncomenda(26130574,26130608);
        menuUser();
        break;
    }
    case 2: {
        menuBase();
        break;
    }
    }
}


std::vector<nodeEdge_t *> nearestNeighbour(std::vector<Package> packages, Point* supportPoint, int color) {

    cout << "Starting NN\n";
    std::vector<nodeEdge_t *> finalPaths; //vector a retornar

    std::vector<Point*> pointsToGo; //pontos a precorrer a cada iteração

    for(auto p : packages) { //PUP iniciais
        pointsToGo.push_back(p.getPickUpPoint());
        cout << "Added PUP "<<p.getPickUpPoint()->getID()<<"\t"<<p.getDeliveryPoint()->getID()<<endl;
    }

    std::vector<nodeEdge_t> dists;

    Point * currentPoint = supportPoint;
    while(pointsToGo.size() != 0) {
        //guarda em dists os caminhos todos calculados
        cout << "while\n";
        for(unsigned int i = 0; i < pointsToGo.size(); i++) {
            dijkstra(currentPoint->getID(), pointsToGo.at(i)->getID());
            dists.push_back(getPath(pointsToGo.at(i)->getID()));
        }

        auto bestPath = min_element(dists.begin(),dists.end(),compSL);//procura o menor caminho
        int temp =  bestPath - dists.begin();//index do menor caminho
        finalPaths.push_back(&(dists.at(temp)));//coloca o caminho no vetor a retornar
        updateColors(dists.at(temp),1);
        currentPoint = pointsToGo.at(temp);//atualiza a posição atual
        cout << "AAA: " << pointsToGo.at(temp)->getType() ;
        if(pointsToGo.at(temp)->getType() == SOURCE) { //Se o ponto era uma Source, coloca a delivery
            pointsToGo.at(temp) = packages.at(temp).getDeliveryPoint();
            cout << "switch\n";
        } else if(pointsToGo.at(temp)->getType() == DELIVERY) { //se era uma delivery retira do vetor
            pointsToGo.erase(pointsToGo.begin()+temp);
            cout << "remove\n";
        }
        cout << "Size "<< pointsToGo.size() << endl;
        dists.clear();//prepara proxima iteração
        cout << "Iter\n";
    }

    dijkstra(currentPoint->getID(), supportPoint->getID());
    auto retPath = getPath(supportPoint->getID());
    updateColors(retPath,color);
    finalPaths.push_back(&retPath);
    gv->setVertexColor(supportPoint->getID(),RED);

    return finalPaths;
}

int main() {
    initMap();
    readMap("Fafe");
    vector<Package> vec;
    PackagesToDelivery.push_back(vec);
    AdicionaEncomenda(26130574,26130608);
    AdicionaEncomenda(1052803108,1242959130);
    AdicionaEncomenda(1052802706,1229047667);
    distributePackages(2);
    cout<<"Sizes:"<<PackagesToDelivery.size()<<"\t"<<PackagesToDelivery[1].size()<<"\t"<<PackagesToDelivery[2].size()<<endl;
    for (long unsigned i=1;i<PackagesToDelivery.size();i++)
        std::vector<nodeEdge_t *> nn = nearestNeighbour(PackagesToDelivery[i], centralPoint, i);
    //cout<<PackagesToDelivery[0].getPickUpPoint()->getID()<<"\t"<<PackagesToDelivery[0].getDeliveryPoint()->getID()<<endl;
    //cout<<PackagesToDelivery[1].getPickUpPoint()->getID()<<"\t"<<PackagesToDelivery[1].getDeliveryPoint()->getID()<<endl;
    
    //for(auto n : nn) {
        //updateColors(*n);
    //}
    
    //getchar();
    //gv->closeWindow();

     displayMap(mainMap);
    //menuBase();

    /*int source=402328721,dest= 1238420455;
    //dijkstra(402328721, 1238420455);
    //displayMap(getPath(402328721,1238420455), r);

    /* int opcao;
    cin >> opcao;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000,'\n');
    }
    switch(opcao) {
    case 1: {

        while (true) {
            cout<<"Source:";
           /* cin>>source;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000,'\n');
                continue;
            }
            cout<<"Destination:";
           /* cin>>dest;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000,'\n');
                continue;
            }
            break;
        }
        initMap();
        readMap("Porto");
        //dijkstra(source,dest);
        displayMap(mainMap);
        break;
    }
    case 2: {
        initMap();
        readMap("Fafe");
        srand(time(NULL));
        int source=mainMap.points[rand()%mainMap.points.size()]->getID(),dest=mainMap.points[rand()%mainMap.points.size()]->getID();
        cout<<"Origin: "<<source<<endl<<"Destination: "<<dest<<endl;
        dijkstra(source,dest);
        nodeEdge_t temp=getPath(dest);
        /*for (long unsigned int i=0; i<temp.points.size(); i++) {
            if (i==0||i==temp.points.size()-1)
                gv->setVertexColor(temp.points[i]->getID(),"yellow");
            else gv->setVertexColor(temp.points[i]->getID(),"green");
        }
        for (long unsigned int i=0; i<temp.roads.size(); i++) {
            gv->setEdgeColor(temp.roads[i]->getID(),"green");
        }*

        displayMap(mainMap);

        break;
    }
    case 3:
        menuBase();
        break;
    }*/
}
