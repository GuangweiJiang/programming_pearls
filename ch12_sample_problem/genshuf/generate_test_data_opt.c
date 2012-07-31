/*
file name: generate_test_data_opt.c
purpose: generate test data and save on the TXT file.
creator: guangwei jiang
create time: 2012-03-20

modify history:
	Guangwei Jiang, 2012-07-25
	Based on the codes and hint on P196 (as below), re-write the codes, and it's very effective,
	for i = [0, n)
		x[i] = i;
	for i = [0, k)
		swap(i, randint(i, n-1))
		print x[i]

	Guangwei Jiang, 2012-07-24
	Save the test data as TXT instead the raw data.
	
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

#define random(x) 				(rand()%x)
#define VALUE_SCOPE				10000000

#define DATA_ARRAY_SIZE			1000000
#define STORE_FILE_NAME			"test_data.txt"

int randint (int min,int max)
{
	int random_val = 0;

	random_val = random(max-min+1) + min;

	return random_val;
}

void swap (int *x, int *y)
{
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

int generate_random_array(int array[], int value_scope, int number)
{
	int i;
	int ret = 0;
	int tmp;
	
	srand((int)time(0));

	for (i = 0; i < value_scope; i++)
		  array[i] = i;
	
	for (i = 0; i < number; i++)
	{
		swap(array+i, array+randint(i, value_scope));
	}
	return ret;
}

void print_array(int array[], int array_size)
{
	int i;
	
	for (i = 0; i < array_size; i++)
	{
		printf("%d\t", array[i]);
		if ((i+1)%5 == 0)
		{
			printf("\n");
		}
	}
}

int store_array_to_file(int array[], int array_size)
{
	int ret = 0;
	FILE *fp;
	size_t result;
	int i = 0;
	
	fp = fopen(STORE_FILE_NAME, "wb");
	if (fp == NULL)
	{
		printf("open test data failed\n");
		ret = -1;
		goto _end;
	}
	
	for (i = 0; i < array_size; i++)
	{
		fprintf(fp, "%d\n", array[i]);
	}
	
_fclose:
	fclose(fp);
	
_end:	
	return ret;
}

void main()
{
	int *array_data;
	int i;
	clock_t start, finish;
	double duration;

	array_data = (int*) malloc (sizeof(int)*VALUE_SCOPE);
	if (array_data == NULL)
	{
		printf("memory(array_bitmap) allocate failed\n");
		goto _free_mem;
	}
	
	generate_random_array(array_data, VALUE_SCOPE, DATA_ARRAY_SIZE);
	
	store_array_to_file(array_data, DATA_ARRAY_SIZE);
	
	printf("Generate test data done, file name is %s, test data number is %d\n\n", STORE_FILE_NAME, DATA_ARRAY_SIZE);

_free_mem:
	if (array_data != NULL)
	{
		free(array_data);
		array_data = NULL;
	}
}
