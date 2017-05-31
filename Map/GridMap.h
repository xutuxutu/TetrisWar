#ifndef __GRIDMAP_H_
#define __GRIDMAP_H_

#include <array>
#include <list>
#include "MapTile.h"
#include "Block.h"

namespace MAP
{
	const int LEFT_SPACE = 62;
	const int RIGHT_SPACE = 62;

	const int LOCATE_X = 0;
	const int LOCATE_Y = 260;
	const int MAX_X_SIZE = 720;
	const int MAX_Y_SIZE = 935;

	const int X_SIZE = 7;
	const int Y_SIZE = 11;
	const int CELL_X = 85;
	const int CELL_Y = 85;
}

namespace MAP_LOCATE
{
	const int X = 0;
	const int Y = 260;
};

USING_NS_CC;

class GridMap
{
private :
	int m_nDangerousFigure[MAP::X_SIZE][2];
	std::array<std::array<MapTile,MAP::X_SIZE>, MAP::Y_SIZE> m_sMap;
	std::list<Soldier*> m_sP_Soldier;
	std::list<Soldier*> m_sE_Soldier;
public :
	GridMap();
	~GridMap() {}

	void UpdateDangerousFigure();
	int CheckDangerousFigure(Block& Block, int mapIndex);

	bool SummonPlayerSoldier(Block& Block, int mapIndex);
	int SummonEnemySoldier(Block& Block, int mapIndex);
	
	void SetSoldierExist(int num, int dir) { m_sMap[num/10][num%10].SetSoldierExist(dir); }
	void SetSoldierNotExist(int num) { m_sMap[num/10][num%10].SetSoldierNotExist(); }

	void SkillDamageStack(int index, int damage) { m_sMap[index/10][index%10].IncreaseDamageStack(damage); }
	void ResetDamageStack();

	int GetDamageStack(int index) { return m_sMap[index/10][index%10].GetDamageStack(); }
	
	std::list<Soldier*>& GetPlayerSoldier() { return m_sP_Soldier; }
	std::list<Soldier*>& GetEnemySoldier() { return m_sE_Soldier; }
};

#endif
