#pragma once

#include "Common.h"
#include "TimelineData.h"

class CParserEngine
{
public:
	CParserEngine();
	virtual ~CParserEngine();

	CTimelineData run(unsigned char* imgPtr_, int imgWidth_, int imgHeight_);

private:
	unsigned char* m_pImageBufferPtr;
	int16_t m_nImageWidth;
	int16_t m_nImageHeight;

	WHITE_PATTERN m_PtnScore[10];
	WHITE_PATTERN m_PtnTime[10];
	WHITE_PATTERN m_PtnAmmo[10];
	WHITE_PATTERN m_PtnArmor[10];
	WHITE_PATTERN m_PtnCredits[10];
	COLOR_PATTERN m_PtnAgents[N_AGENTS];
	WHITE_PATTERN m_PtnWeaponChange[1];
	WHITE_PATTERN m_PtnSpike[1];
	COLOR_PATTERN m_PtnHitHeadShot[2];
	WHITE_PATTERN m_PtnOtherPlayer[1];
	COLOR_PATTERN m_PtnMapAgents[N_MAPAGENTS];
	WHITE_PATTERN m_PtnMapRedCircle[1];
	WHITE_PATTERN m_PtnWeapon[18];

	int m_allyScoreY, m_allyScoreX1, m_allyScoreX10, m_allyScoreX01;
	int m_enemyScoreY, m_enemyScoreX1, m_enemyScoreX10, m_enemyScoreX01;
	int m_timeY, m_timeX100, m_timeX010, m_timeX001;
	int m_ammoY, m_ammoX100, m_ammoX010, m_ammoX001;
	int m_healthY, m_healthX100, m_healthX010, m_healthX001, m_healthX10, m_healthX01, m_healthX1;
	int m_armorY, m_armorX10, m_armorX01, m_armorX1;
	int m_ammoleftY, m_ammoleftX100, m_ammoleftX010, m_ammoleftX001;
	int m_creditsY, m_creditsX1, m_creditsX10, m_creditsX100, m_creditsX1000, m_creditsX10000, m_creditsX100000;
	int m_agentsY, m_agentsXAlly, m_agentsXEnemy, m_agentsXStep;
	int m_weaponchangeY, m_weaponchangeX, m_weaponchangeY1, m_weaponchangeX1, m_weaponchangeY2, m_weaponchangeX2, m_weaponchangeY3, m_weaponchangeX3;
	int m_spikeY, m_spikeX, m_hitheadshotY, m_hitheadshotX, m_otherY, m_otherX;
	int m_skillY, m_skillStep, m_skillWidth;
	int m_weaponX, m_weaponY1, m_weaponY2, m_weaponY3;


private:
	int MatchWhitePattern(int x, int y, WHITE_PATTERN* ptn, int nPtn);
	int MatchWhitePattern_(int x, int y, WHITE_PATTERN* ptn, int nPtn);
	int MatchColorPattern(int x, int y, COLOR_PATTERN* ptn, int nPtn, bool flip = false);
	int MatchColorPattern_(int x, int y, COLOR_PATTERN* ptn, int nPtn, bool flip = false);
	int MatchMapPattern(int x, int y, COLOR_PATTERN* ptn, int nPtn);

	BOOL Init(int imgWidth_, int imgHeight_);

	int8_t GetYourTeamScore();
	int8_t GetEnemyTeamScore();
	std::vector<std::string> GetAllyAgents();
	std::vector<std::string> GetEnemyAgents();
	std::vector<EnemyRect> GetEnemy(int otherPlayer_, int8_t health_);
	int GetEnemyOnScreen(EnemyRect* pEnemy);
	int GetEnemyOnMap(EnemyRect* pMapEnemy);

	int8_t GetRoundTime();
	int8_t GetHealth();
	int8_t GetArmor();
	int16_t GetAmmo();
	int16_t GetAmmoLeft();
	int16_t GetCredits();
	int8_t GetHasSpike();
	int8_t GetWeaponId();
	int8_t GetHitHeadShot();
	void GetAbilityLeft(int8_t* pAbilityInfo);
	int GetIsOtherPlayer();

};

