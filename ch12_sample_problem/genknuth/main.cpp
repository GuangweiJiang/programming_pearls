/*
file name: main.c
purpose: 
	P120-P121
	作者参考了Knuth的The Art of Computer Programming, Volume2: Seminumerical Algorithms,
	作者认为该书3.4.2节的算法S是理想的解决方案。
creator: guangwei jiang
create time: 2012-07-25

modify history:
	Guangwei Jiang, 2012-07-25
	add codes to caculate the duration time.
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

void genknuth(unsigned long m, unsigned long n)
{
	for (unsigned long i = 0; i < n; i++)
	{
		// select m of remaining n-i
		if ((bigrand()%(n-i)) < m)
		{
			printf("i = 0x%lx\n", i);
			m--;
		}
	}
}

int main()
{
	clock_t start, finish;
	double duration;
	unsigned long m, n;

	m = 2;
	n = 0xffffffff;

	printf("m = 0x%lx, n = 0x%lx\n", m, n);

	start = clock();
	srand(time(0));
	genknuth(m, n);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("\nthe duration is %f seconds\n\n", duration);

	return 0;
}
