/*
file name: priqueue.cpp
purpose: 
	优先级队列：
	堆通过插入新元素和提取最小元素这两种操作来维护元素集合，每个操作所需的时间都为O(log n)。
creator: guangwei jiang
create time: 2012-08-14

modify history:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>

#define DEBUG		0
 
using namespace std;

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
	return RAND_MAX*rand() + rand();
}

template<class T>
class priqueue {	
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
	priqueue (int m)
	{
		maxsize = m;
		x = new T[maxsize+1];
		n = 0;
	}
	void insert (T t)
	{
		int i, p;
		x[++n] = t;
		for (i = n; i > 1 && x[p=i/2] > x[i]; i = p)
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
		for (i = 1; (c = 2*i) <= n; i = c)
		{
			if (c+1 <= n && x[c+1] < x[c])
				c++;
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
	priqueue<T> pq(n);
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
		if ((i+1)%10 == 0)
			cout << "\n";
	}
}

int main()
{
	clock_t start, finish;
	double duration;
	int i, m, n;
	int *v = NULL;

	m = 50000;
	n = 10000000;

	v = new int[m];
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
