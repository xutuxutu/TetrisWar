#ifndef __ROTATE_IB_H_
#define __ROTATE_IB_H_

#include "Rotate.h"

class Rotate_IB :public Rotate
{
public :
	Rotate_IB() : Rotate() {}
	virtual ~Rotate_IB() {}

	virtual void RotateState01(std::array<Soldier*,4>& temp);
	virtual void RotateState02(std::array<Soldier*,4>& temp);
	virtual void RotateState03(std::array<Soldier*,4>& temp);
	virtual void RotateState04(std::array<Soldier*,4>& temp);
};

#endif