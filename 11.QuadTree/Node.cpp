﻿#include "Node.h"
#include "QuadTree.h"
Node::~Node()
{
	//// 현재 노드에 저장된 모든 노드 제거.
	//for(Node* node : points)
	//{
	//	SafeDelete(node);
	//}

	//points.clear();

	//// 자식 노드 정리.
	//ClearChildren();

	Clear();
}
Node::Node(const Bounds & bounds,int depth)
	:bounds(bounds),depth(depth)
{}

void Node::Insert(Node * node)
{
	//겹치는 영역 확인
	NodeIndex result = TestRegion(node->GetBounds());

	//겹치면, 현재 노드에 추가
	if(result == NodeIndex::Straddling)
	{
		points.emplace_back(node);
	}

	//겹치지 않은 경우.
	else if(result != NodeIndex::OutOfArea)
	{
		if(Subdivide())	//더 나눌 수 있는지,..등등 보고,
		{
			switch(result)
			{
			case NodeIndex::TopLeft: 			topLeft->Insert(node);
				break;
			case NodeIndex::TopRight: 			topRight->Insert(node);
				break;
			case NodeIndex::BottomLeft: 		bottomLeft->Insert(node);
				break;
			case NodeIndex::BottomRight: 		bottomRight->Insert(node);
				break;

				break;
			default:
			break;
			}
		}
		//더이상 나눌 수 없는 경우.
		else
		{
			points.emplace_back(node);
		}
	}
}

void Node::Query(const Bounds & queryBounds,std::vector<Node*>& possibleNodes)
{
	//현재 노드 추가
	possibleNodes.emplace_back(this);
	if(IsDivided())		//영역이 분할됐으면, 자식노드도 추가 검사
	{
		std::vector<NodeIndex> quads = GetQuads(queryBounds);	// 전달받은 영역와 겹치는 4분면, 목록 확인

		for(NodeIndex& index : quads)		//겹치는 4분면을 기준으로 검사 진행(재귀)
		{
			switch(index)
			{
			case NodeIndex::TopLeft: 			topLeft-> Query(queryBounds,possibleNodes);
				break;
			case NodeIndex::TopRight:			topRight-> Query(queryBounds,possibleNodes);
				break;
			case NodeIndex::BottomLeft:			bottomLeft-> Query(queryBounds,possibleNodes);
				break;
			case NodeIndex::BottomRight:		bottomRight-> Query(queryBounds,possibleNodes);
				break;

			default:
			break;
			}
		}
	}
}

void Node::Clear()
{
	//현재 노드 제거
	for(Node* node:points)
	{
		SafeDelete(node);
	}

	//리스트 정리
	points.clear();

	if(IsDivided())	//분할된 경우 자식 정리 //재귀!
	{
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		ClearChildren()	;
	}
}

bool Node::Subdivide()
{
	//Todo 최대 깊이에 도달했으면, 더 이상, 안나늠.
	if(depth == QuadTree::maxDepth)
	{
		return false;
	}

	//아직 분할 안됐으면, 분할 진행.
	if(!IsDivided())
	{
		int x = bounds.X();	//영역 나누기 위한 값 계산
		int y = bounds.Y();	//영역 나누기 위한 값 계산
		int halfWidth = bounds.Width() / 2;	//영역 나누기 위한 값 계산
		int halfHeight = bounds.Height() / 2;	//영역 나누기 위한 값 계산

		// 각 4분면의 자식 객체 생성.
		topLeft = new Node(Bounds(x,y,halfWidth,halfHeight),depth + 1);
		topRight = new Node(Bounds(x + halfWidth,y,halfWidth,halfHeight),depth + 1);
		bottomLeft = new Node(Bounds(x,y + halfHeight,halfWidth,halfHeight),depth + 1);
		bottomRight = new Node(Bounds(x + halfWidth,y + halfHeight,halfWidth,halfHeight),depth + 1);
	}

	return false;
}

bool Node::IsDivided()
{
	return topLeft != nullptr;
}

void Node::ClearChildren()
{
	if(IsDivided())	//분할 진행되었다면
	{
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}

NodeIndex Node::TestRegion(const Bounds & bounds)
{
	std::vector<NodeIndex> quads = GetQuads(bounds);		//전달된 bounds 와 겹치는 4분면, 목록 확인.

	//겹치는 곳이 없으면, 영역 밖으로 반환!
	if(quads.size() == 0)
	{
		return NodeIndex::OutOfArea;
	}

	//하나만 겹친 경우, 해당 4분면, 반환
	if(quads.size() == 1)
	{
		return quads[0];
	}

	//여러영역이 겹친 경우
	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds & bounds)
{
	std::vector<NodeIndex> quads;

	//영역 계산에 필요한 변수
	int x = this -> bounds.X();
	int y = this -> bounds.Y();
	int halfWidth = this->bounds.Width() /2;
	int halfHeight = this->bounds.Height() /2;
	int centerX = x+halfWidth;
	int centerY = x+halfHeight;

	bool left = bounds.X() < centerX && bounds.MaxX() >= x;						///왼쪽 영역이랑 겹치는지 확인.
	bool right = bounds.MaxX() >=  centerX && bounds.X() < this->bounds.MaxX();	///오른쪽 영역이랑 겹치는지 확인.
	bool top = bounds.Y() < centerY && bounds.MaxY() >= y;						// 위쪽 영역이랑 겹치는지 확인.
	bool bottom = bounds.MaxY() >= centerY && bounds.Y() < this->bounds.MaxY();	// 아래쪽 영역이랑 겹치는지 확인.

	if(top && left)
	{
		quads.emplace_back(NodeIndex::TopLeft);
	}
	if(top && right)
	{
		quads.emplace_back(NodeIndex::TopRight);
	}
	if(bottom && left)
	{
		quads.emplace_back(NodeIndex::BottomLeft);
	}
	if(bottom && right)
	{
		quads.emplace_back(NodeIndex::BottomRight);
	}

	return quads;
}