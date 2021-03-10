#include <iostream>
#include "UnionFind.hpp"


UnionFind::UnionFind(int N) :
	N(N),
	num_of_subsets(N)
{
	parent = new int[N];
	for (int i = 0; i < N; i++)
		parent[i] = i;
	sizes = new int[N];
	for (int i = 0; i < N; i++)
		sizes[i] = 1;
}

UnionFind::~UnionFind()
{
	delete [] parent;
	delete [] sizes;
}

int UnionFind::size() { return N; }

// solution to Lab 1
// parameter p indicates the subset we want, parameter i is the value of the current element in the subset
int UnionFind::next_subset_element(int p, int i) {
	int root = find(p);
	i++;
	// what is the worst-case number of iterations of this loop?
	while (i < N && find(i) != root) { i++; }
	if (i >= N) i = -1;
	return i;
}

//this function is for the cycle detection
//and this is the function we are using for the kruskal's algorithm
//we are passing two parameters
bool UnionFind::connected(int p, int q)
{
	//if element p and q found out from the same subset 
	//then we will return true that mean cycle is detected
	//if not in the same subset then we will return false that means that
	//both elements are in the diefferent subset then return false
	//and cycle is not detected
	if (find(p) == find(q))
		return true;
	else 
		return false;
}

//for finding the root of the set in which pasrameter 
//p is belongs to
int UnionFind::find(int p)
{
	//while our element is not root we will go though the loop
	//and we will set the element to the root and return the 
	//element
	while (p != parent[p]) p = parent[p];
	return p;
}

//this function is for union of two sets
//we are passing two parameters
void UnionFind::set_union(int p, int q)
{
	//we will find the root of the elements p and q belongs to
	int r = find(p);
	int s = find(q);
	
	//if r and s both are in the same set then we will not do anything
	if (r == s) 
		return;
	
	//else we will decrese the subset size by one
	num_of_subsets--;

    //if the size of the set r is greater than size of set s
	//then we will add elements into the seubset s
	//and we will set the root of the s subset to r
	//else if size of r is not greater than then we will incerese the size of r by one
	//I mean we will add that element to r and we will set the root of r to s
	if (sizes[r] > sizes[s])
	{
		sizes[r] += sizes[s];
		parent[s] = r;
	}
	else
	{
		sizes[s] += sizes[r];
		parent[r] = s;
	}
}

void UnionFind::print_sets()
{
	int *visited = new int[size()];
	for (int i = 0; i < size(); i++) visited[i] = 0;
	
	for (int i = 0; i < size(); i++)
	{
		bool printed_loop = false;
		for (int j = 0; j < size(); j++) {
			if (!visited[j] && find(j) == i) {
				printed_loop = true;
				visited[j] = 1;
				std::cout << j << " ";
			}
		}
		if (printed_loop) 
			std::cout << std::endl;
	}
	
	delete [] visited;
}

void UnionFind::print()
{
	for (int i = 0; i < N; i++)
	{
		std::cout << "[" << i << "]: " << parent[i] << std::endl;
	}
	std::cout << std::endl;
}
