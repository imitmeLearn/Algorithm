#pragma once

#include <Windows.h>
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

	//노드 출력 함수
	void Print(int depth = 0,int blackCount = 0);

	//노드 삭제 함수.
	void Remove(int data);

private:
	//노드 생성함수
	Node* CreateNode (int data,Color color);

	//노드 검색 재귀 함수.
	bool FindRecursive(Node* node,Node** outNode,int data);

	//노드 추가 함수 (새 노드 전달)
	void Insert(Node* newNode);

	//노드 삭제 함수.
	void RemoveImpl(Node* node);

	//트리에 노드를 추가하는 재귀 함수.
	void InsertRecursive(Node* node,Node* newNode);

	//노드 삽입 후 재정렬을 처리히는 함수.
	void RestructureAfterInsert(Node* newNode);

	void RestructureAfterRemove(Node* node);

	//회전함수_좌
	void RotateToLeft(Node* node);
	void RotateToRight(Node* node);

	//트리에서 최소 값을 가진 노드를 검색하는 함수.
	Node* FindMinRecursive(Node* node);
	//트리에서 최대 값을 가진 노드를 검색하는 함수.
	Node* FindMaxRecursive(Node* node);

	//삭제함수
	void DestroyRecursive(Node* node);

	//출력 재귀 함수
	void PrintRecursive(Node* node,int depth,int blackCount);

private:
	Node* root = nullptr;
	static Node* nil;
};

//콘솔 텍스트 색상 열거형,
enum class TextColor
{
	Red = FOREGROUND_RED
	,Green = FOREGROUND_GREEN
	,Blue=FOREGROUND_BLUE
	,White = Red|Green|Blue|FOREGROUND_INTENSITY
};

void SetTextColor(TextColor color);