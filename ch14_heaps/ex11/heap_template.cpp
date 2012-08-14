/*
file name: heap_template.cpp
purpose: 
	习题11
	在C++标准模板库中如何实现堆、优先级队列和堆排序？
creator: guangwei jiang
create time: 2012-08-14

modify history:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
#include <algorithm>

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
void pqsort (T v[], int n)
{
	make_heap(v, v+n);
	sort_heap(v, v+n);
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

	m = MAX_ELEMENTS;
	n = MAX_VAL;

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
