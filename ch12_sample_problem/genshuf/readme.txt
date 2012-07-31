P122-P123

生成随机数的有序子集的另一种方法是把包含整数0～n-1的数组顺序打乱，然后把前m个元素排序输出。 Knuth书中3.4.2节的算法P就是这样做的:
for i = [0, n)
	swap(i, randint(i, n-1))

Ashley Shepherd和Alex Woronw发现，在这个问题中我们只需要打乱数组的前m个元素，对应的代码如下。。。
void genshuf (int m, int n)
{
	int i, j;
	int *x = new init[n];
	for (i = 0; i < n; i++)
		x[i] = i;
	for (i = 0; i < m; i++){
		j = randint(i, n-1);
		int t = x[i]; x[i] = x[j]; x[j] = t;
	}
	sort (x, x+m);
	for (i = 0; i < m; i++)
		  count << x[i] << "\n";
}
