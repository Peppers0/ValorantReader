#pragma once

#include <string>
#include <vector>

#include "Common.h"

////////////////////////////////////////////////////////////////////////////////
// Common Structures
////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct rectangle
{
    rectangle() 
    {
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
    }

	T width(void) const
	{
		return x2 - x1 > 0 ? x2 - x1 : x1 - x2;
	}

	T height(void) const
	{
		return y2 - y1 > 0 ? y2 - y1 : y1 - y2;
	}

	T x1, y1;
	T x2, y2;
};

typedef rectangle<unsigned short> recti16;

typedef struct EnemyRect
{
    EnemyRect() : m_mapX(0), m_mapY(0) {}

	int16_t         m_mapX;
	int16_t         m_mapY;
	std::string     m_enemyAgent;
	recti16         m_enemyNormal;
	recti16         m_enemyHead;
	recti16         m_enemyBody;
	recti16         m_enemyLeg;
} EnemyRect;

typedef struct WHITE_PATTERN {
	int width;
	int height;
	char mask[MASK_LEN]; //0: no mask, 1: mask, valid length is width*height
} WHITE_PATTERN;

typedef struct COLOR_PATTERN {
	int width;
	int height;
	unsigned char R[MASK_LEN];
	unsigned char G[MASK_LEN];
	unsigned char B[MASK_LEN];
} COLOR_PATTERN;

////////////////////////////////////////////////////////////////////////////////
// Event Structures
////////////////////////////////////////////////////////////////////////////////
struct IEvent
{
protected:
	IEvent(): m_eventType(kEventNone) {}

public:
	static IEvent* createInstance(EventType eventType)
    {
        IEvent *event_ptr = nullptr;
        if (eventType == kEventAbilityCast)
        {
            event_ptr = new CAbilityCastEvent;
            event_ptr->m_eventType = kEventAbilityCast;
        }
        else if (eventType == kEventAmmoReload)
        {
            event_ptr = new CAmmoReloadEvent;
            event_ptr->m_eventType = kEventAmmoReload;
        }
        else if (eventType == kEventEnemyAppeared)
        {
            event_ptr = new CEnemyAppearedEvent;
            event_ptr->m_eventType = kEventEnemyAppeared;
        }
        else if (eventType == kEventEnemyKill)
        {
            event_ptr = new CKillEvent;
            event_ptr->m_eventType = kEventEnemyKill;
        }
        else if (eventType == kEventAllyDeath)
        {
            event_ptr = new CDeathEvent;
            event_ptr->m_eventType = kEventAllyDeath;
        }
        else if (eventType == kEventYouKilled)
        {
            event_ptr = new CYouKilledEvent;
            event_ptr->m_eventType = kEventYouKilled;
        }
        else if (eventType == kEventShoot)
        {
            event_ptr = new CShootEvent;
            event_ptr->m_eventType = kEventShoot;
        }

        return event_ptr;
    }

public:
	uint8_t         m_eventType;
 	// uint64_t     m_timestamp;
};

struct CAbilityCastEvent : public IEvent
{
    CAbilityCastEvent() : m_ability(-1) {}

	int8_t          m_ability;	// 0 - Q, 1 - C, 2 - E, 3 - X
};

struct CAmmoReloadEvent : public IEvent
{
    CAmmoReloadEvent() : m_oldAmmo(-1), m_newAmmo(-1) {}

	int16_t         m_oldAmmo;
	int16_t         m_newAmmo;
};

struct CDeathEvent : public IEvent
{
	std::string     m_killerAgent;
};

struct CEnemyAppearedEvent : public IEvent
{
	std::string     m_enemyAgent;
	EnemyRect       m_enemyRect;
};

struct CKillEvent : public IEvent
{
    std::string     m_killerAgent;
    std::string     m_targetAgent;
};

struct CShootEvent : public IEvent
{
    CShootEvent() : m_isFirstShot(-1), 
                    m_reactionTimeMs(-1) 
                    m_weaponId(-1) 
                    m_isTargetChanged(-1) 
                    m_crossHairX(-1) 
                    m_crossHairY(-1) 
                    m_crossHairZ(-1) 
                    m_hitType(0) 
                    m_hasKilledEnemy(false) 
                    m_crossHairZ(-1) 
                    {}

    int8_t          m_isFirstShot;
    int32_t         m_reactionTimeMs;
    int8_t          m_weaponId;
    int8_t          m_isTargetChanged;
    std::string     m_targetAgent;
    int16_t         m_crossHairX;
    int16_t         m_crossHairY;
    int16_t         m_crossHairZ;
    int8_t          m_hitType;
    int8_t          m_hasKilledEnemy;

    std::vector<EnemyRect> m_aryEnemyRects;
};

struct CYouKilledEvent : public IEvent
{
	std::string     m_killerAgent;
};


