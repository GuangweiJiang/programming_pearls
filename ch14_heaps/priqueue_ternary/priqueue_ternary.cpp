/*
file name: priqueue_ternary.cpp
purpose: 
	书中的“优先级队列”是基于“完全二叉树”，请基于“完全三叉树”来实现“优先级队列”。
creator: guangwei jiang
create time: 2012-08-14

modify history:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>

#define DEBUG			0
#define MAX_ELEMENTS	50000
#define MAX_VAL			10000000
 
using namespace std;

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
	return RAND_MAX*rand() + rand();
}

template<class T>
class priqueue_ternary {	
private:
	int n, maxsize;
	T *x;
	void swap(int i, int j)
	{
		T t = x[i]; 
		x[i] = x[j]; 
		x[j] = t;
	}
public:
	priqueue_ternary (int m)
	{
		maxsize = m;
		x = new T[maxsize+1];
		n = 0;
	}
	void insert (T t)
	{
		int i, p;
		x[++n] = t;
		for (i = n; i > 1 && x[p=(i+1)/3] > x[i]; i = p)
		{
			swap(p, i);
		}
	}
	T extractmin()
	{
		int i, c;
		// 1st step, get the min value x[1];
		T t = x[1];
		// 2nd step, assign another value(x[n]) to x[1], and n descrease 1;
		x[1] = x[n--];
		// 3rd step, re-sort the heap
		for (i = 1; (c = 3*i-1) <= n; i = c)
		{	
			// choose the min of the value in children, compare and swap with parent(if parent largger than children)
			if (c+1 <= n)
			{
				if (x[c+1] < x[c])					// compare middle and left child
				{
					c++;
					if (c+1 <= n && x[c+1] < x[c])	// compare right and middle child
						c++;
				}
				else
				{
					if (c+2 <= n && x[c+2] < x[c])	// compare left and right child
						c+=2;
				}
			}

			if (x[i] <= x[c])
				break;
			swap(c, i);
		}
		return t;
	}
};

template<class T>
void pqsort (T v[], int n)
{
	priqueue_ternary<T> pq(n);
	int i;

	for (i = 0; i < n; i++)
	{
		pq.insert(v[i]);
	}
	for (i = 0; i < n; i++)
	{
		v[i] = pq.extractmin();
	}
}

template<class T>
void print_queue(T v[], int m)
{
	printf("print queue\n");
	for (int i = 0; i < m; i++)
	{
		cout << v[i] << "\t";
		cout << "\n";
	}
}

int main()
{
	clock_t start, finish;
	double duration;
	int i, m, n;
	int *v = NULL;

	m = MAX_ELEMENTS;
	n = MAX_VAL;

	v = new int[m];
	srand((int)time(0));
	for (i = 0; i < m; i++)
	{
		v[i] = bigrand()%n;
	}

#if DEBUG
	printf("\n");
	printf("before sorting\n");
	print_queue(v, m);
#endif

	start = clock();
	pqsort(v, m);
	finish = clock();

#if DEBUG
	printf("\n");
	printf("after sorting\n");
	print_queue(v, m);
#endif

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n" << "m="<< m << ", n=" << n << ", ";
	cout << "cost time: " << duration << " seconds \n";

	return 0;
}
