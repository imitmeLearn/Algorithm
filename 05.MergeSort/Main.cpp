#include<iostream>

//병합함수 (Merge)  ->벡터 안쓰고, 함수를 나눠서 구현하고, 메모리 카피 쓸 수 있는지, 배열 포인터의 관계같은!
//array : 병합할 배열 변수
//leftarray : 왼쪽)배열변수, leftArrayLength : 왼쪽)배열 크기
void	Merge(int* array
,int* leftArray,int leftArrayLength
,int* rightArray,int rightArrayLength
)
{
	//인덱스 변수 선언.
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	//왼쪽, 오른쪽 배열의 요소를 비교하면서, 작은 순서로 array 에 값 할당
	while(leftIndex < leftArrayLength
		&& rightIndex < rightArrayLength
		)
	{
		//비교
		if(leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}

		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		++mergedIndex;
	}

	while(leftIndex < leftArrayLength)
	{
		array[mergedIndex++] = leftArray[leftIndex++];	//사용 후 증가시킴.	//후위 연산 사용 = 아래와 같은 효과ㅣ!
	}

	while(rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];	//사용 후 증가시킴.	//후위 연산 사용 안한면, 이렇게!
		++rightIndex;
		++mergedIndex;
	}
}

//정렬함수 (MergeSort) - 재귀함수
void MergeSort(int* array,int length)
{
	//재귀이기에, 탈출조건
	if(length <= 1)
	{
		return;
	}

	//배열 분할 - 나누기
	int mid = length /2;

	//왼쪽 오른쪽 배열 공간 확보
	int* leftArray = new int[mid];
	int* rightArray = new int[length-mid];

	//값복사
	memcpy (leftArray,array,sizeof(int)*mid);
	memcpy (rightArray,array+mid,sizeof(int)*(length - mid));

	//재귀적 호출
	MergeSort(leftArray,mid);
	MergeSort(rightArray,length-mid);

	//병합 - 더이상 나눌 수 없을 만큼 쪼개졌으면,
	Merge(array,leftArray,mid,rightArray,length-mid);

	// 메모리 해제.
	delete[] leftArray;
	delete[] rightArray;
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
	// 배열.
	int array[] = {5,2,8,4,1,7,3,6,9,10,15,13,14,12,17,16};
	int length = _countof(array);
	std::cout<<"정렬 전 : ";
	PrintArray(array,length);

	MergeSort(array,length);

	std::cout<<"정렬 후 : ";
	PrintArray(array,length);

	std::cin.get();
}