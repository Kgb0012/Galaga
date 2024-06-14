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

	// 파일 읽기 모드 오픈
	fopen_s(&fp, strRankingFileName, "r");

	if (fp != nullptr)
	{
		// 파일 내용을 배열에 저장
		for (int i = 0; i < PlayerInfo_Num; i++)
		{
			fscanf_s(fp, "%s %d %lf", PlayerInfos[i].cName, unsigned int(sizeof(PlayerInfos[i].cName)), &PlayerInfos[i].nScore, &PlayerInfos[i].dbTime);
		}

		fclose(fp);
	}

	// 마아아아안약 받은 데이터에 오류가 있을 때 실행
	if (PlayerInfos[0].cName == nullptr)
	{
		printf("\n\nError : 플레이어 랭킹 정보 오류. 랭킹을 초기화 합니다.\n\n");
		InitArray();
	}

	// 데이터 정렬
	SortArray();
}

void RankingSystem::StoreRanking(const char* strRankingFileName)
{
	// 일단 정렬하고
	SortArray();

	FILE* fp = nullptr;

	// 파일 쓰기 모드로 오픈
	fopen_s(&fp, strRankingFileName, "w");

	if (fp != nullptr)
	{
		// 배열 내용 파일에 저장
		for (int i = 0; i < PlayerInfo_Num; i++)
		{
			fprintf_s(fp, "%s %d %lf\n", PlayerInfos[i].cName, PlayerInfos[i].nScore, PlayerInfos[i].dbTime);
		}

		fclose(fp);
	}
	// 파일이 열린채로 종료됐거나 존재하지 않는다면 실행
	else
	{
		printf("\n\nError : 파일(명)이 존재하지 않습니다.\n\n");
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
		printf("[%d위] %s  %d  %3.3lf", i + 1, PlayerInfos[i].cName, PlayerInfos[i].nScore, PlayerInfos[i].dbTime);
		i++, j++;
	}

	gotoxy(40, j + 2);
	printf("메인 메뉴로 돌아가려면 아무 키나 눌러주세요.\n");

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
		printf("최종 점수가 0점 입니다. 랭킹에 등록할 수  없습니다.");
		gotoxy(42, 15);
		printf("아무 키나 눌러 메인 메뉴로 돌아가십시오.");
		
		if (_getch())
		{
			return false;
		}
	}

	// 점수가 배열의 끝 인덱스의 점수보다 클때
	if (nGameScore > PlayerInfos[PlayerInfo_Num - 1].nScore)
	{
		int i = PlayerInfo_Num - 1;

		for (; i >= 0; i--)
		{
			// 반복 중 현재 점수가 배열의 i - 1보다 크거나 같다면
			if (nGameScore >= PlayerInfos[i - 1].nScore)
			{
				break;
			}

			// 배열의 i - 1번째와 교체
			PlayerInfos[i - 1] = PlayerInfos[i];
		}

		// 데이터 배열에 삽입
		PlayerInfos[i].nScore = nGameScore;
		PlayerInfos[i].dbTime = dbSurvivalTime;

		// 이름 받기
		gotoxy(40, 15);
		printf("랭킹에 등록할 이름을 입력하세요.");
		gotoxy(40, 16);
		printf("이름 입력 : ");
		scanf_s("%s", PlayerInfos[i].cName, MaxNameIndex);

		return true;
	}
	else
	{
		int i = PlayerInfo_Num - 1;

		// 배열의 끝에 데이터 삽입
		PlayerInfos[i].nScore = nGameScore;
		PlayerInfos[i].dbTime = dbSurvivalTime;

		// 이름 받기
		printf("이름 입력 : ");
		scanf_s("%s", PlayerInfos[i].cName, MaxNameIndex);

		SortArray();

		return true;
	}

	SortArray();
	return false;
}

void RankingSystem::SortArray()
{
	// 배열 데이터 오름차순 정렬
	for (int i = PlayerInfo_Num - 1; i > 0; i--)
	{
		if (PlayerInfos[i - 1].cName == NULL ||
			(PlayerInfos[i - 1].dbTime == 0.00000000 && PlayerInfos[i - 1].nScore == 0))
		{
			// 임시 객체로 순서 바꾸기
			FPlayerInfo temp = PlayerInfos[i - 1];
			PlayerInfos[i - 1] = PlayerInfos[i];
			PlayerInfos[i] = temp;
		}

		if (PlayerInfos[i].nScore > PlayerInfos[i - 1].nScore)
		{
			// 점수 기준 정렬
			if (PlayerInfos[i].nScore < PlayerInfos[i - 1].nScore)
			{
				break;
			}

			// 임시 객체로 순서 바꾸기
			FPlayerInfo temp = PlayerInfos[i - 1];
			PlayerInfos[i - 1] = PlayerInfos[i];
			PlayerInfos[i] = temp;
		}

		// 점수가 i 번 점수와 i - 1번 점수가 같다면 
		if (PlayerInfos[i].nScore == PlayerInfos[i - 1].nScore)
		{
			// 소요 시간 기준 정렬
			if (PlayerInfos[i].dbTime < PlayerInfos[i - 1].dbTime)
			{
				// 임시 객체로 순서 바꾸기
				FPlayerInfo temp = PlayerInfos[i - 1];
				PlayerInfos[i - 1] = PlayerInfos[i];
				PlayerInfos[i] = temp;
			}
		}
	}
}

void RankingSystem::InitArray()
{
	// 임시 객체
	FPlayerInfo temp = { "...", 0, 0.0 };

	// 배열 정보 초기화
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
