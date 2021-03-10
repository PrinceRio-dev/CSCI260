#pragma once

#define DEFAULT_MAXHEAP_MAX_CAPACITY 1048577 // 2^20+1

class max_heap
{
private:
	
	int *m_data; // actual records start at index 1
	int m_M; // max capacity
	int m_N;
	
	void swim(int);
	void sink(int);
	
public:
	
	max_heap();
	max_heap(int);
	~max_heap();
	
	int compare(int, int);
	void exchange(int, int);
	void insert(int);
	int get_max();
	int remove_max();
	bool isEmpty();
	int size();
	void print();
	
};
