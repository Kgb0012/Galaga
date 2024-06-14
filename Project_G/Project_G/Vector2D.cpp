#include "Vector2D.h"
#include <iostream>

void Vector2D::PrintPos() const
{
	printf("(%d, %d)\n", m_x, m_y);
}

bool const Vector2D::operator==(Vector2D Pos)
{
	return ((m_x == Pos.m_x) && (m_y == Pos.m_y)) ? true : false;
}