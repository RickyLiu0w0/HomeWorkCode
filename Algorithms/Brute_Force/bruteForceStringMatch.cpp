int BruteForceStringMatch(char* T, int Tn, char* P, int Pm)
{
	//该算法实现了蛮力字符串匹配
	//输入：一个n个字符的数组，代表一段文本
	//	   一个m个字符的数组，代表一个模式
	//输出：如果查询成功，返回文本第一个匹配字符子串中第一个字符的位置
	//	   否则返回-1
	for (int i = 0; i < Tn - Pm + 1; i++)
	{
		int j = 0;
		while(j < Pm && P[j] == T[i+j])
		{
			j++;
			if (j == Pm)
				return i;
		}
	}
	return -1;
}

int CaculateSize(char* ch)
{
	//Caculate size of ch. It can be used passing arguments to Tn and Pm.
	int i = -1;
	while(ch[++i]!='\0');
	return i;
}