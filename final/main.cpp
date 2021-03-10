#include <iostream>
#include "min_heap.hpp"
#include "graph.hpp"
using namespace std;

int main()
{
	graph G(16);
    
	cout << endl;
	cout << "Inserting this data into the graph:" << endl;

	//adding the given data into the graph
	G.set_adjacency(0,1,0.1);
	G.set_adjacency(0,4,3.2);
	G.set_adjacency(0,12,1.5);

	G.set_adjacency(1,2,0.5);
	G.set_adjacency(1,4,0.2);
	
	G.set_adjacency(2,3,0.2);
	G.set_adjacency(2,5,3.2);

	G.set_adjacency(3,5,0.5);
	G.set_adjacency(3,15,3.2);

	G.set_adjacency(4,5,3.2);
	G.set_adjacency(4,6,0.5);

	G.set_adjacency(5,7,3.2);
	
	G.set_adjacency(6,7,0.2);
	G.set_adjacency(6,8,0.5);
	
	G.set_adjacency(7,9,0.2);
	
	G.set_adjacency(8,9,3.2);
	G.set_adjacency(8,10,0.5);
	
	G.set_adjacency(9,11,0.5);
	
	G.set_adjacency(10,11,0.2);
	G.set_adjacency(10,12,0.2);
	G.set_adjacency(10,13,3.2);

	G.set_adjacency(11,14,0.2);
	G.set_adjacency(11,15,3.2);
	
	G.set_adjacency(12,13,3.2);

	G.set_adjacency(13,14,3.2);
	
	G.set_adjacency(14,15,0.5);
    
    G.print();
    cout << endl;
    cout << "Printing out MST using KRUSKAL's algorithm:" << endl;

    //making the pointer, to call the kruskals function
    graph *MST=graph::kruskal(G);
	//we are calling the function print
	MST->print();

    //graph *MST1=graph::prim(G);
    //cout << endl;
    //MST1->print();
	
	return 0;
}