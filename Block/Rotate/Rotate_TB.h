#ifndef __ROTATE_TB_H_
#define __ROTATE_TB_H_

#include "Rotate.h"

class Rotate_TB : public Rotate
{
public :
	Rotate_TB() : Rotate() {}
	virtual ~Rotate_TB(){}

	virtual void RotateState01(std::array<Soldier*,4>& temp);
	virtual void RotateState02(std::array<Soldier*,4>& temp);
	virtual void RotateState03(std::array<Soldier*,4>& temp);
	virtual void RotateState04(std::array<Soldier*,4>& temp);
};

#endif