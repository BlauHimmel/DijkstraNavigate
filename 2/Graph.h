#ifndef GRAPH_H
#define GRAPH_H

#include "stdafx.h"
#include <stack>
#include <queue>
#include <iostream>
#define INF 2147483647/2
using namespace std;

template <typename VertexType, typename EdgeType>
class Edge
{
public:
	int posOfDestination;	//the position of the another vertex on the edge
	EdgeType Weight;	//weight of the edge
	Edge<VertexType, EdgeType>* link;
	Edge();
	Edge(int dest, EdgeType weight);
	bool operator != (Edge<VertexType, EdgeType>& j) const;
};

template <typename VertexType, typename EdgeType>
class Vertex
{
public:
	VertexType data;
	Edge<VertexType, EdgeType>* adj;	//the head pointer of edge chain node
};

template <typename VertexType, typename EdgeType>
class GraphLink				//if the type of return value is integer,which indicates that a position is returned.If VertexType,which indicates that a data stored in vertex is returned.
{
public:
	GraphLink(int size = 30);
	~GraphLink();
	void Output();
	void Input();
	VertexType getValue(int position);						//return the value of vertex at the position of "position"
	EdgeType getWeight(int vertex1, int vertex2);			//return the weight of edge between vertex1 and vertex2
	bool insertVertex(VertexType& vertex);
	bool removeVertex(int vertex);
	bool insertEdge(int vertex1, int vertex2, EdgeType weight);
	bool removeEdge(int vertex1, int vertex2);
	int getFirstNeighbor(int vertex);						//return the index of fisrt adjacent vertex of "vertex"
	int getNextNeighbor(int vertex, int nextVertex);		//return the index of next adjacent vertext of "nextVertex" which is a adjacent vertex of "vertex"
	bool DFS(GraphLink<VertexType, EdgeType>& graph, const VertexType& vertex, void(*visit)(VertexType data));
	bool BFS(GraphLink<VertexType, EdgeType>& graph, const VertexType& vertex, void(*visit)(VertexType data));
	int getNumberOfVertices();
	int getNumberOfEdges();
	int getVertexPosition(VertexType vertex);		//return the position(index)of the vertex in the graph
private:
	Vertex<VertexType, EdgeType>* VertexTable;			//array to store vertex
	int maxVertices;		//the maximum number f vertices
	int numEdges;			//the present number of edges
	int numVertices;		//the present number of vertices
};

template <typename VertexType, typename EdgeType>
VertexType* GetDijkstraPath(GraphLink<VertexType, EdgeType>& graph, int* path, int* distance, VertexType startVertex, VertexType endVertex,int& N,int& length)
{
	int startPos = graph.getVertexPosition(startVertex);
	int endPos = graph.getVertexPosition(endVertex);
	if (startPos == -1 || endPos == -1)			//Vertex not exist
		return NULL;
	if (startPos == endPos)						//not path exists between them
		return NULL;

	N = 1;
	
	int temp = endPos;
	while (path[temp] != startPos)
	{
		temp = path[temp];
		N++;
	}

	temp = endPos;
	VertexType* result = new VertexType[N + 1];
	result[0] = startVertex;
	for (int i = N ; i > 0;i--)
	{
		result[i] = graph.getValue(temp);
		temp = path[temp];
	}

	length = distance[endPos];
	N++;
	return result;
}

template <typename VertexType, typename EdgeType>
bool Dijkstra(GraphLink<VertexType, EdgeType>& graph, VertexType TargetVertex, int* &path, int* &distance)
{
	int NumberOfVertices = graph.getNumberOfVertices();
	path = new int[NumberOfVertices];
	distance = new int[NumberOfVertices];

	bool* Found = new bool[NumberOfVertices];
	int TargetVertexPos = graph.getVertexPosition(TargetVertex);
	if (TargetVertexPos == -1)
		return false;

	for (int i = 0; i < NumberOfVertices; i++)		//initialization
	{
		Found[i] = false;
		distance[i] = graph.getWeight(TargetVertexPos, i);
		if (TargetVertexPos != i&&distance[i] < INF)	//not the same vertax and have a edge bewteen them
			path[i] = TargetVertexPos;
		else
			path[i] = -1;
	}

	Found[TargetVertexPos] = true;
	distance[TargetVertexPos] = 0;		//add vertex "TargetVertex" into vertex set(array:"Found")
	int temp;	//position of a vertex that is going to be added into vertex set(array:"Found")

	for (int i = 1; i < NumberOfVertices; i++)	//all vertex except "TargetVertex"
	{
		int MIN = INF;
		for (int j = 0; j < NumberOfVertices; j++)
		{
			if (Found[j]==false&&distance[j]<MIN)
			{
				temp = j;
				MIN = distance[j];
			}
		}

		Found[temp] = true;	// add the vertex temp into vertex set (array:"Found")

		for (int j = 0; j < NumberOfVertices; j++)
		{
			if (Found[j] == false && MIN + graph.getWeight(temp, j) < distance[j])		//whether the distance between "TargetVertex" and "j" is short now
			{
				distance[j] = MIN + graph.getWeight(temp, j);		//update the distance and path
				path[j] = temp;
			}
		}
	}
	return true;
};

template <typename VertexType, typename EdgeType>
void GraphLink<VertexType, EdgeType>::Output()
{
	for (int i = 0; i < numVertices; i++)
	{
		cout << i << ":";
		cout << VertexTable[i].data;
		Edge<VertexType, EdgeType>* current = VertexTable[i].adj;
		if (current == NULL)
		{
			cout << "->NULL" << endl;
		}
		else
		{
			while (current != NULL)
			{
				cout << "->|" << current->posOfDestination << ":" << getValue(current->posOfDestination) << "|" << current->Weight << "|";
				current = current->link;
			}
		}
		cout << endl;
	}
};

template <typename VertexType, typename EdgeType>
void GraphLink<VertexType, EdgeType>::Input()
{
	VertexType tempVertex1, tempVertex2;
	int vertexNum, edgeNum;
	cout << "请输入顶点数:";
	cin >> vertexNum;
	cout << "请输入边数:";
	cin >> edgeNum;

	for (int i = 0; i < vertexNum; i++)			//input vertex
	{
		cout << "请输入顶点" << i + 1 << ":";
		cin >> tempVertex1;
		insertVertex(tempVertex1);
	}

	for (int i = 0; i < edgeNum;)			//input edge
	{
		cout << "请输入边" << i + 1 << "的两个端点:\n";
		cout << "1>";
		cin >> tempVertex1;
		cout << "2>";
		cin >> tempVertex2;

		int weight;
		cout << "请输入边的权值:";
		cin >> weight;

		int posOfVertex1, posOfVertex2;
		posOfVertex1 = getVertexPosition(tempVertex1);
		posOfVertex2 = getVertexPosition(tempVertex2);
		if (posOfVertex1 == -1 || posOfVertex2 == -1)
			cout << "输入有误，请重试！" << endl;
		else
		{
			insertEdge(posOfVertex1, posOfVertex2, weight);
			i++;
		}
	}
};

template <typename VertexType, typename EdgeType>
int GraphLink<VertexType, EdgeType>::getNumberOfEdges()
{
	return numEdges;
}

template <typename VertexType, typename EdgeType>
int GraphLink<VertexType, EdgeType>::getNumberOfVertices()
{
	return numVertices;
}

template <typename VertexType, typename EdgeType>
bool GraphLink<VertexType, EdgeType>::BFS(GraphLink<VertexType, EdgeType>& graph, const VertexType& vertex, void(*visit)(VertexType data))
{
	bool *visited = new bool[numVertices];
	for (int i = 0; i < numVertices; i++)
		visited[i] = false;
	int location = graph.getVertexPosition(vertex);
	if (location == -1)
		return false;

	VertexType temp;
	temp = getValue(location);
	visit(temp);
	visited[location] = true;

	queue<int> myQueue;
	myQueue.push(location);

	int next;
	while (!myQueue.empty())
	{
		location = myQueue.front();
		myQueue.pop();
		next = graph.getFirstNeighbor(location);
		while (next != -1)
		{
			if (visited[next] == false)
			{
				VertexType temp;
				temp = getValue(next);
				visit(temp);
				visited[next] = true;
				myQueue.push(next);
			}
			next = graph.getNextNeighbor(location, next);
		}
	}
	delete[] visited;
	return true;
};

template <typename VertexType, typename EdgeType>
bool GraphLink<VertexType, EdgeType>::DFS(GraphLink<VertexType, EdgeType>& graph, const VertexType& vertex, void(*visit)(VertexType data))
{
	bool *visited = new bool[numVertices];
	for (int i = 0; i < numVertices; i++)
		visited[i] = false;
	int location = graph.getVertexPosition(vertex);
	if (location == -1)
		return false;

	stack<int> myStack;
	myStack.push(location);
	int nextV;

	while (!myStack.empty())
	{
		VertexType temp;
		temp = getValue(myStack.top());

		if (visited[location] == false)
		{
			visit(temp);
			visited[location] = true;
			nextV = graph.getFirstNeighbor(location);
		}
		else
			nextV = graph.getNextNeighbor(location, nextV);

		if (nextV == -1)
		{
			nextV = myStack.top();
			myStack.pop();
			if (!myStack.empty())
				location = myStack.top();
			else
				return true;
		}
		else if (visited[nextV] == false)
		{
			myStack.push(nextV);
			location = nextV;
		}
		else
		{
			nextV = graph.getNextNeighbor(location, nextV);
			if (nextV == -1)
			{
				nextV = myStack.top();
				myStack.pop();
				if (!myStack.empty())
					location = myStack.top();
				else
					return true;
				continue;
			}
			while (visited[nextV] == true)
			{
				nextV = graph.getNextNeighbor(location, nextV);
				if (nextV == -1)
				{
					nextV = myStack.top();
					myStack.pop();
					if (!myStack.empty())
						location = myStack.top();
					else
						return true;
					break;
				}
			}
			if (visited[nextV] == false)
			{
				myStack.push(nextV);
				location = nextV;
			}
		}
	}
	delete[] visited;
	return true;
};

template <typename VertexType, typename EdgeType>
int GraphLink<VertexType, EdgeType>::getVertexPosition(VertexType vertex)
{
	for (int i = 0; i < numVertices; i++)
	{
		if (VertexTable[i].data == vertex)
			return i;
	}
	return -1;
};

template <typename VertexType, typename EdgeType>
bool GraphLink<VertexType, EdgeType>::removeEdge(int vertex1, int vertex2)
{
	if (vertex1 != -1 && vertex2 != -1)		//legal parameter
	{
		Edge<VertexType, EdgeType> *current = VertexTable[vertex1].adj, *previous = NULL;
		while (current != NULL&&current->posOfDestination != vertex2)	//find the edge to be deleted in vertex1
		{
			previous = current;
			current = current->link;
		}
		if (current != NULL)		//if found
		{
			if (current = VertexTable[vertex1].adj)			//if it is the first adjacent vertex
				VertexTable[vertex1].adj = current->link;
			else
				previous->link = current->link;
			delete current;
		}
		else					//target not exist
			return false;

		current = VertexTable[vertex2].adj;
		previous = NULL;
		while (current->posOfDestination != vertex1&&current != NULL)	//find the edge to be deleted in vertex2
		{
			previous = current;
			current = current->link;
		}
		if (current = VertexTable[vertex2].adj)
			VertexTable[vertex2].adj = current->link;
		else
			previous->link = current->link;
		delete current;
		return true;
	}
	return false;
};

template <typename VertexType, typename EdgeType>
bool GraphLink<VertexType, EdgeType>::insertEdge(int vertex1, int vertex2, EdgeType weight)
{
	if (vertex1 >= 0 && vertex2 >= 0 && vertex1 < numVertices&&vertex2 < numVertices)	//legal parameter
	{
		Edge<VertexType, EdgeType> *q = NULL, *p = VertexTable[vertex1].adj;
		while (p != NULL&&p->posOfDestination != vertex2)	//search adjacent vertex "vertex2"
			p = p->link;
		if (p != NULL)
			return false;		//an edge existed between vertex1 and vertex2
		p = new Edge<VertexType, EdgeType>;
		q = new Edge<VertexType, EdgeType>;

		p->posOfDestination = vertex2;
		p->link = VertexTable[vertex1].adj;
		p->Weight = weight;
		VertexTable[vertex1].adj = p;

		q->posOfDestination = vertex1;
		q->link = VertexTable[vertex2].adj;
		q->Weight = weight;
		VertexTable[vertex2].adj = q;

		numEdges++;
		return true;
	}
	return false;
};

template <typename VertexType, typename EdgeType>
bool GraphLink<VertexType, EdgeType>::removeVertex(int vertex)
{
	if (numVertices == 0 || vertex == -1 || vertex >= numVertices)	//not enought vertices,or the vertex is out of range
		return false;

	/*******************************************************/
	/*present:the first adjacent vertex of the VertexTable */
	/*previous:the adjacent vertex before the "target"     */
	/*target:vertex which store the target vertex          */
	/*******************************************************/
	Edge<VertexType, EdgeType> *present = NULL, *target = NULL, *previous = NULL;
	int posOfAdjacentVertex;

	while (VertexTable[vertex].adj != NULL)
	{
		present = VertexTable[vertex].adj;
		posOfAdjacentVertex = present->posOfDestination;
		target = VertexTable[posOfAdjacentVertex].adj;
		previous = NULL;
		while (target != NULL&&target->posOfDestination != vertex)	//delete the info on the others vertex
		{
			previous = target;
			target = target->link;
		}
		if (target != NULL)
		{
			if (previous == NULL)			//case:the first adjacent vertex of the target
				VertexTable[posOfAdjacentVertex].adj = target->link;
			else
				previous->link = target->link;
			delete target;
		}
		VertexTable[vertex].adj = present->link;
		delete present;
		numEdges--;
	}
	numVertices--;
	VertexTable[vertex].data = VertexTable[numVertices].data;
	VertexTable[vertex].adj = VertexTable[numVertices].adj;
	present = VertexTable[vertex].adj;
	while (present != NULL)
	{
		target = VertexTable[present->posOfDestination].adj;
		while (target != NULL)
		{
			if (target->posOfDestinatio == numVertices)
			{
				target->posOfDestination = vertex;
				break;
			}
			else
				target = target->link;
		}
	}
	return true;
};

template <typename VertexType, typename EdgeType>
bool GraphLink<VertexType, EdgeType>::insertVertex(VertexType& vertex)
{
	if (numVertices == maxVertices)
		return false;
	VertexTable[numVertices].data = vertex;
	numVertices++;
	return true;
};

template <typename VertexType, typename EdgeType>
EdgeType GraphLink<VertexType, EdgeType>::getWeight(int vertex1, int vertex2)
{
	if (vertex1 != -1 && vertex2 != -1)
	{
		Edge<VertexType, EdgeType>* temp = VertexTable[vertex1].adj;
		while (temp != NULL&&temp->posOfDestination != vertex2)
			temp = temp->link;
		if (temp != NULL)
			return temp->Weight;
	}
	return INF;
};


template <typename VertexType, typename EdgeType>
VertexType GraphLink<VertexType, EdgeType>::getValue(int position)
{
	if (position >= 0 && position < numVertices)
		return VertexTable[position].data;
//	else
//		return NULL;
};

template <typename VertexType, typename EdgeType>
int GraphLink<VertexType, EdgeType>::getNextNeighbor(int vertex, int nextVertex)
{
	if (vertex != -1)
	{
		Edge<VertexType, EdgeType>* temp = VertexTable[vertex].adj;
		while (temp != NULL&&temp->posOfDestination != nextVertex)
			temp = temp->link;
		if (temp != NULL&&temp->link != NULL)
			return temp->link->posOfDestination;
	}
	return -1;		//not existed!
};

template <typename VertexType, typename EdgeType>
int GraphLink<VertexType, EdgeType>::getFirstNeighbor(int vertex)
{
	if (vertex != -1)		//if existed!
	{
		Edge<VertexType, EdgeType>* temp = VertexTable[vertex].adj;
		if (temp != NULL)
			return temp->posOfDestination;
	}
	return -1;	//not existed
};

template <typename VertexType, typename EdgeType>
GraphLink<VertexType, EdgeType>::~GraphLink()
{
	for (int i = 0; i < numVertices; i++)
	{
		Edge<VertexType, EdgeType> *temp = VertexTable[i].adj;
		while (temp != NULL)
		{
			VertexTable[i].adj = temp->link;
			delete temp;
			temp = VertexTable[i].adj;
		}
	}
	delete[] VertexTable;
};

template <typename VertexType, typename EdgeType>
GraphLink<VertexType, EdgeType>::GraphLink(int size)
{
	maxVertices = size;
	numVertices = 0;
	numEdges = 0;
	VertexTable = new Vertex<VertexType, EdgeType>[maxVertices];
	for (int i = 0; i < maxVertices; i++)
		VertexTable[i].adj = NULL;
};

template <typename VertexType, typename EdgeType>
bool Edge<VertexType, EdgeType>::operator != (Edge<VertexType, EdgeType>& j) const
{
	return (posOfDestination != j.posOfDestination) ? true : false;
};

template <typename VertexType, typename EdgeType>
Edge<VertexType, EdgeType>::Edge()
{
	link = NULL;
};

template <typename VertexType, typename EdgeType>
Edge<VertexType, EdgeType>::Edge(int dest, EdgeType weitht)
{
	posOfDestination = dest;
	Weight = weight;
	link = NULL;
};

//struct Info
//{
//	bool tag;	//true为经典，false为拐点
//	int x;
//	int y;
//};
//
//GraphLink<Info, int> MyMap;

#endif
