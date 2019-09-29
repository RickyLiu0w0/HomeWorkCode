#include <iostream>
#include <queue>
#include "../graph.h"

void bfs(GraphLink& g, int index);

void BFS(GraphLink& g)
{
	//实现给定图的广度优先搜索查找遍历
	//输入：图g = <v, e>
	//输出：图g的顶点，按照BFS遍历访问到的先后次序
	for (int i = 0; i < g.getNumVertex(); i++)
		if (!g.vertexTable[i].flag)
			bfs(g, i);
}

void bfs(GraphLink& g, int index)
{
	std::queue<int> que;
	std::cout << g.vertexTable[index].point << std::endl;
	g.vertexTable[index].flag = true;
	que.push(index);
	while(!que.empty())
	{
		Edge* p = g.vertexTable[que.front()].list;
		while(p)
		{
			int next = p -> destvalue;
			p = p -> link;
			if (!g.vertexTable[next].flag)
			{
				std::cout << g.vertexTable[next].point << std::endl;
				g.vertexTable[next].flag = true;
				que.push(next);
			}
		}
		que.pop();
	}	
}