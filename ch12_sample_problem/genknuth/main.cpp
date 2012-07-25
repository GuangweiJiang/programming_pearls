/*
file name: main.c
purpose: 
	P120-P121
	作者参考了Knuth的The Art of Computer Programming, Volume2: Seminumerical Algorithms,
	作者认为该书3.4.2节的算法S是理想的解决方案。
creator: guangwei jiang
create time: 2012-07-25

modify history:
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
	srand(time(0));
	genknuth(2, 10);

	return 0;
}
