/*
file name: qsort5.cpp
purpose: 
	尝试用“循环”替代“递归”，实现“快速排序”。
creator: Guangwei Jiang
create time: 2012-08-02

modify history:

notes:
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE		50000

struct stack_node
{
	int low;
	int up;
};

struct stack_node *stack_node1, *stack_node2;

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

int partition(int *array_data, int array_size, int low, int up)
{
	int i, temp;
	int mid, mid_val;

	if (low >= up)
		return -1;
	
	mid_val = array_data[up];
	mid = low;
	for (i = low; i < up; i++)
	{
		if (array_data[i] <= mid_val)
		{
			temp = array_data[i];
			array_data[i] = array_data[mid];
			array_data[mid] = temp;
			mid++;
		}
	}
	
	array_data[up] = array_data[mid];
	array_data[mid] = mid_val;

	return mid;
}

void qsort5(int *array_data, int array_size, int low, int up)
{
	int i, j, temp;
	int mid, mid_val;
	int stack_level;

	//printf("low=%d, up=%d\n", low, up);

	if (low >= up)
		return;

	// stack level 0, we store the next stack level's low/up to stack_node1
	stack_level = 0;
	mid = partition(array_data, array_size, low, up);
	i = 0;
	if (mid >= 0)
	{
		stack_node1[i].low = mid + 1;
		stack_node1[i].up = up;
		i++;
		
		stack_node1[i].low = low;
		stack_node1[i].up = mid - 1;
		i++;
	}
	// assign "-1" to indicate the end 
	stack_node1[i].low = -1;
	stack_node1[i].up = -1;

	stack_level++;

	do{
		if (stack_level%2 == 1)
		{
			// case 1: the stack level is odd
			// Get current stack level's low/up from stack_node1[]
			// Store the next stack level's low/up in stack_node2[]
			i = 0;
			j = 0;
			while (stack_node1[i].low != -1)
			{
				mid = partition(array_data, array_size, stack_node1[i].low, stack_node1[i].up);
				
				if (mid >= 0)
				{
					stack_node2[j].low = mid + 1;
					stack_node2[j].up = stack_node1[i].up;
					j++;
				
					stack_node2[j].low = stack_node1[i].low;
					stack_node2[j].up = mid - 1;
					j++;
				}
				i++;
			}

			// assign "-1" to indicate the end 
			stack_node2[j].low = -1;
			stack_node2[j].up = -1;
		}
		else if (stack_level%2 == 0)
		{
			// case 2: the stack level is even
			// Get current stack level's low/up from stack_node2[]
			// Store the next stack level's low/up in stack_node1[]
			i = 0;
			j = 0;
			while (stack_node2[i].low != -1)
			{
				mid = partition(array_data, array_size, stack_node2[i].low, stack_node2[i].up);
			
				if (mid >= 0)
				{
					stack_node1[j].low = mid + 1;
					stack_node1[j].up = stack_node2[i].up;
					j++;
				
					stack_node1[j].low = stack_node2[i].low;
					stack_node1[j].up = mid - 1;
					j++;
				}
				i++;
			}
			// assign "-1" to indicate the end 
			stack_node1[j].low = -1;
			stack_node1[j].up = -1;
		}

		stack_level++;

	}while (i > 0);	// it indicates that the current stack no any thing to do, 
					// all data has sorted, so stop 
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

	stack_node1 = (struct stack_node *)malloc(sizeof(struct stack_node)*ARRAY_SIZE);
	if (stack_node1 == NULL)
	{
		printf("mamory(stack_node1) allocate failed\n");
		goto _free_mem;
	}

	stack_node2 = (struct stack_node *)malloc(sizeof(struct stack_node)*ARRAY_SIZE);
	if (stack_node2 == NULL)
	{
		printf("mamory(stack_node2) allocate failed\n");
		goto _free_mem;
	}
	
	printf("Generate the test data...\n");
	//gen_random_array(array_data, ARRAY_SIZE);
	//gen_equal_array(array_data, ARRAY_SIZE);
	gen_increasing_array(array_data, ARRAY_SIZE);

	printf("Sorting data...\n");
	start = clock();
	qsort5(array_data, ARRAY_SIZE, 0, ARRAY_SIZE-1);
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

	if (stack_node1 != NULL)
	{
		free(stack_node1);
		stack_node1 = NULL;
	}

	if (stack_node2 != NULL)
	{
		free(stack_node2);
		stack_node2 = NULL;
	}

	return 0;
}
