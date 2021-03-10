#include <iostream>
#include <iomanip>
#include "graph.hpp"
using namespace std;

void graph::set_positions()
{
    positions = new point[m_V];
	float x[] = {   0, 1,   0, 1,   2, 3, 3,   4,   4,   5};
	float y[] = { 2.5, 3, 0.5, 0, 1.5, 3, 0, 2.5, 0.5, 1.5};
	for (int i = 0; i < m_V; i++)
	{
		positions[i].x = x[i];
		positions[i].y = y[i];
	}
}

graph::graph()
{}

graph::graph(int N) :
	m_V(N),
	m_E(0)
{
	//std::cout << "graph constructor: Before memory allocation." << std::endl;
	m_vertex = new list*[m_V];
	for (int i = 0; i < m_V; i++)
		m_vertex[i] = new list();
	set_positions();
}

graph::~graph()
{
	//std::cout << "graph deconstructor: Before deallocating memory." << std::endl;
	for (int i = 0; i < m_V; i++)
		delete m_vertex[i];
	delete [] m_vertex;
	delete [] positions;
}

void graph::visit(graph &G, int u, min_heap *arc_heap, int visited[])
{
    // set u as visited
    visited[u]=1;
    // for each neighbour v of u
    // if v is not visited
    // insert arc (u, v, weight(u, v)) into arc_heap

    for(int i=0; i< G.order(); i++)
	{
	    if(!visited[i] && G.is_edge(u,i))
		{
		    arc_heap->insert(arc(u, i, G.weight(u, i)));
		}
	}
}


graph* graph::prim(graph &G)
{
    // set up parents and visited array similar to DFS/BFS
    int m_v=G.order();
	int parents[m_v];
	int visited[m_v];

    for(int i=0; i<m_v; i++)
	{
	    parents[i]=-1;
		visited[i]=0;
	}

    // create a min heap to deal with organizing the edges compared by weight
    min_heap *arc_heap= new min_heap(m_v);

     // assume the graph is connected and that there is an edge on vertex 0 to simplify things
    int u,v;
	u = 0;
    parents[u] = u; // set 0 as the root

    // use the visit function to visit u
	G.visit(G,u,arc_heap,visited);
    while (!arc_heap->isEmpty())
    {
       // set u and v to the minimum weighted edge and remove the min edge from the heap
	    struct arc temp; 
        temp=arc_heap->remove_min();
	    u=temp.from;
	    v=temp.to;

        // if both u and v are visited then continue to the next iteration of this loop
        if(visited[u] && visited[v]) continue;
        // set the parent of v to u
        parents[v]=u;
        // if v has not been visited, use the visit function to visit it
	    if(!visited[v])
	    {
		    G.visit(G,v,arc_heap,visited);
	    }
    }
    graph *MST=G.create_spanning_tree_from_array(parents);
    
	delete arc_heap;
    return MST;
}

//***** citation: I was follwing the algorithm which is given in the book and suggested by you***************
//first of all, we will insert the minimum weighted edge into min heap
//after that we will remove the min edge from the heap
//now we will set our vertise u and v to the minimum edge that we have 
//taken out recently
//if u and v both are not in the found in the same subset then we will 
//call the set union function from the union find file and we will make
// a union of those two u and v sets
//and then we will add edge on the minimum spanning tree
//and then we will decrese the number of vertices by one
//and it will return the minimum spanning tree from the implemented graph
graph* graph::kruskal(graph &G)
{
	//number of vertises in this variable
	int m_v=G.order();

	//taking two varaibles u and v, or we can say that from and to vertises
	int u;
	int v;

	//integer array named visited with the size contain number of vertises
	int visited[m_v];

    //we will set up the visited array to 0
    for(int i=0; i<m_v; i++)
	{
	    visited[i]=0;
	}

    //creating a pointer to min heap
	//this will sort all the edges in the graph as compare to weight of edges
	min_heap *arc_heap= new min_heap(m_v);

    //now we are inserting the edges into the min heap
	//we are calling the function first and next
	for(int i=0; i<m_v; i++)
	{
		for(int j=G.first(i); j<m_v; j=G.next(i,j))
		{
			//if j is not visted and vertex i and j has edge betweeen it
	        if(!visited[j] && G.is_edge(i,j))
		    {
				//we will set the visited first index to one
			    visited[i]=1;
				//and then we will insert the from vertise and to vertise and the distance 
				//between those two vertise
				//i mean we will insert arc(from,to,weight of from and to)
		        arc_heap->insert(arc(i,j,G.weight(i,j)));
		    }
		}
	}

    //I was calling the print function from the min heap to check 
	//that all wdges are inserted in the sorted order
	//arc_heap->print();

	//cerating a new graph
    graph *T=new graph(m_v);

	//cereating the pointer to an UnionFind instance
	UnionFind *union_find = new UnionFind(m_v);

	//now we are taking the for loop and it will go through until 
	//number of vertises are greater than 1
	for(int i=0; m_v>1; i++)
	{

		// set u and v to the minimum weighted edge and remove the min edge from the heap
		//declaring the variable named temp
		struct arc temp; 
		
		//now we will remove the min weighted edge from the heap
        temp=arc_heap->remove_min();

		//setting u and v to the vertesies of minimum weighted edge
	    u=temp.from;
		v=temp.to;

		//now we are checking that is it creating a cycle or not?
		//so for that we will call the connected function from the union find
		//if both are not in the same subset than there is not a cycle
		//then we will make union of u and v
		if(!union_find->connected(u,v))
		{
			//calling the function set_union from the union find 
			//making the union of subsets
			union_find->set_union(u,v);

			//then we will add the minimum weighted edge on MST
			//by calling the function set_adjacency from our graph.cpp file
			T->set_adjacency(u,v,G.weight(u,v));

			//and we will decresing the number of vertises by one
			m_v--;   	
		}	
	}

	//and then in the end we will return the graph
	return T;

	//deleting the memory for the union_find that we have allocated before
	delete union_find;		

	//deleting the memory for the arc_heap that we have allocated before
	delete arc_heap;
	
}

int graph::order()
{ return m_V; }

int graph::size()
{ return m_E; }

int graph::degree(int v)
{ return m_vertex[v]->length(); }

int graph::first(int v)
{
	//std::cout << "first: before resetting list and returning first vertex in edge list." << std::endl;
	if (m_vertex[v]->length() == 0) return m_V; // return the number of vertices
	m_vertex[v]->move_to_start();
	return m_vertex[v]->get_value();
}

int graph::next(int u, int v)
{
	//std::cout << "next: before the next vertex in edge list of " << u << " after " << v << "." << std::endl;
	if (is_edge(u, v))
	{
		if (m_vertex[u]->curr_pos()+1 < m_vertex[u]->length())
		{
			m_vertex[u]->next();
			return m_vertex[u]->get_value();
		}
	}
	return m_V;
}

bool graph::is_edge(int u, int v)
{
	//std::cout << "is_edge: checking edge (" << u << ", " << v << ")." << std::endl;
	for (
		m_vertex[u]->move_to_start();
		m_vertex[u]->curr_pos() < m_vertex[u]->length();
		m_vertex[u]->next()
	) {
		int w = m_vertex[u]->get_value();
		if (v == w) return true;
	}
	return false;
}

void graph::set_adjacency(int u, int v, double weight)
{
	//std::cout << "set_adjacency (" << u << ", " << v << ")." << std::endl;
	// simple graphs do not have loops (self-adjacencies)
	if (u == v) return;
	
	// already adjacent
	if (is_edge(u, v) && is_edge(v, u)) {
		// simple graph, so do arcs in both directions
		m_vertex[u]->remove();
		m_vertex[v]->remove();
		set_edge(u, v, weight);
		set_edge(u, u, weight);
	}
	// adjacent in one direction (just to double-check arcs go both ways for each edge added)
	else if (is_edge(u, v)) set_edge(v, u, weight);
	else if (is_edge(v, u)) set_edge(u, v, weight);
	// create a new adjacency
	else
	{
		set_edge(u, v, weight);
		set_edge(v, u, weight);
		m_E++;
	}
}

void graph::set_edge(int u, int v, double weight)
{
	//std::cout << "set_edge (" << u << ", " << v << ")." << std::endl;
	
	for (
		m_vertex[u]->move_to_start();
		m_vertex[u]->curr_pos() < m_vertex[u]->length();
		m_vertex[u]->next()
	) {
		int w = m_vertex[u]->get_value();
		if (w > v) break;
	}
	m_vertex[u]->insert(v, weight);
}


void graph::del_edge(int u, int v)
{
	//std::cout << "del_edge (" << u << ", " << v << ")." << std::endl;
	if (u == v) return;
	
	if (is_edge(u, v)) m_vertex[u]->remove();
	if (is_edge(v, u)) m_vertex[v]->remove();
	m_E--;
}

double graph::weight(int u, int v)
{
	// implemented to have list private nodes "edge"
	if (is_edge(u, v)) // iterates in the list to position with vertex value v
		return m_vertex[u]->get_weight();
	return 0;
}

graph *graph::create_spanning_tree_from_array(int parents[])
{
	//std::cout << "create_spanning_tree_from_array." << std::endl;
	graph *T = new graph(m_V);
	
	// set_adjacency ensures we do not create a loop at the root
	for (int i = 0; i < m_V; i++)
		T->set_adjacency(i, parents[i], weight(i, parents[i]));
	
	return T;
}

int graph::min_vertex(graph &G, double* d, int *visited)
{
	int u;
	int v = -1;
	for (u = 0; u < G.order(); u++)
		if (!visited[u]) { v = u; break; }
	for (u++; u < G.order(); u++)
		if (!visited[u] && d[u] < d[v]) v = u;
	return v;
}

int graph::relax(graph &G, double *d, int v, int r, int *parents)
{
	int closest_vertex = -1;
	for (int w = G.first(v); w < G.order(); w = G.next(v, w))
	{
		// Note that we are iterating through the list *again* with call to weight---could be eliminated
		if (d[w] > d[v] + G.weight(v, w)) {
			closest_vertex = w; 
			if (w != r) parents[closest_vertex] = v;
			d[w] = d[v] + G.weight(v, w);
		}
	}
	return closest_vertex;
}

graph *graph::dijkstra(graph &G, double *d, int r)
{
	int *parents = new int[G.order()];
	int *visited = new int[G.order()];
	
	for (int i = 0; i < G.order(); i++) {
		d[i] = DBL_MAX; // "infinity"
		parents[i] = -1;
		visited[i] = 0;
	}
	
	d[r] = 0; // start at root vertex r
	parents[r] = r; // set the root of the tree as its own parent
	int v, w;
	for (int i = 0; i < G.order(); i++)
	{
		v = min_vertex(G, d, visited);
		if (d[v] == DBL_MAX) return nullptr;
		visited[v] = 1;
		w = relax(G, d, v, r, parents);
	}
	graph *SPT = G.create_spanning_tree_from_array(parents);
	
	delete [] parents;
	delete [] visited;
	
	return SPT;
}

void graph::print()
{    
	for (int i = 0; i < m_V; i++)
	{
		std::cout << setw(3) << "[" << setw(2) << i << "]:" <<setw(4);
		m_vertex[i]->print() ;
		std::cout <<std::endl;
	}
}

void graph::plot()
{
	for (int u = 0; u < m_V; u++)
	{
		for (
			m_vertex[u]->move_to_start();
			m_vertex[u]->curr_pos() < m_vertex[u]->length();
			m_vertex[u]->next()
		) {
			int v = m_vertex[u]->get_value();
			if (u < v) {
				std::cout 
					<< u << " "
					<< positions[u].x << " "
					<< positions[u].y 
					<< std::endl
					<< v << " "
					<< positions[v].x << " "
					<< positions[v].y 
					<< std::endl << std::endl;
			}
		}
	}
}
	
