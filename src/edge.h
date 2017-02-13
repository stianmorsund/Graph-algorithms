#ifndef EDGE_H
#define EDGE_H

class Node;

class Edge {
public:
    Edge(Node* v, Node* w, int wt = 0, bool d = false);
    bool isDirected;
    int weight;
    Node* endpoint[2];
};

Edge::Edge(Node* v, Node* w, int wt, bool d){
    endpoint[0] = v;
    endpoint[1] = w;
    weight = wt;
    isDirected = d;
}

#endif // EDGE_H
