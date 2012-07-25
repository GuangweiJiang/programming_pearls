/*
file name: main.c
purpose: 
	习题1
	C库函数rand()通常返回约15个随机位。使用该函数实现bigrand()和randint(l, u)，
	要求前者至少返回30个随机位，后者返回[l, u]范围的一个随机数。
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


int randint (int low,int up)
{
	return rand()%(up-low+1) + low;
}

void main()
{
	int low, up;
	
	low = 1983;
	up = 2100;

	srand(time(0));

	printf("test bigrand() is %"PRIu64"\n", bigrand());

	printf("test randint(%d, %d) is %d\n", low, up, randint(low, up));

	printf("RAND_MAX is 0x%x, rand() is 0x%x\n", RAND_MAX, rand());
}
