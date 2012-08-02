/*
file name: qsort_api.cpp
purpose: 
	Using qsort() api to do sorting.
creator: Guangwei Jiang
create time: 2012-08-02

modify history:

notes:
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE		5000000

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
	return RAND_MAX*rand() + rand();
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

int compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
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
	qsort (array_data, ARRAY_SIZE, sizeof(int), compare);
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
