#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>

const unsigned int SIZE = 10;

struct Edge
{
	Edge(int v): destvalue(v), link(NULL){}
	int destvalue;
	Edge * link;
};

struct Vertex
{
	Vertex(): list(NULL), flag(false){}
	char point;
	Edge * list;
	bool flag ;
};

class GraphLink
{
public:
	GraphLink()
	{
		maxVertex = SIZE;
		numVertex = numEdge = 0;
		vertexTable = new Vertex[maxVertex];
	}

	void insertVertex(char v)
	{
		if (numVertex >= maxVertex)
			return;
		vertexTable[numVertex++].point = v;
		return;
	}

	int getVertexIndex(char v)
	{
		for (int i = 0; i < numVertex ; i++)
			if (vertexTable[i].point == v)
				return i;
		return -1;
	}
	
	void insertEdge(char v1, char v2)
	{
		int p1 = getVertexIndex(v1);
		int p2 = getVertexIndex(v2);
		if (p1 != -1 && p2 != -1)
		{
			Edge* ed = new Edge(p2);
			ed -> link = vertexTable[p1].list;
			vertexTable[p1].list = ed;

			ed = new Edge(p1);
			ed->link = vertexTable[p2].list;
			vertexTable[p2].list = ed;
			numEdge++;
		}
	}

	void print()
	{
		for (int i = 0; i < numVertex; i++)
		{
			std::cout << vertexTable[i].point << "->";
			Edge* p = vertexTable[i].list;
			while(p)
			{
				std::cout << p->destvalue <<"->";
				p = p->link;
			}
			std::cout << "null" << std::endl;
		}
	}

	void deleteEdge(char v1, char v2)
	{
		int p1 = getVertexIndex(v1);
		int p2 = getVertexIndex(v2);
		if (p1 != -1 && p2 != -1)
		{
			Edge* p = vertexTable[p1].list;
			Edge* s = NULL;
			while (p && p->destvalue != p2)
			{
				s = p;
				p = p->link;
			}
			if (p == NULL)
				return;
			if (s == NULL)
				vertexTable[p1].list = p -> link;
			else
				s -> link = p -> link;
			delete p;

			p = vertexTable[p2].list;
			s = NULL;
			while(p && p->destvalue != p1)
			{
				s = p;
				p = p->link;
			}
			if(s == NULL)
				vertexTable[p2].list = p->link;
			else
				s ->link = p->link;
			delete p;
			p = NULL;
			numEdge--;
		}
	}

	void deleteVertex(char v)
	{
		int p = getVertexIndex(v);
		if (p != -1)
		{
			//先删除和顶点相关联的边
			Edge* s = NULL;
			Edge* p2 = vertexTable[p].list;
			while (p2)
			{
				int destvalue = p2 -> destvalue;
				Edge* q = vertexTable[destvalue].list;
				s = NULL;
				while (q && q -> destvalue != p)
				{
					s = q;
					q = q -> link;
				}
				if (s == NULL)
					vertexTable[destvalue].list = q -> link;
				else
					s -> link = q -> link;
				delete q;
				q = NULL;
				vertexTable[p].list = p2 -> link;
				delete p2;
				p2 = vertexTable[p].list;
				numEdge--;
			}
			numVertex--;

			vertexTable[p].point = vertexTable[numVertex].point;
			vertexTable[p].list = vertexTable[numVertex].list;
			p2 = vertexTable[p].list;
			while (p2)
			{
				int destValue = p2 -> destvalue;
				s = vertexTable[destValue].list;
				while (s && s -> destvalue != numVertex)
					s = s -> link;
				s -> destvalue = p;
				p2 = p2 -> link;
			}
		}
	}
	~GraphLink()
	{
		Edge* p = NULL;
		for (int i = 0 ; i < numVertex ; i++)
		{
			p = vertexTable[i].list;
			while(p)
			{
				vertexTable[i].list = p -> link;
				delete p;
				p = vertexTable[i].list;
			}
		} 
		delete [] vertexTable;
		vertexTable = NULL;
	}

	int getNumVertex() const
	{
		return numVertex;
	}

public:
	Vertex* vertexTable;

private:
	int maxVertex;
	int numVertex;
	int numEdge;
};

#endif