P130-P131
生成[0, maxval]范围内m个随机整数的有序序列，不允许重复。
使用链表实现IntSetList(链表insert使用递归函数).

notes:
m=50000, n=10000000, Cost time: 22.66 seconds
m=100000; n=10000000,Cost time: 173.02 seconds 


**********
P129
生成[0, maxval]范围内m个随机整数的有序序列，不允许重复。
使用整数数组实现IntSetArray。

notes:
m=50000, n=10000000, Cost time: 4.17 seconds 
m=100000, n=10000000, Cost time: 16.69 seconds 


**********
P127-P128
生成[0, maxval]范围内m个随机整数的有序序列，不允许重复。
使用c++标准模板中的set容器，来实现IntSetSTL。

notes:
m=50000, n=10000000, Cost time: 0.14 seconds 
m=100000, n=10000000, Cost time: 0.28 seconds 


**********
我们将待生成的数据结构称之为InsSet，意指整数集合。
下面我们将把该接口定义为具有如下公有成员的C++类：
class IntSetImp {
public:
	IntSetImp(int maxelements, int maxval);
	void insert(int t);
	int size();
	void report(int *v);
}

构造函数IntSetImp将集合初始化为空。该函数有两个参数，分别表示集合元素的最大个数和集合元素的最大值（加1），特定的实现可用忽略其中之一或者两个都忽略；
insert函数向集合中添加一个新的整数（前提是集合中原先没有这个整数）；
sizeof函数返回当前的元素个数；
reprot函数（按顺序）将元素写入到向量v中。
