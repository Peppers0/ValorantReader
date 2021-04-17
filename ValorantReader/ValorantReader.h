#pragma once

#include "TimelineData.h"
#include "GameCapture.h"
#include "ParserEngine.h"
#include "EventBuilder.h"

class CValorantReader : CWinThread
{
public:
	CValorantReader();
	virtual ~CValorantReader();

	BOOL InitInstance(); // Create Instances using as new or malloc
	BOOL Initialize(); // Reset values such as EventType
	BOOL ExitInstance();

	static int Run(LPVOID lParam); // A threaded function that loops pipeline inside

	BOOL pipeline(); // A single function loop to capture a frame,
					 // to recognize the frame and to output it.

	BOOL exportCurrent(CTimelineData& out);
	BOOL exportAll(std::vector<CTimelineData>& outArray);

public:
	std::vector<CTimelineData> m_aryTimelineData;
	CTimelineData m_currSlice;

	PBYTE m_pImgBuffer;

private: // The following instances can be non-pointer
	CGameCapture* m_pGameCapturer;
	CParserEngine* m_pEngine;
	CEventBuilder* m_pEventBuilder;
};

