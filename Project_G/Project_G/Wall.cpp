#include "Wall.h"

#include <iostream>

Wall::Wall()
	: m_pt2(0, 0)
{
	SetPos(Vector2D(MIN_WALL_SIZE_X, MIN_WALL_SIZE_Y), Vector2D(MAX_WALL_SIZE_X, MAX_WALL_SIZE_Y));
	SetShape('=');
}

void Wall::SetPos(const Vector2D& Pos1, const Vector2D& Pos2)
{
	m_pt = Pos1;
	m_pt2 = Pos2;
}

void Wall::Draw() const
{
	// Draw X Pos
	for (int x = m_pt.GetX(); x <= m_pt2.GetX(); x++)
	{
		int y = m_pt.GetY();
		gotoxy(x, y);
		printf("%c", m_shape);

		y = m_pt2.GetY();
		gotoxy(x, y);
		printf("%c", m_shape);
	}

	// Draw Y Pos
	for (int y = m_pt.GetY() + 1; y <= m_pt2.GetY(); y++)
	{
		int x = m_pt.GetX();
		gotoxy(x, y);
		printf("%c", m_shape);

		x = m_pt2.GetX();
		gotoxy(x, y);
		printf("%c", m_shape);
	}
}

void Wall::PrintPos()
{
	gotoxy(0, 20);
	printf("( %d, %d ), ( %d, %d )"
		, m_pt.GetX(), m_pt.GetY(), m_pt2.GetX(), m_pt2.GetY());
}
