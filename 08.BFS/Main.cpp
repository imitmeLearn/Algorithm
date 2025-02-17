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
std::vector<std::vector<char>> map;
//std::vector<std::vector<char>> mapfile;
//std::vector<std::vector<char>> map =
//{
//	{'1','1','1','1','1','1'},
//	{'e','0','1','0','0','1'},
//	{'1','0','0','0','1','1'},
//	{'1','0','1','0','1','1'},
//	{'1','0','1','0','0','x'},
//	{'1','1','1','1','1','1'}
//};

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

bool ParseMap(const char* path,char& startMark,char& destinationMark)
{
	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file,path,"r");
	if(file)
	{
		// 첫 줄 읽기.
		char buffer[2048] = {};
		if(!fgets(buffer,2048,file))
		{
			fclose(file);
			return false;
		}

		//mapfile.clear();	//맵 데이터 정리
		sscanf_s(buffer,"size: %d start: %c destination: %c",&mazeSize,&startMark,1,&destinationMark,1);	// 맵 크기 설정 및 시작/목적 지점 문자 설정.
		std::vector<std::string> lines;		// 줄 데이터 저장을 위한 임시 배열 선언.
		lines.reserve(mazeSize);

		//첫 줄을 제외한 나머지 데이터를 한번에 읽기.  **찾아보기!!
		auto currentPosition = ftell(file);	//파일의 현재 위치
		fseek(file,0,SEEK_END);		//마지막 위치로 이동
		auto endPosition = ftell(file);		//위치저장
		int size = (int)(endPosition - currentPosition);	//크기계산 : 사이지 읽은 후, char* testBuffer= new char[size] ; delete[] textBuffer; 해도됨.
		fseek(file,currentPosition,SEEK_SET);	//rewind
		fread_s(buffer,2048,size,1,file);	//나머지 읽기

		//라인파싱
		char* context = nullptr;
		char* splitString = strtok_s(buffer,"\n",&context);
		if(splitString)
		{
			lines.emplace_back(splitString);
		}
		while(context)
		{
			splitString= strtok_s(nullptr,"\n",&context);
			if(!splitString)
			{
				break;
			}

			lines.emplace_back(splitString);
		}

		std::vector<char> line;	//라인별 파싱 데이터 저장.
		line.reserve(mazeSize);

		splitString = nullptr;	//라인 배열을 순회하면서 파싱처리

		for(auto& item : lines)
		{
			context = nullptr;	//재사용을 위한 정리.

			//첫칸 처리
			splitString = strtok_s(const_cast<char*>(item.c_str()),",",&context);	//const_cast<char*> 이때만쓴다????
			if(splitString)
			{
				line.emplace_back(splitString[0]);
			}

			//두 번째 칸 부터는 루프.
			while(context)
			{
				splitString = strtok_s(nullptr,",",&context);
				if(!splitString)
				{
					break;
				}
				line.emplace_back(splitString[0]);
			}

			//처리된 라인 데이터 맵에 추가
			map.emplace_back(line);
			line.clear();

			fclose(file);
			return true;
		}

		return false;
	}
}

int main()
{
	//ExcapeMaze();
	if(ParseMap("../Assets/MapBFS.txt",startMark,destinationMark))
	{
		ExcapeMaze();
	}

	std::cin.get();
}