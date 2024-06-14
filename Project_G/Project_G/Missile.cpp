#include "Missile.h"
#include "Vector2D.h"

Missile::Missile()
	: m_Owner(nullptr)
{
}

void Missile::Fire()
{
	Draw();
}

void Missile::PlayerUpdate()
{
	Erase();
	Vector2D updatePos = Vector2D(GetPos().GetX(), GetPos().GetY() - 1);
	this->SetPos(updatePos);
	Draw();
}

void Missile::EnemyUpdate()
{
	Erase();
	Vector2D updatePos = Vector2D(GetPos().GetX(), GetPos().GetY() + 1);
	this->SetPos(updatePos);
	Draw();
}
