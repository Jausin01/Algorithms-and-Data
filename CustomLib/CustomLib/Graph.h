#pragma once
#include "Stack.h"
#include "Queue.h"
#include <iostream>

template<typename T>
class Graph
{
private:
	struct Node
	{
		// data stored on a graph Node
		const T* data = nullptr;
		// use flag for if its visited
		bool isVisited = false;
		// for obtaining path
		Node* fromNode = nullptr;
		// connected edges
		Vector<int> edges;

	};

public:
	Graph()
	{

	}
	~Graph()
	{
		Terminate();
	}

	int AddItem(const T* data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		mNodes.PushBack(newNode);
		return mNodes.Size() - 1;
	}

	void AddLink(std::size_t a, std::size_t b, bool bothWays = true)
	{
		if (a >= mNodes.Size() || b >= mNodes.Size())
		{
			return;
		}
		mNodes[a]->edges.PushBack(b);
		if (bothWays)
		{
			mNodes[b]->edges.PushBack(a);
		}
	}

	void GetAllConnectionsDFS(int startIndex, Vector<const T*>& v)
	{
		//LIFO
		Reset();

		Stack<Node*> stack;
		stack.Push(mNodes[startIndex]);
		while (!stack.Empty())
		{
			Node* node = stack.Top();
			stack.Pop();
			if (!node->isVisited)
			{
				node->isVisited = true;
				v.PushBack(node->data);
				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					int edgeIndex = node->edges[i];
					Node* edgeNode = mNodes[edgeIndex];
					if (!edgeNode->isVisited)
					{
						stack.Push(edgeNode);
					}
				}

			}
		}
	}

	void GetAllConnectionsBFS(int startIndex, Vector<const T*>& v)
	{
		//LIFO
		Reset();

		Queue<Node*> queue;
		queue.Enqueue(mNodes[startIndex]);
		while (!queue.Empty())
		{
			Node* node = queue.Front();
			queue.Dequeue();
			if (!node->isVisited)
			{
				node->isVisited = true;
				v.PushBack(node->data);
				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					int edgeIndex = node->edges[i];
					Node* edgeNode = mNodes[edgeIndex];
					if (!edgeNode->isVisited)
					{
						queue.Enqueue(edgeNode);
					}
				}

			}
		}
	}

	bool GetPathDFS(int startIndex, int endIndex, Vector<const T*>& path)
	{
		Reset();

		bool pathFound = false;
		Node* startNode = mNodes[startIndex];
		Node* endNode = mNodes[endIndex];
		Stack<Node*> stack;
		stack.Push(startNode);

		while (!stack.Empty())
		{
			Node* node = stack.Top();
			stack.Pop();
			if (!node->isVisited)
			{
				node->isVisited = true;
				if (node == endNode)
				{
					pathFound = true;
					break;
				}
				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					int edgeIndex = node->edges[i];
					Node* edgeNode = mNodes[edgeIndex];
					if (!edgeNode->isVisited)
					{
						edgeNode->fromNode = node;
						stack.Push(edgeNode);
					}
				}
			}
		}
		if (pathFound)
		{
			Node* pathNode = endNode;
			while (pathNode != nullptr)
			{
				path.PushBack(pathNode->data);
				pathNode = pathNode->fromNode;
			}
		}
		return pathFound;
	}

	bool GetPathBFS(int startIndex, int endIndex, Vector<const T*>& path)
	{
		Reset();
		bool pathFound = false;
		Node* startNode = mNodes[startIndex];
		Node* endNode = mNodes[endIndex];
		Queue<Node*> queue;
		queue.Enqueue(startNode);

		while (!queue.Empty())
		{
			Node* node = queue.Front();
			queue.Dequeue();
			if (!node->isVisited)
			{
				node->isVisited = true;
				if (node == endNode)
				{
					pathFound = true;
					break;
				}
				for (std::size_t i = 0; i < node->edges.Size(); ++i)
				{
					int edgeIndex = node->edges[i];
					Node* edgeNode = mNodes[edgeIndex];
					if (!edgeNode->isVisited)
					{
						edgeNode->fromNode = node;
						queue.Enqueue(edgeNode);
					}
				}
			}
		}
		if (pathFound)
		{
			Node* pathNode = endNode;
			while (pathNode != nullptr)
			{
				path.PushBack(pathNode->data);
				pathNode = pathNode->fromNode;
			}
		}
		return pathFound;

	}

	void PrintGraph()
	{
		std::cout << "Printing Graph:\n";
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			std::cout << (*mNodes[i]->data) << ": ";
			for (std::size_t e = 0; e < mNodes[i]->edges.Size(); ++e)
			{
				int edgeNodeIndex = mNodes[i]->edges[e];
				std::cout << (*mNodes[edgeNodeIndex]->data) << " ";
			}
			std::cout << "\n";

		}
	}

	void Terminate()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			delete mNodes[i];
			mNodes[i] = nullptr;
		}
		mNodes.Clear();
	}

private:
	void Reset()
	{
		for (std::size_t i = 0; i < mNodes.Size(); ++i)
		{
			mNodes[i]->isVisited = false;
			mNodes[i]->fromNode = nullptr;
		}
	}

	Vector<Node*> mNodes;
};