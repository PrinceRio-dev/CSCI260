#include <cmath>
#include <iostream>
#include <iomanip>
#include "median_heap.hpp"

median_heap::median_heap(int max_capacity) :
	m_M(max_capacity+1),
	m_N(0)
{
	m_min = new min_heap[max_capacity+1];
        m_max = new max_heap[max_capacity+1];
}

median_heap::~median_heap()
{
	delete [] m_min;
        delete [] m_max;
}

int median_heap::get_median()
{ 
	int median;
        if(m_min->size() < m_max->size())
	{
		median = m_max->get_max();
	}else if (m_min->size() > m_max->size())
 	{
		median = m_min->get_min();
	}else 
        {
		median = (m_min->get_min() + m_max->get_max())/2;
	}
	return median;
}

void median_heap::insert(int key)
{
	int median = get_median();
	if(m_max->isEmpty() && m_min->isEmpty())
	{
		m_max->insert(key);
	}
	if(key > median)
	{
		m_min->insert(key);
	}
	if (key <= median)
	{
		m_max->insert(key);
	}

	//rebalacing the heaps after inserting the elements
        //if the size of the min heap and max heap is differ by 2
	//than we will check the size of the min heap and max heap
	//if the max heap size is greater than min heap size than we will remove
	//the node from the max heap and we will isnert it into the min heap
	//and if the size of max heap is less than min heap than we will remove the 
	//root node from the min heap and we will insert that into the max heap
        //to rebalance the sizes of the heap
	if(abs(m_max->size() - m_min->size()) > 1)
	{
		if(m_max->size() > m_min->size())
		{
			m_min->insert(m_max->remove_max());
		}else
		{
			m_max->insert(m_min->remove_min());
		}
	}
    
} 

//this is the remove function
//for the remove function we will need min and max heap sizes
//I am adding the size of the min and max heap and if the size is even
//then we will remove the element from the min heap
//and if the sizes are odd then we will remove the element from the max heap
int median_heap::remove_median()
{
	int max = m_max->size();
	int min = m_min->size();
	int sum = max+min;
	if(sum % 2 ==0)
	{
		return m_min->remove_min();		
	}
	
	return m_max->remove_max();	
}

void median_heap::print_heaps()
{
	std::cout << "Max Heap :" << std::endl;
	m_max->print();
	std::cout << "Min Heap :" << std::endl;
	m_min->print();
}