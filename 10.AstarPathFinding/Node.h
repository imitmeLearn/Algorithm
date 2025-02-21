#pragma once

#include <iostream>

struct Position
{
	Position(int x= 0,int y=0)
		:x(x),y(y)
	{}
	int x;
	int y;
};

class Node
{
public:
	Node(int x,int y,Node* parent = nullptr): position(x,y),parent(parent){}
	~Node() = default;

	//연산자 오버로딩. //두 노드 같은지 비교하려면, 포인터라면, 주소비교, 스택이면, 값을 비교
	Position operator-(const Node& other)
	{
		return Position(position.x - other.position.x,position.y - other.position.y);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x && position.y == other.position.y;
	}

public:
	Position position;	//노드의 위치

	float gCost =0.f;	//현재 노드에서 이동 노드까지의 비용
	float hCost =0.f;	//이동 노드에서 목표 노드까지의 비용 ( 추청치, 휴리스틱)
	float fCost =0.f;	//두 비용을 합친 비용 (최종 Cost)

	Node* parent = nullptr;	//링크 필드(부모 노드)

private:
};
