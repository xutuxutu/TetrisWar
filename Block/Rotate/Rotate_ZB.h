#ifndef __ROTATE_ZB_H_
#define __ROTATE_ZB_H_

#include "Rotate.h"

class Rotate_ZB : public Rotate
{
public :
	Rotate_ZB() : Rotate() {}
	virtual ~Rotate_ZB(){}

	virtual void RotateState01(std::array<Soldier*,4>& temp);
	virtual void RotateState02(std::array<Soldier*,4>& temp);
	virtual void RotateState03(std::array<Soldier*,4>& temp);
	virtual void RotateState04(std::array<Soldier*,4>& temp);
};

#endif