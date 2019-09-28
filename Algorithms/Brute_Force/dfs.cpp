#include <iostream>
#include "../graph.h"

void dfs(GraphLink& g, int index);
void DFS(GraphLink& g)	
{
	//实现给定图的深度优先查找遍历
	//输入：图g = <V, E>
	//输出：图g的顶点，按照被DFS遍历的第一次访问到的先后次序
	for (int i = 0 ; i < g.getNumVertex(); i++)
	{
		if (!g.vertexTable[i].flag)
			dfs(g, i);
	}
}

void dfs(GraphLink& g, int index)
{
	std::cout << g.vertexTable[index].point << std::endl;
	g.vertexTable[index].flag = true;
	Edge* p =  g.vertexTable[index].list;
	while (p)
	{
		int next = p -> destvalue;
		if (!g.vertexTable[next].flag)
			dfs(g, next);
		p = p -> link;
	}
}