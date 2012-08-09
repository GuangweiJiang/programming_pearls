/*
file name: IntSetBitVec.cpp
purpose: 
	生成[0, maxval]范围内m个随机整数的有序序列，不允许重复。
	使用“二分搜索树”实现IntSetBitVec.
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

class IntSetBitVec {	
private:
	enum {BITSPERWORD = 32, SHIFT = 5, MASK = 0x1F};
	int n, hi, *x;
	void set(int i) {        x[i>>SHIFT] |=  (1<<(i & MASK)); }
	void clr(int i) {        x[i>>SHIFT] &= ~(1<<(i & MASK)); }
	int test(int i) { return x[i>>SHIFT] &   (1<<(i & MASK)); }
public:
	IntSetBitVec (int maxelements, int maxval)
	{
		int i;
		hi = maxval;
		x = new int[1 + hi/BITSPERWORD];
		for (i = 0; i < hi; i++)
			clr(i);
		n = 0;
	}
	int size() {return n;}
	void insert (int t)
	{
		if (test(t))
			return;
		set(t);
		n++;
	}
	void report(int *v)
	{
		int i = 0, j = 0;
		for (i = 0; i < hi; i++)
			if (test(i))
				v[j++] = i;
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
	IntSetBitVec S(m, n);

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

	m = 1000000;
	n = 10000000;

	start = clock();
	gensets(m, n);
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n" << "m="<< m << ", n=" << n << ", ";
	cout << "Cost time: " << duration << " seconds \n";
	cout << "\n";

	return 0;
}
