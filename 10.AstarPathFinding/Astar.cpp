#include "Astar.h"
#include "Node.h"

Astar::~Astar()
{
	//메모리 해제
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

std::vector<Node*> Astar::FindPath(Node * startNode,Node * goalNode,const std::vector<std::vector<int>>& grid)
{
	//변수이름, 같게 하면 안돼서 다른거 작성하곤 한다.
	this->startNode = startNode;
	this->goalNode = goalNode;

	openList.emplace_back(startNode);	//시작 위치를 열린 리스트에 추가

	std::vector<Direction> directions =	//상하좌우 및 대각성 이동 방향 및 비용 계산.
	{
		//비용이 같을때,
		{0,1,1.f}	//하
		,{0,-1,1.f}	//상
		,{1,0,1.f}	//우
		,{-1,0,1.f}	//좌

		//대각선 이동.
		,{1,1,1.414f}
		,{1,-1,1.414f}
		,{-1,1,1.414f}
		,{-1,-1,1.414f}
	};

	//이웃노드 탐색 (열린 리스트가 비어 있지 않으면, 반복)
	while(!openList.empty())
	{
		Node* lowestNode = openList[0];			//현재 열린 리스트에서 비용(fCost)이 가장 낮은 노드 검색. //최적화 가능(우선순위 큐, 힙).
		for(Node* node:openList)
		{
			if(node->fCost < lowestNode ->fCost)
			{
				lowestNode = node;
			}
		}

		Node* currentNode = lowestNode;			//비용이 가장 작은 노드를 현재 노드로 선택

		if(IsDestination(currentNode))			//현재 노드가 목표 노드인지 확인
		{
			return ConstructPath(currentNode);	//목쵸 지점으로 부터 역추척해서 경로를 생성 후 반환.
		}

		for(int ix = 0; ix < (int)openList.size(); ix++)
		{
			if(*openList[ix] == *currentNode)			//주소값을 비교하는 이유는,노드에 하나만 있다고 확신할 수 없어서, 위치기반으로 같은지 확인임.
			{
				openList.erase(openList.begin() + ix);	//방문처리를 위해 현재 노드를 열린 리스트에서 제거.
				break;
			}
		}

		bool isNodeInList = false;		//이미 추가되 노드인지 확인용 :
		for(Node* node : closedList)	// - 이미 닫힌 노드에 있는 노드일 수도 있으니, 확인
		{
			if(*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		if(isNodeInList)	//이미 닫힌 노드에 있으면 있으면,
		{
			continue;		// 닫힌 노드에 추가 무시, 제외,
		}

		closedList.emplace_back(currentNode);	//닫힌 리스트에 없으니, 리스트에 추가//방문처리를 위해 닫힌 리스트에 추가.

		//이웃노드 방문. (하상우좌,...차례로 방문)
		for(const Direction& direction : directions)	//실수 방지로 위해, const 로! 주소값만 복사
		{
			//다음에 위치할 위치 확인
			int newX = currentNode -> position.x + direction.x;
			int newY = currentNode -> position.y + direction.y;

			//그리드 벗어나면 무시
			if(!IsInRange(newX,newY,grid))
			{
				continue;
			}

			//이동할 노드가 이동 가능한지 확인. 0 ,1  맵 //행이 Y,
			if(grid[newY][newX] == 1)
			{
				continue;
			}

			//이미 방문했는지 확인
			if(HasVisited(newX,newY,currentNode -> gCost + direction.cost))
			{
				continue;
			}

			//방문할 노드 생성 (비용 설정)
			Node* neighborNode = new Node(newX,newY,currentNode);
			neighborNode->gCost =currentNode->gCost + direction.cost;
			neighborNode->hCost = CalculateHeuristic(neighborNode,goalNode);
			neighborNode->fCost = neighborNode->gCost+neighborNode->hCost;

			//열린 리스트에 추가
			Node* openListNode = nullptr;	//이미 있는 노드인지 확인 //bool 안한 이유는 -//- 포인터라 for 돌려도 많이 먹지 않아 + 비용을 가져와야 함.
			for(Node* node : openList)
			{
				if(*node == *neighborNode)	// 새로생성한 이웃이라, 위치 같은 다른 노드 있을 수 있기에 위치로 비교한다.
				{
					openListNode = node;
					break;
				}
			}

			//이웃 노드가 리스트에 없으면, 바로 추가!
			// 리스트에 있으면, 비용을 비교해서, 더 저렴한거 추가 : 위치 같은데, 비용이 적으면, 위치기준으로 싼거니까, 넣어줌.
			if(openListNode == nullptr
				|| neighborNode->gCost < openListNode -> gCost
				|| neighborNode->fCost < openListNode -> fCost				//비용 합산만해도 되고, 분리해서 비용으로 비교해도 된다.
				)
			{
				openList.emplace_back(neighborNode);
			}
			//리스트 추가 대상이 아니라면, 메모리 해제.
			else
			{
				SafeDelete(neighborNode);
			}
		}
	}

	//탐색실패 시 빈 배열 보냄.
	//return {}; ////initialize list(c++)	//아래와 같은거
	return std::vector<Node*>();
}

void Astar::DisplayGridWithPath(std::vector<std::vector<int>>& grid,const std::vector<Node*>& path)
{
	//경로에 있는 위치는 2로 표기
	for(const Node* node : path)
	{
		grid[node->position.y][node->position.x] = 2;
	}

	//맵 출력
	for(int y = 0; y < (int)grid.size(); y++)
	{
		for(int x = 0; x < (int)grid[0].size(); x++)
		{
			//장애물
			if(grid[y][x] == 1)
			{
				std::cout << "1 ";
			}

			//경로
			if(grid[y][x] == 2)
			{
				std::cout << "+ ";
			}

			//맵
			if(grid[y][x] == 0)
			{
				std::cout << "0 ";
			}
		}
		std::cout << "\n";
	}
}

std::vector<Node*> Astar::ConstructPath(Node * goalNode)
{
	std::vector<Node*> path;	//목표노드로부터 부모노드를 따라 역추척하면서 경로르 설정.

	Node* currentNode = goalNode;
	while(currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	std::reverse(path.begin(),path.end());		//시작 지점부터 목표 지점으로 향하도록 배열 뒤집기.

	return path;
}

float Astar::CalculateHeuristic(Node* currentNode,Node* goalNode)
{
	Position diff = *currentNode - *goalNode;		//현재 노드에서 목표노드 까지의 차이 계산

	return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool Astar::IsInRange(int x,int y,const std::vector<std::vector<int>>& grid)
{
	if(x<0 || x>= grid[0].size() || y <0 || y>=grid.size())
	{
		return false;
	}
	return true;
}
bool Astar::IsDestination(const Node * node)
{
	return *node == *goalNode;
}
bool Astar::HasVisited(int x,int y,float gCost)
{
	//열린, 닫힌 리스트 이미 해당 위치가 있으면, 방문한 것으로 판단.
	for(int ix = 0; ix < (int)openList.size(); ix++)
	{
		Node* node = openList[ix];
		if(node->position.x == x && node->position.y == y)
		{
			//위치 같고, 비용 크면 방문 이유 없기에! 방문했다고 해주고.
			if(gCost >= node->gCost)
			{
				return true;
			}

			//위치 같고, 비용 작으면,//새 노드의 비용이 작은 경우에는, 기존 노드 제거.
			openList.erase(openList.begin() + ix);	//포인트 값만 지우고, 노드는 남아있는 상태
			SafeDelete(node);
		}
	}

	for(int ix = 0; ix < (int)closedList.size(); ix++)
	{
		Node* node = closedList[ix];
		if(node->position.x == x && node->position.y == y)
		{
			//위치 같고, 비용 크면 방문 이유 없기에! 방문했다고 해주고.
			if(gCost >= node->gCost)
			{
				return true;
			}

			//위치 같고, 비용 작으면,//새 노드의 비용이 작은 경우에는, 기존 노드 제거.
			closedList.erase(closedList.begin() + ix);	//포인트 값만 지우고, 노드는 남아있는 상태
			SafeDelete(node);
		}
	}

	//리스트에 없으면, 방문하지 않은 것으로!
	return false;
}