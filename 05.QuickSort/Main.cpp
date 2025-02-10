#include <iostream>
#include <Windows.h>

//피봇(Pivot) 선택 함수
int Partition(int* array,int left,int right)
{
	std::cout << "\n" << "//피봇선택 //왼쪽 첫번째요소를 피봇으로.//왼쪽 첫번째요소를 피봇으로." << "\n";
	int first = left;
	int pivot = array[first];

	std::cout << "\n" << "//다음 위치로 이동" << "\n";
	++left;

	std::cout << "\n" << "//두 인덱스가 서로 교차할 때까지 진행" << "\n";
	while(left <= right)
	{
		std::cout <<left<<" "<<right << ": " <<array[left]<< "//left는 pivot 보다 큰 값 검색" << " \n";
		while(array[left] <= pivot)
		{
			++left;
		}

		std::cout <<left<<" "<<right << ": " <<array[right]<< "//right는 pivot 보다 작은 값 검색" << " \n";
		while(array[right] > pivot)
		{
			--right;
		}

		std::cout <<left<<" " <<right<< ": " <<right<< " " << "//left는 right 가 교차하지 않았을 떄만 값 교환" << " ";
		if(left >= right)
		{
			break;	//안되는 걸 처낸 후 나머지 하는것이 세윤님 편하다 함;	//루프처리할때, 건너뛰어도 되는 경우 continue, break 등는 귀찮아도 다 넣으라고 하더라고요, 성능차이 난다해서, 미리 경우에서 없는지 파악하는 습관을 들이라는 조언을 들었기에! 이렇게 작성하기 시작함
		}

		std::swap(array[left],array[right]);
	}

	std::cout << "\n" << "//최종 교환" << "\n";
	std::swap(array[first],array[right]);

	return right;
}
//퀵 정렬함수
void QuickSort(int* array,int left,int right)
{
	if(left >= right)
	{
		std::cout << " " << "// 더 이상 분할 할 수 없는 상태 == 탈출조건" << "\n";

		return ;
	}
	//	std::cout << "\n" << "//분할" << "\n";
	int partition = Partition(array,left,right);
	//	std::cout << " " << "//배열 퀵 정렬  - 왼쪽" << "\n";
	QuickSort(array,left,partition-1);
	//	std::cout << " " << "//배열 퀵 정렬  - 오른쪽" << "\n";
	QuickSort(array,partition+1,right);
}

void PrintArray(int array[],int length)
{
	for(int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : " ");
	}

	std::cout << "\n";
}

//메인함수(진입점)
int main()
{
	int array[] = {18,19,21,5,2,8,4,1,7,3,6,9,10,15,13,14,12,17,16,11,25};
	//int array[] = {18,19,21,5,2,8,4,1,7,3,6,9,10,15,13,13,13,13,13,13,14,12,17,16,11,25};

	int length = _countof(array);	//int length = sizeof(array) / sizeof(int);	//이거와 같은 define 문!
	std::cout << "\n" << "//정열 전" << "\n";
	PrintArray(array,length);

	std::cout << "\n" << "//정열" << "\n";
	QuickSort(array,0,length-1);

	std::cout << "\n" << "//정열 후" << "\n";
	PrintArray(array,length);
	std::cin.get();
}