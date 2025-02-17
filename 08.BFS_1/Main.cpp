//#include "Queue.h"
#include <queue>
#include <iostream>
#include <vector>

class Location2D
{
public:
	Location2D(size_t row = 0,size_t col = 0)
		: row(row),col(col)
	{}

public:
	size_t row;
	size_t col;
};
// 맵 배열.
std::vector<std::vector<char>> map;
char startMark = 'e';		// 시작 위치 문자.
char destinationMark = 'x';	// 목적 지점 문자.

const size_t MAZE_SIZE = 6;
//char map[MAZE_SIZE][MAZE_SIZE] =
//{
//	{'1','1','1','1','1','1'},
//	{'e','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','x'},
//	{'1','1','1','1','1','1'}
//};

//const size_t MAZE_SIZE = 20;
//char map[MAZE_SIZE][MAZE_SIZE] =
//{
//	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
//	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1'},
//	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
//	{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
//	{'1', '0', '1', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
//	{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
//	{'1', '1', '1', '1', '1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1'},
//	{'e', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
//	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1'},
//	{'1', '0', '1', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
//	{'1', '0', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1'},
//	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '0', '1'},
//	{'1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1'},
//	{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
//	{'1', '0', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1'},
//	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', 'x'},
//	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
//};

bool IsValidLocation(size_t row,size_t col)
{
	if(row >= MAZE_SIZE || col >= MAZE_SIZE)
	{
		return false;
	}

	return map[row][col] == '0' || map[row][col] == 'x';
}

//함수 구현 예시
// 맵 파일을 열어 필요한 정보를 설정하는 함수.
bool ParseMap(const char* path,char& startMark,char& destinationMark)
{
	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file,path,"r");
	if(file)
	{
		// 첫 줄 읽기.
		char buffer[256] = {};
		if(!fgets(buffer,256,file))
		{
			fclose(file);
			return false;
		}

		// 맵 크기 설정 및 시작/목적 지점 문자 설정.
		sscanf_s(buffer,"size: %d start: %c destination: %c",&MAZE_SIZE,&startMark,1,&destinationMark,1);

		// 줄 데이터 저장을 위한 임시 배열 선언.
		std::vector<char> line;
		line.reserve(MAZE_SIZE);

		// 맵 데이터 해석을 위한 루프 처리.
		while(fgets(buffer,256,file))
		{
			// 첫 칸 처리.
			char* context = nullptr;
			char* splitString = strtok_s(buffer,",",&context);
			if(splitString)
			{
				line.emplace_back(splitString[0]);
			}

			// 둘째 칸 부터는 루프 처리.
			while(context)
			{
				splitString = strtok_s(nullptr,",",&context);
				if(!splitString)
				{
					break;
				}

				line.emplace_back(splitString[0]);
			}

			// 처리된 라인 데이터를 맵에 추가.
			map.emplace_back(line);
			line.clear();
		}

		// 파일 닫기.
		fclose(file);
		return true;
	}

	return false;
}

int main()
{
	// 맵 파일 해석.
	if(!ParseMap("../Assets/MapBFS.txt",startMark,destinationMark))
		//if(!ParseMap("../Assets/BFS/Map.txt",startMark,destinationMark))
	{
		std::cout << " \n파일없음\n";

		return 0;
	}

	// 시작 지점 검색 및 맵 출력.
	size_t startRow = 0;
	size_t startCol = 0;
	for(size_t ix = 0; ix < MAZE_SIZE; ++ix)
	{
		for(size_t jx = 0; jx < MAZE_SIZE; ++jx)
		{
			std::cout << map[ix][jx] << " ";
			if(map[ix][jx] == startMark)
			{
				startRow = ix;
				startCol = jx;
			}
		}

		std::cout << std::endl;
	}

	// 미로 탐색 시작을 위해 큐에 시작 위치 추가.
	std::queue<Location2D> locationQueue;
	locationQueue.push(Location2D(startRow,startCol));

	size_t count = 0;
	while(locationQueue.empty() == false)
	{
		// 큐에 가장 앞에 있는 요소 추출.
		Location2D here = locationQueue.front();
		locationQueue.pop();

		// 편의를 위해 행/열 저장.
		size_t row = here.row;
		size_t col = here.col;

		// 방문 위치 출력.
		std::cout << "(" << row << "," << col << ") ";

		// 가로 10칸 출력 후 개행(엔터).
		count++;
		if(count == 10)
		{
			count = 0;
			std::cout << std::endl;
		}

		// 탈출 조건(목적지점 도착 확인).
		if(map[row][col] == destinationMark)
		{
			std::cout << " \n미로 탐색 성공\n";

			std::cin.get();
			return 0;
		}

		map[row][col] = '.';
		if(IsValidLocation(row - 1,col) == true)
		{
			locationQueue.push(Location2D(row - 1,col));
		}
		if(IsValidLocation(row + 1,col) == true)
		{
			locationQueue.push(Location2D(row + 1,col));
		}
		if(IsValidLocation(row,col - 1) == true)
		{
			locationQueue.push(Location2D(row,col - 1));
		}
		if(IsValidLocation(row,col + 1) == true)
		{
			locationQueue.push(Location2D(row,col + 1));
		}
	}

	std::cout << " \n미로 탐색 실패\n";

	std::cin.get();
}