/*
file name: map_string.cpp
purpose: 
	使用标准库中的map将整个计数与每个字符串联系起来。
creator: guangwei jiang
create time: 2012-09-12

modify history:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
#include <map>
 
using namespace std;

int main()
{
	map <string, int> M;
	map <string, int>::iterator j;
	string t;
	clock_t start, finish;
	double duration;
	
	start = clock();
	
	// notes: press "CTRL+D" in Linux to exit "cin";
	// press "CTRL+Z" in Windows to exit "cin";
	while (cin >> t)
		M[t]++;
	for (j = M.begin(); j != M.end(); ++j)
		cout << j->first << " " << j->second << "\n";
	
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "Cost time: " << duration << " seconds \n";

	return 0;
}
