#ifndef __ROTATE_LB_H_
#define __ROTATE_LB_H_

#include "Rotate.h"

class Rotate_LB : public Rotate
{
public :
	Rotate_LB() : Rotate() {}
	virtual ~Rotate_LB(){}

	virtual void RotateState01(std::array<Soldier*,4>& temp);
	virtual void RotateState02(std::array<Soldier*,4>& temp);
	virtual void RotateState03(std::array<Soldier*,4>& temp);
	virtual void RotateState04(std::array<Soldier*,4>& temp);
};

#endif