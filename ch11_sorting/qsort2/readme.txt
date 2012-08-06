P113, P116, P209-P210
Bob Sedgewick修改了Lomuto的划分方案，改为从右向左进行。

notes:
If the test data are random, using "g++ qsort2.cpp",
when test data is 5,000,000, it costs around 1.33 seconds;
when test data is 10,000,000, it costs around 2.77 seconds;

If the test data are equal, using "g++ qsort2.cpp", 
when test data is 50,000, it costs around 9.84 seconds;
when test data is 100,000, it costs around 39.10 seconds;
when test data is 200,000, it has errors "Segmentation fault";

If the test data are increasing, using "g++ qsort2.cpp",
when test data is 50,000, it costs around 9.91 seconds;
when test data is 100,000, it costs around 39.23 seconds;
when test data is 200,000, it has errors "Segmentation fault";


**********
P110
一种简单的快速排序(Quicksort)：
该算法用到了8.3节的“分治法”，排序数组时，将数组分成两个小部分，然后对它们递归排序。

notes:
If the test data are random, using "g++ qsort1.cpp",
when test data is 5,000,000, it costs around 1.30 seconds;
when test data is 10,000,000, it costs around 2.72 seconds;

If the test data are equal, using "g++ qsort1.cpp", 
when test data is 50,000, it costs around 6.69 seconds;
when test data is 100,000, it costs around 38.70 seconds;
when test data is 200,000, it has errors "Segmentation fault";

If the test data are increasing, using "g++ qsort1.cpp",
when test data is 50,000, it costs around 9.67 seconds;
when test data is 100,000, it costs around 38.67 seconds;
when test data is 200,000, it has errors "Segmentation fault";


**********
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
