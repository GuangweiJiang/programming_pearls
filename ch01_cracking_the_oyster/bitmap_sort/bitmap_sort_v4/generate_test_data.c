/*
file name: generate_test_data.c
purpose: generate test data and save on the TXT file.
creator: guangwei jiang
create time: 2012-03-20

modify history:
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

#define DATA_ARRAY_SIZE			100000
#define STORE_FILE_NAME			"test_data.txt"

int generate_random_array(int array[])
{
	int i, j;
	int random_val;
	bool is_repeat_random;
	int ret = 0;
	
	srand((int)time(0));
	
	for (i = 0; i < DATA_ARRAY_SIZE; i++)
	{
		random_val = random(VALUE_SCOPE);
		
		is_repeat_random = false;
		for (j = 0; j<=i; j++)
		{
			if (random_val == array[j])
			{
				is_repeat_random = true;
				break;
			}
		}
		
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
	int array_data[DATA_ARRAY_SIZE];
	int i;
	clock_t start, finish;
	double duration;
	
	generate_random_array(array_data);
	
	store_array_to_file(array_data, DATA_ARRAY_SIZE);
	
	printf("Generate test data done, file name is %s, test data number is %d\n\n", STORE_FILE_NAME, DATA_ARRAY_SIZE);
}
