#include <cmath>
#include <iostream>
#include <iomanip>
#include "min_heap.hpp"

min_heap::min_heap() :
	m_M(DEFAULT_MINHEAP_MAX_CAPACITY),
	m_N(0)
{
	m_data = new int[m_M];
}

min_heap::min_heap(int max_capacity) :
	m_M(max_capacity+1),
	m_N(0)
{
	m_data = new int[max_capacity+1];
}

min_heap::~min_heap()
{
	delete [] m_data;
}

void min_heap::swim(int k)
{
	while (k > 1 && compare(k/2, k) < 0)
	{
		exchange(k/2, k);
		k = k/2;
	}
}

void min_heap::sink(int k)
{
	while (2*k <= m_N)
	{
		int j = 2*k;
		if (j < m_N && compare(j, j+1) < 0) j++;
		if (compare(k, j) >= 0) break;
		exchange(k, j);
		k = j;
	}
}

//making change in the compare function because
//swim and sink both are depend on this compare function
//and I found that if I will change in this function then I don't need
//to change any other function
int min_heap::compare(int p, int q)
{
	if (m_data[p] < m_data[q]) return 1;
	if (m_data[p] > m_data[q]) return -1;
	return 0;
}

void min_heap::exchange(int p, int q)
{
	int temp = m_data[p];
	m_data[p] = m_data[q];
	m_data[q] = temp;
}

void min_heap::insert(int key)
{
	m_data[++m_N] = key;
	swim(m_N);
}

int min_heap::get_min()
{ return m_data[1]; }

int min_heap::remove_min()
{
	int min = m_data[1];
	exchange(1, m_N--);
	sink(1);
	return min;
}

bool min_heap::isEmpty()
{ return m_N == 0; }

int min_heap::size()
{ return m_N; }

void min_heap::print()
{
	int height = log2(ceil(m_N));
	int width = pow(2, height) * 6;
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j < pow(2, i); j++) {
			if ((int)pow(2, i) + j > m_N) break;
			int tab = (width/pow(2, i) - 4);
			std::cout << std::setw(tab/2) << " ";
			std::cout << std::setw(4);
			std::cout << m_data[(int)pow(2, i) + j];
			std::cout << std::setw(tab/2) << " ";
		}
		std::cout << std::endl;
	}
}
