#pragma once

#include <string>

#define SETTING_INI _T(".\\set.ini")
#define POS_INI (".\\pos.ini")

#define MATCH_ERROR -2
#define INVALID -1
#define MASK_LEN 1600

#define MAX_ABILITY 4

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif // !MAX

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif // !MIN

#define N_AGENTS 20
#define N_MAPAGENTS 28

enum EventType
{
	kEventNone = 0,

	kEventAbilityCast,
	kEventAmmoReload,
	kEventEnemyAppeared,
	kEventEnemyKill,
	kEventAllyDeath,
	kEventYouKilled,
	kEventShoot,

	kEventCount
};

static char				g_szBuffer[0x20000];
static wchar_t			g_wszMyOutputLog[0x20000];

static void G_OutputDebugStringA(const char* lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);
	int nBuf;
	nBuf = _vsnprintf_s(g_szBuffer, sizeof(g_szBuffer), lpszFormat, args);
	va_end(args);

	::OutputDebugStringA(g_szBuffer);
}

static void G_OutputDebugStringW(const WCHAR* lEndPtrFormat, ...)
{
	va_list args;
	va_start(args, lEndPtrFormat);
	int nBuf;
	nBuf = _vsnwprintf_s(g_wszMyOutputLog, sizeof(g_wszMyOutputLog), lEndPtrFormat, args);
	va_end(args);
	::OutputDebugStringW(g_wszMyOutputLog);
}

#define GLogA	G_OutputDebugStringA
#define GLogW	G_OutputDebugStringW