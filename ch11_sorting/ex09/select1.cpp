/*
file name: select1.cpp
purpose: 
	编写程序，在O(n)时间内从数组x[0..n-1]中找出第k个最小的元素。
	算法可用对x中的元素进行排序。
creator: Guangwei Jiang
create time: 2012-08-07

modify history:

notes:
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE		50
#define CUT_OFF			1

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

void select1(int *array_data, int array_size, int low, int up, int k)
{
	int i, j,temp;
	int mid, mid_val;
	int rand_int;

	//printf("low=%d, up=%d\n", low, up);

	if (up - low < CUT_OFF)
		return;
	
	rand_int = randint(low, up);
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

	if (mid < k)
		select1(array_data, array_size, mid+1, up, k);
	else if (mid > k)
		select1(array_data, array_size, low, mid-1,k);

}

void qsort4(int *array_data, int array_size, int low, int up)
{
	int i, j,temp;
	int mid, mid_val;
	int rand_int;

	//printf("low=%d, up=%d\n", low, up);

	if (up - low < CUT_OFF)
		return;
	
	rand_int = randint(low, up);
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

	qsort4(array_data, array_size, low, mid-1);
	qsort4(array_data, array_size, mid+1, up);

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
	int k;

	srand(time(0));
	k = randint(0, ARRAY_SIZE-1);

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
	select1(array_data, ARRAY_SIZE, 0, ARRAY_SIZE-1, k);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	// print the data after sorting
	print_array(array_data, ARRAY_SIZE);

	printf("Test data number is %d\n", ARRAY_SIZE);
	printf("the duration is %f seconds\n", duration);
	printf("find the min %d is %d\n", k+1, array_data[k]);
	printf("\n");

	printf("sorting all of data\n");
	qsort4(array_data, ARRAY_SIZE, 0, ARRAY_SIZE-1);
	print_array(array_data, ARRAY_SIZE);

_free_mem:
	if (array_data != NULL)
	{
		free(array_data);
		array_data = NULL;
	}

	return 0;
}
