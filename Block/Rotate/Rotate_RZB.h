#ifndef __ROTATE_RZB_H_
#define __ROTATE_RZB_H_

#include "Rotate.h"

class Rotate_RZB : public Rotate
{
public :
	Rotate_RZB() : Rotate() {}
	virtual ~Rotate_RZB(){}

	virtual void RotateState01(std::array<Soldier*,4>& temp);
	virtual void RotateState02(std::array<Soldier*,4>& temp);
	virtual void RotateState03(std::array<Soldier*,4>& temp);
	virtual void RotateState04(std::array<Soldier*,4>& temp);
};

#endif