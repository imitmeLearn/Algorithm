#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <vector>
#include "Node.h"
#include "Astar.h"

// 그리드 생성.
	// 0: 이동 가능.
	// 1: 이동 불가(장애물).
	// 2: 시작 위치.
	// 3: 목표 위치.
std::vector<std::vector<int>> grid =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,0,0,3,1},
	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,2,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int main()
{
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//std::cout<<"\n"<<"//"<<"\n";

	Node* startNode = nullptr;
	Node* goaltNode = nullptr;

	bool initialized = false;
	for(int y = 0; y < (int)grid.size(); y++)
	{
		if(startNode && goaltNode)	//이미 찾았다면, 종료
		{
			initialized = true;
			break;
		}

		for(int x = 0; x < (int)grid[0].size(); x++)
		{
			if(startNode && goaltNode)	//이미 찾았다면, 종료
			{
				initialized = true;
				break;
			}
			//시작지점
			if(grid[y][x] ==2)
			{
				startNode = new Node(x,y);
				grid[y][x] = 0;
				continue;
			}

			if(grid[y][x] ==3)
			{
				goaltNode = new Node(x,y);
				grid[y][x] = 0;
				continue;
			}
		}
	}

	Astar aStar;	//Astar 객체
	std::vector<Node*> path = aStar.FindPath(startNode,goaltNode,grid);	//경로탐색

	if(!path.empty())
	{
		std::cout << "경로 찾음.  탐색 경로:"<<'\n';
		for(Node* node : path)
		{
			std::cout
				<<"(" << node->position.x
				<<","
				<< node->position.y <<") ->"
				;//	<<"\n";
		}

		std::cout<<" 도착 \n";
		//맵출력
		std::cout<<" 경로 맵 표시 결과 : \n";
		aStar.DisplayGridWithPath(grid,path);
	}

	else
	{
		std::cout<<" 경로 못 찾음. \n";
	}

	SafeDelete(goaltNode);	//목표 노드만 제거

	std::cin.get();
}