#pragma once

#include <vector>

#include "Common.h"
#include "IEvent.h"
#include "GameState.h"
#include "PlayerState.h"

class CTimelineData
{
public:
	CTimelineData();
	virtual ~CTimelineData();

public:
	CGameState m_clsGameState;
	CPlayerState m_clsPlayerState;
	std::vector<IEvent*> m_aryEvents;
	uint64_t m_timestamp;
	int16_t m_imageWidth;
	int16_t m_imageHeight;
};

