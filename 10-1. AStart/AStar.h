#pragma once

#include <vector>

template<typename T>
void SafeDelete(T*& t)
{
	if(t)
	{
		delete t;
		t = nullptr;
	}
}

class Node;
class AStar
{
	struct Direction
	{
		int x = 0;
		int y = 0;

		float cost = 0.0f;
	};

public:
	AStar();
	~AStar();

	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		const std::vector<std::vector<int>>& grid
	);

	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid,
		const std::vector<Node*>& path
	);

private:

	std::vector<Node*> ConstructPath(Node* goalNode);

	float CalculateHeuristic(Node* currentNode,Node* goalNode);

	bool IsInRange(int x,int y,const std::vector<std::vector<int>>& grid);

	bool HasVisited(int x,int y,float gCost);

	bool IsDestination(const Node* node);

private:

	std::vector<Node*> openList;

	std::vector<Node*> closedList;

	Node* startNode = nullptr;

	Node* goalNode = nullptr;
};