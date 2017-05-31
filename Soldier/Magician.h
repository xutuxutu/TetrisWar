#ifndef __MAGICIAN_H_
#define __MAGICIAN_H_

#include "Soldier.h"

class Magician : public Soldier
{
private :
	int m_nRange[3];
public :
	Magician() : Soldier(0,0,3,1,SOLDIER_TYPE::MAGICIAN) {}
	Magician(int x, int y, int atkPoint) : Soldier(x,y,atkPoint, 1 ,SOLDIER_TYPE::MAGICIAN) {}
	virtual ~Magician() {}

	virtual void SetMapIndex();
	virtual int UseSkill(int index);
};

#endif