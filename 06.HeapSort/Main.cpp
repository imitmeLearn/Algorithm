#include<iostream>
#include <vector>

// 힙 만들기 (Heapify) 함수.
void Heapify(std::vector<int>& array,int length,int ix)
{}

// 힙 정렬 함수 (HeapSort).
void HeapSort(std::vector<int>& array)
{}

// 벡터 출력 함수.
void PrintArray(std::vector<int>& array)
{
	for(int ix = 0; ix < (int)array.size(); ++ix)
	{
		std::cout << array[ix] << (ix < (int)array.size() - 1 ? ", " : "");
	}

	std::cout << "\n";
}

// 배열 출력 함수.
void PrintArray(int array[],int length)
{
	for(int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : "");
	}

	std::cout << "\n";
}
int main()
{
	//메모리 누수 확인

	 // 배열.
	std::vector<int> array = {5,2,8,4,1,7,3,6,9,10,15,13,14,12,17,16};
	std::cout<<"정렬 전 : ";
	PrintArray(array);

	HeapSort(array);

	std::cout<<"정렬 후 : ";
	PrintArray(array);

	std::cin.get();
}