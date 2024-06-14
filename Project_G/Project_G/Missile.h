#pragma once
#include "Object.h"

class Player;

class Missile : public Object
{
private:
	Object* m_Owner;

public:
	Missile();

	void Fire();
	void PlayerUpdate();
	void EnemyUpdate();

	template<typename T>
	void SetOwner() { if(T != nullptr) m_Owner = T; }
};

