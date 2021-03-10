#include <cmath>
#include <iostream>
#include <iomanip>
#include "median_heap.hpp"

//this is the constructor for the median heap
//here we are allocating the memory for min heap and max heap
median_heap::median_heap() :
	m_M(DEFAULT_MEDIANHEAP_MAX_CAPACITY),
	m_N(0)
{
	m_min = new min_heap[m_M];
    m_max = new max_heap[m_M];
}

//this is passed by parameter 
//here we are allocating the memory for the min heap and max heap
//but this time it is increased by one
median_heap::median_heap(int max_capacity) :
	m_M(max_capacity+1),
	m_N(0)
{
	m_min = new min_heap[max_capacity+1];
    m_max = new max_heap[max_capacity+1];
}

//here we are dallocating the memory that we have allocated before
median_heap::~median_heap()
{
	delete [] m_min;
    delete [] m_max;
}

//this is the get median function
//it will return the median from the max heap or min heap
int median_heap::get_median()
{ 
	//taking the integer variable named median
	int median;

	//if the size of the min heap is less than the size of max heap
    //then our median should be from the max heap so we are calling the
	//function get max from the max heap and it will give the root node of the
	//max heap
    if(m_min->size() < m_max->size())
	{
		median = m_max->get_max();
	}
	//if the size of the min heap is greater than the max heap size than 
	//it will take the median from the min heap and we are calling the get min 
	//function which will return the root node of the min heap
	else if (m_min->size() > m_max->size())
 	{
		median = m_min->get_min();
	}
	//if the size of the both heaps are similar than it will take the root of the min heap
	//and also take root of the max heap and it will return the average of these two
	else 
    {
		median = (m_min->get_min() + m_max->get_max())/2;
	}

	//this function will return the variable named median
	return median;
}

//this is the insert function and we are passing the integer key as a parameter
void median_heap::insert(int key)
{
	//this is the variable where we are calling the get median function
	//and it will store into the median named variable
	int median = get_median();

	//if the max heap and min heap both are empty than we want to insert the 
	//element into the max heap
	if(m_max->isEmpty() && m_min->isEmpty())
	{
		m_max->insert(key);
	}
	//if the elements is greater than median than it should insert element into the min heap
	if(key > median)
	{
		m_min->insert(key);
	}
	//if the elements are greater than the median than it will isnert that element into the
	//max heap
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


//this is the print function where we are calling the print function from the min heap and max heap
//this will print the max heap first and then it will print the min heap
void median_heap::print_heaps()
{
	std::cout << "Max Heap :" << std::endl;
	m_max->print();
	std::cout << " " << std::endl;
	std::cout << "Min Heap :" << std::endl;
	m_min->print();
	std::cout << " " << std::endl;
}