#include "pch.h"
#include "ParserEngine.h"


CParserEngine::CParserEngine()
	: m_nImageWidth(0)
	, m_nImageHeight (0)
	, m_pImageBufferPtr (nullptr)
{
	ZeroMemory(m_PtnScore, sizeof(WHITE_PATTERN) * 10);
	ZeroMemory(m_PtnTime, sizeof(WHITE_PATTERN) * 10);
	ZeroMemory(m_PtnAmmo, sizeof(WHITE_PATTERN) * 10);
	ZeroMemory(m_PtnArmor, sizeof(WHITE_PATTERN) * 10);
	ZeroMemory(m_PtnCredits, sizeof(WHITE_PATTERN) * 10);
	ZeroMemory(m_PtnAgents, sizeof(COLOR_PATTERN) * N_AGENTS);
	ZeroMemory(m_PtnWeaponChange, sizeof(WHITE_PATTERN) * 1);
	ZeroMemory(m_PtnSpike, sizeof(WHITE_PATTERN) * 1);
	ZeroMemory(m_PtnHitHeadShot, sizeof(COLOR_PATTERN) * 2);
	ZeroMemory(m_PtnOtherPlayer, sizeof(WHITE_PATTERN) * 1);
	ZeroMemory(m_PtnMapAgents, sizeof(COLOR_PATTERN) * N_MAPAGENTS);
	ZeroMemory(m_PtnMapRedCircle, sizeof(WHITE_PATTERN) * 1);
	ZeroMemory(m_PtnWeapon, sizeof(WHITE_PATTERN) * 18);

	m_allyScoreY = 0; 
	m_allyScoreX1 = 0; 
	m_allyScoreX10 = 0; 
	m_allyScoreX01 = 0;
	
	m_enemyScoreY = 0; 
	m_enemyScoreX1 = 0; 
	m_enemyScoreX10 = 0; 
	m_enemyScoreX01 = 0;

	m_timeY = 0; 
	m_timeX100 = 0; 
	m_timeX010 = 0; 
	m_timeX001 = 0;

	m_ammoY = 0; 
	m_ammoX100 = 0; 
	m_ammoX010 = 0; 
	m_ammoX001 = 0;

	m_healthY = 0; 
	m_healthX100 = 0; 
	m_healthX010 = 0; 
	m_healthX001 = 0; 
	m_healthX10 = 0; 
	m_healthX01 = 0; 
	m_healthX1 = 0;

	m_armorY = 0; 
	m_armorX10 = 0; 
	m_armorX01 = 0; 
	m_armorX1 = 0;

	m_ammoleftY = 0; 
	m_ammoleftX100 = 0; 
	m_ammoleftX010 = 0; 
	m_ammoleftX001 = 0;

	m_creditsY = 0; 
	m_creditsX1 = 0; 
	m_creditsX10 = 0; 
	m_creditsX100 = 0; 
	m_creditsX1000 = 0; 
	m_creditsX10000 = 0; 
	m_creditsX100000 = 0;

	m_agentsY = 0; 
	m_agentsXAlly = 0; 
	m_agentsXEnemy = 0; 
	m_agentsXStep = 0;

	m_weaponchangeY = 0; 
	m_weaponchangeX = 0; 
	m_weaponchangeY1 = 0; 
	m_weaponchangeX1 = 0; 
	m_weaponchangeY2 = 0; 
	m_weaponchangeX2 = 0; 
	m_weaponchangeY3 = 0; 
	m_weaponchangeX3 = 0;

	m_spikeY = 0; 
	m_spikeX = 0; 
	m_hitheadshotY = 0; 
	m_hitheadshotX = 0; 
	m_otherY = 0; 
	m_otherX = 0;

	m_skillY = 0; 
	m_skillStep = 0; 
	m_skillWidth = 0;

	m_weaponX = 0; 
	m_weaponY1 = 0; 
	m_weaponY2 = 0; 
	m_weaponY3 = 0;
}

CParserEngine::~CParserEngine()
{
}

CTimelineData CParserEngine::run(unsigned char* imgPtr_, int imgWidth_, int imgHeight_)
{
	CTimelineData *pResult = new CTimelineData();

	pResult->m_imageWidth = imgWidth_;

	if (!Init(imgWidth_, imgHeight_))
	{
		pResult->m_imageHeight = 0;
		return *pResult;
	}

	pResult->m_imageHeight = imgHeight_;
	m_pImageBufferPtr = imgPtr_;	

	// GameState
	pResult->m_clsGameState.m_yourTeamScore = GetYourTeamScore();
	//pResult->m_clsGameState.m_enemyTeamScore = GetEnemyTeamScore();
	//pResult->m_clsGameState.m_round = pResult->m_clsGameState.m_yourTeamScore + pResult->m_clsGameState.m_enemyTeamScore + 1;
	//pResult->m_clsGameState.m_roundTime = GetRoundTime();
	//pResult->m_clsGameState.m_aryYourAgents = GetAllyAgents();
	//pResult->m_clsGameState.m_aryEnemyAgents = GetEnemyAgents();
	// PlayerState
	//pResult->m_clsPlayerState.m_health = GetHealth();

	//int nOtherPlayer = GetIsOtherPlayer();

	//if (nOtherPlayer != 0 && pResult->m_clsPlayerState.m_health > 0)
	//	pResult->m_clsPlayerState.m_isAlive = true;
	//pResult->m_clsPlayerState.m_armor = GetArmor();
	//pResult->m_clsPlayerState.m_ammo = GetAmmo();
	//pResult->m_clsPlayerState.m_ammoLeft = GetAmmoLeft();
	//pResult->m_clsPlayerState.m_hasSpike = GetHasSpike();
	//pResult->m_clsPlayerState.m_credits = GetCredits();
	//pResult->m_clsPlayerState.m_weaponId = GetWeaponId();
	//pResult->m_clsPlayerState.m_hitHeadShot = GetHitHeadShot();
	//GLogA("CParserEngine::run - 5 - credit[%d]", pResult->m_clsPlayerState.m_credits);
	//GetAbilityLeft(pResult->m_clsPlayerState.m_aryAbilityLeft);

	//pResult->m_clsGameState.m_enemyList = GetEnemy(nOtherPlayer, pResult->m_clsPlayerState.m_health);
	return *pResult;
}

int8_t CParserEngine::GetYourTeamScore()
{
	int8_t u8YourTeamScore = 0;
	int ally, ally1, ally2;

	GLogA("m_allyScoreX1: %d, m_allyScoreX10: %d, m_allyScoreX01: %d, m_allyScoreY: %d",
		m_allyScoreX1, 
		m_allyScoreX10, 
		m_allyScoreX01, 
		m_allyScoreY);

	ally = MatchWhitePattern(m_nImageWidth / 2 + m_allyScoreX1, m_allyScoreY, m_PtnScore, 10);
	ally1 = MatchWhitePattern(m_nImageWidth / 2 + m_allyScoreX10, m_allyScoreY, m_PtnScore, 10);
	ally2 = MatchWhitePattern(m_nImageWidth / 2 + m_allyScoreX01, m_allyScoreY, m_PtnScore, 10);

	if ((ally == INVALID) && (ally1 != INVALID) && (ally2 != INVALID))
		u8YourTeamScore  = ally1 * 10 + ally2;
	else if ((ally != INVALID) && (ally1 == INVALID) && (ally2 == INVALID))
		u8YourTeamScore = ally;
	else if ((ally == INVALID) && (ally1 == INVALID) && (ally2 == INVALID))
		u8YourTeamScore = INVALID;
	else
		u8YourTeamScore = MATCH_ERROR;

	GLogA("ally: %d, ally1: %d, ally2: %d", ally, ally1, ally2);

	return u8YourTeamScore;
}

int8_t CParserEngine::GetEnemyTeamScore()
{
	int8_t u8EnemyTeamScore = 0;
	int enemy, enemy1, enemy2;
	enemy = MatchWhitePattern(m_nImageWidth / 2 + m_enemyScoreX1, m_enemyScoreY, m_PtnScore, 10);
	enemy1 = MatchWhitePattern(m_nImageWidth / 2 + m_enemyScoreX10, m_enemyScoreY, m_PtnScore, 10);
	enemy2 = MatchWhitePattern(m_nImageWidth / 2 + m_enemyScoreX01, m_enemyScoreY, m_PtnScore, 10);

	if ((enemy == INVALID) && (enemy1 != INVALID) && (enemy2 != INVALID))
		u8EnemyTeamScore = enemy1 * 10 + enemy2;
	else if ((enemy != INVALID) && (enemy1 == INVALID) && (enemy2 == INVALID))
		u8EnemyTeamScore = enemy;
	else if ((enemy == INVALID) && (enemy1 == INVALID) && (enemy == INVALID))
		u8EnemyTeamScore = INVALID;
	else
		u8EnemyTeamScore = MATCH_ERROR;

	return u8EnemyTeamScore;
}

int8_t CParserEngine::GetRoundTime()
{
	int8_t u8RoundTime = 0;
	int time1, time2, time3;

	time1 = MatchWhitePattern(m_nImageWidth / 2 + m_timeX100, m_timeY, m_PtnTime, 2);
	time2 = MatchWhitePattern(m_nImageWidth / 2 + m_timeX010, m_timeY, m_PtnTime, 6);
	time3 = MatchWhitePattern(m_nImageWidth / 2 + m_timeX001, m_timeY, m_PtnTime, 10);

	if ((time1 != INVALID) && (time2 != INVALID) && (time3 != INVALID))
		u8RoundTime = time1 * 60 + time2 * 10 + time3;
	else if ((time1 == INVALID) && (time2 == INVALID) && (time3 == INVALID))
		u8RoundTime = INVALID;
	else
		u8RoundTime = MATCH_ERROR;

	return u8RoundTime;
}

int8_t CParserEngine::GetHealth()
{
	int8_t u8Health = 0;
	int health1, health2, health3, health4, health5, health6;

	health1 = MatchWhitePattern(m_nImageWidth / 2 + m_healthX100, m_healthY, m_PtnAmmo, 2);
	health2 = MatchWhitePattern(m_nImageWidth / 2 + m_healthX010, m_healthY, m_PtnAmmo, 10);
	health3 = MatchWhitePattern(m_nImageWidth / 2 + m_healthX001, m_healthY, m_PtnAmmo, 10);

	health4 = MatchWhitePattern(m_nImageWidth / 2 + m_healthX10, m_healthY, m_PtnAmmo, 10);
	health5 = MatchWhitePattern(m_nImageWidth / 2 + m_healthX01, m_healthY, m_PtnAmmo, 10);

	health6 = MatchWhitePattern(m_nImageWidth / 2 + m_healthX1, m_healthY, m_PtnAmmo, 10);

	if ((health1 != INVALID) && (health2 != INVALID) && (health3 != INVALID) && (health4 == INVALID) && (health5 == INVALID) && (health6 == INVALID))
		u8Health = health1 * 100 + health2 * 10 + health3;
	else if ((health1 == INVALID) && (health2 == INVALID) && (health3 == INVALID) && (health4 != INVALID) && (health5 != INVALID) && (health6 == INVALID))
		u8Health = health4 * 10 + health5;
	else if ((health1 == INVALID) && (health2 == INVALID) && (health3 == INVALID) && (health4 == INVALID) && (health5 == INVALID) && (health6 != INVALID))
		u8Health = health6;
	else if ((health1 == INVALID) && (health2 == INVALID) && (health3 == INVALID) && (health4 == INVALID) && (health5 == INVALID) && (health6 == INVALID))
		u8Health = INVALID;
	else
		u8Health = MATCH_ERROR;

	return u8Health;
}

int CParserEngine::GetIsOtherPlayer()
{
	int u8IsOtherPlayer = 0;

	u8IsOtherPlayer = MatchWhitePattern(m_otherX, m_otherY, m_PtnOtherPlayer, 1);

	return u8IsOtherPlayer;
}

int8_t CParserEngine::GetArmor()
{
	int8_t u8Armor = 0;
	int armor1, armor2, armor3;

	armor1 = MatchWhitePattern(m_nImageWidth / 2 + m_armorX10, m_armorY, m_PtnArmor, 10);
	armor2 = MatchWhitePattern(m_nImageWidth / 2 + m_armorX01, m_armorY, m_PtnArmor, 10);
	armor3 = MatchWhitePattern(m_nImageWidth / 2 + m_armorX1, m_armorY, m_PtnArmor, 10);

	if ((armor1 != INVALID) && (armor2 != INVALID) && (armor3 == INVALID))
		u8Armor = armor1 * 10 + armor2;
	else if ((armor1 == INVALID) && (armor2 == INVALID) && (armor3 != INVALID))
		u8Armor = armor3;
	else if ((armor1 == INVALID) && (armor2 == INVALID) && (armor3 == INVALID))
		u8Armor = INVALID;
	else
		u8Armor = MATCH_ERROR;

	return u8Armor;
}

int16_t CParserEngine::GetAmmo()
{
	int16_t u16Ammo = 0;
	int ammo0, ammo1, ammo2;

	ammo0 = MatchWhitePattern(m_nImageWidth / 2 + m_ammoX100, m_ammoY, m_PtnAmmo, 3);
	ammo1 = MatchWhitePattern(m_nImageWidth / 2 + m_ammoX010, m_ammoY, m_PtnAmmo, 10);
	ammo2 = MatchWhitePattern(m_nImageWidth / 2 + m_ammoX001, m_ammoY, m_PtnAmmo, 10);

	if ((ammo0 != INVALID) && (ammo1 != INVALID) && (ammo2 != INVALID))
		u16Ammo = ammo0 * 100 + ammo1 * 10 + ammo2;
	else if ((ammo0 == INVALID) && (ammo1 != INVALID) && (ammo2 != INVALID))
		u16Ammo = ammo1 * 10 + ammo2;
	else if ((ammo0 == INVALID) && (ammo1 == INVALID) && (ammo2 != INVALID))
		u16Ammo = ammo2;
	else if ((ammo0 == INVALID) && (ammo1 == INVALID) && (ammo2 == INVALID))
		u16Ammo = INVALID;
	else
		u16Ammo = MATCH_ERROR;

	return u16Ammo;
}

int16_t CParserEngine::GetAmmoLeft()
{
	int16_t u16AmmoLeft = 0;
	int ammoleft1, ammoleft2, ammoleft3;

	ammoleft1 = MatchWhitePattern(m_nImageWidth / 2 + m_ammoleftX100, m_ammoleftY, m_PtnArmor, 10);
	ammoleft2 = MatchWhitePattern(m_nImageWidth / 2 + m_ammoleftX010, m_ammoleftY, m_PtnArmor, 10);
	ammoleft3 = MatchWhitePattern(m_nImageWidth / 2 + m_ammoleftX001, m_ammoleftY, m_PtnArmor, 10);

	if ((ammoleft1 != INVALID) && (ammoleft2 == INVALID) && (ammoleft3 == INVALID))
		u16AmmoLeft = ammoleft1;
	else if ((ammoleft1 != INVALID) && (ammoleft2 != INVALID) && (ammoleft3 == INVALID))
		u16AmmoLeft = ammoleft1 * 10 + ammoleft2;
	else if ((ammoleft1 != INVALID) && (ammoleft2 != INVALID) && (ammoleft3 != INVALID))
		u16AmmoLeft = ammoleft1 * 100 + ammoleft2 * 10 + ammoleft3;
	else if ((ammoleft1 == INVALID) && (ammoleft2 == INVALID) && (ammoleft3 == INVALID))
		u16AmmoLeft = INVALID;
	else
		u16AmmoLeft = MATCH_ERROR;

	return u16AmmoLeft;
}

int16_t CParserEngine::GetCredits()
{
	int16_t u16Credits = 0;
	int credit;

	u16Credits = INVALID;

	credit = MatchWhitePattern(m_nImageWidth + m_creditsX1, m_creditsY, m_PtnCredits, 10);

	if (credit == INVALID)
		return u16Credits;

	u16Credits = credit;
	credit = MatchWhitePattern(m_nImageWidth + m_creditsX10, m_creditsY, m_PtnCredits, 10);

	if (credit == INVALID)
		return u16Credits;

	u16Credits += credit * 10;
	credit = MatchWhitePattern(m_nImageWidth + m_creditsX100, m_creditsY, m_PtnCredits, 10);

	if (credit == INVALID)
		return u16Credits;

	u16Credits += credit * 100;
	credit = MatchWhitePattern(m_nImageWidth + m_creditsX1000, m_creditsY, m_PtnCredits, 10);

	if (credit == INVALID)
		return u16Credits;

	u16Credits += credit * 1000;
	credit = MatchWhitePattern(m_nImageWidth + m_creditsX10000, m_creditsY, m_PtnCredits, 10);

	if (credit == INVALID)
		return u16Credits;

	u16Credits += credit * 10000;

	return u16Credits;
}

int8_t CParserEngine::GetHasSpike()
{
	return MatchWhitePattern(m_nImageWidth + m_spikeX, m_spikeY, m_PtnSpike, 1);
}

int8_t CParserEngine::GetWeaponId()
{
	int8_t u8WeaponId = -1;
	int nWeaponChange;

	nWeaponChange = MatchWhitePattern(m_nImageWidth + m_weaponchangeX, m_weaponchangeY, m_PtnWeaponChange, 1);

	if (nWeaponChange != INVALID)
	{
		unsigned char* p;
		int c1, c2, c3;

		p = m_pImageBufferPtr + (m_nImageWidth * m_weaponchangeY1 + m_nImageWidth + m_weaponchangeX1) * 3;
		c1 = (int)(*p) + *(p + 1) + *(p + 2);
		p = m_pImageBufferPtr + (m_nImageWidth * m_weaponchangeY2 + m_nImageWidth + m_weaponchangeX2) * 3;
		c2 = (int)(*p) + *(p + 1) + *(p + 2);
		p = m_pImageBufferPtr + (m_nImageWidth * m_weaponchangeY3 + m_nImageWidth + m_weaponchangeX3) * 3;
		c3 = (int)(*p) + *(p + 1) + *(p + 2);

		if (c1 < 255 * 3 - 150 && c2 < 255 * 3 - 80 && c3 < 255 * 3 - 150)
		{
			//skill
			u8WeaponId = -1;
		}
		else if (c1 >= c2 && c1 >= c3)
		{
			//automatic rifle
			u8WeaponId = MatchWhitePattern(m_nImageWidth + m_weaponX, m_weaponY1, &(m_PtnWeapon[6]), 12);

			if (u8WeaponId != INVALID)
			{
				u8WeaponId += 6;
			}
		}
		else if (c2 >= c1 && c2 >= c3)
		{
			//pistol
			u8WeaponId = MatchWhitePattern(m_nImageWidth + m_weaponX, m_weaponY2, &(m_PtnWeapon[1]), 5);

			if (u8WeaponId != INVALID)
			{
				u8WeaponId += 1;
			}
		}
		else if (c3 >= c1 && c3 >= c2)
		{
			//knife
			u8WeaponId = 0;
		}
	}

	return u8WeaponId;
}

int8_t CParserEngine::GetHitHeadShot()
{
	return MatchColorPattern(m_nImageWidth / 2 + m_hitheadshotX, m_hitheadshotY, m_PtnHitHeadShot, 2);
}

void CParserEngine::GetAbilityLeft(int8_t* pAbilityInfo)
{
	int x = m_nImageWidth / 2 - 1 - m_skillStep - (m_skillStep + m_skillWidth) / 2;
	int R = 95, G = 238, B = 184, diff = 35;
	unsigned char* p;

	for (int j = 0; j < MAX_ABILITY; j++)
	{
		pAbilityInfo[j] = 0;

		int f = 0;

		for (int i = 0; i < m_skillWidth; i++)
		{
			p = m_pImageBufferPtr + (m_skillY * m_nImageWidth + x + i) * 3;

			if ((abs(B - *p) < diff) && (abs(G - *(++p)) < diff) && (abs(R - *(++p)) < diff))
			{
				if (f == 0)
				{
					pAbilityInfo[j]++;
				}

				f = 1;
			}
			else
			{
				f = 0;
			}
		}

		x += m_skillStep;
	}
}

std::vector<std::string> CParserEngine::GetAllyAgents()
{
	std::vector<std::string> agentList;

	for (int i = 0; i < 5; i++)
	{
		int n = MatchColorPattern(m_nImageWidth / 2 + m_agentsXAlly + i * m_agentsXStep, m_agentsY, m_PtnAgents, N_AGENTS);

		if (n == 19)
			n = 8;

		if (n != INVALID)
		{
			char szAliveAgent[MAX_PATH] = { 0 };

			sprintf_s(szAliveAgent, "agent%d", n);
			agentList.push_back(szAliveAgent);
		}
	}

	return agentList;
}

std::vector<std::string> CParserEngine::GetEnemyAgents()
{
	std::vector<std::string> agentList;

	for (int i = 0; i < 5; i++)
	{
		int n = MatchColorPattern(m_nImageWidth / 2 + m_agentsXEnemy + i * m_agentsXStep, m_agentsY, m_PtnAgents, N_AGENTS, true);

		if (n == 19)
			n = 8;

		if (n != INVALID)
		{
			char szAliveAgent[MAX_PATH] = { 0 };

			sprintf_s(szAliveAgent, "agent%d", n);
			agentList.push_back(szAliveAgent);
		}
	}

	return agentList;
}

BOOL CParserEngine::Init(int imgWidth_, int imgHeight_)
{
	FILE* fp = nullptr;
	char fn[MAX_PATH];

	m_nImageWidth = imgWidth_;
	GLogA("CParserEngine::Init -- 1");
	if (m_nImageHeight == imgHeight_)
	{
		return TRUE;
	}

	m_nImageHeight = imgHeight_;

	sprintf_s(fn, "ptn%d.dat", m_nImageHeight);
	GLogA("CParserEngine::Init -- 2");
	if (fopen_s(&fp, fn, "rb"))
	{
		m_nImageHeight = 0;
		return FALSE;
	}
	GLogA("CParserEngine::Init -- 3");
	if (!fp)
	{
		return FALSE;
	}
	GLogA("CParserEngine::Init -- 4");
	fread(m_PtnScore, 10, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnTime, 10, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnAmmo, 10, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnArmor, 10, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnCredits, 10, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnAgents, N_AGENTS, sizeof(COLOR_PATTERN), fp);
	fread(m_PtnWeaponChange, 1, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnSpike, 1, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnHitHeadShot, 2, sizeof(COLOR_PATTERN), fp);
	fread(m_PtnOtherPlayer, 1, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnMapAgents, N_MAPAGENTS, sizeof(COLOR_PATTERN), fp);
	fread(m_PtnMapRedCircle, 1, sizeof(WHITE_PATTERN), fp);
	fread(m_PtnWeapon, 18, sizeof(WHITE_PATTERN), fp);

	fclose(fp);

	char strApp[MAX_PATH];

	sprintf_s(strApp, "%d", m_nImageHeight);

	m_allyScoreY = GetPrivateProfileIntA(strApp, "allyScoreY", 0, POS_INI);
	m_allyScoreX1 = GetPrivateProfileIntA(strApp, "allyScoreX1", 0, POS_INI);
	m_allyScoreX10 = GetPrivateProfileIntA(strApp, "allyScoreX10", 0, POS_INI);
	m_allyScoreX01 = GetPrivateProfileIntA(strApp, "allyScoreX01", 0, POS_INI);
	m_enemyScoreY = GetPrivateProfileIntA(strApp, "enemyScoreY", 0, POS_INI);
	m_enemyScoreX1 = GetPrivateProfileIntA(strApp, "enemyScoreX1", 0, POS_INI);
	m_enemyScoreX10 = GetPrivateProfileIntA(strApp, "enemyScoreX10", 0, POS_INI);
	m_enemyScoreX01 = GetPrivateProfileIntA(strApp, "enemyScoreX01", 0, POS_INI);

	m_timeY = GetPrivateProfileIntA(strApp, "timeY", 0, POS_INI);
	m_timeX100 = GetPrivateProfileIntA(strApp, "timeX100", 0, POS_INI);
	m_timeX010 = GetPrivateProfileIntA(strApp, "timeX010", 0, POS_INI);
	m_timeX001 = GetPrivateProfileIntA(strApp, "timeX001", 0, POS_INI);

	m_ammoY = GetPrivateProfileIntA(strApp, "ammoY", 0, POS_INI);
	m_ammoX100 = GetPrivateProfileIntA(strApp, "ammoX100", 0, POS_INI);
	m_ammoX010 = GetPrivateProfileIntA(strApp, "ammoX010", 0, POS_INI);
	m_ammoX001 = GetPrivateProfileIntA(strApp, "ammoX001", 0, POS_INI);

	m_healthY = GetPrivateProfileIntA(strApp, "healthY", 0, POS_INI);
	m_healthX100 = GetPrivateProfileIntA(strApp, "healthX100", 0, POS_INI);
	m_healthX010 = GetPrivateProfileIntA(strApp, "healthX010", 0, POS_INI);
	m_healthX001 = GetPrivateProfileIntA(strApp, "healthX001", 0, POS_INI);
	m_healthX10 = GetPrivateProfileIntA(strApp, "healthX10", 0, POS_INI);
	m_healthX01 = GetPrivateProfileIntA(strApp, "healthX01", 0, POS_INI);
	m_healthX1 = GetPrivateProfileIntA(strApp, "healthX1", 0, POS_INI);

	m_armorY = GetPrivateProfileIntA(strApp, "armorY", 0, POS_INI);
	m_armorX10 = GetPrivateProfileIntA(strApp, "armorX10", 0, POS_INI);
	m_armorX01 = GetPrivateProfileIntA(strApp, "armorX01", 0, POS_INI);
	m_armorX1 = GetPrivateProfileIntA(strApp, "armorX1", 0, POS_INI);

	m_ammoleftY = GetPrivateProfileIntA(strApp, "ammoleftY", 0, POS_INI);
	m_ammoleftX100 = GetPrivateProfileIntA(strApp, "ammoleftX100", 0, POS_INI);
	m_ammoleftX010 = GetPrivateProfileIntA(strApp, "ammoleftX010", 0, POS_INI);
	m_ammoleftX001 = GetPrivateProfileIntA(strApp, "ammoleftX001", 0, POS_INI);

	m_creditsY = GetPrivateProfileIntA(strApp, "creditsY", 0, POS_INI);
	m_creditsX1 = GetPrivateProfileIntA(strApp, "creditsX1", 0, POS_INI);
	m_creditsX10 = GetPrivateProfileIntA(strApp, "creditsX10", 0, POS_INI);
	m_creditsX100 = GetPrivateProfileIntA(strApp, "creditsX100", 0, POS_INI);
	m_creditsX1000 = GetPrivateProfileIntA(strApp, "creditsX1000", 0, POS_INI);
	m_creditsX10000 = GetPrivateProfileIntA(strApp, "creditsX10000", 0, POS_INI);

	m_agentsY = GetPrivateProfileIntA(strApp, "agentsY", 0, POS_INI);
	m_agentsXAlly = GetPrivateProfileIntA(strApp, "agentsXAlly", 0, POS_INI);
	m_agentsXEnemy = GetPrivateProfileIntA(strApp, "agentsXEnemy", 0, POS_INI);
	m_agentsXStep = GetPrivateProfileIntA(strApp, "agentsXStep", 0, POS_INI);

	m_weaponchangeY = GetPrivateProfileIntA(strApp, "weaponchangeY", 0, POS_INI);
	m_weaponchangeX = GetPrivateProfileIntA(strApp, "weaponchangeX", 0, POS_INI);
	m_weaponchangeY1 = GetPrivateProfileIntA(strApp, "weaponchangeY1", 0, POS_INI);
	m_weaponchangeX1 = GetPrivateProfileIntA(strApp, "weaponchangeX1", 0, POS_INI);
	m_weaponchangeY2 = GetPrivateProfileIntA(strApp, "weaponchangeY2", 0, POS_INI);
	m_weaponchangeX2 = GetPrivateProfileIntA(strApp, "weaponchangeX2", 0, POS_INI);
	m_weaponchangeY3 = GetPrivateProfileIntA(strApp, "weaponchangeY3", 0, POS_INI);
	m_weaponchangeX3 = GetPrivateProfileIntA(strApp, "weaponchangeX3", 0, POS_INI);
	m_weaponX = GetPrivateProfileIntA(strApp, "weaponX", 0, POS_INI);
	m_weaponY1 = GetPrivateProfileIntA(strApp, "weaponY1", 0, POS_INI);
	m_weaponY2 = GetPrivateProfileIntA(strApp, "weaponY2", 0, POS_INI);
	m_weaponY3 = GetPrivateProfileIntA(strApp, "weaponY3", 0, POS_INI);

	m_spikeY = GetPrivateProfileIntA(strApp, "spikeY", 0, POS_INI);
	m_spikeX = GetPrivateProfileIntA(strApp, "spikeX", 0, POS_INI);
	m_hitheadshotY = GetPrivateProfileIntA(strApp, "hitheadshotY", 0, POS_INI);
	m_hitheadshotX = GetPrivateProfileIntA(strApp, "hitheadshotX", 0, POS_INI);
	m_otherY = GetPrivateProfileIntA(strApp, "otherY", 0, POS_INI);
	m_otherX = GetPrivateProfileIntA(strApp, "otherX", 0, POS_INI);

	m_skillY = GetPrivateProfileIntA(strApp, "skillY", 0, POS_INI);
	m_skillStep = GetPrivateProfileIntA(strApp, "skillStep", 0, POS_INI);
	m_skillWidth = GetPrivateProfileIntA(strApp, "skillWidth", 0, POS_INI);

	GLogA("CParserEngine::Init -- 5");
	return TRUE;
}

int CParserEngine::MatchWhitePattern(int x, int y, WHITE_PATTERN* ptn, int nPtn)
{
	int ret = INVALID;

	ret = MatchWhitePattern_(x, y, ptn, nPtn);

	if (ret == INVALID)
		ret = MatchWhitePattern_(x - 1, y, ptn, nPtn);

	if (ret == INVALID)
		ret = MatchWhitePattern_(x + 1, y, ptn, nPtn);

	return ret;
}

int CParserEngine::MatchWhitePattern_(int x, int y, WHITE_PATTERN* ptn, int nPtn)
{
	int w = ptn[0].width, h = ptn[0].height;
	unsigned int* blackImg = new unsigned int[w * h];
	unsigned char* p;
	unsigned int* pi = blackImg;
	unsigned int avgBlackColor = 0;
	unsigned int maxRGB = 0;
	int i, j, n;

	GLogA("w: %d, h: %d, w1: %d, h1: %d", w, h, m_nImageWidth, m_nImageHeight);
	
	for (j = 0; j < h; j++)
	{
		if (y + j >= m_nImageHeight)
		{
			GLogA("CParserEngine::MatchWhitePattern_ - 1");
			delete[] blackImg;
			return INVALID;
		}

		for (i = 0; i < w; i++)
		{
			if (x + i >= m_nImageWidth)
			{
				GLogA("CParserEngine::MatchWhitePattern_ - 2");
				delete[] blackImg;
				return INVALID;
			}

			p = m_pImageBufferPtr + (m_nImageWidth * (y + j) + (x + i)) * 3;
			
			avgBlackColor += *p;
			*pi = *p;
			p++;

			avgBlackColor += *p;
			*pi += *p;
			p++;

			avgBlackColor += *p;
			*pi += *p;

			if (maxRGB < *pi)
			{
				maxRGB = *pi;
			}

			pi++;
		}
	}

	avgBlackColor /= (w * h);
	avgBlackColor += 9;

	if (avgBlackColor >= 253 * 3)
	{
		avgBlackColor = 253 * 3 - 1;
	}

	for (i = 0; i < w*h; i++)
	{
		if (blackImg[i] > avgBlackColor)
			blackImg[i] = 1;
		else
			blackImg[i] = 0;
	}
	GLogA("CParserEngine::MatchWhitePattern_ - 5");
	for (n = nPtn-1; n >= 0; n--)
	{
		for (i = 0; i < w * h; i++)
		{
			if (ptn[i].mask[i] == 0)
				continue;

			if (blackImg[i] == 0)
				break;
		}

		if (i == w * h)
		{
			GLogA("CParserEngine::MatchWhitePattern_ - 3");
			delete[] blackImg;
			return n;
		}
	}

	delete[] blackImg;

	GLogA("CParserEngine::MatchWhitePattern_ - 4");
	return INVALID;
}

int CParserEngine::MatchColorPattern(int x, int y, COLOR_PATTERN* ptn, int nPtn, bool flip)
{
	int ret = INVALID;

	ret = MatchColorPattern_(x, y, ptn, nPtn, flip);

	if (ret == INVALID)
		ret = MatchColorPattern_(x - 1, y, ptn, nPtn, flip);

	if (ret == INVALID)
		ret = MatchColorPattern_(x + 1, y, ptn, nPtn, flip);

	return ret;
}

int CParserEngine::MatchColorPattern_(int x, int y, COLOR_PATTERN* ptn, int nPtn, bool flip)
{
	int w = ptn[0].width, h = ptn[0].height;
	int diff = h * w * 3 * 300;
	unsigned char* p;
	int i, j, n, ii, jj;
	int idx;
	int total, t, tt;

	for (n = 0; n < nPtn; n++)
	{
		if ((ptn[n].B[0] == 255) && (ptn[n].G[0] == 255) && (ptn[n].R[0] == 255))
		{
			continue;
		}

		total = 0;

		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				if (flip)
					idx = (j + 1) * w - 1 - i;
				else
					idx = j * w + i;

				t = 0x0FFFFFFFF;

				for (jj = -1; jj <= 1; jj++)
				{
					for (ii = -1; ii <= 1; ii++)
					{
						if (y + j + jj >= m_nImageHeight)
							return INVALID;

						if (y + j + jj < 0)
							return INVALID;

						if (x + i + ii >= m_nImageWidth)
							return INVALID;

						if (x + i + ii < 0)
							return INVALID;

						p = m_pImageBufferPtr + (m_nImageWidth * (y + j + jj) + (x + i + ii)) * 3;
						tt = ((ptn[n].B[idx] > (*p)) ? ptn[n].B[idx] - (*p) : (*p) - ptn[n].B[idx]) *
							((ptn[n].B[idx] > (*p)) ? ptn[n].B[idx] - (*p) : (*p) - ptn[n].B[idx]);
						p++;
						tt += ((ptn[n].G[idx] > (*p)) ? ptn[n].G[idx] - (*p) : (*p) - ptn[n].G[idx]) *
							((ptn[n].G[idx] > (*p)) ? ptn[n].G[idx] - (*p) : (*p) - ptn[n].G[idx]);
						p++;
						tt += ((ptn[n].R[idx] > (*p)) ? ptn[n].R[idx] - (*p) : (*p) - ptn[n].R[idx]) *
							((ptn[n].R[idx] > (*p)) ? ptn[n].R[idx] - (*p) : (*p) - ptn[n].R[idx]);

						if (tt < t)
							t = tt;
					}
				}

				total += t;

				if (total >= diff)
				{
					break;
				}
			}

			if (i < w)
			{
				break;
			}
		}

		if (j == h)
		{
			return n;
		}
	}

	return INVALID;
}

int CParserEngine::MatchMapPattern(int x, int y, COLOR_PATTERN* ptn, int nPtn)
{
	int w = ptn[0].width, h = ptn[0].height;
	unsigned char* p;
	int i, j, n, d, dd, diff = 350 * h * w * 3;
	int idx;

	for (n = 0; n < nPtn; n++)
	{
		if ((ptn[n].B[0] == 255) && (ptn[n].G[0] == 255) && (ptn[n].R[0] == 255))
		{
			continue;
		}

		d = 0;
		for (j = 0; j < h; j++)
		{
			for (i = 0; i < w; i++)
			{
				p = m_pImageBufferPtr + (m_nImageWidth * (y + j) + (x + i)) * 3;
				idx = j * w + i;

				dd = abs((int)(ptn[n].B[idx]) - (*p));
				dd = min(dd, abs((int)(ptn[n].B[idx]) - (*(p + 3))));
				dd = min(dd, abs((int)(ptn[n].B[idx]) - (*(p + m_nImageWidth* 3))));
				dd = min(dd, abs((int)(ptn[n].B[idx]) - (*(p + m_nImageWidth * 3 + 3))));
				d += dd * dd;

				if (d > diff)
					break;

				p++;
				dd = abs((int)(ptn[n].G[idx]) - (*p));
				dd = min(dd, abs((int)(ptn[n].G[idx]) - (*(p + 3))));
				dd = min(dd, abs((int)(ptn[n].G[idx]) - (*(p + m_nImageWidth * 3))));
				dd = min(dd, abs((int)(ptn[n].G[idx]) - (*(p + m_nImageWidth * 3 + 3))));
				d += dd * dd;

				if (d > diff)
					break;

				p++;
				dd = abs((int)(ptn[n].R[idx]) - (*p));
				dd = min(dd, abs((int)(ptn[n].R[idx]) - (*(p + 3))));
				dd = min(dd, abs((int)(ptn[n].R[idx]) - (*(p + m_nImageWidth * 3))));
				dd = min(dd, abs((int)(ptn[n].R[idx]) - (*(p + m_nImageWidth * 3 + 3))));
				d += dd * dd;

				if (d > diff)
				{
					break;
				}
			}

			if (i < w)
			{
				break;
			}
		}

		if (j == h)
		{
			return n;
		}
	}

	return INVALID;
}

int CParserEngine::GetEnemyOnMap(EnemyRect* pMapEnemy)
{
	int dxy = 50 * m_nImageHeight / 1080, oxy = 227 * m_nImageHeight / 1080;
	int i, j, m;
	int ii, jj;
	int wid = oxy * 2 - dxy * 2;
	int hei = oxy - dxy + 15;
	unsigned char* pMap = new unsigned char[wid * hei], * p;
	int nMapEnemyCount = 0;

	//detect red color on map
	for (j = 0; j < hei; j++)
	{
		for (i = 0; i < wid; i++)
		{
			p = m_pImageBufferPtr + ((dxy + j) * m_nImageWidth + dxy + i) * 3;

			if ((p[2] == 255) && (p[1] == 0) && (p[0] == 0))
			{
				pMap[j * wid + i] = 0;
			}
			else if ((abs((int)(p[0]) - p[1]) < 5) && ((int)(p[2]) - p[1] > 70))
			{
				pMap[j * wid + i] = 255;
			}
			else if ((abs((int)(p[0]) - 80) < 6) && (abs((int)(p[1]) - 94) < 6) && (p[2] > 200))
			{
				pMap[j * wid + i] = 255;
			}
			else if ((abs((int)(p[0]) - 68) < 6) && (abs((int)(p[1]) - 82) < 6) && (p[2] > 180))
			{
				pMap[j * wid + i] = 255;
			}
			else
			{
				pMap[j * wid + i] = 0;
			}
		}
	}

	//set detect area on map
	for (j = 0; j < hei; j++)
	{
		for (i = 0; i < wid; i++)
		{
			if (pMap[j * wid + i] == 0)
			{
				continue;
			}

			for (jj = 0; jj < m_PtnMapRedCircle->height; jj++)
			{
				if (j - jj < 0)
				{
					break;
				}

				for (ii = 0; ii < m_PtnMapRedCircle->width; ii++)
				{
					if (i - ii < 0)
					{
						break;
					}

					pMap[(j - jj) * wid + (i - ii)] |= 1;
				}
			}

		}
	}

	//detect red circle on map
	for (j = 0; j <= hei - m_PtnMapRedCircle->height; j++)
	{
		for (i = 0; i <= wid - m_PtnMapRedCircle->width; i++)
		{
			if (pMap[j * wid + i] == 0)
			{
				continue;
			}

			int cc = 0;

			for (jj = 0; jj < m_PtnMapRedCircle->height; jj++)
			{
				for (ii = 0; ii < m_PtnMapRedCircle->width; ii++)
				{
					if ((pMap[(j + jj) * wid + i + ii] > 1) && (m_PtnMapRedCircle->mask[jj * m_PtnMapRedCircle->width + ii]))
					{
						cc++;
					}
				}
			}


			if (cc >= m_PtnMapRedCircle->width * 2 / 3)//detect agent icon on map
			{
				ii = dxy + i + (m_PtnMapRedCircle->width - m_PtnMapAgents[0].width) / 2;
				jj = dxy + j + (m_PtnMapRedCircle->height - m_PtnMapAgents[0].height) / 2;

				pMapEnemy[nMapEnemyCount].m_mapX = ii + (m_PtnMapAgents[0].width + 1) / 2 - oxy;
				pMapEnemy[nMapEnemyCount].m_mapY = oxy - jj - (m_PtnMapAgents[0].height + 1) / 2;

				if (pMapEnemy[nMapEnemyCount].m_mapY < 1)
				{
					break;
				}

				for (m = 0; m < nMapEnemyCount; m++)
				{
					if (abs(pMapEnemy[m].m_mapX - pMapEnemy[nMapEnemyCount].m_mapX) +
						abs(pMapEnemy[m].m_mapY - pMapEnemy[nMapEnemyCount].m_mapY) <
						(m_PtnMapRedCircle->width + m_PtnMapAgents[0].width) / 2 - 1)
					{
						break;
					}
				}

				if (m < nMapEnemyCount)
				{
					continue;
				}

				m = MatchMapPattern(ii, jj, m_PtnMapAgents, N_MAPAGENTS);

				if (m != INVALID)
				{
					char szAliveAgent[MAX_PATH] = { 0 };

					m /= 2;
					
					sprintf_s(szAliveAgent, "agent%d", m);
					pMapEnemy[nMapEnemyCount].m_enemyAgent = szAliveAgent;
					nMapEnemyCount++;

					if (nMapEnemyCount == 5)
					{
						break;
					}
				}

			}
		}

		if (nMapEnemyCount == 5)
		{
			break;
		}
	}

	delete[] pMap;

	//sort by mapY
	EnemyRect er;
	for (i = 0; i < nMapEnemyCount - 1; i++)
	{
		for (j = i + 1; j < nMapEnemyCount; j++)
		{
			if (pMapEnemy[i].m_mapY > pMapEnemy[j].m_mapY)
			{
				er = pMapEnemy[i]; pMapEnemy[i] = pMapEnemy[j]; pMapEnemy[j] = er;
			}
		}
	}

	//detect enemy on screen according mapEnemy
	int k, siz;

	for (k = 0; k < nMapEnemyCount; k++)
	{
		int dx = pMapEnemy[k].m_mapX;
		int dy = pMapEnemy[k].m_mapY;
		int x;

		siz = m_nImageWidth / 2 / dy;

		for (j = m_nImageHeight / 4; j < m_nImageHeight * 3 / 4; j++)
		{
			x = m_nImageWidth / 2 + (m_nImageWidth * 2 / 5) * dx / dy;
			p = m_pImageBufferPtr + (j * m_nImageWidth) * 3;

			int i1, i2;

			i1 = MAX(0, x - siz * 3 / 2); i2 = MIN(x + siz * 3 / 2, m_nImageWidth);

			for (i = i1; i < i2; i++)
			{
				//avoid past enemy rect
				int kk;

				for (kk = 0; kk < k; kk++)
				{
					if ((i >= pMapEnemy[kk].m_enemyNormal.x1) && (i <= pMapEnemy[kk].m_enemyNormal.x2) &&
						(j >= pMapEnemy[kk].m_enemyNormal.y1) && (j <= pMapEnemy[kk].m_enemyNormal.y2))
					{
						break;
					}
				}

				if (kk < k)
				{
					continue;
				}

				if (((*(p + i * 3) < 80) && (*(p + i * 3 + 1) < 100) && (*(p + i * 3 + 2) > 252)) ||
					((*(p + i * 3) < 120) && (*(p + i * 3 + 1) < 120) && (*(p + i * 3 + 2) > 252) && (abs((int)(*(p + i * 3)) - *(p + i * 3 + 1)) < 4)) ||
					((abs((int)(*(p + i * 3)) - *(p + i * 3 + 1)) < 4) && (*(p + i * 3 + 2) > *(p + i * 3 + 1) * 3) && (*(p + i * 3 + 2) > 150)))
				{
					pMapEnemy[k].m_enemyNormal.y1 = j;
					pMapEnemy[k].m_enemyNormal.x1 = i - siz * 3 / 4;
					pMapEnemy[k].m_enemyNormal.x2 = i + siz * 3 / 4;
					pMapEnemy[k].m_enemyNormal.y2 = MIN(j + 4 * siz, m_nImageHeight - 1);
					break;
				}
			}

			if (i < i2)
			{
				break;
			}
		}
	}

	return nMapEnemyCount;
}

int CParserEngine::GetEnemyOnScreen(EnemyRect * pEnemy)
{
	//enemy detect
	unsigned char* p, * pt = m_pImageBufferPtr;
	unsigned char* pp, * pptr = new unsigned char[m_nImageWidth * m_nImageHeight * 3];

	memset(pptr, 0, m_nImageWidth * m_nImageHeight * 3);

	int i, j, ii, jj, tp = m_nImageHeight, bt = -1, rt = -1, lt = m_nImageWidth, cnt = 0;
	int mapSize = 440 * m_nImageHeight / 1080;
	int nEnemyCount = 0;

	for (j = 5; j < m_nImageHeight - 5; j++)
	{
		p = pt + j * m_nImageWidth * 3; p += 3 * 5;
		pp = pptr + j * m_nImageWidth * 3; pp += 3 * 5;

		for (i = 5; i < m_nImageWidth - 5; i++)
		{
			if ((i < mapSize) && (j < mapSize))
			{
				p += 3;
				pp += 3;
				continue;
			}

			if ((*(p + 2) >= 254) && (*(p + 1) != 0) && (*p != 0) && (

				((*(p + 1) < 50) && (*p < 50) && (*(p + 1) < *p * 1.5))
				|| ((*(p + 1) < 70) && (*p < 70) && (((*(p + 1) < *p) ? *p - *(p + 1) : *(p + 1) - *p) < 4))

				)

				)
			{
				int cc = 0, st = 2; byte d = 150; byte* zz;

				for (jj = -st; jj <= st; jj++)
				{
					for (ii = -st; ii <= st; ii++)
					{
						zz = pt + ((j + jj) * m_nImageWidth + i + ii) * 3;
						if (zz[2] < d)cc++;
						if (zz[2] / 3 * 2 < zz[0] / 2 + zz[1] / 2)cc++;
					}
				}

				if (cc >= 23)
				{
					*pp = 255;

					if (i > rt) rt = i;
					if (i < lt) lt = i;
					if (j < tp) tp = j;
					if (j > bt) bt = j;

					cnt++;
				}
			}

			p += 3;
			pp += 3;
		}
	}

	int r, l, t, b;
	int r1, l1, t1, b1;
	double screenWidthRate = ((double)(1080)) * m_nImageWidth / 1920 / m_nImageHeight;

	if (cnt > 1)
	{
		double rate = (double(rt - lt)) / (bt - tp) / screenWidthRate;
		//			cout << "  " << rate << "  " << rt - lt << "  " << bt - tp;

		if ((rate < 0.9) || ((bt - tp < 27) && (rate < 3)))//one enemy  
		{
			nEnemyCount = 1;
			pEnemy[0].m_enemyNormal.x1 = lt;
			pEnemy[0].m_enemyNormal.y1 = tp;
			pEnemy[0].m_enemyNormal.x2 = rt;
			pEnemy[0].m_enemyNormal.y2 = bt;
		}
		else//two enemy
		{
			//first enemy
			r = lt; l = rt; t = bt; b = tp;

			for (j = tp; j <= bt; j++)
			{
				pp = pptr + (j * m_nImageWidth + lt) * 3;

				for (i = lt; i < (lt + rt) / 2; i++)
				{
					if (*pp)
					{
						if (i > r) r = i;
						if (i < l) l = i;
						if (j < t) t = j;
						if (j > b) b = j;
					}

					pp += 3;
				}
			}

			r1 = r; l1 = l; t1 = t; b1 = b;

			//second enemy
			r = lt; l = rt; t = bt; b = tp;

			for (j = tp; j <= bt; j++)
			{
				pp = pptr + (j * m_nImageWidth + (lt + rt) / 2) * 3;

				for (i = (lt + rt) / 2; i <= rt; i++)
				{
					if (*pp)
					{
						if (i > r) r = i;
						if (i < l) l = i;
						if (j < t) t = j;
						if (j > b) b = j;
					}

					pp += 3;
				}
			}

			if (l - r1 < (rt - lt) * 0.1)//one enemy
			{
				if (((rt - lt) > (bt - tp) * 4) && (bt - tp < 10))
				{
					nEnemyCount = 0;
				}
				else
				{
					nEnemyCount = 1;
					pEnemy[0].m_enemyNormal.x1 = lt;
					pEnemy[0].m_enemyNormal.y1 = tp;
					pEnemy[0].m_enemyNormal.x2 = rt;
					pEnemy[0].m_enemyNormal.y2 = bt;
				}
			}
			else//two enemy
			{
				if ((b1 == t1) || (((r1 - l1) > (b1 - t1) * 4) && (b1 - t1 < 15)))
				{
					nEnemyCount = 0;
				}
				else
				{
					nEnemyCount = 1;
					pEnemy[0].m_enemyNormal.x1 = l1;
					pEnemy[0].m_enemyNormal.y1 = t1;
					pEnemy[0].m_enemyNormal.x2 = r1;
					pEnemy[0].m_enemyNormal.y2 = b1;
				}

				if (!((b == t) || (((r - l) > (b - t) * 4) && (b - t < 15))))
				{
					pEnemy[nEnemyCount].m_enemyNormal.x1 = l;
					pEnemy[nEnemyCount].m_enemyNormal.y1 = t;
					pEnemy[nEnemyCount].m_enemyNormal.x2 = r;
					pEnemy[nEnemyCount].m_enemyNormal.y2 = b;
					nEnemyCount++;
				}
			}
		}
	}

	//recheck rect
	for (i = 0; i < nEnemyCount; i++)
	{
		r = (int)min(m_nImageWidth, pEnemy[i].m_enemyNormal.x2 + max((pEnemy[i].m_enemyNormal.x2 - pEnemy[i].m_enemyNormal.x1) * 0.2, 5));
		l = (int)max(0, pEnemy[i].m_enemyNormal.x1 - max((pEnemy[i].m_enemyNormal.x2 - pEnemy[i].m_enemyNormal.x1) * 0.2, 5));
		t = (int)max(0, tp - max((pEnemy[i].m_enemyNormal.y2 - pEnemy[i].m_enemyNormal.y1) * 0.2, 30));
		b = (int)min(m_nImageHeight, pEnemy[i].m_enemyNormal.y2 + max((pEnemy[i].m_enemyNormal.y2 - pEnemy[i].m_enemyNormal.y1) * 0.2, 30));

		for (j = t; j < b; j++)
		{
			p = pt + (j * m_nImageWidth + l) * 3;
			pp = pptr + (j * m_nImageWidth + l) * 3;

			for (int k = l; k < r; k++)
			{
				if ((*(p + 2) >= 254) && (*(p + 1) != 0) && (*p != 0) && (
					((*(p + 1) < 50) && (*p < 50))
					|| ((*(p + 1) < 120) && (*p < 120) && (((*(p + 1) < *p) ? *p - *(p + 1) : *(p + 1) - *p) < 4))

					)
					)
				{
					*pp = 255;

					if (k > pEnemy[i].m_enemyNormal.x2) pEnemy[i].m_enemyNormal.x2 = k;
					if (k < pEnemy[i].m_enemyNormal.x1) pEnemy[i].m_enemyNormal.x1 = k;
					if (j < pEnemy[i].m_enemyNormal.y1) pEnemy[i].m_enemyNormal.y1 = j;
					if (j > pEnemy[i].m_enemyNormal.y2) pEnemy[i].m_enemyNormal.y2 = j;
				}

				p += 3;
				pp += 3;
			}
		}

		pEnemy[i].m_enemyNormal.y2 = (int)min(m_nImageHeight, pEnemy[i].m_enemyNormal.y2 + (pEnemy[i].m_enemyNormal.y2 - pEnemy[i].m_enemyNormal.y1) * 0.3);
	}

	delete[]pptr;

	return nEnemyCount;
}

std::vector<EnemyRect> CParserEngine::GetEnemy(int otherPlayer_, int8_t health_)
{
	int i, j;
	int nEnemy = 0, nMapEnemy = 0;
	EnemyRect rtEnemy[5], rtMapEnemy[5];

	ZeroMemory(rtEnemy, sizeof(EnemyRect) * 5);
	ZeroMemory(rtMapEnemy, sizeof(EnemyRect) * 5);

	nEnemy = GetEnemyOnScreen(rtEnemy);

	if (otherPlayer_ != 0 && health_ != INVALID)
	{
		nMapEnemy = GetEnemyOnMap(rtMapEnemy);

		// combine two result
		for (i = 0; i < nMapEnemy; i ++)
		{
			if (rtMapEnemy[i].m_enemyNormal.x2 == 0)
			{
				continue;
			}

			for (j = 0; j < nEnemy; j ++)
			{
				if (rtEnemy[j].m_enemyNormal.x2 == 0)
				{
					continue;
				}

				if (rtMapEnemy[i].m_enemyNormal.y1 <= rtEnemy[j].m_enemyNormal.y2 &&
					rtMapEnemy[i].m_enemyNormal.y2 >= rtEnemy[j].m_enemyNormal.y1 &&
					rtMapEnemy[i].m_enemyNormal.x1 <= rtEnemy[j].m_enemyNormal.x2 &&
					rtMapEnemy[i].m_enemyNormal.x2 >= rtEnemy[j].m_enemyNormal.x1)
				{
					break;
				}
			}

			if (j < nEnemy)
			{
				int64_t v1 = (rtEnemy[j].m_enemyNormal.x2 - rtEnemy[j].m_enemyNormal.x1 + 1) * (rtEnemy[j].m_enemyNormal.y2 - rtEnemy[j].m_enemyNormal.y1 + 1);
				int64_t v2 = (rtMapEnemy[i].m_enemyNormal.x2 - rtMapEnemy[i].m_enemyNormal.x1 + 1) * (rtEnemy[i].m_enemyNormal.y2 - rtEnemy[i].m_enemyNormal.y1 + 1) * 2;
				
				if (v1 < v2)
				{
					rtMapEnemy[i].m_enemyNormal.x2 = (rtMapEnemy[i].m_enemyNormal.x2 + rtEnemy[j].m_enemyNormal.x2) / 2;
					rtMapEnemy[i].m_enemyNormal.x1 = (rtMapEnemy[i].m_enemyNormal.x1 + rtEnemy[j].m_enemyNormal.x1) / 2;
					rtMapEnemy[i].m_enemyNormal.y1 = min(rtMapEnemy[i].m_enemyNormal.y1, rtEnemy[j].m_enemyNormal.y1);
					rtMapEnemy[i].m_enemyNormal.y2 = (rtMapEnemy[i].m_enemyNormal.y2 + rtEnemy[j].m_enemyNormal.y2) / 2;
				}

				rtEnemy[j].m_enemyNormal.x2 = 0;
			}
		}

		for (j = 0; j < nEnemy; j ++)
		{
			if (rtEnemy[j].m_enemyNormal.x2 == 0)
			{
				nEnemy--;
				rtEnemy[j] = rtEnemy[nEnemy];
				j--;
			}
		}

		for (i = 0; i < nMapEnemy; i ++)
		{
			if (rtMapEnemy[i].m_enemyNormal.x2 > 0)
			{
				rtEnemy[nEnemy] = rtMapEnemy[i];
				nEnemy++;
			}
		}
	}

	std::vector<EnemyRect> res;

	// set head, body, leg
	for (i = 0; i < nEnemy; i ++)
	{
		rtEnemy[i].m_enemyHead.x1 = (rtEnemy[i].m_enemyNormal.x1 * 65 + rtEnemy[i].m_enemyNormal.x2 * 35) / 100;
		rtEnemy[i].m_enemyHead.x2 = (rtEnemy[i].m_enemyNormal.x1 * 35 + rtEnemy[i].m_enemyNormal.x2 * 65) / 100;
		rtEnemy[i].m_enemyHead.y1 = rtEnemy[i].m_enemyNormal.y1;
		rtEnemy[i].m_enemyHead.y2 = (rtEnemy[i].m_enemyNormal.y1 * 90 + rtEnemy[i].m_enemyNormal.y2 * 10) / 100;

		rtEnemy[i].m_enemyBody.x1 = rtEnemy[i].m_enemyNormal.x1;
		rtEnemy[i].m_enemyBody.x2 = rtEnemy[i].m_enemyNormal.x2;
		rtEnemy[i].m_enemyBody.y1 = (rtEnemy[i].m_enemyNormal.y1 * 90 + rtEnemy[i].m_enemyNormal.y2 * 10) / 100;
		rtEnemy[i].m_enemyBody.y2 = (rtEnemy[i].m_enemyNormal.y1 * 50 + rtEnemy[i].m_enemyNormal.y2 * 50) / 100;

		rtEnemy[i].m_enemyLeg.x1 = rtEnemy[i].m_enemyNormal.x1;
		rtEnemy[i].m_enemyLeg.x2 = rtEnemy[i].m_enemyNormal.x2;
		rtEnemy[i].m_enemyLeg.y1 = (rtEnemy[i].m_enemyNormal.y1 * 50 + rtEnemy[i].m_enemyNormal.y2 * 50) / 100;
		rtEnemy[i].m_enemyLeg.y2 = rtEnemy[i].m_enemyNormal.y2;

		rtEnemy[i].m_enemyNormal.x1 -= 3;
		rtEnemy[i].m_enemyNormal.y1 -= 3;
		rtEnemy[i].m_enemyNormal.x2 += 3;
		rtEnemy[i].m_enemyNormal.y2 += 3;

		res.push_back(rtEnemy[i]);
	}

	return res;
}
