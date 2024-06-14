#include "RankingSystem.h"

#include "Object.h"

#include <iostream>
#include <conio.h>

const char* RankingSystem::FileName = "Galaga_User_Ranking.txt";

RankingSystem::RankingSystem()
	: MaxNameIndex(20)
	, PlayerInfos{}
{
	LoadRanking(FileName);

	if (IsFileVaild(FileName))
	{
		InitArray();
	}

	SortArray();
}

void RankingSystem::LoadRanking(const char* strRankingFileName)
{
	FILE* fp = nullptr;

	// ���� �б� ��� ����
	fopen_s(&fp, strRankingFileName, "r");

	if (fp != nullptr)
	{
		// ���� ������ �迭�� ����
		for (int i = 0; i < PlayerInfo_Num; i++)
		{
			fscanf_s(fp, "%s %d %lf", PlayerInfos[i].cName, unsigned int(sizeof(PlayerInfos[i].cName)), &PlayerInfos[i].nScore, &PlayerInfos[i].dbTime);
		}

		fclose(fp);
	}

	// ���ƾƾƾȾ� ���� �����Ϳ� ������ ���� �� ����
	if (PlayerInfos[0].cName == nullptr)
	{
		printf("\n\nError : �÷��̾� ��ŷ ���� ����. ��ŷ�� �ʱ�ȭ �մϴ�.\n\n");
		InitArray();
	}

	// ������ ����
	SortArray();
}

void RankingSystem::StoreRanking(const char* strRankingFileName)
{
	// �ϴ� �����ϰ�
	SortArray();

	FILE* fp = nullptr;

	// ���� ���� ���� ����
	fopen_s(&fp, strRankingFileName, "w");

	if (fp != nullptr)
	{
		// �迭 ���� ���Ͽ� ����
		for (int i = 0; i < PlayerInfo_Num; i++)
		{
			fprintf_s(fp, "%s %d %lf\n", PlayerInfos[i].cName, PlayerInfos[i].nScore, PlayerInfos[i].dbTime);
		}

		fclose(fp);
	}
	// ������ ����ä�� ����ưų� �������� �ʴ´ٸ� ����
	else
	{
		printf("\n\nError : ����(��)�� �������� �ʽ��ϴ�.\n\n");
	}
}

void RankingSystem::PrintRanking()
{
	SortArray();

	int i = 0, j = i + 13;

	gotoxy(50, 10);
	printf("[ User Ranking ]");

	// for range loop
	for (const FPlayerInfo& playerinfos : PlayerInfos)
	{
		gotoxy(45, j);
		printf("[%d��] %s  %d  %3.3lf", i + 1, PlayerInfos[i].cName, PlayerInfos[i].nScore, PlayerInfos[i].dbTime);
		i++, j++;
	}

	gotoxy(40, j + 2);
	printf("���� �޴��� ���ư����� �ƹ� Ű�� �����ּ���.\n");

	if (_getch())
	{
		system("cls");
		return;
	}
}

bool RankingSystem::AddRanking(int nGameScore, double dbSurvivalTime)
{
	if (nGameScore == 0)
	{
		gotoxy(37, 14);
		printf("���� ������ 0�� �Դϴ�. ��ŷ�� ����� ��  �����ϴ�.");
		gotoxy(42, 15);
		printf("�ƹ� Ű�� ���� ���� �޴��� ���ư��ʽÿ�.");
		
		if (_getch())
		{
			return false;
		}
	}

	// ������ �迭�� �� �ε����� �������� Ŭ��
	if (nGameScore > PlayerInfos[PlayerInfo_Num - 1].nScore)
	{
		int i = PlayerInfo_Num - 1;

		for (; i >= 0; i--)
		{
			// �ݺ� �� ���� ������ �迭�� i - 1���� ũ�ų� ���ٸ�
			if (nGameScore >= PlayerInfos[i - 1].nScore)
			{
				break;
			}

			// �迭�� i - 1��°�� ��ü
			PlayerInfos[i - 1] = PlayerInfos[i];
		}

		// ������ �迭�� ����
		PlayerInfos[i].nScore = nGameScore;
		PlayerInfos[i].dbTime = dbSurvivalTime;

		// �̸� �ޱ�
		gotoxy(40, 15);
		printf("��ŷ�� ����� �̸��� �Է��ϼ���.");
		gotoxy(40, 16);
		printf("�̸� �Է� : ");
		scanf_s("%s", PlayerInfos[i].cName, MaxNameIndex);

		return true;
	}
	else
	{
		int i = PlayerInfo_Num - 1;

		// �迭�� ���� ������ ����
		PlayerInfos[i].nScore = nGameScore;
		PlayerInfos[i].dbTime = dbSurvivalTime;

		// �̸� �ޱ�
		printf("�̸� �Է� : ");
		scanf_s("%s", PlayerInfos[i].cName, MaxNameIndex);

		SortArray();

		return true;
	}

	SortArray();
	return false;
}

void RankingSystem::SortArray()
{
	// �迭 ������ �������� ����
	for (int i = PlayerInfo_Num - 1; i > 0; i--)
	{
		if (PlayerInfos[i - 1].cName == NULL ||
			(PlayerInfos[i - 1].dbTime == 0.00000000 && PlayerInfos[i - 1].nScore == 0))
		{
			// �ӽ� ��ü�� ���� �ٲٱ�
			FPlayerInfo temp = PlayerInfos[i - 1];
			PlayerInfos[i - 1] = PlayerInfos[i];
			PlayerInfos[i] = temp;
		}

		if (PlayerInfos[i].nScore > PlayerInfos[i - 1].nScore)
		{
			// ���� ���� ����
			if (PlayerInfos[i].nScore < PlayerInfos[i - 1].nScore)
			{
				break;
			}

			// �ӽ� ��ü�� ���� �ٲٱ�
			FPlayerInfo temp = PlayerInfos[i - 1];
			PlayerInfos[i - 1] = PlayerInfos[i];
			PlayerInfos[i] = temp;
		}

		// ������ i �� ������ i - 1�� ������ ���ٸ� 
		if (PlayerInfos[i].nScore == PlayerInfos[i - 1].nScore)
		{
			// �ҿ� �ð� ���� ����
			if (PlayerInfos[i].dbTime < PlayerInfos[i - 1].dbTime)
			{
				// �ӽ� ��ü�� ���� �ٲٱ�
				FPlayerInfo temp = PlayerInfos[i - 1];
				PlayerInfos[i - 1] = PlayerInfos[i];
				PlayerInfos[i] = temp;
			}
		}
	}
}

void RankingSystem::InitArray()
{
	// �ӽ� ��ü
	FPlayerInfo temp = { "...", 0, 0.0 };

	// �迭 ���� �ʱ�ȭ
	for (int i = 0; i < PlayerInfo_Num; i++)
	{
		PlayerInfos[i] = temp;
	}
}

bool RankingSystem::IsFileVaild(const char* FileName)
{
	FILE* file = nullptr;

	fopen_s(&file, FileName, "r");
	if (file != nullptr)
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}
