/*
file name: map_string.cpp
purpose: 
	统计“TheAutobiographyOfBenjaminFranklin.txt”中出现频率最高的100个单词。
	（使用标准库中的map将整个计数与每个字符串联系起来。）。
creator: guangwei jiang
create time: 2012-09-12

modify history:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
#include <map>
 
using namespace std;

#define INPUT_FILE_NAME			"TheAutobiographyOfBenjaminFranklin.±txt"
#define MAX_CHAR_NUM			128

int main()
{
	FILE * fp;
	map <string, int> M;
	map <string, int>::iterator j;
	char str[MAX_CHAR_NUM];
	clock_t start, finish;
	double duration;
	
	start = clock();
	
	fp = fopen (INPUT_FILE_NAME, "rb" );
	if (fp==NULL)
	{
		printf("open file failed\n");
		return -1;
	}
	
	while (fscanf(fp, "%s", str) != EOF)
	{
		M[str]++;
	}
	fclose(fp);
	
	for (j = M.begin(); j != M.end(); ++j)
		cout << j->first << " " << j->second << "\n";
	
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "Cost time: " << duration << " seconds \n";

	return 0;
}
