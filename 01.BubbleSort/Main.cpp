#include <iostream>

//교환
void Swap(int& a,int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//버블 정렬 함수
void BubbleSort(int* array,int length)
{
	for(int ix = 0; ix < length - 1; ix++)
	{
		for(int jx = 0; jx < length - 1 -ix; jx++)
		{
			//두개씩 비교
			if(array[jx] > array[jx + 1])
			{
				Swap(array[jx],array[jx + 1]);	//std::swap<int>();	//이거 써도 된다!!!!!!나중에!!!!지금은 실습하느라 Swap() 만들엇지만
			}
		}
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
	int array[] = {5,3,2,8,10,15,20,23};			//배열
	int length = sizeof(array) / sizeof(int);		//배열 길이 //전체크기에서, 나누면, 매  4바이트*5 = 20 바이트, 크기로나누면, 개수??

	std::cout << "\n" << "//출력" << "\n";
	std::cout << "정렬 전 : ";
	PrintArray(array,length);

	std::cout << "\n" << "//정렬" << "\n";
	BubbleSort(array,length);

	std::cout << "\n" << "//출력" << "\n";
	std::cout << "정렬 후 : ";
	PrintArray(array,length);
}