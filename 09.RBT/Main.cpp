﻿#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include <Windows.h>
#include "RedBlackTree.h"
#include <vector>

enum class Command	//명령 구분을 위한 열거형.
{
	None=0,
	Insert,
	Delete,
	Find,
	Print,
	Quit
};

//화면 지우는 함수.
void ClearScreen()
{
	system("cls");
}

//명령입력처리 //출력할 것이기에 & 사용
void ProcessCommandInput(int& commandInput)
{
	char inputBuffer[100] = {};
	while(true)
	{
		std::cout<<"\n"<<"명령 숫자 입력"<<"\n";
		std::cout<<"(1) 노드 추가, (2)노드 삭제, (3)노드 검색, (4) 노드 출력, (5) 종료"<<"\n";
		std::cin>> inputBuffer;

		//atoi : ascii to integer //문자를 정수로 변경
		if(commandInput = atoi(inputBuffer))
		{
			//예회
			if(commandInput <= (int)Command::None
				||commandInput > (int)Command::Quit)
			{
				ClearScreen();
				std::cout<<"\n"<<"오류 : 입력 숫자 확인"<<"\n";

				continue;
			}
			break;
		}

		//예외처리.
		ClearScreen();
		std::cout<<"\n"<<"오류 : 명령 숫자만 입력"<<"\n";
	}
}

void ProcessParamInput(int& param)
{
	//입력 처리 버퍼
	char inputBuffur[100];
	while(true)
	{
		std::cout<<"\n"<<"파라미터 임력 (1-200)."<<"\n";
		std::cin >> inputBuffur;

		//검증
		if(param = atoi(inputBuffur))
		{
			//예외처리
			if(param < 1 || param > 200)
			{
				ClearScreen();

				std::cout <<"입력 : " << inputBuffur
					<< "오류 ㅣ 파라미터 1~200 사이 숫자만 입력";
				continue;
			}
			break;
		}

		ClearScreen();
		std::cout  <<"입력 : " << inputBuffur
			<< "오류 ㅣ 파라미터 숫자만 입력";
	}
}

//명령처리 함수
void ProcessCommand(int commandInput,RedBlackTree& tree)
{
	Command command = (Command)commandInput;	//입력값을열거형으로
	if(command == Command::Print)
	{
		ClearScreen();

		tree.Print();
		return ;
	}

	//프로그램 종료
	if(command == Command::Quit)
	{
		//	exit(0);	//delete 호출 안함.
		return;
	}

	//1,2,3 명령 처리
	int param = 0;
	ProcessParamInput(param);

	switch(command)
	{
	case Command::None:
	break;
	case Command::Insert:
	{
		ClearScreen();
		tree.Insert(param);
	}
	break;
	case Command::Delete:
	{
		ClearScreen();
		tree.Remove(param);
	}
	break;
	case Command::Find:
	{
		//검색
		Node* result = nullptr;
		if(!tree.Find(param,&result))
		{
			std::cout<<"노드 못 찾음, 검색 값: (" << param << ")\n";
			return;
		}

		if(result ->GetColor() == Color::Red)
		{
			SetTextColor(TextColor::Red);
		}

		else
		{
			SetTextColor(TextColor::White);
		}

		//검색 결과 출력
		std::cout
			<<"검색 노드 : " << result->Data()
			<< " (Color: " << result->ColorString()
			<<"\n";

		// 콘솔 텍스트 복구.
		SetTextColor(TextColor::White);
	}
	break;
	case Command::Print:
	break;
	case Command::Quit:
	break;
	default:
	break;
	}
}
void Initialization(const char* path,RedBlackTree* tree)
{
	if(tree == nullptr)
	{
		std::cout << "오류: 전달된 트리가 null 입니다.\n";
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file,path,"r");
	if(file == nullptr)
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		return;
	}

	char line[1024] = {};
	if(!fgets(line,1024,file))
	{
		std::cout << "오류: 파일 읽기 실패.\n";
		fclose(file);
		return;
	}

	fclose(file);

	std::vector<int> datas;

	// 첫 토근 읽기.
	char* context = nullptr;
	char* splitString = strtok_s(line,",",&context);
	if(splitString)
	{
		if(int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// 나머지 토근 읽기.
	while(context)
	{
		splitString = strtok_s(nullptr,",",&context);
		if(!splitString)
		{
			break;
		}

		if(int parsed = atoi(splitString))
		{
			datas.emplace_back(parsed);
		}
	}

	// 트리에 데이터 추가.
	for(auto data : datas)
	{
		tree->Insert(data);
	}

	// 초기 데이터를 설정한 후의 데이터 출력.
	std::cout << "초기 데이터가 적용되었습니다.\n";
	tree->Print();
	std::cout << "\n";
}

int main()
{
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout<<"\n"<<"//"<<"\n";

	//레드블랙 트리 생성
	RedBlackTree tree;

	// 초기 데이터 추가.

	Initialization("../Assets/InitData.txt",&tree);

	while(1)
	{
		int commandInput = 0;

		ProcessCommandInput(commandInput);
		ProcessCommand(commandInput,tree);

		//종료처리
		if(commandInput == (int)Command::Quit)
		{
			break;
		}
	}

	std::cin.get();
}