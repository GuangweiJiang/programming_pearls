/*
file name: randselect.cpp
purpose: 
	P124-125
	使用递归生成组合对象。
creator: Guangwei Jiang
create time: 2012-07-31

modify history:

notes:
	Guangwei Jiang, 2012-07-31
	If n=1,000,000, then will have error "Segmentation fault";
	The cause should be "recursion" cost too may resource.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
		return RAND_MAX*rand() + rand();
}

void randselect(int m, int n)
{
	if ((m > n) || (m < 0))
		  return;

	//printf("m=%d, n=%d\n", m, n);
	if (m > 0)
	{
		if ((bigrand()%n) < m)
		{
			//printf("%d\n", n-1);	// if print here, then in decreasing order
			randselect(m-1, n-1);
			printf("%d\n", n-1);	// if print here, then in increading order
		}
		else
		{
			randselect(m, n-1);
		}
	}
}

int main()
{
	clock_t start, finish;
	double duration;
	int m, n;

	m = 10000;
	n = 100000;

	start = clock();
	srand(time(0));
	randselect(m, n);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("m = %d, n = %d\n", m, n);
	printf("the duration is %f seconds\n\n", duration);

	return 0;
}
