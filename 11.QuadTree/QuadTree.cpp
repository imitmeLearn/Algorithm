#include "QuadTree.h"

QuadTree::QuadTree(const Bounds& bounds)
{
	root = new Node(bounds);
}

QuadTree::~QuadTree()
{
	SafeDelete(root);
}

void QuadTree::Insert(Node * node)
{
	root->Insert(node);
}

std::vector<Node*> QuadTree::Query(Node * queryNode)
{
	std::vector<Node*> possibleNodes;	//겹침 가능성이 있는 영역 확인
	root->Query(queryNode->GetBounds(),possibleNodes);

	//겹침 가능서 있는 노드에 실제로 겹치는 노드들만 다시 검사.
	std::vector<Node*> intersects;
	for(Node* node : possibleNodes)
	{
		for(Node* point : node->Points())
		{
			if(point->GetBounds().Intersects(queryNode->GetBounds()))
			{
				intersects.emplace_back(point);
				continue;
			}
		}
	}

	return intersects;
}