/*
file name: using_cpp_template.cpp
purpose: 
	次算法利用C++标准模板库，用std::set表示集合。
creator: guangwei jiang
create time: 2012-07-26

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

void gensets (int m, int n)
{
	set<int> S;

	srand((int)time(0));

	while (S.size() < m)
		  S.insert(bigrand()%n);
	
	set<int>::iterator i;
	for (i = S.begin(); i != S.end(); ++i)
		  cout << *i << "\n";
}

int main()
{
	clock_t start, finish;
	double duration;
	int m, n;

	m = 300000;
	n = 1000000;

	start = clock();
	gensets(m, n);
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n" << "m is "<< m << "; n is " << n << "\n";
	cout << "Cost time: " << duration << " seconds \n";

	return 0;
}
