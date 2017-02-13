#include <iostream>
#include "graph.h"

using namespace std;

int main()
{

    Graph* graf = new Graph();

    Node* a = new Node(1);
    a->data = '1';
    Node* b = new Node(2);
    b->data = '2';
    Node* c = new Node(3);
    c->data = '3';
    Node* d = new Node(4);
    d->data = '4';
    Node* e = new Node(5);
    e->data = '5';
    Node* f = new Node(6);
    f->data = '6';
    Node* g = new Node(7);
    f->data = '7';

    graf->insertVertex(a);
    graf->insertVertex(b);
    graf->insertVertex(c);
    graf->insertVertex(d);
    graf->insertVertex(e);
    graf->insertVertex(f);
    graf->insertVertex(g);


    graf->insertEdge(a,d);
    graf->insertEdge(a,b);
    graf->insertEdge(b,e);
    graf->insertEdge(b,c);
    graf->insertEdge(e,f);
    graf->insertEdge(c,f);
    graf->insertEdge(c,g);



 std::vector<Node*> vertexCover;

     vertexCover = graf->vertexCover();
        for(Node* n : vertexCover) {
            std::cout << n->data << " ";
        }


    (graf->verifyVertexCover(vertexCover)) ? std::cout << "Gyldig vertexcover" : std::cout << "Ikke gyldig vertexcover";

    std::cout << std::endl;

    std::vector<Node*> vertexCoverSomIkkeErGyldig = {a,b,g};

    (graf->verifyVertexCover(vertexCoverSomIkkeErGyldig)) ? std::cout << "Gyldig vertexcover" : std::cout << "Ikke gyldig vertexcover";

    std::cout << std::endl;



    return 0;
}
