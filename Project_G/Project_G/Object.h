#pragma once

#include "Vector2D.h"
#include <deque>

struct StatComponent
{
	int Health = 0;

	StatComponent(int health)
		: Health(health){}
};

class Object
{
protected:
	Vector2D m_pt;
	char m_shape;

public:
	Object();

	void SetPos(const Vector2D& Pos);
	void SetShape(char shape) { m_shape = shape; }

	Vector2D GetPos() const { return m_pt; }

	virtual void PrintPos();
	virtual void Draw();
	virtual void Erase();

	virtual void FireMissile() {}
	virtual void UpdateMissile() {}

	bool OutofRange() const;
};

void const gotoxy(int x, int y);