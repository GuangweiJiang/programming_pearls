/*
file name: bitmap_sort.c
purpose: 使用稀疏矩阵/位图排序。 (programming pearls, 2nd edition, 书中示例)
		 输入： 一个最多包含n个正整数的文件，每个数都小于n，其中n=10的7次方。文件中无重复数。
		 输出： 按升序排列输入的整数表。
		 约束： 最多大约1M的内存空间可用，有充足的磁盘存储空间可用。运行时间最多几分钟，运行时间为10秒就不需要进一步优化。
creator: guangwei jiang
create time: 2012-03-16

modify history:
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

#define INPUT_FILE_NAME			"test_data_2000000.bin"

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
		printf("%d\t\t", array[i]);
		if ((i+1)%5 == 0)
		{
			printf("\n");
		}
	}
}

int sort_bitmap(int array_data[], int data_array_size, char array_bitmap[], int bitmap_array_size)
{
	int ret = 0;
	int i, j;
	
	i = 0;
	j = 0;
	
	for (i = 0; i < bitmap_array_size; i++)
	{
		array_bitmap[i] = 0;
	}
	
	for (i = 0; i < data_array_size; i++)
	{
		array_bitmap[array_data[i]/8] |= 1<< (array_data[i]%8);
	}
	
	for (i = 0; i < bitmap_array_size*8; i++)
	{
		if ((array_bitmap[i/8]) &(1 << (i%8)))
		{
			array_data[j++] = i;
		}
	}
		
	return ret;
}

void main()
{
	int *array_data;
	char *array_bitmap;; 
	int i;
	clock_t start, finish;
	double duration;
	FILE * fp;
	long lSize;
	size_t result;
	
	fp = fopen (INPUT_FILE_NAME, "rb" );
	if (fp==NULL)
	{
		printf("open file failed\n");
		return;
	}
	
	// obtain file size:
	fseek (fp , 0 , SEEK_END);
	lSize = ftell (fp);
	rewind (fp);
	
	// allocate memory to contain the whole file:
	array_data = (int*) malloc (lSize);
	if (array_data == NULL)
	{
		printf("memory allocate failed\n");
		goto _fclose;
	}
	
	// copy the file into the buffer:
	result = fread (array_data,1,lSize,fp);
	if (result != lSize)
	{
		printf("read failed\n");
		goto _free_mem;
	}
	
	array_bitmap = (char*) malloc (sizeof(char)*BITMAP_ARRAY_SIZE);
	if (array_bitmap == NULL)
	{
		printf("memory(array_bitmap) allocate failed\n");
		goto _free_mem;
	}
	memset(array_bitmap, 0, sizeof(char)*BITMAP_ARRAY_SIZE);
		
	printf("before sorting\n");
	print_array(array_data, lSize/4);
		
	start = clock();
	sort_bitmap(array_data, lSize/4, array_bitmap, BITMAP_ARRAY_SIZE);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	
	printf("\nafter sorting\n");
	print_array(array_data, lSize/4);
	
	printf("\nthe duration of qsort() is %f seconds\n\n", duration);
	
_free_mem:
	if (array_bitmap != NULL)
	{
		free(array_bitmap);
	}
	if (array_data != NULL)
	{
		free(array_data);
	}
	
_fclose:
	fclose(fp);

}
