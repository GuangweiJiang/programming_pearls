P114-P115
在qsort3()的基础上增加2项功能：
a. 随机产生划分元素；
b. l和u比较接近时，不进行任何操作；之后再用isort3()排序。

notes:
If the test data are random, test data is 5,000,000, using "g++ qsort4.cpp",
when cut-off is 5, it costs around 1.33 seconds;
when cut-off is 10, it costs around 1.27 seconds;
when cut-off is 15, it costs around 1.25 seconds;
when cut-off is 20, it costs around 1.23 seconds;
when cut-off is 50, it costs around 1.25 seconds;
when cut-off is 100, it costs around 1.39 seconds;
when cut-off is 200, it costs around 1.75 seconds;

If the test data are equal, test data is 100,000, using "g++ qsort4.cpp",
when cut-off is 20, it costs around 14.45 seconds;
when cut-off is 200, it costs around 14.45 seconds;

If the test data are equal, test data is 5,000,000, using "g++ qsort4.cpp",
when cut-off is 20, it costs around 0.47 seconds;
when cut-off is 200, it costs around 0.36 seconds;
when cut-off is 1000, it costs around 0.33 seconds;


**********
P113-P114
使用双向划分的快速排序(Quicksort);

notes:
If the test data are random, using "g++ qsort3.cpp",
when test data is 5,000,000, it costs around 1.29 seconds;
when test data is 10,000,000, it costs around 2.70 seconds;

If the test data are equal, using "g++ qsort3.cpp", 
when test data is 50,000, it costs around 3.62 seconds;
when test data is 100,000, it costs around 14.40 seconds;

If the test data are increasing, using "g++ qsort3.cpp",
when test data is 50,000, it costs around 3.63 seconds;
when test data is 100,000, it costs around 14.37 seconds;


**********
P110-P113
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
