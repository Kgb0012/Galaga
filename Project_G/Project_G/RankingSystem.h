#pragma once

constexpr int PlayerInfo_Num = 5;

/*
	Save PlayerInfo in this structure
*/
struct FPlayerInfo
{
	char cName[20];
	int nScore;
	double dbTime;
};

class RankingSystem
{
private:
	int MaxNameIndex;
	static const char* FileName;
	FPlayerInfo PlayerInfos[PlayerInfo_Num];

public:
	RankingSystem();

	/*
		��ŷ�� ���Ͽ��� ����
		@param File Name
	*/
	void LoadRanking(const char* strRankingFileName);

	/*
		���� ��ŷ ������ ���Ͽ� �����ϴ� �Լ�
		@param File Name
	*/
	void StoreRanking(const char* strRankingFileName);

	/*
		���� ��ŷ�� ȭ�鿡 ���
	*/
	void PrintRanking();

	/*
		��������(nGameScore)�� Ȯ���Ͽ� ��ŷ�� ������
			��ŷ�� ����� �� �ִ� ����̸� ���� �̸��� �߰��� �Է� �ް�, ��� ����� ��ŷ�� �����

		@param GameScore
		@param DurationTime

		@return �迭�� �����͸� ���������� ���� �� 1 ��ȯ
	*/
	bool AddRanking(int nGameScore, double dbSurvivalTime);

	/*
		���Ͽ� �����Ͱ� ���� �� �迭 �ʱ�ȭ
	*/
	void InitArray();

	bool IsFileVaild(const char* FileName);

	const char* GetFileName() const { return FileName; }
	
private:
	/*
		PlayerInfos �迭 �������� ����
	*/
	void SortArray();
};