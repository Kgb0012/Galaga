#include "Enemy.h"

#include "Wall.h"
#include "Player.h"
#include "Missile.h"
#include "Vector2D.h"

int missile_limit = rand() % 4;

Enemy::Enemy()
	: m_MonStat{ 100}
	, m_MoveCount(0)
	, m_nPattern(0)
{
	int InitPos_X = (MIN_WALL_SIZE_X + MAX_WALL_SIZE_X) / 2;
	int InitPos_Y = (MIN_WALL_SIZE_Y + MAX_WALL_SIZE_Y) / 2 - 10;
	SetPos(Vector2D(InitPos_X, InitPos_Y));
	SetShape('A');
}

Enemy::Enemy(Vector2D Pos)
	: m_MonStat{ 100 }
	, m_MoveCount(0)
	, m_nPattern(0)
{
	SetPos(Pos);
	SetShape('W');
}

void Enemy::Run()
{
	Move();

	if (!Enemymissiles.empty())
	{
		UpdateMissile();
	}
}

void Enemy::DecreaseHP()
{
	m_MonStat.Health -= 50;
}

void Enemy::Move()
{
	Erase();
	Logic();
	Draw();
}

void Enemy::Logic()
{
	// 랜덤성을 주기 위해 무작위로 배치함
	m_nPattern = rand() % 10;
	switch (m_nPattern)
	{
	case 3:
	{
		Pattern1();
		break;
	}
	case 7:
	{
		Pattern2();
		break;
	}
	default:
		break;
	}
}

void Enemy::FireMissile()
{
	Missile* missile = new Missile();
	Vector2D InitMissilePos = Vector2D(this->GetPos().GetX(), this->GetPos().GetY() + 1);
	missile->SetPos(InitMissilePos);
	missile->SetShape('|');
	missile->Draw();

	Enemymissiles.push_front(missile);
}

void Enemy::UpdateMissile()
{
	for (const auto& missile : Enemymissiles)
	{
		missile->EnemyUpdate();
	}

	for (int i = 0; i < Enemymissiles.size(); i++)
	{
		if (Enemymissiles[i]->OutofRange())
		{
			int end = int(Enemymissiles.size()) - 1;

			Missile* temp = Enemymissiles[end];
			Enemymissiles[end] = Enemymissiles[i];
			Enemymissiles[i] = temp;

			Enemymissiles[end]->Erase();
			Enemymissiles.pop_back();
		}
	}
}

bool Enemy::CheckHP()
{
	return m_MonStat.Health == 0 ? true : false;
}

bool Enemy::IsMissileHit(Player* player)
{
	for (int i = 0; i < Enemymissiles.size(); i++)
	{
		if (Enemymissiles[i]->GetPos().GetX() == player->GetPos().GetX()
			&& Enemymissiles[i]->GetPos().GetY() == player->GetPos().GetY())
		{
			int size = int(Enemymissiles.size()) - 1;

			Missile* temp = Enemymissiles[i];
			Enemymissiles[i] = Enemymissiles[size];
			Enemymissiles[size] = temp;

			player->DecreaseHP();
			Enemymissiles[size]->Erase();
			Enemymissiles.pop_back();

			return true;
		}
	}

	return false;
}

void Enemy::Pattern1()
{
	switch (m_MoveCount)
	{
	case 0:
	{
		if (m_pt.GetX() - 2 <= MIN_WALL_SIZE_X)
		{
			return;
		}
		else
		{
			m_pt.MovePos(Vector2D(-2, 0));
		}

		m_MoveCount++;
		break;
	}
	case 1:
	{
		if (m_pt.GetX() + 2 >= MAX_WALL_SIZE_X)
		{
			return;
		}
		else
		{
			m_pt.MovePos(Vector2D(2, 0));
		}

		m_MoveCount--;
		break;
	}
	}
}

void Enemy::Pattern2()
{
	FireMissile();
}