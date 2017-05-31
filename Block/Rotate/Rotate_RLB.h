#ifndef __ROTATE_RLB_H_
#define __ROTATE_RLB_H_

#include "Rotate.h"

class Rotate_RLB : public Rotate 
{
public :
	Rotate_RLB() : Rotate() {}
	virtual ~Rotate_RLB(){}

	virtual void RotateState01(std::array<Soldier*,4>& temp);
	virtual void RotateState02(std::array<Soldier*,4>& temp);
	virtual void RotateState03(std::array<Soldier*,4>& temp);
	virtual void RotateState04(std::array<Soldier*,4>& temp);
};

#endif