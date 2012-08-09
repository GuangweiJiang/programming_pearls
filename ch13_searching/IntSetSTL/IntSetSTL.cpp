/*
file name: IntSetSTL.cpp
purpose: 
	利用C++标准模板库的set容器，实现顺序插入排序。
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

class IntSetSTL {	
private:
	set<int> S;
public:
	IntSetSTL (int maxelements, int maxval){}
	int size() {return S.size();}
	void insert (int t){S.insert(t);}
	void report(int *v)
	{
		int j = 0;
		set<int>::iterator i;
		for (i = S.begin(); i != S.end(); ++i)
			v[j++] = *i;
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
	IntSetSTL S(m, n);

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
