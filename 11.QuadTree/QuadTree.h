#pragma once

#include <vector>
#include "Node.h"

class QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	//트리에 노드를 추가하는 함수
	void Insert(Node* node);

	//전달할 노드와 겹치는 노드 반환하는 함수.
	std::vector<Node*> Query(Node* queryNode);
public:
	static const int maxDepth = 4;	//원칙적으로 static const 안되는데 h에서는 가능.

private:
	Node* root = nullptr;
};
