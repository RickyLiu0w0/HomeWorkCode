#include <vector>
#include <iostream>
class point
{
public:
	point(int X, int Y):x(X),y(Y){};
	point() {x = 0; y = 0;}
	int getX() {return x;}
	int getY() {return y;}

private:
	int x;
	int y;	
};

bool allSide(std::vector<point> p, int i,int j)
{
	int a = p[j].getY() - p[i].getY();
	int b = p[i].getX() - p[j].getX();
	int c = p[i].getX() * p[j].getY() - p[i].getY() * p[j].getX();
	bool flag = true;
	bool side ;
	for (int k = 0 ; k < p.size(); k ++)
	{
		if (k == i || k == j)
			continue;
		int result = a * p[k].getX() + b * p[k].getY() - c;
		/**
		std::cout << "i = " << i <<"\tj = " << j << "\tk = " << k << std::endl;
		std::cout << "a = " << a << "\tb = " << b << "\tc = " << c << std::endl;
		std::cout << "result = " << result <<std::endl;
		std::cout << "flag = " << flag << std::endl;  
		**/
		if (!result) ;
		else if (flag)
		{
			if (result > 0 )
				side = true;
			else
				side = false;
			flag = false;
		}
		else if (side)
		{
			if (result < 0 )
			{
				//std::cout << i << "和" << j << "不能构成凸包的一条边\n";
				return false;
			}
		}
		else 
		{
			if (result > 0)
			{
				//std::cout << i << "和" << j << "不能构成凸包的一条边\n";
				return false;
			}
		}
	}
	return true;
}

std::vector<point> BruteForceConvexHull(std::vector<point> p)
{
	//使用蛮力法求平面中距离构成凸包的极点的集合
	//输入：一个n(n >= 2)个点的列表p, p1=(x1,y1), ..., pn(xn,yn)
	//输出：构成凸包的边的集合，p0和p1是一条边，p2和p3是一条边...
	std::vector<point> result;
	for (int i = 0; i < p.size() - 1 ; i++)
	{
		for (int j = i + 1; j < p.size(); j++)
		{
			std::cout << "intput :i = " << i <<"\tj = " << j << std::endl;
			if (allSide(p, i, j))
			{
				result.push_back(p[i]);
				result.push_back(p[j]);
			}
		}
	}
	return result;
}
