#include<iostream>
#include <conio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;


/*
0: 벽
1: 길
2: 시작점
3: 도착점
4. 폭탄
5. 파워아이템
6. 벽밀기 아이템
7. 투명화 아이템
8. 웜홀
*/
struct _tagPoint
{
	int x;
	int y;
};

// typedef : 타입을 재정의하는 기능이다.
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer
{
	_tagPoint tPos;
	bool bWallPush;
	bool bTransparency;
	int iBombPower;
}PLAYER, *PPLAYER;

void SetMaze(char Maze[21][21],PPLAYER pPlayer, PPOINT pStartPos,
	PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0],  "21100000000000000000");
	strcpy_s(Maze[1],  "00111111111110000000");
	strcpy_s(Maze[2],  "00100010000011111100");
	strcpy_s(Maze[3],  "01100010000000000100");
	strcpy_s(Maze[4],  "01000011110001111100");
	strcpy_s(Maze[5],  "01000000001111000000");
	strcpy_s(Maze[6],  "01100000001000000000");
	strcpy_s(Maze[7],  "00100000001111111000");
	strcpy_s(Maze[8],  "00000000000000001000");
	strcpy_s(Maze[9],  "00001111111111111000");
	strcpy_s(Maze[10], "00001000000000001000");
	strcpy_s(Maze[11], "00001100001111001000");
	strcpy_s(Maze[12], "00000100000001111000");
	strcpy_s(Maze[13], "00000100000000000000");
	strcpy_s(Maze[14], "00000111111111110000");
	strcpy_s(Maze[15], "00000000001000011100");
	strcpy_s(Maze[16], "11100000001000000110");
	strcpy_s(Maze[17], "10111111111000000000");
	strcpy_s(Maze[18], "10000000000000000000");
	strcpy_s(Maze[19], "11111111111111111113");
}

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (Maze[i][j] == '4')
				cout << "♨";
			 
			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "☆";
			else if (Maze[i][j] == '0')
				cout << "■";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "★";
			else if (Maze[i][j] == '3')
				cout << "◎";
			else if (Maze[i][j] == '5')
				cout << "㈜";
			else if (Maze[i][j] == '6')
				cout << "※";
			else if (Maze[i][j] == '7')
				cout << "▷";

		}

		cout << endl;
	}
	cout << "폭탄파워 : " << pPlayer->iBombPower << endl;
	cout << "벽통과 : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";
	cout << "벽밀기 : ";
	if (pPlayer->bWallPush)
		cout << "ON" << endl;

	else
		cout << "OFF" << endl;
}

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5')
	{
		if(pPlayer->iBombPower < 5)
		++pPlayer->iBombPower;

		return true;
	}
	else if (cItemType == '6')
	{
		pPlayer->bWallPush = true;
		return true;
	}
	else if (cItemType == '7')
	{
		pPlayer->bTransparency = true;
		return true;
	}
	
	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{
		

		//벽인지 체크한다.
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0'
			&& Maze[pPlayer->tPos.y -1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		if(AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		


	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		//벽인지 체크한다.
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0'
		 && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x ], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';


	}
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		//벽인지 체크한다.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0'
		 && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}
		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';


	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		//벽인지 체크한다.
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0'
		 && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}
		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';


	}
}

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput) {
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

// 포인터 변수를 const로 생성하면 가리키는 대상의 값을 변경 할 수 없다.
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer,
	PPOINT pBombArr, int* pBombCount)
{
	if (*pBombCount == 5)
		return;

	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;
	for (int i = 0; i < *pBombCount; ++i)
	{
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr,
	int* pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		// 플레이어가 폭탄에 맞았을때 시작점으로 보낸다.
		if ( ((abs(pBombArr[i].x - pPlayer->tPos.x)<=pPlayer->iBombPower)&&(pBombArr[i].y == pPlayer->tPos.y)) 
			|| (((abs(pBombArr[i].y - pPlayer->tPos.y)) <= pPlayer->iBombPower)&&(pBombArr[i].x == pPlayer->tPos.x)) )
		{
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}

		for (int j = 1; j <= pPlayer->iBombPower; ++j)
		{
			if (pBombArr[i].y - j >= 0)
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{ 
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						else if(iPercent < 80)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else 
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
					}
					else
					Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}		
			}

			if (pBombArr[i].y + j < 20)
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
					}
					else
					Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}
			}
			if (pBombArr[i].x - j >= 0)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
					}
					else
					Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}
			}
			if (pBombArr[i].x + j < 20)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					// 아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						else
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
					}
					else
					Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}

			}
		}
	}

	*pBombCount = 0;
}
int main() 
{
	srand((unsigned int)time(0));
	// 20 x 20 미로를 만들어준다.
	char  strMaze[21][21] = {};
	
	PLAYER tPlayer;
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;
	tPlayer.bTransparency = 0;
	tPlayer.bWallPush = 0;
	int iBombCount = 0;

	POINT tBombPos[5];
	// 미로를 설정한다.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true) {

		system("cls");
		// 미로를 출력한다.
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "t : 폭탄 설치 u : 폭탄 터트리기 i : 벽밀기" << endl;
		cout << "w : 위 s: 아래  a : 왼쪽 d : 오른쪽 q : 종료 :";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T')
		{
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'u' || cInput == 'U')
		{
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}
		else
		MovePlayer(strMaze, &tPlayer, cInput);
	}
	return 0;
}