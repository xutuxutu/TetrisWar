#ifndef __ROTATE_H_
#define __ROTATE_H_

#include <array>
#include "cocos2d.h"
#include "Warrior.h"
#include "Archer.h"
#include "Magician.h"

const int BlockAncher_X  = 0;
const int BlockAncher_Y  = 0;
const int PIECE_X_SIZE = 30;
const int PIECE_Y_SIZE = 30;

USING_NS_CC;

class Rotate //추상 클래스
{
private :
	int m_nB_RotateState;
public :
	Rotate() : m_nB_RotateState(0) {}
	virtual ~Rotate() {}

	void RotateBlock(std::array<Soldier*,4>& temp);
	virtual void RotateState01(std::array<Soldier*,4>& temp) = 0; //순수 가상함수
	virtual void RotateState02(std::array<Soldier*,4>& temp) = 0;
	virtual void RotateState03(std::array<Soldier*,4>& temp) = 0;
	virtual void RotateState04(std::array<Soldier*,4>& temp) = 0;
};

#endif