#pragma once

/*
* enum class 의 상수를 int로 반환
*/
template<typename T>
constexpr int ENUM_TO_INT(T Value) { return static_cast<int>(Value); }

/*
* 키보드가 눌렸을 때 해당 키 값을 반환
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