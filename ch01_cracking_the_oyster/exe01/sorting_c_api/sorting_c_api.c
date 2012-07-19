/*
file name: sorting_c_api.c
purpose: 如果不缺内存，如何使用一个具有库的语言来实现一种排序算法以表示和排序集合？ (programming pearls, 2nd edition, section1_exe01)
creator: guangwei jiang
create time: 2012-03-14

modify history:

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Linux gcc doesn't support "bool", we define it as below
#define bool 			int
enum BOOL {
false = 0,
true = !false
};

#define random(x) 		(rand()%x)
#define RANDOM_SCOPE	1000000

#define ARRAY_SIZE		200000



int generate_random_array(int array[])
{
	int i, j;
	int random_val;
	bool is_repeat_random;
	int ret = 0;
	
	srand((int)time(0));
	
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		random_val = random(RANDOM_SCOPE);
		
		is_repeat_random = false;
		/*for (j = 0; j<=i; j++)
		{
			if (random_val == array[j])
			{
				is_repeat_random = true;
				break;
			}
		}*/
		
		if (!is_repeat_random)
		{
			array[i] = random_val;
		}
		else
		{
			i--;
		}
	}
	
	return ret;
}

void print_array(int array[])
{
	int i;
	
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		printf("%d\t", array[i]);
		if ((i+1)%10 == 0)
		{
			printf("\n");
		}
	}
}

int compare(const void *elem1, const void *elem2)
{
	return *((int*)(elem1)) - *((int*)(elem2));
}

void main()
{
	int array[ARRAY_SIZE];
	int i;
	clock_t start, finish;
	double duration;
	
	generate_random_array(array);
	
	printf("before sorting\n");
	print_array(array);
	
	
	// Using c lib api/qsort() to do sorting
	start = clock();
	qsort(array, ARRAY_SIZE, sizeof(int), compare);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	
	printf("\nthe duration of qsort() is %f seconds,\n", duration);
	
	printf("\nafter sorting\n");
	//print_array(array);
	
	
}
