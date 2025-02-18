#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "RedBlackTree.h"
#include <Windows.h>
#include "Main.h"

enum class Command	//명령 구분을 위한 열거형.
{
	None,
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

int main()
{
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::cout<<"\n"<<"//"<<"\n";

	int commandInput = 0;
	ProcessCommandInput(commandInput);

	std::cin.get();
}