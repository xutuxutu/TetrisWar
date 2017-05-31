#include "Block.h"

Block::Block(int x, int y, int type, Soldier* soldier_1, Soldier* soldier_2, Soldier* soldier_3, Soldier* soldier_4) 
	: m_nX(x), m_nY(y), m_nBlockType(type)
{
	m_sBlockPiece[0] = soldier_1;
	m_sBlockPiece[1] = soldier_2;
	m_sBlockPiece[2] = soldier_3;
	m_sBlockPiece[3] = soldier_4;
}

Block::~Block()
{
}

void Block::SetBlockPiece(int type)
{
	
	switch (m_nBlockType)
	{
	case BLOCK_TYPE::S_B :
		m_sRotateBlock = new Rotate_SB;
		m_sRotateBlock->RotateBlock(m_sBlockPiece);
		break;
	case BLOCK_TYPE::I_B :
		m_sRotateBlock = new Rotate_IB;
		m_sRotateBlock->RotateBlock(m_sBlockPiece);
		break;
	case BLOCK_TYPE::T_B :
		m_sRotateBlock = new Rotate_TB;
		m_sRotateBlock->RotateBlock(m_sBlockPiece);
		break;
	case BLOCK_TYPE::L_B :
		m_sRotateBlock = new Rotate_LB;
		m_sRotateBlock->RotateBlock(m_sBlockPiece);
		break;
	case BLOCK_TYPE::RL_B :
		m_sRotateBlock = new Rotate_RLB;
		m_sRotateBlock->RotateBlock(m_sBlockPiece);
		break;
	case BLOCK_TYPE::Z_B :
		m_sRotateBlock = new Rotate_ZB;
		m_sRotateBlock->RotateBlock(m_sBlockPiece);
		break;
	case BLOCK_TYPE::RZ_B :
		m_sRotateBlock = new Rotate_RZB;
		m_sRotateBlock->RotateBlock(m_sBlockPiece);
		break;
	}
}

void Block::RotateBlock()
{
	m_sRotateBlock->RotateBlock(m_sBlockPiece);
}