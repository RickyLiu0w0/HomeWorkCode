#include <vector>
#include <cmath>

class point
{
public:
	point(int X, int Y):x(X),y(Y){};
	point() {x = 0; y = 0;}

	int getX() const {return x;}
	int getY() const {return y;}

	double d(const point& p2) const
	{
		double distanceDouble = pow(this -> getX() - p2.getX(), 2)+ 
				pow(this -> getY() - p2.getY(), 2);
		return sqrt(distanceDouble);
	}

	void print()
	{
		std::cout << "x=" << x << "  " << "y=" << y << std::endl;
		return;
	}

private:
	int x;
	int y;
};

bool sortByX(const point& p1,const point& p2)
{
	return p1.getX() < p2.getX();
}

bool sortByY(const point& p1,const point& p2)
{
	return p1.getY() < p2.getY();
}


double efficientCloserPairHelp(int low, int high, std::vector<point>& p, 
	std::vector<point>& q)
{
	//std::cout << "pSize = " << p.size() <<" qSize = " << q.size() << std::endl;
	double result = 0.0;
	int size = high - low + 1;
	if ( size <= 3)
	{
		double d1 = p[low].d(p[low + 1]);
		if (3 == size)
		{
			double d2 = p[low+1].d(p[high]);
			double d3 = p[low].d(p[high]);
			result = d1<d2?(d1<d3?d1:d3):(d2<d3?d2:d3);
		}
		else 
			result = d1;
		//printf("result = %.2f\n", result);
	}
	else
	{
		int mid = (low + high) / 2;
		std::cout << "mid = " << mid << std::endl;
		int x0 = p[mid].getX();
		std::cout << "x0 = " << x0 << std::endl;

		double tempD1 = efficientCloserPairHelp(low, mid, p, q);
		double tempD2 = efficientCloserPairHelp(mid + 1, high, p, q);

		result = fmin(tempD1,tempD2);
		//printf("result = %.2f\n", result);

		std::vector<point> t;
		//std::cout << "q.size = " << q.size() << std::endl;
		for (int i = 0; i < q.size(); i++)
			if (abs(q[i].getX() - x0) <= result)
			{
				//std::cout << "i = " << i <<"  ";
				t.push_back(q.at(i));
				//for(auto arr :t)
				//	arr.print();
				//std::cout << std::endl;
			}

		double tempResult = 2 * result;

		for(int i = 0; i < t.size() - 1; i++)
			for (int j = i + 1 ; j < fmin(i+7,t.size()); j++)
				if (t[i].d(t[j]) < tempResult)
				{
					//std::cout << "t" <<i <<"=" ;
				    //t[i].print();
					//std::cout << "t" <<j <<"=" ;
					//t[j].print();
					tempResult = t[i].d(t[j]);
					//printf("tempResult = %.2f\n", tempResult);
				}
		result = fmin(result,tempResult);
	}
	return result;
}

double efficientCloserPair(std::vector<point> p)
{
	//使用分治法来求解最近点对问题
	//输入：数组P中储存来平面上n>=2个点
	//输出：最近点对的欧几里得距离
	sort(p.begin(), p.end(), sortByX);
	//for (auto arr : p)
	//	arr.print();
	std::vector<point> q(p);
	sort(q.begin(), q.end(), sortByY);
	std::cout << std::endl;
	//for (auto arr : q)
	//	arr.print();
	std::cout << std::endl;
	return  efficientCloserPairHelp(0, p.size() - 1, p, q);
}