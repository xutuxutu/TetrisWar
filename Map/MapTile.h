#ifndef __MAP_TILE_H_
#define __MAP_TILE_H_

#include "cocos2d.h"

USING_NS_CC;

class MapTile
{
private :
	int m_nIndex;
	int m_nDamageStack;
	int m_nX, m_nY;
	int m_bExistSoldier;
public :
	MapTile() : m_nX(0), m_nY(0), m_bExistSoldier(0), m_nIndex(0) , m_nDamageStack(0) {}
	MapTile(int x, int y, int Index, int damage, bool m_bExistSoldier) 
		:m_nX(0), m_nY(0), m_bExistSoldier(0), m_nIndex(0) , m_nDamageStack(0) {}
	~MapTile() {}

	void SetXpos(int x) { m_nX = x; }
	void SetYpos(int y) { m_nY = y; }
	void SetXYpos(int x, int y) { SetXpos(x), SetYpos(y); }
	void SetXYpos(Point point) { SetXpos(point.x), SetYpos(point.y); }
	void SetIndex(int index) { m_nIndex = index; }
	void SetSoldierExist(int dir) { m_bExistSoldier = dir; }
	void SetSoldierNotExist() { m_bExistSoldier = 0; }

	void IncreaseDamageStack(int damage) { m_nDamageStack += damage; }
	void ResetDamageStack() { m_nDamageStack = 0; }

	int GetXpos() { return m_nX; }
	int GetYpos() { return m_nY; }
	Point GetXYpos() { return Point(m_nX,m_nY); }
	int GetIndex() { return m_nIndex; }
	int GetSoldierIsExist() { return m_bExistSoldier; }
	int GetDamageStack() { return m_nDamageStack; }
};

#endif