#include "RedBlackTree.h"

Node* RedBlackTree::nil = nullptr;
Node * RedBlackTree::CreateNode(int data,Color color)
{
	Node* newNode = new Node(data,color);
	newNode -> SetLeft(nil);
	newNode -> SetRight(nil);
	return newNode;
}

RedBlackTree::~RedBlackTree()
{
	DestroyRecursive(root);
	SafeDelete(nil);
}

RedBlackTree::RedBlackTree()
{
	if(nil == nullptr)
	{
		nil = new Node(0,Color::Black);
	}
	root = nil;
}

bool RedBlackTree::Find(int data,Node** outNode)
{
	//트리가 비었다면, 검색 실패
	if(root == nil)
	{
		return false;
	}

	//재귀적으로 검색 진행.
	return FindRecursive(root,outNode,data);
}

bool RedBlackTree::FindRecursive(Node* node,Node** outNode,int data)
{
	//재귀 탈출 조건(검색 실패)
	if(node == nil)
	{
		return false;
	}

	//검색에 성공했으면, true 및 outNode 반환
	if(node->Data() == data)
	{
		*outNode = node;
		return true;
	}

	//검색할 데이터가 현재 노드 값 보다 작으면 왼쪽으로 검색 진행.
	if(node->Data() > data)
	{
		return FindRecursive(node->Left(),outNode,data);
	}

	else
	{
		return FindRecursive(node->Right(),outNode,data);
	}
	return false;
}
bool RedBlackTree::Insert(int data)
{
	Node* node = nullptr;
	if(Find(data,&node))
	{
		std::cout <<"오류 - 노드 추가 실패 : 이미 같은 값이 있다. 입력값 : "
			<<data<<" \n";
		return false;
	}

	Insert(CreateNode(data,Color::Red));	//노드 생성 후 결과 반환.
	return true;	//중복 안되면, 성공!
}

void RedBlackTree::Print(int depth,int blackCount)
{
	PrintRecursive(root,depth,blackCount);
}

void RedBlackTree::Insert(Node * newNode)
{
	//트리가 비어있는 경우, 루트로 설정
	if(root == nil)
	{
		root = newNode;
		root->SetColor(Color::Black);
		return;
	}

	//비어있지 않은 경우, 재귀적으로 위치 검색 후 삽입. 이진트리와 같아.
	InsertRecursive(root,newNode);

	//삽입 된 노드 값 정리.
	newNode->SetColor(Color::Red);
	newNode->SetLeft(nil);
	newNode->SetRight(nil);

	//	케이스에 따라서, 재정렬-삽입 후 재정랼
	RestructureAfterInsert(newNode);
}

void RedBlackTree::InsertRecursive(Node * node,Node * newNode)
{
	//새 노드의 데이터가 현재 노드보다 작으면, 외쪽하위 느==느===트리로 삽입 진행
	if(node->Data() > newNode ->Data())
	{
		if(node->Left() == nil)
		{
			node->SetLeft(newNode);
			node->SetParent(node);
			return;
		}

		InsertRecursive(node->Left(),newNode);
	}

	else
	{
		if(node->Right() == nil)
		{
			node->SetRight(newNode);
			node->SetParent(node);
			return;
		}

		InsertRecursive(node->Right(),newNode);
	}
}

void RedBlackTree::RotateToLeft(Node * node)
{
	Node* right = node->Right();

	//오늘쪽 자식 노드의 왼쪽 자식 노드를 부모의 오른쪽 자식 으로 등록
	node ->SetRight(right->Left());

	if(right -> Left() != nil)
	{
		right->Left()->SetParent(node);
	}

	right->SetParent(node->Parent());	//오늘쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정

	if(right-> Parent() == nullptr) //부모가 root인 경우
	{
		root=right;
	}

	else
	{
		//조부모 기준 원원래의 자식 위치로 복구
		if(node == node -> Parent()->Left())
		{
			node ->Parent() ->SetLeft(right);
		}

		else
		{
			node ->Parent() ->SetRight(right);
		}
	}
	right->SetLeft(node);
	node->SetParent(right);
}

void RedBlackTree::RotateToRight(Node * node)
{
	//RotateToLeft 의 반대방얗으로 변경

	Node* left = node->Left();

	node ->SetLeft(left->Right());

	if(left -> Right() != nil)
	{
		left->Right()->SetParent(node);
	}

	left->SetParent(node->Parent());	//왼쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정

	if(left-> Parent() == nullptr) //부모가 root인 경우
	{
		root=left;
	}

	else
	{
		//조부모 기준 원원래의 자식 위치로 복구S
		if(node == node -> Parent()->Left())
		{
			node ->Parent() ->SetLeft(left);
		}

		else
		{
			node ->Parent() ->SetRight(left);
		}
	}

	left->SetRight(node);
	node->SetParent(left);
}

void RedBlackTree::DestroyRecursive(Node * node)
{
	if(node == nil)	//재귀 탈출 조건.
	{
		return;
	}

	//자식
	Node* left = node->Left();
	Node* right = node->Right();

	//자식 없는 경우
	/*if(left == nil && right == nil)
	{
		SafeDelete(node);
		return;
	}*/ //위에서, 검색하니 없어도 될듯.

	//자식 있는 경우
	DestroyRecursive(left);
	DestroyRecursive(right);

	//노드삭제
	SafeDelete(node);
}

void RedBlackTree::PrintRecursive(Node * node,int depth,int blackCount)
{
	//탈출조건
	if(node == nil)
	{
		return;
	}
	//노드 색상이 검정이면 blackCount 증가.
	if(node -> GetColor() == Color::Black)
	{
		++blackCount;
	}
	//부모 표기 문자열 설정.
	int parentData = 0;
	const char* position = "Root";

	//부모 노드가 있는지 확인.
	if(node -> Parent())
	{
		//부모 노드의 데이터 저장.
		parentData = node->Parent()->Data();

		//부모 노드로부터 현재 노드의 위치 설정
		if(node==node->Parent()->Left())
		{
			position = "Left";
		}

		else
		{
			position = "Right";
		}
	}

	//검은색 수 출력을 위한 문자열.
	char blackCountString[50] = {};

	//자손이 없으면, 현재까지의 검은색 노드 수 설정.
	if(node->Left() == nil && node -> Right() == nil)
	{
		sprintf_s(blackCountString,"------%d",blackCount);
	}

	// Depth 출력.
	for(int ix = 0; ix < depth; ix++)
	{
		std::cout << " ";
	}

	// 노드 색상에 따른 콘솔 설정.
	if(node->GetColor() == Color::Red)
	{
		SetTextColor(TextColor::Red);
	}

	else
	{
		SetTextColor(TextColor::White);
	}

	// 현재 노드 값 출력.
	std::cout
		<< node->Data() << " "
		<< node->ColorString() << " ["
		<< position << ", "
		<< parentData << "] "
		<< blackCountString << "\n";

	// 노드를 출력한 뒤에는 콘솔 원래대로.
	SetTextColor(TextColor::White);

	// 하위 노드 출력.
	PrintRecursive(node->Left(),depth + 1,blackCount);
	PrintRecursive(node->Right(),depth + 1,blackCount);
}
void SetTextColor(TextColor color)
{
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console,(int)color);
}
void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
	//부모가 빨간색인 경우, (Red-Red Conflict)
	while(newNode != root && newNode ->Parent() ->GetColor() == Color::Red)
	{
		//삼촌구하기 - 왼쪽인 경우
		if(newNode->Parent() ==newNode->Parent()->Parent()->Left())
		{
			//삼촌
			Node* uncle = newNode-> Parent() ->Parent()->Right();

			//삼촌노드가 빨간색 일 때 - Case1.
			//해결 : 부모와 삼촌을 Black,할아버지를 Red로 변경 후,할아버지 기준으로 다시 검사
			if(uncle -> GetColor() == Color::Red())
			{
				newNode -> Parent() ->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				newNode=newNode->Parent()->Parent();
				continue;
			}

			//위에서, continue; 했으니, else안함.
			//삼촌이 검정색 일 때 : case2,3
			//해결 2: 지그재그 형태: 부모위치와나의위치가 반대 : 일직으로ㅡ 변경 후 case3 처리.

			if(newNode == newNode->Parent()->Right())
			{
				//부모를 중심으로 회전 처리(일직선으로 만들기 위해)
				newNode = newNode->Parent();
				RotateToLeft(newNode);
			}

			//해결 3:부모와 일치할때 -일직선 일 떄,
			newNode -> Parent()->SetColor(Color::Black);
			newNode ->Parent()->Parent()->SetColor(Color::Red);

			RotateToRight(newNode->Parent()->Parent());
		}
		//삼촌구하기 -부모가 조부모 기준으로 오른쪽 자손일 때
		else
		{
			//삼촌
			Node* uncle = newNode-> Parent() ->Parent()->Left();

			//삼촌노드가 빨간색 일 때 - Case1.
			//해결 : 부모와 삼촌을 Black,할아버지를 Red로 변경 후,할아버지 기준으로 다시 검사
			if(uncle -> GetColor() == Color::Red())
			{
				newNode -> Parent() ->SetColor(Color::Black);
				uncle->SetColor(Color::Black);
				newNode->Parent()->Parent()->SetColor(Color::Red);

				newNode=newNode->Parent()->Parent();
				continue;
			}

			//위에서, continue; 했으니, else안함.
			//삼촌이 검정색 일 때 : case2,3
			//해결 2: 지그재그 형태: 부모위치와나의위치가 반대 : 일직으로ㅡ 변경 후 case3 처리.

			if(newNode == newNode->Parent()->Left())
			{
				//부모를 중심으로 회전 처리(일직선으로 만들기 위해)
				newNode = newNode->Parent();
				RotateToRight(newNode);
			}

			//해결 3:부모와 일치할때 -일직선 일 떄,
			newNode -> Parent()->SetColor(Color::Black);
			newNode ->Parent()->Parent()->SetColor(Color::Red);

			RotateToLeft(newNode->Parent()->Parent());
		}
	}

	//루트노드는 블랙
	root->SetColor(Color::Black);
}