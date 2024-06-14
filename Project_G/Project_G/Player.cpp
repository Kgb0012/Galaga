#include "Player.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>

#include "public.h"
#include "Wall.h"
#include "Missile.h"
#include "Enemy.h"
#include "Vector2D.h"

#include <conio.h>

Player::Player()
	: m_kbValue(0)
	, m_nGameScore(0)
	, m_dir(EDirection::NONE)
	, bIsFire(false)
	, bIsOutofRange(false)
	, PlayerStat{100}
{
	int InitXPos = (MIN_WALL_SIZE_X + MAX_WALL_SIZE_X) / 2;
	SetPos(Vector2D(InitXPos, 25));
	SetShape('^');
	Draw();
}

void Player::Run()
{
	Input();
	Move();
	UpdateMissile();

	PrintCurrentInfo();
}

bool Player::IsMissileHit(Enemy* enemy)
{
	bool bResult = false;

	// range for loop에 문제가 생길거 같아 그때를 대비해서 주석 처리 ( 재사용 예정 )
	/*for (int i = 0; i < missiles.size(); i++)
	{
		if (missiles[i]->GetPos().GetX() == enemy->GetPos().GetX()
			&& missiles[i]->GetPos().GetY() == enemy->GetPos().GetY())
		{
			missiles[i]->Erase();
			bResult = true;
		}
	}*/

	for (const auto& missile : missiles)
	{
		if (missile->GetPos().GetX() == enemy->GetPos().GetX()
			&& missile->GetPos().GetY() == enemy->GetPos().GetY())
		{
			missile->Erase();
			enemy->DecreaseHP();
			bResult = true;
		}
	}
	
	return bResult;
}

bool Player::IsZeroHP() const
{
	return PlayerStat.Health == 0 ? true : false;
}

void Player::DecreaseHP()
{
	PlayerStat.Health -= 10;
}

void Player::Move()
{
	Erase();
	Logic(m_dir);
	Draw();
}

void Player::Input()
{
	// On keyboard down event
	if (_kbhit())
	{
		SetKBValue(GetKeyValue());
		EDirection currentDir = EDirection::NONE;

		switch (GetKBValue())
		{
		case 'a': case ENUM_TO_INT(KEY::IK_LEFT):
		{
			currentDir = EDirection::LEFT;
			break;
		}
		case 'd': case ENUM_TO_INT(KEY::IK_RIGHT):
		{
			currentDir = EDirection::RIGHT;
			break;
		}
		case 'w': case ENUM_TO_INT(KEY::IK_UP):
		{
			currentDir = EDirection::UP;
			break;
		}
		case ENUM_TO_INT(KEY::IK_SPACE):
		{
			FireMissile();
			SetIsFire(true);
			break;
		}
		default:
			break;
		}

		if (currentDir != EDirection::NONE)
		{
			SetDir(currentDir);
		}
	}
}

void Player::PrintCurrentInfo() const
{
	// GameScore
	gotoxy(23, 6);
	printf("Score : %d", m_nGameScore);

	// Stat
	gotoxy(23, 7);
	printf("HP    : %3d", PlayerStat.Health);
}

void Player::FireMissile()
{
	Missile* missile = new Missile();
	Vector2D InitMissilePos = Vector2D(this->GetPos().GetX(), this->GetPos().GetY() - 1);
	missile->SetPos(InitMissilePos);
	missile->SetShape('|');
	missile->Draw();
	PlayMissileSound();

	missiles.push_front(missile);
}

void Player::UpdateMissile()
{
	if (IsFire())
	{
		for (const auto& missile : missiles)
		{
			missile->PlayerUpdate();
		}

		for (int i = 0; i < missiles.size(); i++)
		{
			if (missiles[i]->OutofRange())
			{
				missiles[i]->Erase();
				missiles.pop_back();
			}
		}
	}

	if (missiles.empty())
	{
		SetIsFire(false);
		return;
	}
}

void Player::PlayMissileSound() const
{
	PlaySound(GetMissileSoundPath(), 0, SND_FILENAME | SND_ASYNC);
}

void Player::Logic(EDirection Newdir)
{
	switch (GetDir())
	{
	case EDirection::LEFT:
	{
		m_pt.MovePos(Vector2D(-1, 0));
		SetShape('<');
		break;
	}
	case EDirection::RIGHT:
	{
		m_pt.MovePos(Vector2D(1, 0));
		SetShape('>');
		break;
	}
	case EDirection::UP:
	{
		m_pt.MovePos(Vector2D(0, 0));
		SetShape('^');
		break;
	}
	default:
		break;
	}

	if (this->OutofRange())
	{
		SetIsOutofRange(true);
	}
}
