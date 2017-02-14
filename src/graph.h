#ifndef GRAPH_H
#define GRAPH_H

#include "graphadt.h"
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <cmath>
#include <ctime>

class Graph : public GraphADT {

public:
    // General graph methods
    Node* aVertex();
    void insertVertex(Node* n);
    void insertEdge(Node* v, Node* w, int i = 0);
    void removeVertex(Node* n);
    void removeEdge(Edge* e);
    std::vector<Edge*>& incidentEdges(Node* n);
    Node** endVertices(Edge* e);
    Node* opposite(Node* n, Edge* e);
    bool areAdjacent(Node* v, Node* w);
    int weight(Node* v, Node* w);

    // Methods for directed edges
    bool isDirected(Edge* e);
    void insertDirectedEdge(Node* v, Node* w, int i = 0);
    Node* origin(Edge* e);
    Node* destination(Edge* e);

    // Generic methods
    int numVertices();
    int numEdges();
    std::vector<Node*>& vertices();
    std::vector<Edge*>& edges();

    // Algorithms
    void depthFirstTraversal(Node* n);
    void breadthFirstTraversal(Node* n);
    std::vector<Edge*> primsAlgorithm();
    void dijkstrasAlgorithm(Node* n);

    void printMatrix();
    Node* findUnvisitedNode(Edge* e);
    std::vector<Node*> vertexCover();
    bool verifyVertexCover(std::vector<Node*> vertexCover);

private:
    void setAllUnvisited();
    std::vector<Node*> verticeList;
    std::vector<Edge*> edgeList;
};


Node* Graph::aVertex()
{
    if(verticeList.size() > 0)
        return verticeList.at(0);
    else
        return NULL;
}

void Graph::insertVertex(Node* n)
{
    verticeList.push_back(n);
}

void Graph::insertEdge(Node *v, Node *w, int i)
{
    Edge* e = new Edge(v, w, i);
    edgeList.push_back(e);
    v->edgeList.push_back(e);
    w->edgeList.push_back(e);
}


void Graph::removeEdge(Edge *e)
{
    std::vector<Edge*>::iterator it1 = std::find(edgeList.begin(), edgeList.end(), e);
    if(it1 != edgeList.end()) {
        // kanten har to endepunkter; må fjerne kanten fra kantlisten til disse
        for(int i = 0; i < 2; i++) {
            std::vector<Edge*> nodensKanter = (*it1)->endpoint[i]->edgeList;
            std::vector<Edge*>::iterator it2 = std::find(nodensKanter.begin(), nodensKanter.end(), e);
                if(it2 != nodensKanter.end()) {
                    nodensKanter.erase(it2);
                }
        }
        edgeList.erase(it1);
        delete e;
        e = NULL;
    }
}

void Graph::removeVertex(Node *n)
{
    std::vector<Node*>::iterator i = std::find(verticeList.begin(), verticeList.end(),n);
    if(i != verticeList.end()) {
        for(Edge* e : (*i)->edgeList) {
            removeEdge(e);
        }
        verticeList.erase(i);
        delete n;
        n = NULL;
    }
}

std::vector<Edge*>& Graph::incidentEdges(Node *n)
{
    return n->edgeList;
}

Node** Graph::endVertices(Edge *e)
{
    return e->endpoint;
}

Node* Graph::opposite(Node *n, Edge *e)
{
    if(e->endpoint[0] == n)
        return e->endpoint[1];
    else
        return e->endpoint[0];
}

bool Graph::areAdjacent(Node *v, Node *w)
{
    std::vector<Edge*>::iterator i = v->edgeList.begin();
    while(i != v->edgeList.end()){
        if(((*i)->endpoint[0] == w || (*i)->endpoint[1] == w)) {
            return true;
        }
    }
    return false;
}

bool Graph::isDirected(Edge *e)
{
    return e->isDirected;
}

void Graph::insertDirectedEdge(Node *v, Node *w, int i)
{
    Edge* e = new Edge(v, w, i, true);
    edgeList.push_back(e);
    v->edgeList.push_back(e);
    w->edgeList.push_back(e);
}

Node *Graph::origin(Edge *e)
{
    if(e->isDirected)
        return e->endpoint[0];
    else
        return NULL;
}

Node *Graph::destination(Edge *e)
{
    if(e->isDirected)
        return e->endpoint[1];
    else
        return NULL;
}

int Graph::numVertices()
{
    return verticeList.size();
}

int Graph::numEdges()
{
    return edgeList.size();
}

std::vector<Node*>& Graph::vertices()
{
    return verticeList;
}

std::vector<Edge*>& Graph::edges()
{
    return edgeList;
}

void Graph::depthFirstTraversal(Node* n)
{
    setAllUnvisited();
    std::stack<Node*> verticeStack;
    verticeStack.push(n);
    while(!verticeStack.empty()){
        Node* v = verticeStack.top();
        verticeStack.pop();
        if(!v->visited){
            for(std::vector<Edge*>::iterator i = v->edgeList.begin(); i != v->edgeList.end(); i++){
                verticeStack.push(opposite(v, *i));
            }
            std::cout << v->data << " ";
            v->visited = true;
        }
    }
    std::cout << std::endl;
}

void Graph::breadthFirstTraversal(Node* n)
{
    setAllUnvisited();
    std::queue<Node*> ko;
    ko.push(n);
    while(!ko.empty()) {
        Node* v = ko.front();
        ko.pop();
        if(!v->visited) {
            for(std::vector<Edge*>::iterator i = v->edgeList.begin(); i != v->edgeList.end(); i++) {
                ko.push(opposite(v,*i));
            }
            std::cout << v->data << " ";
            v->visited = true;
        }
    }
    std::cout << std::endl;
}

void Graph::setAllUnvisited()
{
    for(std::vector<Node*>::iterator i = verticeList.begin(); i != verticeList.end(); i++){
        (*i)->visited = false;
    }
}

/*
 *  Here we create a functor class that we can use to create a priority queue for Edges
 */
class CompareEdges
{
public:
    bool operator()(const Edge* e, const Edge* f)
    {
        /* Returns true if edge e has higher weight than edge f */
        return e->weight > f->weight;
    }
};

/*
 *  Here we create a functor class that we can use to create a priority queue for Nodes
 */
class CompareNodeDistance
{
public:
    bool operator()(const Node* v, const Node* w)
    {
        /* Returns true if node v has longer path than node w */
        return v->distance > w->distance;
    }
};

void Graph::dijkstrasAlgorithm(Node *n)
{
    setAllUnvisited();
    n->distance = 0;
    std::priority_queue<Node*,std::vector<Node*>,CompareNodeDistance> unvisitedNodes(verticeList.begin(), verticeList.end());

    while(!unvisitedNodes.empty()){
        // Find min distance node
        Node* v = unvisitedNodes.top();
        unvisitedNodes.pop();
        for(std::vector<Edge*>::iterator i = v->edgeList.begin(); i != v->edgeList.end(); i++){
            Node* w = opposite(v,*i);
            int dist = v->distance + (*i)->weight;
            if( dist < w->distance ){
                w->distance = dist;
                w->previous = v;
            }
        }
    }
}

std::vector<Edge*> Graph::primsAlgorithm()
{
    setAllUnvisited();

    // vi lager et mst bestående av kanter
    std::vector<Edge*> mstEdges;
    // tilgjengelige kanter etterhvert som vi bygger mst
    std::priority_queue<Edge*,std::vector<Edge*>,CompareEdges> kandidatKanter;

    // velger en vilkårlig startnode og setter den som besøkt
    Node* v = verticeList.front();
    v->visited = true;
    unsigned int visitedNodes = 1;

    // legger til alle nodens nabokanter
    for(Edge* ed : v->edgeList) {
        kandidatKanter.push(ed);
    }

    while(visitedNodes < verticeList.size()){

        // minste kant
        Edge* e = kandidatKanter.top();
        kandidatKanter.pop();

        // finner en ubesøkt node på denne kanten, setter den som besøkt,
        // og legger til alle kantene til denne noden i køen med kandidatkanter.
        Node* v = findUnvisitedNode(e);
        if(v != NULL) {
            v->visited = true;
            mstEdges.push_back(e);
            visitedNodes++;

            for(Edge* edgy : v->edgeList) {
                kandidatKanter.push(edgy);
            }
        }
    }
    return mstEdges;
}

/**
 * @brief Hvis dette er en kant hvor den ene noden som utgjør kanten er ubesøkt,
  vil den ubesøkte noden returneres. NULL hvis begge/ingen er besøkt
 * @param e kanten vi vil finne en ubesøkt node på
 * @return
 */
Node* Graph::findUnvisitedNode(Edge* e) {
    if((e->endpoint[0]->visited && !e->endpoint[1]->visited)) {
        return e->endpoint[1];
    }
    else if((e->endpoint[1]->visited && !e->endpoint[0]->visited)) {
        return e->endpoint[0];
    }
    return NULL; // begge er besøkt/ubesøkt
}


/*======================================================*
 *  O(n * n + 2) = O(n^2)                               *
 *======================================================*/

std::vector<Node*> Graph::vertexCover() {


    setAllUnvisited();
    std::vector<Node*> vertexCover;
    std::vector<Edge*> kanter = edgeList;

    srand(time(0));
    while(!kanter.empty()) {

        Edge* e = kanter.at(std::rand() % kanter.size());

        for(unsigned int i = 0; i < 2; i++) {
            e->endpoint[i]->visited = true;
            vertexCover.push_back(e->endpoint[i]);
        }

        for(std::vector<Edge*>::iterator it = kanter.begin(); it != kanter.end(); it++){
            if((*it)->endpoint[0]->visited ||(*it)->endpoint[1]->visited)
                kanter.erase(it--);
        }
    }

    return vertexCover;
}


/*======================================================*
 * I verste tilfelle (gyldige vertex-cover) vil vi få
 * O(k) * O(n*n), hvor k er antall kanter og n er antall noder.
 * Siden maksimum antall kanter i en urettet graf er gitt ved
 * k = n(n-1)/2 (komplett graf)
 * får vi
 *
 * 1/2 n(n-1) * n^2, som gir O(n^4)
 *
 *======================================================*/
bool Graph::verifyVertexCover(std::vector<Node*> vertexCover) {
    bool valid = true;

    for(std::vector<Edge*>::iterator edgeIt = edgeList.begin(); edgeIt != edgeList.end() && valid; edgeIt++) {
        std::vector<Node*>::iterator nodeIt1 = std::find(vertexCover.begin(), vertexCover.end(), (*edgeIt)->endpoint[0]);
        // trenger bare sjekke node nr 2 hvis node nr 1 ikke er med
        if(nodeIt1 == vertexCover.end()) {
            std::vector<Node*>::iterator nodeIt2 = std::find(vertexCover.begin(), vertexCover.end(), (*edgeIt)->endpoint[1]);
            if(nodeIt2 == vertexCover.end()) valid = false;
        }
    }

    return valid;
}


#endif // GRAPH_H
