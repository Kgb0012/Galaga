#pragma once

/*
* enum class �� ����� int�� ��ȯ
*/
template<typename T>
constexpr int ENUM_TO_INT(T Value) { return static_cast<int>(Value); }

/*
* Ű���尡 ������ �� �ش� Ű ���� ��ȯ
*/
const int GetKeyValue();

// Sound Resource
const wchar_t* GetLogoSoundPath();
const wchar_t* GetSelectModeSoundPath();
const wchar_t* GetMissileSoundPath();
const wchar_t* GetPlayerDamagedSoundPath();
const wchar_t* GetEnemyDestroySoundPath();
const wchar_t* GetGameWinSoundPath();
const wchar_t* GetGameOverSoundPath();