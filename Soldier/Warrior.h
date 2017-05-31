#ifndef _WARRIOR_H_
#define _WARRIOR_H_

#include "Soldier.h"

class Warrior : public Soldier
{
public :
	Warrior() : Soldier(0,0,5,0,SOLDIER_TYPE::WARRIOR) {}
	Warrior(int x, int y, int atkPoint) : Soldier(x,y,atkPoint,0,SOLDIER_TYPE::WARRIOR) {}
	virtual ~Warrior() {}
	
	virtual void SetMapIndex() { Soldier::SetMapIndex(); }
	virtual int UseSkill(int index) { return false; }
};

#endif