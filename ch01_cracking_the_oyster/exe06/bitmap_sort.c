/*
file name: bitmap_sort.c
purpose:
	习题6：
	如果那个程序员说的不是每个整数最多出现一次，而是最多出现10次，你又如何建议他呢？
	你的解决方案如何随着可用存储空间总量的变化而变化？ 
creator: guangwei jiang
create time: 2012-03-16

modify history:
	Guangwei Jiang, 2012-07-24
	Allow one value repeat less or equal 10 times.

	Guangwei Jiang, 2012-07-24
	Store and read the test data in TXT file.

	guangwei_jiang, 2012-03-29
	Will read the input data from extern file.
	The extern file is a bin file (not txt file), it stores the array we needed.
	We can read out from the file to RAM directly.

	guangwei_jiang, 2012-03-20
	Using array, it's OK to allocate 8MB memory from stack, but can not exceed 10MB from test;
	So, we use "malloc" to allocate more memory from heap. 
	
notes:
	思考：如果输入的数重复，会有什么结果？又该如何处理？

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Linux gcc doesn't support "bool", we define it as below
#define bool 			int
enum BOOL {
false = 0,
true = !false
};

#define random(x) 				(rand()%x)
#define VALUE_SCOPE				10000000
#define BITMAP_ARRAY_SIZE		(VALUE_SCOPE/2)	// Using 4 bits to indicate the repeat times of a value (repeat times less or equal 10);
									 			// The array type is "char" (8 bits), so divide by 2.

#define INPUT_FILE_NAME			"test_data.txt"
#define OUTPUT_FILE_NAME		"test_data_sorted.txt"

int set_bitmap(char array_bitmap[], int value)
{
	int ret = 0;
	char cur_times = 0;

	if (value % 2) 
	{
		// It's high 4 bits
		cur_times = array_bitmap[value/2] >> 4;
		if (cur_times <15)
		{
			cur_times++;
			array_bitmap[value/2] &= 0x0F;
			array_bitmap[value/2] |= cur_times << 4;
		}
		else
		{
			ret = -1;
			printf("%s: error - cur_times over 15\n", __func__);
		}
	}
	else
	{
		// It's low 4 bits
		cur_times = array_bitmap[value/2] & 0x0F;
		if (cur_times <15)
		{
			cur_times++;
			array_bitmap[value/2] &= 0xF0;
			array_bitmap[value/2] |= cur_times;
		}
		else
		{
			ret = -1;
			printf("%s: error - cur_times over 15\n", __func__);
		}

	}

	return ret;
}

int get_bitmap(char array_bitmap[], int value)
{
	int ret = 0;
	char cur_times = 0;

	if (value % 2)
	{
		// It's high 4 bits
		cur_times = array_bitmap[value/2] >> 4;
	}
	else
	{
		// It's low 4 bits
		cur_times = array_bitmap[value/2] & 0x0F;
	}
		
	ret = (int)cur_times;
	return ret;
}

int store_sorted_file(char array_bitmap[], char *file_name)
{
	int ret = 0;
	FILE *fp;
	size_t result;
	int i = 0, j = 0;
	int repeat_times = 0;
	
	fp = fopen(file_name, "w");
	if (fp == NULL)
	{
		printf("open test data failed\n");
		ret = -1;
		goto _end;
	}
	
	for (i = 0; i < VALUE_SCOPE; i++)
	{
		repeat_times = get_bitmap(array_bitmap, i);
		for(j = 0; j < repeat_times; j++)
		{
			fprintf(fp, "%d\n", i);
		}
	}
	
_fclose:
	fclose(fp);
	
_end:	
	return ret;
}

void main()
{
	char *array_bitmap;; 
	int i, value;
	clock_t start, finish;
	double duration;
	FILE * fp;
	
	fp = fopen (INPUT_FILE_NAME, "r" );
	if (fp==NULL)
	{
		printf("open file failed\n");
		return;
	}
	
	array_bitmap = (char*) malloc (sizeof(char)*BITMAP_ARRAY_SIZE);
	if (array_bitmap == NULL)
	{
		printf("memory(array_bitmap) allocate failed\n");
		goto _free_mem;
	}
	memset(array_bitmap, 0, sizeof(char)*BITMAP_ARRAY_SIZE);
		
	start = clock();
	while (fscanf(fp, "%d", &value) != EOF)
	{
		set_bitmap(array_bitmap, value);
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	store_sorted_file(array_bitmap, OUTPUT_FILE_NAME);
	
	printf("\nSorting Done, please check file %s\n", OUTPUT_FILE_NAME);
	
	printf("\nthe duration of sort is %f seconds\n\n", duration);
	
_free_mem:
	if (array_bitmap != NULL)
	{
		free(array_bitmap);
	}
	
_fclose:
	fclose(fp);

}
