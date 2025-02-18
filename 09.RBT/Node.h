#pragma once

#include <iostream>
#include <string>

//메모리 삭제 함수
template<typename T>
void SafeDelete(T*& t)
{
	if(t)
	{
		delete t;
		t = nullptr;
	}
}

//노드 색상 열거형 //트리안에서 넣는게 의미상 맞지만, 코드 작성 시 가독성 차원에서 밖으로 뺌.
enum class Color
{
	Red,
	Black,
};

class Node
{
public:
	~Node() = default;
	Node(int data =0,Color color = Color::Red);

	//Getter /Seetter
	inline	const int Data() const {
		return data;
	}
	inline	void SetData(int newData){
		data = newData;
	}
	inline	const Color GetColor() const{
		return color;
	}

	inline	void SetColor(Color newColor){
		color = newColor;
	}
	const char* ColorString() const;

	inline	Node* Parent() const {
		return parent;
	}

	inline	void SetParent(Node* newParent)  {
		parent = newParent;
	}

	inline	Node* Left() const {
		return left;
	}
	inline void SetLeft(Node* newleft)  {
		left = newleft;
	}

	inline	Node* Right() const {
		return right;
	}
	inline void SetRight(Node* newright)  {
		right = newright;
	}

private:
	int data = 0;	//데이터
	Color color = Color::Red;	//색상

	Node* parent = nullptr;	//부모노드
	Node* left = nullptr;	//왼쪽 자식 노드.
	Node* right = nullptr;	//자식 노드 _오른쪽
};
