#include<iostream>
#include <vector>

// 힙 만들기 (Heapify) 함수.
void Heapify(std::vector<int>& array,int length,int ix)
{
	while(true)
	{
		//힙 구성을 위한 인덱스 변수
		int largest = ix;

		//자손 인덱트
		int left = 2*ix+1;
		int right = 2*ix+2;

		if(left < length
			&& array[left] > array[largest]
			)
		{
			largest = left;
		}

		if(right < length
			&& array[right] > array[largest]
			)
		{
			largest = right;
		}

		if(largest == ix)	//변동사항이 없는경우
		{
			break;
		}

		std::swap(array[ix],array[largest]);
		ix = largest;
	}
}

// 힙 정렬 함수 (HeapSort).
void HeapSort(std::vector<int>& array)
{
	//전체 크기
	int length = (int)array.size();

	//힙 구성
	for(int ix = length /2 - 1; ix >= 0 ; ix--)
	{
		Heapify(array,length,ix);
	}

	std::cin.get();
}

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