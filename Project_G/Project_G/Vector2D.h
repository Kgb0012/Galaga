#pragma once

class Vector2D
{
	int m_x = 0;
	int m_y = 0;

public:
	Vector2D() = default;
	Vector2D(int x, int y) : m_x(x), m_y(y) {}
	Vector2D(const Vector2D& Pos) { SetPos(Pos); }

	inline void SetPos(const Vector2D& Pos) { m_x = Pos.m_x, m_y = Pos.m_y; }
	inline void MovePos(const Vector2D& Pos) { MovePos(Pos.GetX(), Pos.GetY()); }
	void PrintPos() const;

	inline int GetX() const { return m_x; }
	inline int GetY() const { return m_y; }

	bool const operator==(Vector2D Pos);

private:
	void MovePos(int x, int y) { m_x += x, m_y += y; }
};