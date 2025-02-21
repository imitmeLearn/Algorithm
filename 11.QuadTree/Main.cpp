#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "QuadTree.h"
#include "Bounds.h"

std::ostream& operator<<(std::ostream& os,const Bounds& bound)
{
	return os <<"(" << bound.X()<<", "<< bound.Y() <<")" ;
}
int main()
{
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	std::cout<<"\n"<<"//"<<"\n";

	QuadTree tree (Bounds(0,0,200,200));	//duddur tjsdjs

	tree.Insert(new Node(Bounds(50,50)));
	tree.Insert(new Node(Bounds(60,80)));
	tree.Insert(new Node(Bounds(90,120)));
	tree.Insert(new Node(Bounds(150,150)));
	tree.Insert(new Node(Bounds(10,10)));

	std::cout << "노드 삽입 완료.\n";

	//Node testNode(Bounds(45,45,20,20));	//1개
	Node testNode(Bounds(45,45,20,40));		//2개
	std::vector<Node*> intersects = tree.Query(&testNode);
	if(intersects.size() == 0)
	{
		std::cout << "겹치는 노드를 찾지 못했습니다.\n";
	} else
	{
		std::cout << "겹치는 노드를 " << intersects.size() << "개 찾았습니다.\n";
		for(int ix = 0; ix < intersects.size(); ix++)
		{
			std::cout<<	intersects[ix]->GetBounds();
		}
	}

	std::cin.get();
}