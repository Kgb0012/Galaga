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

	int nEnemySpawnLimits = 0;

	// Create Default Object
	Wall* wall = new Wall();
	wall->Draw();

	// Spawn Enemy
	std::deque<Enemy*> enemies = GetEnemies();

	Player* player = new Player();

	// Start Timer
	tStartTime = clock();

	// Main
	while (1)
	{
		Sleep(GetFPS());

		// �÷��̾� ���� ó��
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Run();

			if (player->IsMissileHit(enemies[i]))
			{
				if (enemies[i]->CheckHP())
				{
					// ���� �� �̻��� ����
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

					// �ı��� ��ü ������ ���� ��ġ ����
					Enemy* temp = enemies[i];
					enemies[i] = enemies[enemies.size() - 1];
					enemies[enemies.size() - 1] = temp;
					enemies.pop_back();

					PlayEnemyDestroyBGM();
				}
			}
		}
		
		// �� ���� ó��
		for (const auto& enemy : enemies)
		{
			if (enemy->IsMissileHit(player))
			{
				PlayPlayerDamagedBGM();
			}
		}

		// �÷��̾� �й� ����
		if (player->IsOutofRange() || player->IsZeroHP())
		{
			player->PrintCurrentInfo();
			PlayGameOverBGM();
			UI::GetInstance()->ShowGameOver();
			break;
		}

		// n�� ���̺갡 ������ ��
		if (enemies.empty())
		{
			enemies = GetEnemies();
			nEnemySpawnLimits++;

			// ��� ���̺갡 ������ ��
			if (nEnemySpawnLimits >= m_nEnemySpawnCount)
			{
				// TODO : ���⿡ �¸� ����� UI ��ġ
				PlayGameWinBGM();
				UI::GetInstance()->ShowGameWin();
				break;
			}
		}
		
		// UI �ֽ�ȭ ������ �ؿ� ��ġ��
		player->Run();
	}

	// Stop Timer
	tEndTime = clock();

	double dbSurvivalTime = double(tEndTime - tStartTime) / CLOCKS_PER_SEC;

	CleanScreen();

	// ��ŷ ����
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
	printf("������ �����մϴ�.\n");
	SetGameLoop(false);

	if (RankSys->IsFileVaild(RankSys->GetFileName()))
	{
		// ���� ����
		gotoxy(47, 18);
		printf("������ ���� ��...\n\n");
		RankSys->StoreRanking(RankSys->GetFileName());
	}
	// �׳� ������
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
		// ���� ����
		CleanScreen();
		UI::GetInstance()->ShowHowToPlay();
		CleanScreen();
		GameStart();
		break;
	}
	case 2:
	{
		// ��ũ ����
		CleanScreen();
		ShowRanking();
		break;
	}
	case 3:
	{
		// ���� ����
		GameQuit();
		break;
	}
	default:
	{
		gotoxy(50, 16);
		printf("�߸��� �����Դϴ�. �ٽ� �Է��� �ּ���.");
		if (_getch())
		{
			return;
		}
		break;
	}
	}
}

void Core::PlayLogoBGM() const
{
	// wav ������ ����ϴµ� �̰� ��� �� �ٸ� ���尡 ��ġ�� ����ȴ�.
	// mci ���̺귯���� ����ؼ� ����Ϸ� �ϴµ� �� �ȵ�. ���߿� �ٽ� �����غ�����
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
