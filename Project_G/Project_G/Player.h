#pragma once
#include "Object.h"

class Vector2D;
class Missile;
class Enemy;

enum class EDirection : int
{
	LEFT,
	RIGHT,
	UP,
	NONE
};

enum class KEY
{
	IK_LEFT = 19424,
	IK_RIGHT = 19936,
	IK_UP = 18656,
	IK_SPACE = 32
};

class Player : public Object
{
private:
	int m_kbValue;
	int m_nGameScore;

	bool bIsFire;
	bool bIsOutofRange;

	EDirection m_dir;

	std::deque<Missile*> missiles;

	StatComponent PlayerStat;

public:
	Player();

	void Run();

	int GetGameScore() const { return m_nGameScore; }
	void AddScore(int score) { m_nGameScore += score; }

	bool IsOutofRange() const { return bIsOutofRange; }
	void SetIsOutofRange(bool bOut) { bIsOutofRange = bOut; }

	bool IsMissileHit(Enemy* enemy);
	bool IsZeroHP() const;
	void DecreaseHP();

	void PrintCurrentInfo() const;

private:
	void Move();
	void Logic(EDirection Newdir);
	void Input();

	virtual void FireMissile() override;
	virtual void UpdateMissile() override;

	void PlayMissileSound() const;

	bool IsFire() const { return bIsFire; }
	void SetIsFire(bool bFire) { bIsFire = bFire; }

	void SetKBValue(int kb) { m_kbValue = kb; }
	int GetKBValue() const { return m_kbValue; }

	void SetDir(EDirection dir) { m_dir = dir; }
	EDirection GetDir() const { return m_dir; }
};