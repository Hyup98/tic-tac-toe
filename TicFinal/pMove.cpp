#include "pMove.h"


pMove::pMove(int x, int y)
{
	mX = x;
	mY = y;
	mPoint = 0;
}


pMove::~pMove()
{
}

void pMove::setPoint(int a)
{
	mPoint = a;
}


