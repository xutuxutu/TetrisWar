#ifndef __ROTATE_SB_H_
#define __ROTATE_SB_H_

#include "Rotate.h"

class Rotate_SB : public Rotate
{
public :
	Rotate_SB() : Rotate() {}
	virtual ~Rotate_SB(){}

	virtual void RotateState01(std::array<Soldier*,4>& temp);
	virtual void RotateState02(std::array<Soldier*,4>& temp);
	virtual void RotateState03(std::array<Soldier*,4>& temp);
	virtual void RotateState04(std::array<Soldier*,4>& temp);
};

#endif