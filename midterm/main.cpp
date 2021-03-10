/*
	Author: Princekumar Diyora
	Date :  10-08-20
	Purpose: making the design using the merge sort and using compare function

*/


#include <iostream>
using namespace std;

#define N 25
typedef struct point
{
	double x;
	double y;
} point;


int compare(point &s, point &t);
void merge_sort(point arr[], int low, int mid, int high);
void merge(point arr[], int low, int mid, int high);
void print_merge(point arr[]);

int main()
{

        point p[N*N];

	for (int i=1; i<=N; i++)
	{
		  for(int j=1; j<=N; j++)
		  {
			p[N*(i-1)+j-1].x=i;
			p[N*(i-1)+j-1].y=j;
		 }
	}
	
	int low=0;
	int high=N*N-1;
	int mid=(high-low+1)/2;

	cout << "Without using merge sort: " << endl;
	//This will print the 25 by 25 grid without using merge sort
	print_merge(p);

	//calling the function
	merge_sort(p,low,mid,high);
	
	cout << endl;
	cout << "With merge sort: " << endl;

	//it will print the element with using merge sort
	print_merge(p);
     
	return 0;
}

int compare (point &s, point &t)
{
	if ((s.x/s.y) < (t.x/t.y))
        {
		return -1;
        }else if ((s.x/s.y) > (t.x/t.y))
        {
		return 1;
        }else
        {
		return 0;
        }

}


void merge_sort(point arr[], int low, int mid, int high)
{
	//if there is only one element in the array it will not do anything
	if(high-low+1 == 1)
	{
		return;
		
	}else
        {

		merge_sort(arr,low,(low+mid)/2,mid);
		merge_sort(arr,mid+1,(mid+high+1)/2,high);
		
		//now we are bringing the two sorted array together
		//low and high together
		merge(arr,low,mid,high);
	}
}

//output is the left half of the array and right half of the array
//it will be sorted and together
void merge(point arr[], int low, int mid, int high)
{
	//this local array is temp array
	//it is the size of high-low
	point temp[high-low];	

	int left = low;
	int right = mid+1;

	for (int i=0; i<high-low+1; i++)
	{
		//if all the lements are exsausted from the left half
		//we have to take the element from the right half
		//and we have to increase the index to keep track of it
		if(left > mid)
		{
			temp[i]=arr[right++];
		}else if(right > high)
		{
			temp[i]=arr[left++];
		}else if(compare(arr[left],arr[right])==1)
		{
			temp[i]=arr[right++];

		}else 
		{
			temp[i]=arr[left++];
		}
	}

	for(int i=0; i<high-low+1; i++)
	{
		//copying elements from the temp array
		arr[low+i]=temp[i];
	}


}

void print_merge(point arr[])
{
	
	for(int i=0; i<N*N; i++)
	{
		cout << arr[i].x << " ";
		cout << arr[i].y << endl;
	}
	
}



//for the merging two arrays the time complexity is theta m+n beca
//we have a m number of elements in the first sorted array and n number 
//of elements in the second array
//and for the result we are combine both the array together and result
//will be the merging of two sorted arry

//total time for merge sort is nlogn and here we have n is 25 and how many passes
//we have during dividing the elements and merging them together. we have
//25 passes

//runtime growth will t(n)=2t(n/2)+n for n>1 and when n=1 we can see that 
//it is not doing anything
//a=2, b=2, and f(n)=n
//loga base b will be log 2 base 2 that means log 1
//and n^p=n^1 so p=1 and log 2 base 2 is also 1
//we can see that f(n) and sub problems are the same so it is falling in the second case
//When both the upper/lower bounds are the same, then the cost of the work for f(n) and the subproblems is about equal (Case 2).
//so as we know about the case two whatever is f(n) we are multiplying it by
//logn that means theta nlogn bcz our f(n) is n

