#include "Queue.h"
#include <iostream>

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

const size_t MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] =
{
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};

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

int main()
{
	// Print Map.
	size_t startRow = 0;
	size_t startCol = 0;
	for(size_t ix = 0; ix < MAZE_SIZE; ++ix)
	{
		for(size_t jx = 0; jx < MAZE_SIZE; ++jx)
		{
			std::cout << map[ix][jx] << " ";
			if(map[ix][jx] == 'e')
			{
				startRow = ix;
				startCol = jx;
			}
		}

		std::cout << std::endl;
	}

	Queue<Location2D,MAZE_SIZE> locationQueue;
	locationQueue.Enqueue(Location2D(startRow,startCol));

	size_t count = 0;
	while(locationQueue.IsEmpty() == false)
	{
		Location2D here = locationQueue.Dequeue();

		size_t row = here.row;
		size_t col = here.col;

		std::cout << "(" << row << "," << col << ") ";
		count++;
		if(count == 10)
		{
			count = 0;
			std::cout << std::endl;
		}

		if(map[row][col] == 'x')
		{
			std::cout << " \n미로 탐색 성공\n";

			std::cin.get();
			return 0;
		}

		map[row][col] = '.';
		if(IsValidLocation(row - 1,col) == true)
		{
			locationQueue.Enqueue(Location2D(row - 1,col));
		}
		if(IsValidLocation(row + 1,col) == true)
		{
			locationQueue.Enqueue(Location2D(row + 1,col));
		}
		if(IsValidLocation(row,col - 1) == true)
		{
			locationQueue.Enqueue(Location2D(row,col - 1));
		}
		if(IsValidLocation(row,col + 1) == true)
		{
			locationQueue.Enqueue(Location2D(row,col + 1));
		}
	}

	std::cout << " \n미로 탐색 실패\n";

	std::cin.get();
}