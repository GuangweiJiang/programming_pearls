/*
file name: generate_test_data.c
purpose: generate test data and save on the TXT file.
creator: guangwei jiang
create time: 2012-03-20

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

#define random(x) 				(rand()%x)
#define VALUE_SCOPE				10000000

#define DATA_ARRAY_SIZE			2000000

#define STORE_FILE_NAME			"test_data.bin"

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
	
	fp = fopen(STORE_FILE_NAME, "wb");
	if (fp == NULL)
	{
		printf("open test data failed\n");
		ret = -1;
		goto _end;
	}
	
	result = fwrite(array, 1, array_size*sizeof(int), fp);
	if (result != array_size*sizeof(int))
	{
		printf("write file failed\n");
		ret = -1;
		goto _fclose;
	}
	
	
_fclose:
	fclose(fp);
	
_end:	
	return ret;
}

int read_array_from_file(char * filename)
{
	int ret = 0;
	FILE * fp;
	long lSize;
	char * buffer;
	size_t result;
	
	fp = fopen ( filename , "rb" );
	if (fp==NULL)
	{
		printf("open file failed\n");
		ret = -1;
		goto _end;
	}
	
	// obtain file size:
	fseek (fp , 0 , SEEK_END);
	lSize = ftell (fp);
	rewind (fp);
	
	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL)
	{
		printf("memory allocate failed\n");
		ret = -1;
		goto _fclose;
	}
	
	// copy the file into the buffer:
	result = fread (buffer,1,lSize,fp);
	if (result != lSize)
	{
		printf("read failed\n");
		ret = -1;
		goto _free_buffer;
	}
	
	// print the array
	printf("\nafter read from file\n");
	print_array((int *)buffer, lSize/sizeof(int));

_free_buffer:	
	free (buffer);

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
	
	printf("read before store to file\n");
	print_array(array_data, DATA_ARRAY_SIZE);
	
	store_array_to_file(array_data, DATA_ARRAY_SIZE);
	
	read_array_from_file(STORE_FILE_NAME);

}
