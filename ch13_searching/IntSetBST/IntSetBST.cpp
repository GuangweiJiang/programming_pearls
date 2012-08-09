/*
file name: IntSetBST.cpp
purpose: 
	生成[0, maxval]范围内m个随机整数的有序序列，不允许重复。
	使用“二分搜索树”实现IntSetBST.
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

class IntSetBST {	
private:
	int n, *v, vn;
	struct node{
		int val;
		node *left, *right;
		node(int i){val = i; left = right = 0;}
	};
	node *root;
public:
	IntSetBST (int maxelements, int maxval)
	{
		root = 0;
		n = 0;
	}
	int size() {return n;}
	node *rinsert(node *p, int t)
	{
		if (p == 0)
		{
			p = new node(t);
			n++;
		}
		else if (t < p->val)
			p->left = rinsert(p->left, t);
		else if (t > p->val)
			p->right = rinsert(p->right, t);
		// do nothing if p->val == t
		return p;
	}
	void insert (int t)
	{
		root = rinsert(root, t);
	}
	void traverse(node *p)
	{
		if (p == 0)
			return;
		traverse(p->left);
		v[vn++] = p->val;
		traverse(p->right);
	}
	void report(int *x)
	{
		v = x;
		vn = 0;
		traverse(root);
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
	IntSetBST S(m, n);

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

	m = 500000;
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
