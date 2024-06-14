#include "UI.h"
#include "Object.h"

#include <new>
#include <cstdlib>
#include <iostream>
#include <Windows.h>

bool UI::bDestroyed = false;
UI* UI::uIns = nullptr;

int min_x = 53;
int max_x = 68;
int min_y = 13;
int max_y = 17;

void UI::Create()
{
	static UI ins;
	uIns = &ins;
}

void UI::KillUI()
{
	uIns->~UI();
}

UI* UI::GetInstance()
{
	if (bDestroyed)
	{
		new(uIns) UI;
		atexit(KillUI);
		bDestroyed = false;
	}
	else if (uIns == nullptr)
	{
		Create();
	}

	return uIns;
}

int UI::SelectMenu()
{
	int GameMode = 0;
	gotoxy(50, 10);
	printf("----Menu----");
	gotoxy(50, 11);
	printf("1. 게임 시작");
	gotoxy(50, 12);
	printf("2. 랭크 보기");
	gotoxy(50, 13);
	printf("3. 게임 종료");

	gotoxy(50, 15);
	printf("모드 입력 : ");
	scanf_s("%d", &GameMode);

	return GameMode;
}

void UI::ShowLogo() const
{
	gotoxy(20, 10);
	printf("  .d8888b.         d8888 888             d8888  .d8888b.         d8888");
	gotoxy(20, 11);
	printf(" d88P  Y88b       d88888 888            d88888 d88P  Y88b       d88888");
	gotoxy(20, 12);
	printf(" 888    888      d88P888 888           d88P888 888    888      d88P888");
	gotoxy(20, 13);
	printf(" 888            d88P 888 888          d88P 888 888            d88P 888");
	gotoxy(20, 14);
	printf(" 888  88888    d88P  888 888         d88P  888 888  88888    d88P  888");
	gotoxy(20, 15);
	printf(" 888    888   d88P   888 888        d88P   888 888    888   d88P   888");
	gotoxy(20, 16);
	printf(" Y88b  d88P  d8888888888 888       d8888888888 Y88b  d88P  d8888888888");
	gotoxy(20, 17);
	printf("  Y8888P88  d88P     888 88888888 d88P     888  Y8888P88  d88P     888");

	Sleep(8500);
}

void UI::ShowHowToPlay() const
{
	gotoxy(45, 13);
	printf(" 이동 [ ← → A D ]");
	gotoxy(45, 14);
	printf("  정지 [ ↑ W ]");
	gotoxy(40, 15);
	printf(" 모든 웨이브 클리어 시 승리!!");

	Sleep(5000);
}

void UI::ShowGameWin() const
{
	// Draw X
	for (int x = min_x; x <= max_x; x++)
	{
		int y = min_y;
		gotoxy(x, y);
		printf("-");

		y = max_y;
		gotoxy(x, y);
		printf("-");
	}

	// Draw Y
	for (int y = min_y; y <= max_y; y++)
	{
		int x = min_x;
		gotoxy(x, y);
		printf("l");

		x = max_x;
		gotoxy(x, y);
		printf("l");
	}

	gotoxy(57, 15);
	printf("You Win!!");

	Sleep(4000);
}

void UI::ShowGameOver() const
{
	// Draw X
	for (int x = min_x; x <= max_x; x++)
	{
		int y = min_y;
		gotoxy(x, y);
		printf("-");

		y = max_y;
		gotoxy(x, y);
		printf("-");
	}

	// Draw Y
	for (int y = min_y; y <= max_y; y++)
	{
		int x = min_x;
		gotoxy(x, y);
		printf("l");

		x = max_x;
		gotoxy(x, y);
		printf("l");
	}

	gotoxy(57, 15);
	printf("Game Over");

	Sleep(3000);
}
