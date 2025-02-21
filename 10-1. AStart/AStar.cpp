#include "AStar.h"
#include "Node.h"

AStar::AStar()
{}

AStar::~AStar()
{
	for(Node* node : openList)
	{
		SafeDelete(node);
	}

	openList.clear();

	for(Node* node : closedList)
	{
		SafeDelete(node);
	}

	closedList.clear();
}

std::vector<Node*> AStar::FindPath(Node* startNode,Node* goalNode,const std::vector<std::vector<int>>& grid)
{
	this->startNode = startNode;
	this->goalNode = goalNode;

	openList.emplace_back(startNode);

	std::vector<Direction> directions =
	{
		{0,1,1.0f},{0,-1,1.0f},{1,0,1.0f},{-1,0,1.0f},

		{1,1,1.414f},{1,-1,1.414f},{-1,1,1.414f},{-1,-1,1.414f}
	};

	while(!openList.empty())
	{
		Node* lowestNode = openList[0];
		for(Node* node : openList)
		{
			if(node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		Node* currentNode = lowestNode;

		if(IsDestination(currentNode))
		{
			return ConstructPath(currentNode);
		}

		for(int ix = 0; ix < (int)openList.size(); ++ix)
		{
			if(*openList[ix] == *currentNode)
			{
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		//bool isNodeInList = false;
		//for (Node* node : closedList)
		//{
		//    if (*node == *currentNode)
		//    {
		//        isNodeInList = true;
		//        break;
		//    }
		//}

		//if (isNodeInList)
		//{
		//    continue;
		//}

		closedList.emplace_back(currentNode);

		for(const Direction& direction : directions)
		{
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			if(!IsInRange(newX,newY,grid))
			{
				continue;
			}

			if(grid[newY][newX] == 1)
			{
				continue;
			}

			if(HasVisited(newX,newY,currentNode->gCost + direction.cost))
			{
				continue;
			}

			Node* neighborNode = new Node(newX,newY,currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			neighborNode->hCost = CalculateHeuristic(neighborNode,goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			Node* openListNode = nullptr;
			for(Node* node : openList)
			{
				if(*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			if(openListNode == nullptr
				|| neighborNode->gCost < openListNode->gCost
				|| neighborNode->fCost < openListNode->fCost)
			{
				openList.emplace_back(neighborNode);
			} else
			{
				SafeDelete(neighborNode);
			}
		}
	}

	// initialize_list (c++).
	//return {};
	return std::vector<Node*>();
}

void AStar::DisplayGridWithPath(
	std::vector<std::vector<int>>& grid,const std::vector<Node*>& path)
{
	for(const Node* node : path)
	{
		grid[node->position.y][node->position.x] = 2;
	}

	for(int y = 0; y < (int)grid.size(); ++y)
	{
		for(int x = 0; x < (int)grid[0].size(); ++x)
		{
			if(grid[y][x] == 1)
			{
				std::cout << "1 ";
			}

			else if(grid[y][x] == 2)
			{
				std::cout << "+ ";
			}

			else if(grid[y][x] == 0)
			{
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	std::vector<Node*> path;
	this->goalNode = goalNode;
	Node* currentNode = goalNode;
	while(currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	std::reverse(path.begin(),path.end());
	return path;
}

float AStar::CalculateHeuristic(Node* currentNode,Node* goalNode)
{
	Position diff = *currentNode - *goalNode;
	return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool AStar::IsInRange(int x,int y,const std::vector<std::vector<int>>& grid)
{
	if(x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
	{
		return false;
	}

	return true;
}

bool AStar::HasVisited(int x,int y,float gCost)
{
	for(int ix = 0; ix < (int)closedList.size(); ++ix)
	{
		Node* node = closedList[ix];
		if(node->position.x == x && node->position.y == y)
		{
			return true;
		}
	}

	for(int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];
		if(node->position.x == x && node->position.y == y)
		{
			if(gCost >= node->gCost)
			{
				return true;
			}

			openList.erase(openList.begin() + ix);
			SafeDelete(node);
		}
	}

	return false;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *goalNode;
}