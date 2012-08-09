/*
file name: IntSetArray.cpp
purpose: 
	利用整数数组，实现顺序插入排序。
creator: guangwei jiang
create time: 2012-08-09

modify history:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
 
using namespace std;

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
	return RAND_MAX*rand() + rand();
}

class IntSetArray {	
private:
	int n, *x;
public:
	IntSetArray (int maxelements, int maxval)
	{
		x = new int[1+maxelements];
		n = 0;
		x[0] = maxval;
	}
	int size() {return n;}
	void insert (int t)
	{
		int i, j;

		for (i = 0; x[i] < t; i++)
			;
		if (x[i] == t)
			  return;
		for (j = n; j>= i; j--)
			x[j+1] = x[j];
		x[i] = t;
		n++;
	}
	void report(int *v)
	{
		int i = 0;
		for (i = 0; i < n; i++)
			v[i] = x[i];
	}
};

/*
 * parameter: 
 *		m - the max number of elements
 *		n - the max value
 */
void gensets (int m, int n)
{
	int *v = new int[m];
	IntSetArray S(m, n);

	srand((int)time(0));

	while (S.size() < m)
		  S.insert(bigrand()%n);
	
	S.report(v);
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
	int m, n;

	m = 50000;
	n = 10000000;

	start = clock();
	gensets(m, n);
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n" << "m is "<< m << "; n is " << n << "\n";
	cout << "Cost time: " << duration << " seconds \n";

	return 0;
}
