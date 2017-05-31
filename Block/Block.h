#ifndef __BLOCK_H_
#define __BLOCK_H_

#include "Rotate_SB.h"
#include "Rotate_IB.h"
#include "Rotate_TB.h"
#include "Rotate_LB.h"
#include "Rotate_RLB.h"
#include "Rotate_ZB.h"
#include "Rotate_RZB.h"

#include "Soldier.h"
#include "cocos2d.h"

USING_NS_CC;

namespace BLOCK_TYPE //1:¤± 2:¤Ó 3: ¤Ç 4: ¤¤ 5: ¦¥ 6: Z 7: ¡Ã
{
	enum {S_B, I_B, T_B, L_B, RL_B, Z_B, RZ_B };
};

class Block
{
private :
	int m_nX, m_nY;
	int m_nBlockType;
	std::array<Soldier*,4> m_sBlockPiece;
public :
	Rotate* m_sRotateBlock;
public :
	Block(int x, int y, int type, Soldier* soldier_1, Soldier* soldier_2, Soldier* soldier_3, Soldier* soldier_4);
	~Block();
	
	void RotateBlock();
	
	int GetXpos() { return m_nX; }
	int GetYpos() { return m_nY; }
	int GetBlockType() { return m_nBlockType; }
	std::array<Soldier*,4>& GetPieceArray(){ return m_sBlockPiece; } 

	void SetXpos(int x) { m_nX = x; }
	void SetYpos(int y) { m_nY = y; }
	void SetXYpos(Vec2 point) { SetXpos(point.x), SetYpos(point.y); } 

	void SetBlockPiece(int type);
};

#endif