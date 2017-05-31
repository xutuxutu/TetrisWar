#ifndef __ARCHER_H_
#define __ARCHER_H_

#include "Soldier.h"

class Archer : public Soldier
{
private :
	int m_nRange[2];
public :
	Archer() : Soldier(0,0,2,1,SOLDIER_TYPE::ARCHER) {}
	Archer(int x, int y, int atkPoint) : Soldier(x,y,atkPoint,1,SOLDIER_TYPE::ARCHER) {}
	virtual ~Archer() {}

	virtual void SetMapIndex();
	virtual int UseSkill(int index);
};

#endif