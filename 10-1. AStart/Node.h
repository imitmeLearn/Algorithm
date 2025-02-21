#pragma once

#include <iostream>

// ��ġ�� ��Ÿ���� ����ü.
struct Position
{
	Position(int x = 0,int y = 0)
		: x(x),y(y)
	{}

	int x;
	int y;
};

// ��� Ŭ����.
class Node
{
public:
	Node(int x,int y,Node* parent = nullptr)
		: position(x,y),parent(parent)
	{}

	~Node() = default;

	// ������ �����ε�.
	Position operator-(const Node& other)
	{
		return Position(position.x - other.position.x,position.y - other.position.y);
	}

	bool operator==(const Node& other) const
	{
		return position.x == other.position.x && position.y == other.position.y;
	}

public:
	// ����� ��ġ.
	Position position;

	// ���.
	// ���� ��忡�� �̵� �������� ���.
	float gCost = 0.0f;
	// �̵� ��忡�� ��ǥ �������� ���(�޸���ƽ, ����)
	float hCost = 0.0f;
	// �� ����� ��ģ ���.
	float fCost = 0.0f;

	// ��ũ �ʵ�(�θ� ���).
	Node* parent = nullptr;
};