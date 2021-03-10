#include <iostream>
#include <iomanip>
#include "graph.hpp"

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
		std::cout << "[" << i << "]: ";
		m_vertex[i]->print();
		std::cout << std::endl;
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
