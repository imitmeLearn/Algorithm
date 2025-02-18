#pragma once

#include <iostream>
#include <string>
#include "Node.h"

class RedBlackTree
{
public:
	~RedBlackTree();
	RedBlackTree();

	//노드 검색 함수
	bool Find(int data,Node** outNode);

	//노드 추가 함수
	bool Insert(int data);

private:
	//노드 생성함수
	Node* CreateNode (int data,Color color);

	//노드 검색 재귀 함수.
	bool FindRecursive(Node* node,Node** outNode,int data);

	//노드 추가 함수 (새 노드 전달)
	void Insert(Node* newNode);

	//트리에 노드를 추가하는 재귀 함수.
	void InsertRecursive(Node* node,Node* newNode);

	//노드 삽입 후 재정렬을 처리히는 함수.
	void RestructureAfterInsert(Node* newNode);

	//회전함수_좌
	void RotateToLeft(Node* node);
	void RotateToRight(Node* node);

private:
	Node* root = nullptr;
	static Node* nil;
};
