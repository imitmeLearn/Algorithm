#pragma once
#include <vector>
template <typename T>

//포인터 삭제 함수
void SafeDelete(T*& t)
{
	if(t)
	{
		delete t;
		t=nullptr;
	}
}

class Node;	//전방선언
class Astar //A* 길찾기 기능 처리 클래스.
{
	struct Direction
	{
		int x = 0;
		int y = 0;

		float cost = 0.f;
	};

public:
	//Astar();
	~Astar();

	//경로 검색 함수.
	std::vector<Node*> FindPath(
		Node* startNode
		,Node* goalNode
		,const std::vector<std::vector<int>>& grid
	);

	//그리드 출력 함수. : 맵 보여주는 함수
	void DisplayGridWithPath(
		 std::vector<std::vector<int>>& grid
		,const std::vector<Node*>& path
	);

private:	//처리관련 함수는 private 로!
	//탐색을 완료한 후에 최적 경로를 반환하는 함수. : //목표노드로 부터 부모 노드를 역추적해 구함
	std::vector<Node*> ConstructPath(Node* goalNode);

	//경로 계산 비용계산 함수. 휴리스트 계산 함수.
	float CalculateHeuristic(Node* currentNode,Node* goalNode);

	//탐색 하려는 곳이 그리드(맵) 안에 있는지, 실제 게임엔진도, 네비게이션 처리 시, 이동 가능한 맵인지, 경로계산 불가하게 하는 부분 파악하는 함수.
	bool IsInRange(int x,int y,const std::vector<std::vector<int>>& grid);	//2차원 배열인데, 참조니까 또 복사하지 않지만, 그래도 1차원으로 바쑬 필요 있음

	//이미 방문한 위치인지 확인하는 함수
	bool HasVisited(int x,int y,float gCost);

	//탐색하려는 위치가 목표 위치인지 확인하는 함수
	bool IsDestination(const Node* node);

private:
	std::vector<Node*> openList;	//열린 리스트
	std::vector<Node*> closedList;	//닫힌 리스트

	Node* startNode = nullptr;		//시작 노드
	Node* goalNode = nullptr;		//목표 노드
};