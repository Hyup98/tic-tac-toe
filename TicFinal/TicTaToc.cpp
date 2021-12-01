#include "TicTaToc.h"
#include <iostream>
#include "pMove.h"
#include <vector>
using namespace std;

//User = x
//Computer = o
TicTaToc::TicTaToc()
{
	board = new char* [3];
	for (size_t i = 0; i < 3; i++)
	{
		board[i] = new char[3];
	}
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			board[i][j] = 0;
		}
	}
}

void TicTaToc::printBoard(char** board)
{
	cout << " <*********>\n";
	for (size_t i = 0; i < 3; i++)
	{
		cout << "-------------\n";
		cout << "|";
		for (size_t j = 0; j < 3; j++)
		{

			if (board[i][j] == 'x') {
				cout << " x";
			}
			else if (board[i][j] == 'o') {
				cout << " o";
			}
			else {
				cout << "  ";
			}
			cout << " |";
		}
		cout << '\n';
	}
	cout << "-------------\n";
	cout << " <*********>\n";
}

TicTaToc::~TicTaToc()
{
	for (size_t i = 0; i < 3; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}

//T - 무승부
//U - 유저 우승
//C - 컴퓨터 우승
//N - 진행중
char TicTaToc::isOver(char** board)
{
	if (board[0][1] == board[0][2] && board[0][1] == board[0][0])
	{
		if (board[0][0] == 'x')
		{
			return 'U';
		}
		else if (board[0][0] == 'o')
		{
			return 'C';
		}
	}
	else if (board[1][1] == board[1][2] && board[1][1] == board[1][0])
	{
		if (board[1][0] == 'x')
		{
			return 'U';
		}
		else if (board[1][0] == 'o')
		{
			return 'C';
		}
	}
	else if (board[2][1] == board[2][2] && board[2][1] == board[2][0])
	{
		if (board[2][1] == 'x')
		{
			return 'U';
		}
		else if (board[2][1] == 'o')
		{
			return 'C';
		}
	}
	else if (board[0][0] == board[1][0] && board[0][0] == board[2][0])
	{
		if (board[0][0] == 'x')
		{
			return 'U';
		}
		else if (board[0][0] == 'o')
		{
			return 'C';
		}
	}
	else if (board[0][1] == board[1][1] && board[0][1] == board[2][1])
	{
		if (board[0][1] == 'x')
		{
			return 'U';
		}
		else if (board[0][1] == 'o')
		{
			return 'C';
		}
	}
	else if (board[0][2] == board[1][2] && board[0][2] == board[2][2])
	{
		if (board[0][2] == 'x')
		{
			return 'U';
		}
		else if (board[0][2] == 'o')
		{
			return 'C';
		}
	}
	else if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		if (board[0][0] == 'x')
		{
			return 'U';
		}
		else if (board[0][0] == 'o')
		{
			return 'C';
		}
	}
	else if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		if (board[0][2] == 'x')
		{
			return 'U';
		}
		else if (board[0][2] == 'o')
		{
			return 'C';
		}
	}

	bool flag = true;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
			{
				flag = false;
				break;
			}
		}
		if (!flag)
		{
			break;
		}
	}
	if (!flag)
	{
		return 'N';
	}
	return 'T';
}

//true -> 홀수번쨰 유저가 둔다
//false -> 짝수번째 유저가 둔다

void TicTaToc::Play()
{
	cout << "**WELLCOME**\n\n";
	printBoard(board);
	int turn = 1;
	pMove tem(0, 0);
	while (true)
	{
		if (isOver(board) != 'N')
		{
			if (isOver(board) == 'C')
			{
				cout << "컴퓨터 우승";
			}
			else if (isOver(board) == 'U')
			{
				cout << "유저 우승";
			}
			else if (isOver(board) == 'T')
			{
				cout << "무승부";
			}
			break;
		}

		// 홀수번쨰->유저
		if (turn % 2 == 1)
		{
			cout << "둘 곳을 입력하세요: ";
			int a, b;
			cin >> a;
			cin >> b;
			board[a][b] = 'x';
		}
		//짝수번쨰->컴퓨터
		else
		{
			tem = Move(0);
			board[tem.mX][tem.mY] = 'o';
		}
		turn++;
		printBoard(board);
	}
}

//짝수가 자기 자신이다.
//내가 둘 차례
pMove TicTaToc::Move(int depth)
{
	//종료조건
	// 1) 더 이상 둘 곳이 없다 -> 무승부 반환
	// 2) 결과가 나왔다 -> 승리시 가중치 1 패배시 가중치 -1 반환

    //가능한 모든 수를 찾기
	vector<pMove> tem;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
			{
				tem.push_back(pMove(i, j));
			}
		}
	}
	
	//자식으로 다시 재귀함수 호출
	for (size_t i = 0; i < tem.size(); i++)
	{
		//보드 복사본 생성
		char** temBoard = new char* [3];
		for (size_t k= 0;  k < 3;  k++)
		{
			temBoard[k] = new char[3];
		}
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t t = 0; t < 3; t++)
			{
				temBoard[j][t] = board[j][t];
			}
		}
		temBoard[tem[i].mX][tem[i].mY] = 'o';
		tem[i].setPoint(MoveRecursive(temBoard, depth+1));

		for (size_t i = 0; i < 3; i++)
		{
			delete[] temBoard[i];
		}
		delete[] temBoard;
	}	

	//모든 자식이 반환 받은 값으로 최댓값 반환한다.
	int max = tem[0].mPoint;
	int index = 0;
	for (size_t i = 0; i < tem.size(); i++)
	{
		if (max < tem[i].mPoint)
		{
			max = tem[i].mPoint;
			index = i;
		}
	}

	return tem[index];
}

int TicTaToc::MoveRecursive(char** input, int depth)
{

	//종료조건
	// 1) 더 이상 둘 곳이 없다 -> 무승부 반환
	// 2) 결과가 나왔다 -> 승리시 가중치 1 패배시 가중치 -1 반환
	
	//T - 무승부
    //U - 유저 우승
    //C - 컴퓨터 우승
    //N - 진행중
	if (isOver(input) == 'T')
	{
		return 0;
	}
	else if (isOver(input) == 'U')
	{
		return -10;
	}
	else if (isOver(input) == 'C')
	{
		return 10;
	}

	//가능한 모든 수를 찾기
	vector<pMove> tem;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (input[i][j] == 0)
			{
				tem.push_back(pMove(i, j));
			}
		}
	}

	//자식으로 다시 재귀함수 호출
	if (depth % 2 == 1)
	{
		for (size_t i = 0; i < tem.size(); i++)
		{
			//보드 복사본 생성
			char** temBoard = new char* [3];
			for (size_t k = 0; k < 3; k++)
			{
				temBoard[k] = new char[3];
			}
			for (size_t j = 0; j < 3; j++)
			{
				for (size_t t = 0; t < 3; t++)
				{
					temBoard[j][t] = input[j][t];
				}
			}
			temBoard[tem[i].mX][tem[i].mY] = 'x';
			tem[i].setPoint(MoveRecursive(temBoard, depth + 1));
			//printBoard(temBoard);
			for (size_t i = 0; i < 3; i++)
			{
				delete[] temBoard[i];
			}
			delete[] temBoard;
		}
		int min = tem[0].mPoint;
		int index = 0;
		for (size_t i = 0; i < tem.size(); i++)
		{
			if (min > tem[i].mPoint)
			{
				min = tem[i].mPoint;
				index = i;
			}
		}
		return tem[index].mPoint;
	}
	else
	{
		for (size_t i = 0; i < tem.size(); i++)
		{
			//보드 복사본 생성
			char** temBoard = new char* [3];
			for (size_t k = 0; k < 3; k++)
			{
				temBoard[k] = new char[3];
			}
			for (size_t j = 0; j < 3; j++)
			{
				for (size_t t = 0; t < 3; t++)
				{
					temBoard[j][t] = input[j][t];
				}
			}
			temBoard[tem[i].mX][tem[i].mY] = 'o';
			tem[i].setPoint(MoveRecursive(temBoard, depth + 1));
			//printBoard(temBoard);
			for (size_t i = 0; i < 3; i++)
			{
				delete[] temBoard[i];
			}
			delete[] temBoard;
		}

		int max = tem[0].mPoint;
		int index = 0;
		for (size_t i = 0; i < tem.size(); i++)
		{
			if (max < tem[i].mPoint)
			{
				max = tem[i].mPoint;
				index = i;
			}
		}
		return tem[index].mPoint;
	}
	//최솟값 반환
	//최댓값 반환

}