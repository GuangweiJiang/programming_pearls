书中的“优先级队列”是基于“完全二叉树”，请基于“完全三叉树”来实现“优先级队列”。

分析：
完全三叉树的特点，
1. 三叉树的构成：parent, child(left, mid, right);
2. root节点以1开始；
3. parent-child数学关系
   mid   child = parent*3;
   left  child = parent*3 -1；
   right child = parent*3 +1;

   parent = (child+1)/3; (child包含mid/left/right)
4. 深度计算：近似为log3n(以3为底的n)

Test results:
m=50000,  n=10000000, cost time: 0.01 seconds
m=100000, n=10000000, cost time: 0.04 seconds
m=200000, n=10000000, cost time: 0.09 seconds
m=400000, n=10000000, cost time: 0.20 seconds


**********
优先级队列：
堆通过插入新元素和提取最小元素这两种操作来维护元素集合，每个操作所需的时间都为O(log n)。

Test results:
m=50000,  n=10000000, cost time: 0.02 seconds 
m=100000, n=10000000, cost time: 0.05 seconds 
m=200000, n=10000000, cost time: 0.11 seconds 
m=400000, n=10000000, cost time: 0.21 seconds

可以使用模板（指定队列中元素的类型为T）定义一个C++类来完成这一任务：
template<class T>
class priqueue {
	priqueue(int maxsize);		// init set S to empty
	void insert(T t);			// add t to S
	T extractmin();				// return smallest in S
};
