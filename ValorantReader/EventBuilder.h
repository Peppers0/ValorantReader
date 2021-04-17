#pragma once

#include "TimelineData.h"

#include <string>

class CEventBuilder
{
public:
	CEventBuilder();
	virtual ~CEventBuilder();

	CTimelineData build(CTimelineData* pCurrSlice, std::vector<CTimelineData>& aryTimelineData);

private:
	void buildAbiltyCastEvent(CTimelineData* pCurrSlice, CTimelineData* pPrevSlice);
	void buildAmmoReloadEvent(CTimelineData* pCurrSlice, CTimelineData* pPrevSlice);
	void buildKillEvent(CTimelineData* pCurrSlice, CTimelineData* pPrevSlice);
	void buildDeathEvent(CTimelineData* pCurrSlice, CTimelineData* pPrevSlice);
	void buildEnemyAppearedEvent(CTimelineData* pCurrSlice, CTimelineData* pPrevSlice);
	void buildShootEventFromAmmo(CTimelineData* pCurrSlice, CTimelineData* pPrevSlice);
	void buidShootEventFromEtc(CTimelineData* pCurrSlice, CTimelineData* pPrevSlice);

public:

private:
	int32_t m_tStartTickCount;
	int32_t m_tTickCount;
	int32_t m_tShoot;
	int32_t m_tEnemyAppear;
	int32_t m_tChangeTargetShootDely;
	std::string m_killedEnemy;
};

