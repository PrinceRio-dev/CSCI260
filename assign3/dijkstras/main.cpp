#include <iostream>
#include "graph.hpp"

int main()
{
	graph G(10);
	
	G.set_adjacency(0, 1, 0.5);
	G.set_adjacency(0, 2, 3.0);
	G.set_adjacency(1, 3, 3.0);
	G.set_adjacency(1, 4, 0.5);
	G.set_adjacency(1, 5, 3.0);
	G.set_adjacency(2, 3, 3.0);
	G.set_adjacency(3, 4, 3.0);
	G.set_adjacency(3, 6, 3.0);
	G.set_adjacency(4, 5, 3.0);
	G.set_adjacency(4, 6, 0.5);
	G.set_adjacency(5, 6, 3.0);
	G.set_adjacency(5, 7, 0.5);
	G.set_adjacency(5, 8, 0.5);
	G.set_adjacency(6, 8, 0.5);
	G.set_adjacency(7, 8, 3.0);
	G.set_adjacency(7, 9, 0.5);
	G.set_adjacency(8, 9, 3.0);
	
	G.print();
	std::cout << std::endl;
	
	// testing dijkstra's
	double *dist_to = new double[G.order()];
	
	graph *SPT = graph::dijkstra(G, dist_to, 0);
	
	SPT->print();
	
	// std::cout << std::endl;
	// for (int i = 0; i < G.order(); i++)
	// 	std::cout << "dist_to[" << i << "] = " << dist_to[i] << std::endl;
	// std::cout << std::endl;
	
	return EXIT_SUCCESS;
}
