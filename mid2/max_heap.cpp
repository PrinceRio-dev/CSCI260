#include <cmath>
#include <iostream>
#include <iomanip>
#include "max_heap.hpp"


max_heap::max_heap() :
	m_M(DEFAULT_MAXHEAP_MAX_CAPACITY),
	m_N(0)
{
	m_data = new int[m_M];
}

max_heap::max_heap(int max_capacity) :
	m_M(max_capacity+1),
	m_N(0)
{
	m_data = new int[max_capacity+1];
}

max_heap::~max_heap()
{
	delete [] m_data;
}

void max_heap::swim(int k)
{
	while (k > 1 && compare(k/2, k) < 0)
	{
		exchange(k/2, k);
		k = k/2;
	}
}

void max_heap::sink(int k)
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

int max_heap::compare(int p, int q)
{
	if (m_data[p] < m_data[q]) return -1;
	if (m_data[p] > m_data[q]) return 1;
	return 0;
}

void max_heap::exchange(int p, int q)
{
	int temp = m_data[p];
	m_data[p] = m_data[q];
	m_data[q] = temp;
}

void max_heap::insert(int key)
{
	m_data[++m_N] = key;
	swim(m_N);
}

int max_heap::get_max()
{ return m_data[1]; }

int max_heap::remove_max()
{
	int max = m_data[1];
	exchange(1, m_N--);
	sink(1);
	return max;
}

bool max_heap::isEmpty()
{ return m_N == 0; }

int max_heap::size()
{ return m_N; }

void max_heap::print()
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
