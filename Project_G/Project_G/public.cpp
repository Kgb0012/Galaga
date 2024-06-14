#include "public.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <conio.h>

const int GetKeyValue()
{
	char key = _getch();
	if (key > 0)
	{
		return int(key);
	}
	else
	{
		int key1 = key;
		if (key1 < 0)
		{
			key1 += 256;
		}

		int key2 = _getch();

		// 비트 이동
		return (key2 << 8) + key1;
	}
}

const wchar_t* GetLogoSoundPath()
{
	return L"Resource\\Galaga_Logo_Bgm.wav";
}

const wchar_t* GetSelectModeSoundPath()
{
	return L"Resource\\ButtonClick.wav";
}

const wchar_t* GetMissileSoundPath()
{
	return L"Resource\\MissileSound.wav";
}

const wchar_t* GetPlayerDamagedSoundPath()
{
	return L"Resource\\Player_Hit_Sound.wav";
}

const wchar_t* GetEnemyDestroySoundPath()
{
	return L"Resource\\Enemy_Destroy_Sound.wav";
}

const wchar_t* GetGameWinSoundPath()
{
	return L"Resource\\GameWin_BGM.wav";
}

const wchar_t* GetGameOverSoundPath()
{
	return L"Resource\\GameOver_BGM.wav";
}
