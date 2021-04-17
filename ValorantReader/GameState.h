#pragma once

#include "Common.h"

#include <vector>
#include <string>

class CGameState
{
public:
	CGameState();
	virtual ~CGameState();

public:
	int8_t m_round;
	int8_t m_roundTime;
	int8_t m_yourTeamScore;
	int8_t m_enemyTeamScore;
	std::vector<std::string> m_aryYourAgents;
	std::vector<std::string> m_aryEnemyAgents;

	std::vector<EnemyRect> m_enemyList;
	std::vector<EnemyRect> m_mapEnemyList;
};

