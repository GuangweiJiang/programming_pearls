优先级队列：
堆通过插入新元素和提取最小元素这两种操作来维护元素集合，每个操作所需的时间都为O(log n)。

notes:
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
