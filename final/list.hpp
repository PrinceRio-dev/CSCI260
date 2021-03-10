#pragma once

#include <cfloat>

typedef struct point {
	float x, y;
} point;

typedef struct edge edge;
struct edge {
	int v;
	double wt;
	point p;
	edge *next;
	float x() { return p.x; }
	float y() { return p.y; }
	
	edge(int v) :
		edge(v, 0, nullptr)
	{}
	
	edge(int v, double wt, edge *next) :
		v(v),
		wt(wt),
		next(next)
	{}
};

class list
{
private:
	edge *m_head = nullptr;
	edge *m_tail = nullptr;
	int m_N = 0; // number of nodes in this list
	edge *m_curr = nullptr;
	int m_currPos = 0;
	
	void init();
	void remove_all();
	
public:
	
	list();
	list(int);
	~list();
	
	int length();
	void move_to_start();
	int curr_pos();
	void next();
	
	void append(int,double=0);
	void insert(int,double=0);
	int remove();
	
	void clear();
	
	bool is_empty();
	int get_value();
	double get_weight();
	
	int* toArray();
	
	void print();
	
};
