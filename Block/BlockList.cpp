#include "BlockList.h"
#include "Warrior.h"
#include "Archer.h"
#include "Magician.h"

Block& BlockList::InsertBlock()
{
	int useNum = m_sBlockList.size();
	Point position;
	int solType = rand() % 3;
	Soldier* soldier[4];
	
	switch (useNum)
	{
	case 0 :
		position = B_LIST_POSITION::POSITION_01;
		break;
	case 1 :
		position = B_LIST_POSITION::POSITION_02;
		break;
	case 2 :
		position = B_LIST_POSITION::POSITION_03;
		break;
	}

	for(int i = 0; i < 4; i++ )
	{
		solType = rand() % 3;
		switch(solType)
		{
		case SOLDIER_TYPE::WARRIOR :
			soldier[i] = new Warrior;
			break;
		case SOLDIER_TYPE::ARCHER :
			soldier[i] = new Archer;
			break;
		case SOLDIER_TYPE::MAGICIAN :
			soldier[i] = new Magician;
			break;
			}
	}

	int type = rand() % 7;
	Block* newBlock = new Block(position.x, position.y, type, soldier[0], soldier[1], soldier[2], soldier[3]);
	newBlock->SetBlockPiece(type);
	m_sBlockList.push_back(newBlock);

	return  *newBlock;
}

void BlockList::DeleteBlock(int position)
{
	auto temp = m_sBlockList.begin();

	for(int i = 0 ; i < position; i ++)
		temp++;

	m_sBlockList.erase(temp);
}

void BlockList::SortBlock()
{
	auto temp = m_sBlockList.begin();

	for(int i = 0; i < m_sBlockList.size(); i++)
	{
		auto node = *temp;

		switch (i)
		{
		case 0 :
			node->SetXYpos(B_LIST_POSITION::POSITION_01);
			break;
		case 1 :
			node->SetXYpos(B_LIST_POSITION::POSITION_02);
			break;
		case 2 :
			node->SetXYpos(B_LIST_POSITION::POSITION_03);
			break;
		}
		temp++;
	}
}

Block& BlockList::RotateBlock(int blockNum)
{
	auto temp = m_sBlockList.begin();

	for(int i = 0 ; i < blockNum; i ++)
		temp++;

	auto node = *temp;
	node->RotateBlock();

	return *node;
}

Block& BlockList::GetBlock(int num)
{	
	auto temp = m_sBlockList.begin();

	for(int i = 0 ; i < num; i ++)
		temp++;

	return *(*temp);
}