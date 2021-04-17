#include "pch.h"
#include "TimelineData.h"

CTimelineData::CTimelineData()
{
}

CTimelineData::~CTimelineData()
{
	std::vector<IEvent*>::iterator iter;

	for (iter = m_aryEvents.begin(); iter != m_aryEvents.end(); iter++)
	{
		if ((*iter))
			delete (*iter);
	}
}
