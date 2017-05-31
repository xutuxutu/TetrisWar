#ifndef __BLOCK_LIST_H_
#define __BLOCK_LIST_H_

#include <list>
#include "Block.h"

namespace LAYER_SIZE
{
	const int X = 120;
	const int Y = 120;
}

namespace B_LIST_POSITION
{
	const Point POSITION_01 = Point(490 + LAYER_SIZE::X/2, 30 + LAYER_SIZE::Y/2);
	const Point POSITION_02 = Point(290 + LAYER_SIZE::X/2, 30 + LAYER_SIZE::Y/2);
	const Point POSITION_03 = Point(90 + LAYER_SIZE::X/2, 30 + LAYER_SIZE::Y/2);
}
class BlockList
{
private :
	int m_nCaptainHp;
	std::list<Block*> m_sBlockList;
public :
	BlockList() : m_nCaptainHp(5) {}
	~BlockList() { m_sBlockList.clear(); }

	Block& InsertBlock();
	void DeleteBlock(int position);
	void SortBlock();
	Block& RotateBlock(int blockNum);

	bool IsGameOver() { return m_nCaptainHp <= 0; }
	void DecreaseHP() { m_nCaptainHp -= 1; }
	int GetHp() { return m_nCaptainHp; }
	Block& GetBlock(int num);
	std::list<Block*>& GetBlockList() { return m_sBlockList; }

	int GetBlockNum() { return m_sBlockList.size(); }
};

#endif