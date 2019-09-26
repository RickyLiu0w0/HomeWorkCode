#include <iostream>

int Eculid(int m,int n) 
{
	//使用欧几里得算法计算gcd(m,n)
	//输入：两个不全为0的非负整数m，n
	//输出：m，n的最大公约数
	while (!n) 
	{
		int r = m % n ;
		m = n ;
		n = r;
	}
	return m;
}