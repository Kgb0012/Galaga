#include "Object.h"

#include <Windows.h>
#include <iostream>

#include "Vector2D.h"

#include "Wall.h"

Object::Object()
	: m_pt(0, 0)
	, m_shape(' ')
{

}

void Object::PrintPos()
{
	m_pt.PrintPos();
}

void Object::Draw()
{
	gotoxy(m_pt.GetX(), m_pt.GetY());
	printf("%c", m_shape);
}

void Object::Erase()
{
	gotoxy(m_pt.GetX(), m_pt.GetY());
	printf(" ");
}

bool Object::OutofRange() const
{
	bool XResult = GetPos().GetX() <= MIN_WALL_SIZE_X || GetPos().GetX() >= MAX_WALL_SIZE_X;
	bool YResult = GetPos().GetY() <= MIN_WALL_SIZE_Y + 1 || GetPos().GetY() >= MAX_WALL_SIZE_Y - 1;

	return (XResult || YResult) ? true : false;
}

void const gotoxy(int x, int y)
{
	COORD pos = { SHORT(x), SHORT(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Object::SetPos(const Vector2D& Pos)
{
	m_pt.SetPos(Pos);
}