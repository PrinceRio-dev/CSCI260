#pragma once

class UnionFind 
{
private:
	
	int *parent;
	int *sizes;
	int N;
	int num_of_subsets;
	
public:
	
	UnionFind(int);
	~UnionFind();
	
	int size();
	int next_subset_element(int, int);
	bool connected(int p, int q);
	int find(int p);
	void set_union(int p, int q);
	void print_sets();
	void print();
	
};
