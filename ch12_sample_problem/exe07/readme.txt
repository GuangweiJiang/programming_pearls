[V.A. Vyssotsky]生成组合对象的算法通常用递归函数来表达。
Knuth的算法如下所示：
void randselect (m, n)
		pre 0 <= m <=n
		post m distict integers from 0..n-1 are
			printed in decreasing order
		if m > 0
			if (bigrand() % n ) < m
				print n-1
				randselect (m-1, n-1)
			else
				randselect(m, n-1)
