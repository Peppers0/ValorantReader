#pragma once

#include "Common.h"

class CPlayerState
{
public:
	CPlayerState();
	virtual ~CPlayerState();

public:
	int8_t 		m_isAlive;
	int8_t 		m_health;
	int8_t 		m_armor;
	int16_t 	m_ammo;
	int16_t 	m_ammoLeft;
	int8_t 		m_hasSpike;
	int16_t 	m_credits;
	int8_t 		m_weaponId;
	int8_t 		m_hitHeadShot;
	int8_t 		m_aryAbilityLeft[MAX_ABILITY];
};

