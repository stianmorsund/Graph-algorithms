#ifndef GRAFADT_H
#define GRAFADT_H
#include <vector>
#include "node.h"
#include "edge.h"

class GraphADT {

    // General graph methods
    virtual Node* aVertex() = 0;
    virtual void insertVertex(Node* n) = 0;
    virtual void insertEdge(Node* v, Node* w, int i) = 0;
    virtual void removeVertex(Node* n) = 0;
    virtual void removeEdge(Edge* e) = 0;
    virtual std::vector<Edge*>& incidentEdges(Node* n) = 0;
    virtual Node** endVertices(Edge* e) = 0;
    virtual Node* opposite(Node* n, Edge* e) = 0;
    virtual bool areAdjacent(Node* v, Node* w) = 0;

    // Methods for directed edges
    virtual bool isDirected(Edge* e) = 0;
    virtual void insertDirectedEdge(Node* v, Node* w, int i) = 0;
    virtual Node* origin(Edge* e) = 0;
    virtual Node* destination(Edge* e) = 0;

    // Generic methods
    virtual int numVertices() = 0;
    virtual int numEdges() = 0;
    virtual std::vector<Node*>& vertices() = 0;
    virtual std::vector<Edge*>& edges() = 0;
};

#endif // GRAFADT_H
