#pragma once
#include "pMove.h"

class TicTaToc
{
public:
	TicTaToc();//���� ����
	~TicTaToc();
	char isOver(char** board);
	void Play();
	void printBoard(char** board);
	pMove Move(int depth);
	int MoveRecursive(char** board, int depth);
private:
	char** board;
};

