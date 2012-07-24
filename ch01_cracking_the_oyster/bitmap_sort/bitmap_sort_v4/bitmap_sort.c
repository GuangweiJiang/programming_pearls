/*
file name: bitmap_sort.c
purpose: 使用稀疏矩阵/位图排序。 (programming pearls, 2nd edition, 书中示例)
		 输入： 一个最多包含n个正整数的文件，每个数都小于n，其中n=10的7次方。文件中无重复数。
		 输出： 按升序排列输入的整数表。
		 约束： 最多大约1M的内存空间可用，有充足的磁盘存储空间可用。运行时间最多几分钟，运行时间为10秒就不需要进一步优化。
creator: guangwei jiang
create time: 2012-03-16

modify history:
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
#define BITMAP_ARRAY_SIZE		(VALUE_SCOPE/8)	// Using "bit" to indicate the value exist or not
									 			// The array type is "char", so divide by 8.

#define INPUT_FILE_NAME			"test_data.txt"
#define OUTPUT_FILE_NAME		"test_data_sorted.txt"

int set_bitmap(char array_bitmap[], int value)
{
	int ret = 0;

	array_bitmap[value/8] |= 1 << (value%8);

	return ret;
}

int get_bitmap(char array_bitmap[], int value)
{
	int ret = 0;
		
	if ((array_bitmap[value/8]) &(1 << value%8))
	{
		// the bit has been set before
		ret = 1;
	}
	else
	{
		// the bit doesn't set before
		ret = 0;
	}

	return ret;
}

int store_sorted_file(char array_bitmap[], char *file_name)
{
	int ret = 0;
	FILE *fp;
	size_t result;
	int i = 0;
	
	fp = fopen(file_name, "wb");
	if (fp == NULL)
	{
		printf("open test data failed\n");
		ret = -1;
		goto _end;
	}
	
	for (i = 0; i < VALUE_SCOPE; i++)
	{
		if (get_bitmap(array_bitmap, i))
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
	
	fp = fopen (INPUT_FILE_NAME, "rb" );
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
