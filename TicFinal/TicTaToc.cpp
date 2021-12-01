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

//T - ���º�
//U - ���� ���
//C - ��ǻ�� ���
//N - ������
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

//true -> Ȧ������ ������ �д�
//false -> ¦����° ������ �д�

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
				cout << "��ǻ�� ���";
			}
			else if (isOver(board) == 'U')
			{
				cout << "���� ���";
			}
			else if (isOver(board) == 'T')
			{
				cout << "���º�";
			}
			break;
		}

		// Ȧ������->����
		if (turn % 2 == 1)
		{
			cout << "�� ���� �Է��ϼ���: ";
			int a, b;
			cin >> a;
			cin >> b;
			board[a][b] = 'x';
		}
		//¦������->��ǻ��
		else
		{
			tem = Move(0);
			board[tem.mX][tem.mY] = 'o';
		}
		turn++;
		printBoard(board);
	}
}

//¦���� �ڱ� �ڽ��̴�.
//���� �� ����
pMove TicTaToc::Move(int depth)
{
	//��������
	// 1) �� �̻� �� ���� ���� -> ���º� ��ȯ
	// 2) ����� ���Դ� -> �¸��� ����ġ 1 �й�� ����ġ -1 ��ȯ

    //������ ��� ���� ã��
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
	
	//�ڽ����� �ٽ� ����Լ� ȣ��
	for (size_t i = 0; i < tem.size(); i++)
	{
		//���� ���纻 ����
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

	//��� �ڽ��� ��ȯ ���� ������ �ִ� ��ȯ�Ѵ�.
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

	//��������
	// 1) �� �̻� �� ���� ���� -> ���º� ��ȯ
	// 2) ����� ���Դ� -> �¸��� ����ġ 1 �й�� ����ġ -1 ��ȯ
	
	//T - ���º�
    //U - ���� ���
    //C - ��ǻ�� ���
    //N - ������
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

	//������ ��� ���� ã��
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

	//�ڽ����� �ٽ� ����Լ� ȣ��
	if (depth % 2 == 1)
	{
		for (size_t i = 0; i < tem.size(); i++)
		{
			//���� ���纻 ����
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
			//���� ���纻 ����
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
	//�ּڰ� ��ȯ
	//�ִ� ��ȯ

}