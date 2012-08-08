/*
file name: qsort6.cpp
purpose: 
	Based on qsort4.
	优化“划分元素”（取数组样本的中间值）：
	随机选择3个数，取中间大小数为“划分元素”。
creator: Guangwei Jiang
create time: 2012-08-08

modify history:

notes:
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE		5000000
#define CUT_OFF			20

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
	return RAND_MAX*rand() + rand();
}

int randint(int low, int up)
{
	return (low + bigrand()%(up-low+1));
}

void gen_random_array(int *array_data, int array_size)
{
	int i;

	printf("The test data are random.\n");

	srand(time(0));
	for (i = 0; i < array_size; i++)
	{
		array_data[i] = bigrand()%RAND_MAX;
	}
}

void gen_equal_array(int *array_data, int array_size)
{
	int i, test_val;

	printf("The test data are equal.\n");

	srand(time(0));
	test_val = bigrand()%RAND_MAX;

	for (i = 0; i < array_size; i++)
	{
		array_data[i] = test_val;
	}
}

void gen_increasing_array(int *array_data, int array_size)
{
	int i;

	printf("The test data are increasing.\n");

	for (i = 0; i < array_size; i++)
	{
		array_data[i] = i;
	}
}

int select_mid(int *array_data, int low, int up)
{
	int mid;
	int rand_int1, rand_int2, rand_int3;

	rand_int1 = randint(low, up);
	rand_int2 = randint(low, up);
	rand_int3 = randint(low, up);

	if (((array_data[rand_int1]>=array_data[rand_int2]) &&(array_data[rand_int1]<=array_data[rand_int3])) ||
	    ((array_data[rand_int1]>=array_data[rand_int3]) &&(array_data[rand_int1]<=array_data[rand_int2])))
		mid = rand_int1;
	else if (((array_data[rand_int2]>=array_data[rand_int1]) &&(array_data[rand_int2]<=array_data[rand_int3])) ||
	    ((array_data[rand_int2]>=array_data[rand_int3]) &&(array_data[rand_int2]<=array_data[rand_int1])))
		mid = rand_int2;
	else if (((array_data[rand_int3]>=array_data[rand_int1]) &&(array_data[rand_int3]<=array_data[rand_int2])) ||
	    ((array_data[rand_int3]>=array_data[rand_int2]) &&(array_data[rand_int3]<=array_data[rand_int1])))
		mid = rand_int3;

	return mid;
}

void qsort6(int *array_data, int array_size, int low, int up)
{
	int i, j,temp;
	int mid, mid_val;
	int rand_int;

	//printf("low=%d, up=%d\n", low, up);

	if (up - low < CUT_OFF)
		return;
	
	rand_int = select_mid(array_data, low, up);
	temp = array_data[rand_int];
	array_data[rand_int] = array_data[up];
	array_data[up] = temp;

	mid_val = array_data[up];
	i = low;
	j = up-1;
	while (i<j)
	{
		while((array_data[i] <= mid_val) && (i<j))
		{
			i++;
		}

		while((array_data[j] > mid_val) && (i<j))
		{
			j--;
		}

		if (i != j)
		{
			temp = array_data[i];
			array_data[i] = array_data[j];
			array_data[j] = temp;
		}
	}
	
	mid = i;
	if (array_data[up] < array_data[mid])
	{
		array_data[up] = array_data[mid];
		array_data[mid] = mid_val;
	}
	else // why need "mid++"? if the array is "38 34 62", how do you solve it? I do like below.
		  mid++;

	qsort6(array_data, array_size, low, mid-1);
	qsort6(array_data, array_size, mid+1, up);

}

void isort3(int *array_data, int array_size)
{
	int i, j, temp;

	for (i = 0; i < array_size; i++)
	{
		temp = array_data[i];
		for (j = i; j > 0 && array_data[j-1] > temp; j--)
			array_data[j] = array_data[j-1];
		array_data[j] = temp;
	}
}

void print_array(int *array_data, int array_size)
{
	int i;

	for (i = 0; i < array_size; i++)
	{
		printf("%12d ", array_data[i]);

		if ((i+1)%10 == 0)
			  printf("\n");
	}

	printf("\n");
}

int main()
{
	clock_t start, finish;
	double duration;	
	int *array_data;

	array_data = (int*) malloc (sizeof(int)*ARRAY_SIZE);
	if (array_data == NULL)
	{
		printf("memory(array_bitmap) allocate failed\n");
		goto _free_mem;
	}
	
	printf("Generate the test data...\n");
	gen_random_array(array_data, ARRAY_SIZE);
	//gen_equal_array(array_data, ARRAY_SIZE);
	//gen_increasing_array(array_data, ARRAY_SIZE);

	printf("Sorting data...\n");
	start = clock();
	qsort6(array_data, ARRAY_SIZE, 0, ARRAY_SIZE-1);
	isort3(array_data, ARRAY_SIZE);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	// print the data after sorting
	//print_array(array_data, ARRAY_SIZE);

	printf("Test data number is %d\n", ARRAY_SIZE);
	printf("the duration is %f seconds\n\n", duration);

_free_mem:
	if (array_data != NULL)
	{
		free(array_data);
		array_data = NULL;
	}

	return 0;
}
