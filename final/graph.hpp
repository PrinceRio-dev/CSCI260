#pragma once
#include "min_heap.hpp"
#include "list.hpp"
#include "UnionFind.hpp"

class graph
{
private:
	
	list **m_vertex;
	int m_E;
	int m_V;
	point *positions;
	
	void set_positions();
	void depth_first_traversal(int[], int&, int[], int[]);
	void set_edge(int, int, double);
	static int min_vertex(graph&, double*, int[]);
	static int relax(graph&, double*, int, int, int*);
	
public:
	
	graph();
	graph(int);
	~graph();
	
	void visit(graph&, int, min_heap*, int[]);
    static graph *prim(graph&);
	static graph *kruskal(graph&);
	int order();
	int size();
	int degree(int);
	
	int first(int);
	int next(int, int);
	
	bool is_edge(int,int);
	void set_adjacency(int,int,double=0);
	void del_edge(int,int);
	
	double weight(int,int);
	
	graph *create_spanning_tree_from_array(int[]);
	static graph *dijkstra(graph&,double*,int);
	
	void print();
	void plot();
};


