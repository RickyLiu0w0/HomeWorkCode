#include <vector>
#include <limits>
#include <cmath>

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

double BruteForcestPoints(std::vector<point> p)
{
	//使用蛮力法求平面中距离最近的两点
	//输入：一个n(n >= 2)个点的列表p, p1=(x1,y1), ..., pn(xn,yn)
	//输出：两个最近点的距离
	double d = (std::numeric_limits<int>::max)();
	for (int i = 0;i < p.size()- 1 ; i++)
		for (int j = i + 1; j < p.size(); j++)
		{
			double d1 = sqrt(pow(p[i].getX() - p[j].getX(), 2)+ 
				pow(p[i].getY() - p[j].getY(), 2));
			d = (d < d1)? d : d1;
		}
	return d;
}