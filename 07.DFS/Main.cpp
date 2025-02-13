#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include <vector>
#include <stack>

#include <string.h>
#include <stdio.h>

//미로 탐색
struct Location2D
{
	Location2D(int row=0,int col =0)
		:row(row),col(col)
	{}

	int row;
	int col;
};
//맵 배열
int mapSize =0;
std::vector<std::vector<char>> map
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
}
;

//이동 가능 여부 판단 함수.
bool IsValidLocation(int row,int col)
{
	if(row < 0 || row >= mapSize
		||col < 0 || col >= mapSize)
	{
		return false;
	}
	return map[row][col] =='0' || map[row][col] =='x';
}

//시작지점 검색 함수
void FindStartLocation(int& row,int& col)
{
	for(int ix = 0; ix < mapSize; ix++)
	{
		for(int jx = 0; jx < mapSize; jx++)
		{
			//맵출력
			std::cout << map[ix][jx] << " ";

			if(map[ix][jx] == 'e')
			{
				row = ix;
				col = jx;
				//return;
			}
		}

		//개행
		std::cout<<"\n";
	}
}

//미로탐색 함수
void EscapeMaze()
{
	//맵 크기 확인
	mapSize =(int)map.size();

	int row = 0;
	int col = 0;

	//시작위치찾기
	FindStartLocation(row,col);

	//스택선언
	std::stack<Location2D> stack;

	stack.push(Location2D(row,col));

	//미로탐색
	while(!stack.empty())
	{
		//현재위치 반환
		Location2D current = stack.top();
		stack.pop();

		//탐색 위치 출력
		std::cout<<"("<< current.row << ", " << current.col <<") ";

		//값 저장
		row = current.row;
		col = current.col;

		//탈출 조건 확인
		if(map[row][col] == 'x')
		{
			std::cout<<"\n 미로 탐색 성공 \n";
			return;
		}

		//탐색 진행.
		//방문한 현재 위치는 재방문 방지를 위해 표시.
		map[row][col] = '.';

		if(IsValidLocation(current.row -1,current.col))
		{
			stack.push(Location2D(current.row -1,current.col));
		}
		if(IsValidLocation(current.row +1,current.col))
		{
			stack.push(Location2D(current.row +1,current.col));
		}
		if(IsValidLocation(current.row,current.col-1))
		{
			stack.push(Location2D(current.row,current.col-1));
		}
		if(IsValidLocation(current.row,current.col+1))
		{
			stack.push(Location2D(current.row,current.col+1));
		}
	}

	std::cout<<"\n 미로 탐색 실패 \n";
}

char string[] = "A string\tof ,,tokens\nand some  more tokens";
char seps[]   = " ,\t\n";
char *token;

//맵 물러와 해석 : 파싱 , JSON PARSER
bool ParseMap(const char* path)
{
	FILE* file = nullptr; //파일 열기
	fopen_s(&file,path,"r");
	if(file)
	{
		// 첫줄 읽기.
		char buffer[256]={};
		if(!	fgets(buffer,256,file))
		{
			fclose(file);
			return false;
		}

		std::cout<<"\n"<<"//읽기 성공"<<"\n";
		fclose(file);
		return	true;
	}
	return false;
}

int main()
{
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//printf("Tokens:\n");

	//// Establish string and get the first token:
	//token = strtok(string,seps); // C4996
	//// Note: strtok is deprecated; consider using strtok_s instead
	//while(token != NULL)
	//{
	//	// While there are tokens in "string"
	//	printf(" %s\n",token);

	//	// Get next token:
	//	token = strtok(NULL,seps); // C4996
	//}

	//std::cout<<"\n"<<"//미로탐색"<<"\n";

	if(ParseMap("../Assets/Map.txt"))
	{
		EscapeMaze();
	}
	std::cin.get();
}