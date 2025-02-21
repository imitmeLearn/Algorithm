#include "Bounds.h"

bool Bounds::Intersects(const Bounds & other) const
{
	if(MaxX() < other.x) return false;	//다른 영역이 현재 영역의 오른쪽 바깥에 있는 경우
	if(other.MaxX() < x) return false;	//다른 영역이 현재 영역의 왼쪽 바깥에 있는 경우

	if(MaxY() < other.y) return false;	//다른 영역이 현재 영역의 아래쪽 바깥에 있는 경우 //OK 꺽쇠위치 확인해보기 -  축 Y 가 아래가 + 여서, 꺽쇠 그림 반대임.
	if(other.MaxY() < y) return false;	//다른 영역이 현재 영역의 위쪽 바깥에 있는 경우

	return true;
	//return !(other.x > GetMaxX() || other.GetMaxX() < x || other.y > GetMaxY() || other.GetMaxY() < y);	//위에 4개 합치면, 이렇게
}