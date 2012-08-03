Using API <qsort> to do sorting.

notes:
Test data is 5,000,000, using "g++ qsort_api.cpp",
If the test data are random, it costs around 1.16 seconds;
If the test data are equal, it costs around 0.34 seconds;
If the test data are increasing, it costs around 0.34 seconds;

Test data is 10,000,000, using "g++ qsort_api.cpp",
If the test data are random, it costs around 2.44 seconds;
If the test data are equal, it costs around 0.70 seconds;
If the test data are increasing, it costs around 0.70 seconds;

**********
function-qsort
void qsort ( void * base, size_t num, size_t size, int ( * comparator ) ( const void *, const void * ) );

Sort elements of array
Sorts the num elements of the array pointed by base, each element size bytes long, using the comparator function to determine the order.
The sorting algorithm used by this function compares pairs of values by calling the specified comparator function with two pointers to elements of the array.
The function does not return any value, but modifies the content of the array pointed by base reordering its elements to the newly sorted order.

Parameters
base - Pointer to the first element of the array to be sorted.
num - Number of elements in the array pointed by base.
size - Size in bytes of each element in the array.
comparator - Function that compares two elements. The function shall follow this prototype:

int comparator ( const void * elem1, const void * elem2 ); 
The function must accept two parameters that are pointers to elements, type-casted as void*. 
These parameters should be cast back to some data type and be compared.
The return value of this function should represent whether elem1 is considered less than, equal to, or greater than elem2 by returning, respectively, a negative value, zero or a positive value.

Return Value
(none) 

**********
Example
/* qsort example */
#include <stdio.h>
#include <stdlib.h>

int values[] = { 40, 10, 100, 90, 20, 25 };

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main ()
{
  int n;
  qsort (values, 6, sizeof(int), compare);
  for (n=0; n<6; n++)
     printf ("%d ",values[n]);
  return 0;
}


Output:

10 20 25 40 90 100

**********
See also
bsearch
Binary search in array (function )
