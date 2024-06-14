#pragma once
#include "Object.h"

class Missile;
class Player;

class Enemy : public Object
{
private:
	int m_MoveCount;
	int m_nPattern;

	std::deque<Missile*> Enemymissiles;

	StatComponent m_MonStat;

public:
	Enemy();
	Enemy(Vector2D Pos);

	std::deque<Missile*> GetMissile() const { return Enemymissiles; }

	void Run();

	void DecreaseHP();
	bool CheckHP();

	bool IsMissileHit(Player* player);

private:
	void Move();
	void Logic();

	virtual void FireMissile() override;
	virtual void UpdateMissile() override;

	void Pattern1();
	void Pattern2();
};