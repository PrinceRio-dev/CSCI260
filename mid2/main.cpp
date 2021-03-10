#include <iostream>
#include <ctime>
#include "median_heap.hpp"
using namespace std;

int main()
{
	median_heap mHeap=median_heap(15);
	int key;
	for (int i=0; i<15; i++)
    {
		key=100+rand()%899;
		mHeap.insert(key);
    }
	mHeap.print_heaps();
	cout << " " << endl;
	cout << "This is the Median : " << mHeap.get_median() << endl;
	cout << " " << endl;
	cout << "This is Removed from the heap : " << mHeap.remove_median() << endl;
	cout << "******************************************************" << endl;
	mHeap.print_heaps();
	cout << "This is the median:" << mHeap.get_median() << endl;
	cout << " " << endl;
	cout << "This is Removed from the heap : " << mHeap.remove_median() << endl;
	cout << "*****************************************************" << endl;
	mHeap.print_heaps();
	cout << "This is the median : " << mHeap.get_median() << endl;
	cout << " " << endl;
	cout << "This is Removed from heap : " << mHeap.remove_median() << endl;
	cout << "*****************************************************" << endl;
	mHeap.print_heaps();
	cout << "This is the median : " << mHeap.get_median() << endl;
	cout << " " << endl;
	cout << "This is Removed from heap : " << mHeap.remove_median() << endl;
	cout << "*****************************************************" << endl;
	mHeap.print_heaps();
	cout << "End of the program! Thank you!" << endl;
	cout << " " << endl;
	return 0;

}
