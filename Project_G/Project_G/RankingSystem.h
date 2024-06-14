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
		랭킹을 파일에서 읽음
		@param File Name
	*/
	void LoadRanking(const char* strRankingFileName);

	/*
		현재 랭킹 정보를 파일에 저장하는 함수
		@param File Name
	*/
	void StoreRanking(const char* strRankingFileName);

	/*
		현재 랭킹을 화면에 출력
	*/
	void PrintRanking();

	/*
		게임점수(nGameScore)를 확인하여 랭킹을 갱신함
			랭킹에 등록할 수 있는 결과이면 선수 이름을 추가로 입력 받고, 경기 결과를 랭킹에 등록함

		@param GameScore
		@param DurationTime

		@return 배열에 데이터를 성공적으로 삽입 시 1 반환
	*/
	bool AddRanking(int nGameScore, double dbSurvivalTime);

	/*
		파일에 데이터가 없을 시 배열 초기화
	*/
	void InitArray();

	bool IsFileVaild(const char* FileName);

	const char* GetFileName() const { return FileName; }
	
private:
	/*
		PlayerInfos 배열 오름차순 정렬
	*/
	void SortArray();
};