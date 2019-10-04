#include <string>
#include <cmath>
using namespace std;

long recursive_miltiply(string x, string y)
{
	//已经假设x，y的长度一样
	int xlength = x.length();
	int ylength = y.length();
	if(xlength == 1 || ylength == 1)
	{
		//长度足够小，采用直接相乘，递归结束
		int result = stoi(x) * stoi(y);
		return result;
	}
	else if (xlength%2 != 0 || ylength%2 != 0)
	{
		cout << "目前只支持偶数长度的数字串输入，程序退出\n";
		cout << "错误数字串为 " << x << " 或 " << y << endl;
		exit(1);
	}
	string x1 = x.substr(0, xlength / 2);
	string x0 = x.substr(xlength/2);
	string y1 = y.substr(0, ylength / 2);
	string y0 = y.substr(ylength/2);
	cout << "x1 = " << x1 << " x0 = " << x0 <<endl;
	cout << "y1 = " << y1 << " y0 = " << y0 <<endl;
	long p = recursive_miltiply(to_string(stol(x1) + stol(x0)),
		to_string(stol(y1) + stol(y0)));
	long x1y1 = recursive_miltiply(x1, y1);
	long x0y0 = recursive_miltiply(x0, y0);
	long center = p - x1y1 - x0y0;
	long result = (x1y1)*pow(10,xlength) + center*pow(10,xlength/2) + x0y0;
	cout << "x1y1 = " << x1y1 << " x0y0 = " << x0y0 <<endl;
	cout << x << " * " << y << " = " << result << endl;
	return result;
}