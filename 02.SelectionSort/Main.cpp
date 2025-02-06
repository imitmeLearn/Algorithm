#include <iostream>

void SelectionSort(int* array,int length)
{
	for(int ix = 0; ix < length-1; ix++)
	{
		int minIndex = ix;		//최소값 저장할 변수	//값 저장하면 바꿀 것 못 찾으니까, 인덱스 저장하기
		for(int jx = ix+1; jx < length; jx++)
		{
			if(array[jx] < array[minIndex])
			{
				minIndex = jx;
			}
		}

		std::swap<int>(array[ix],array[minIndex]);		////값 바꾸기
	}
}

//출력함수
void PrintArray(int* array,int length)
{
	for(int ix = 0; ix < length; ix++)
	{
		std::cout << array[ix] << " ";
	}
	std::cout << "\n";
}

int main()
{
	int array[] = {5,2,8,4,1,7,3,6,9,10,15,13,14,12,17,16};			//배열
	int length = sizeof(array) / sizeof(int);		//배열 길이 //전체크기에서, 나누면, 매  4바이트*5 = 20 바이트, 크기로나누면, 개수??

	std::cout << "\n" << "//출력" << "\n";
	std::cout << "정렬 전 : ";
	PrintArray(array,length);

	std::cout << "\n" << "//정렬" << "\n";
	SelectionSort(array,length);

	std::cout << "정렬 후 : ";
	PrintArray(array,length);
}