#include "Core.h"

#include "RankingSystem.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"
#include "UI.h"
#include "public.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>

#include <time.h>
#include <conio.h>

static int DefaultGameScore = 10;

Core::Core()
	: m_bGameLoop(false)
	, m_nFPS(100)
	, m_nEnemySpawnCount(5)
	, m_nEnemySpawnLimits(0)
{
	system("title Galaga");
	srand(unsigned int(time(NULL)));

	SetGameLoop(true);

	RankSys = new RankingSystem();

	if (RankSys->IsFileVaild(RankSys->GetFileName()))
	{
		RankSys->LoadRanking(RankSys->GetFileName());
	}
	else
	{
		RankSys->InitArray();
	}
}

Core::~Core()
{
	delete RankSys;
}

void Core::RunGame()
{
	PlayLogoBGM();
	UI::GetInstance()->ShowLogo();

	while (m_bGameLoop)
	{
		CleanScreen();
		ShowMenu();
	}
}

void Core::GameStart()
{
	// Timer setting
	clock_t tStartTime = 0, tEndTime = 0;

	// Create Default Object
	Wall* wall = new Wall();
	wall->Draw();

	// Spawn Enemy
	std::deque<Enemy*> enemies = GetEnemies();

	// Spawn Player
	Player* player = new Player();

	// Start Timer
	tStartTime = clock();

	// Main
	while (1)
	{
		Sleep(GetFPS());

		PlayerAttackLogic(enemies, player);
		EnemyAttackLogic(enemies, player);

		if (PlayerDefeatConditions(player))
		{
			break;
		}

		if (WaveClear(enemies))
		{
			break;
		}
		
		// UI 최신화 때문에 밑에 배치함
		player->Run();
	}

	// Stop Timer
	tEndTime = clock();

	double dbSurvivalTime = double(tEndTime - tStartTime) / CLOCKS_PER_SEC;

	CleanScreen();

	// 랭킹 저장
	if (RankSys->AddRanking(player->GetGameScore(), dbSurvivalTime))
	{
		RankSys->StoreRanking(RankSys->GetFileName());
	}
}

void Core::ShowRanking() const
{
	RankSys->PrintRanking();
}

void Core::GameQuit()
{
	gotoxy(47, 17);
	printf("게임을 종료합니다.\n");
	SetGameLoop(false);

	if (RankSys->IsFileVaild(RankSys->GetFileName()))
	{
		// 파일 저장
		gotoxy(47, 18);
		printf("데이터 저장 중...\n\n");
		RankSys->StoreRanking(RankSys->GetFileName());
	}
	// 그냥 연출임
	Sleep(2000);
}

void Core::ShowMenu()
{
	int GameMode = UI::GetInstance()->SelectMenu();
	PlaySelectModeBGM();
	SelectMode(GameMode);
}

void Core::CleanScreen() const
{
	system("cls");
}

void Core::SelectMode(int GameMode)
{
	switch (GameMode)
	{
	case 1:
	{
		// 게임 시작
		CleanScreen();
		UI::GetInstance()->ShowHowToPlay();
		CleanScreen();
		GameStart();
		break;
	}
	case 2:
	{
		// 랭크 보기
		CleanScreen();
		ShowRanking();
		break;
	}
	case 3:
	{
		// 게임 종료
		GameQuit();
		break;
	}
	default:
	{
		gotoxy(50, 16);
		printf("잘못된 접근입니다. 다시 입력해 주세요.");
		if (_getch())
		{
			return;
		}
		break;
	}
	}
}

void Core::PlayerAttackLogic(std::deque<Enemy*>& enemies, Player* player)
{
	// 플레이어 공격 처리
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Run();

		if (player->IsMissileHit(enemies[i]))
		{
			if (enemies[i]->CheckHP())
			{
				// 남은 적 미사일 삭제
				for (const auto& EnemyMissile : enemies[i]->GetMissile())
				{
					if (enemies[i]->GetMissile().empty())
					{
						break;
					}

					EnemyMissile->Erase();
					enemies[i]->GetMissile().pop_back();
				}

				player->AddScore(DefaultGameScore);

				// 파괴된 객체 삭제를 위해 위치 변경
				Enemy* temp = enemies[i];
				enemies[i] = enemies[enemies.size() - 1];
				enemies[enemies.size() - 1] = temp;
				enemies.pop_back();

				PlayEnemyDestroyBGM();
			}
		}
	}
}

void Core::EnemyAttackLogic(std::deque<Enemy*>& enemies, Player* player)
{
	// 적 공격 처리
	for (const auto& enemy : enemies)
	{
		if (enemy->IsMissileHit(player))
		{
			PlayPlayerDamagedBGM();
		}
	}
}

bool Core::PlayerDefeatConditions(Player* player)
{
	// 플레이어 패배 조건
	if (player->IsOutofRange() || player->IsZeroHP())
	{
		player->PrintCurrentInfo();
		PlayGameOverBGM();
		UI::GetInstance()->ShowGameOver();

		return true;
	}

	return false;
}

bool Core::WaveClear(std::deque<Enemy*>& enemies)
{
	// n차 웨이브가 끝났을 때
	if (enemies.empty())
	{
		enemies = GetEnemies();
		m_nEnemySpawnLimits++;

		// 모든 웨이브가 끝났을 때
		if (m_nEnemySpawnLimits >= m_nEnemySpawnCount)
		{
			// TODO : 여기에 승리 사운드와 UI 배치
			PlayGameWinBGM();
			UI::GetInstance()->ShowGameWin();
			return true;
		}

		return false;
	}

	return false;
}

void Core::PlayLogoBGM() const
{
	// wav 파일을 사용하는데 이건 재생 중 다른 사운드가 겹치면 종료된다.
	// mci 라이브러리를 사용해서 출력하려 하는데 잘 안됨. 나중에 다시 연습해봐야지
	PlaySound(GetLogoSoundPath(), 0, SND_FILENAME | SND_ASYNC);
}

void Core::PlaySelectModeBGM() const
{
	PlaySound(GetSelectModeSoundPath(), 0, SND_FILENAME | SND_ASYNC);
}

void Core::PlayPlayerDamagedBGM() const
{
	PlaySound(GetPlayerDamagedSoundPath(), 0, SND_FILENAME | SND_ASYNC);
}

void Core::PlayEnemyDestroyBGM() const
{
	PlaySound(GetEnemyDestroySoundPath(), 0, SND_FILENAME | SND_ASYNC);
}

void Core::PlayGameWinBGM() const
{
	PlaySound(GetGameWinSoundPath(), 0, SND_FILENAME | SND_ASYNC);
}

void Core::PlayGameOverBGM() const
{
	PlaySound(GetGameOverSoundPath(), 0, SND_FILENAME | SND_ASYNC);
}

std::deque<Enemy*> Core::GetEnemies()
{
	std::deque<Enemy*> enemies;
	for (int i = 0; i < 5; i++)
	{
		int x = (rand() % 39) + 41, y = 10;

		Enemy* enemy = new Enemy(Vector2D(x, y));
		enemy->Draw();
		enemies.push_front(enemy);
	}

	return enemies;
}
