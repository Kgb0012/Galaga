#pragma once
#include "Object.h"

constexpr int MIN_WALL_SIZE_X = 40;
constexpr int MIN_WALL_SIZE_Y = 1;
constexpr int MAX_WALL_SIZE_X = 80;
constexpr int MAX_WALL_SIZE_Y = 29;

class Wall : public Object
{
private:
	Vector2D m_pt2;

public:
	Wall();

	void SetPos(const Vector2D& Pos1, const Vector2D& Pos2);
	void Draw() const;

	virtual void PrintPos() override;
};

