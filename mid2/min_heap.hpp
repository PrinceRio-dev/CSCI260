#pragma once

#define DEFAULT_MINHEAP_MAX_CAPACITY 1048577 // 2^20+1

class min_heap
{
private:
	
	int *m_data; // actual records start at index 1
	int m_M = 0; // max capacity
	int m_N = 0; //number of keys are in heap
	
	void swim(int);
	void sink(int);
	
public:
	
	min_heap();
	min_heap(int);
	~min_heap();
	
	int compare(int, int);
	void exchange(int, int);
	void insert(int);
	int get_min();
	int remove_min();
	bool isEmpty();
	int size();
	void print();
	
};