#include <iostream>
#include <iomanip>
#include "list.hpp"

// header node contains value -1 as a sentinel
void list::init()
{ m_curr = m_head = m_tail = new edge(-1); }

list::list() :
	m_N(0)
{
    init();
}

list::list(int v) :
	m_N(0)
{
    init();
	append(v);
}

list::~list()
{ 
	clear();
	delete m_head;
}

int list::length() { return m_N; }

void list::move_to_start()
{
	m_currPos = 0; 
	m_curr = m_head;
}

int list::curr_pos()
{ return m_currPos; }

void list::next()
{ 
	if (m_curr != m_tail)
	{
		m_currPos++;
		m_curr = m_curr->next;
	}
}

int list::get_value()
{
	if (!m_curr->next)
	{
	    std::cerr << "Error: there is no value in the current position." << std::endl;
		exit(1);
	}
	return m_curr->next->v;
}

double list::get_weight()
{
	if (!m_curr->next)
	{
		std::cerr << "Error: there is no weight in the current position." << std::endl;
		exit(1);
	}
	return m_curr->next->wt;
}

void list::append(int v, double weight)
{
	m_tail = m_tail->next = new edge(v, weight, nullptr);
	m_N++;
}

void list::insert(int v, double weight)
{
	//std::cout << "list.insert: " << v << std::endl;
	m_curr->next = new edge(v, weight, m_curr->next);
	if (m_tail == m_curr) m_tail = m_curr->next;
	m_N++;
}

int list::remove()
{
	if (!m_curr->next)
	{
		std::cerr << "Error: no element to remove at current position" << std::endl;
		exit(1);
	}
	edge *temp = m_curr;
	int v = temp->v;
	if (m_tail == m_curr->next) m_tail = m_curr;
	m_curr->next = m_curr->next->next;
	delete temp;
	m_N--;
	return v;
}

void list::remove_all()
{
	while (m_head != nullptr)
	{
		m_curr = m_head;
		m_head = m_head->next;
		delete m_curr;
	}
}

void list::clear()
{
	remove_all();
	init();
}

bool list::is_empty()
{
	if (m_N == 0) return true;
	return false;
}

int* list::toArray()
{
	int *temp = new int[m_N];
	edge *it = m_head;
	for (int i = 0; i < m_N; i++) {
		temp[i] = it->v;
		it = it->next;
	}
	return temp;
}


void list::print()
{
	for (move_to_start(); curr_pos() < length(); next())
	{
	    std::cout << get_value();
		std::cout << "(" << get_weight() << ")," << std::setw(4);
	}
}

