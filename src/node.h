#ifndef NODE_H
#define NODE_H
#include <vector>
#include<climits>
#include<cstdlib>
#include "edge.h"

class Node {
public:
    Node(int d) : data(d), visited(false), distance(INT_MAX), previous(NULL){}
    ~Node() { edgeList.clear();}
    char data;
    bool visited;
    int distance;
    Node* previous;
    std::vector<Edge*> edgeList;

};

#endif // NODE_H
