#include <iostream>
#include <queue>
#include <string>

struct  Location
{
	Location(int row = 0,int col = 0)
		:row(row),col(col)
	{}

	int row;
	int col;
};

//맵 선언.
int mazeSize = 6;
char startMark = 'e';
char destinationMark = 'x';
std::vector<std::vector<char>> map =
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

//이동하려는 위치가 이동 가능한 위치인지 확인하는 함수.
bool IsValid(int row,int col)
{
	//out of index 검사
	if(row < 0 || row >= mazeSize || col <0 || col >= mazeSize)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == destinationMark;
}

//맵 출력 및 시작 위치 검색 함수/
void FindStartLocation(int& row,int& col)
{
	for(int ix = 0; ix < mazeSize; ix++)
	{
		//시작 위치 찾았으면, 전달하는 파라미터 출력.
		for(int jx = 0; jx < mazeSize; jx++)
		{
			if(map[ix][jx] == startMark)
			{
				row = ix;
				col = jx;
			}

			//맵출력
			std::cout<< map[ix][jx]  << " ";
		}

		//개행
		std::cout << "\n";
	}
}

void ExcapeMaze()
{
	//시작위치
	//int startRow,int startCol;
	int row = 0;
	int col= 0;
	FindStartLocation(row,col);

	std::queue<Location> queue;	//팀색에 사용힐 큐 선언.
	queue.emplace (Location(row,col));//시작위치 추가

	//탐색
	while(!queue.empty())
	{
		Location current = queue.front();	//큐에서 가장 앞에 위치한 데이터를 추출
		queue.pop();

		//편의를 위해 저장
		row = current.row;
		col = current.col;

		//탐색 위치 출력
		std::cout <<"(" << current.row << ", " << current.col << ") ";

		//탈출 조건 (목표지점에 도달한 경우)
		if(map[row][col] == destinationMark)
		{
			std::cout << "\n 미로 탐색 성공 \n";
			return;
		}

		map[current.row][current.col] ='.';//탐색할 위치를 다른 문자로 설정

		//탐색할 위치를 큐에 넣기.
		if(IsValid(row -1,col))
		{
			queue.emplace(Location(row-1,col));
		}

		if(IsValid(row +1,col))
		{
			queue.emplace(Location(row+1,col));
		}
		if(IsValid(row,col-1))
		{
			queue.emplace(Location(row,col-1));
		}
		if(IsValid(row,col+1))
		{
			queue.emplace(Location(row,col+1));
		}
	}

	//탐색 실패
	std::cout << "\n 미로 탐색 실패 \n";
}
int main()
{
	ExcapeMaze();
	std::cin.get();
}