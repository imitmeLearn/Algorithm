#include <iostream>

//삽압 정렬 함수.
void InsertionSort(int* array,int length)
{
	for(int ix = 0; ix < length; ix++)
	{
		int keyValue = array[ix];	//키 뽑기
		int jx = ix-1;

		//std::cout << "\n" << "//셔플링 (교환)" << "\n";

		while(jx >= 0 && array[jx] > keyValue)
		{
			array[jx+1] = array[jx];
			std::cout  << ix << " :  "<<jx <<" -- ";
			--jx;
			std::cout  << ix << " : "<<jx <<" ";
		}

		std::cout<<"\n"  << ix << "["<<keyValue<<"] s//값 끼우기 " <<array[jx+1]<<" =" << keyValue<<"\n";
		array[jx+1] = keyValue;
	}
}

// 배열 출력 함수.
void PrintArray(int* array,int length)
{
	for(int ix = 0; ix < length; ix++)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : "");
	}

	std::cout << "\n";
}

int main()
{
	// 자료 집합
	int array[] = {5,2,8,4,1,7,3,6,9,10,15,13,14,12,17,16};
	int length = sizeof(array) / sizeof(int);

	std::cout << "\n" << "//정렬 전" << "\n";
	PrintArray(array,length);

	std::cout << "\n" << "//정렬" << "\n";
	InsertionSort(array,length);

	std::cout << "\n" << "// 정렬 후 출력." << "\n";
	PrintArray(array,length);

	std::cin.get();
}