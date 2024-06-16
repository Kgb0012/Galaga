#pragma once
#include <deque>

class RankingSystem;
class Enemy;
class Player;

class Core
{
private:
	int m_nFPS;
	int m_nEnemySpawnCount;
	int m_nEnemySpawnLimits;
	
	bool m_bGameLoop;

	RankingSystem* RankSys;

public:
	Core();
	~Core();

	void RunGame();

private:
	void GameStart();
	void ShowRanking() const;
	void GameQuit();

	void ShowMenu();

	void CleanScreen() const;
	void SelectMode(int GameMode);

	void PlayerAttackLogic(std::deque<Enemy*>& enemies, Player* player);
	void EnemyAttackLogic(std::deque<Enemy*>& enemies, Player* player);
	bool PlayerDefeatConditions(Player* player);
	bool WaveClear(std::deque<Enemy*>& enemies);

	void PlayLogoBGM() const;
	void PlaySelectModeBGM() const;
	void PlayPlayerDamagedBGM() const;
	void PlayEnemyDestroyBGM() const;
	void PlayGameWinBGM() const;
	void PlayGameOverBGM() const;

	void SetGameLoop(bool GameLoop) { m_bGameLoop = GameLoop; }

	int GetFPS() const { return m_nFPS; }
	class std::deque<Enemy*> GetEnemies();
};