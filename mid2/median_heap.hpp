#pragma once

#define DEFAULT_MEDIANHEAP_MAX_CAPACITY 1048577 // 2^20+1
#include "max_heap.hpp"
#include "min_heap.hpp"
class median_heap
{
private:
	
        //pointer to min_heap named m_min
	min_heap *m_min;
        //pointer to max_heap named m_max
        max_heap *m_max;
	int m_M=0; //maximum capacity 
        int m_N=0; //to keep track of number of keys in median heap
        
	
public:

        median_heap();
        median_heap(int max_capacity);
	~median_heap();
	
	int get_median(); //runs in constant time 
        int remove_median(); //runs in logarithmic time
        void insert(int);    //runs in logarithmic time
        void print_heaps();  //this will use the min heap and max heap print function	
};
