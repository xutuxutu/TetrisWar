#include "Rotate_IB.h"

void Rotate_IB::RotateState01(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X, BlockAncher_Y);
	temp[1]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE);
	temp[2]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE * 2);
	temp[3]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE * 3);
}

void Rotate_IB::RotateState02(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X, BlockAncher_Y);
	temp[1]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y);
	temp[2]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 2, BlockAncher_Y);
	temp[3]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 3, BlockAncher_Y);
}

void Rotate_IB::RotateState03(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE * 3);
	temp[1]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE * 2);
	temp[2]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE);
	temp[3]->SetXYpos(BlockAncher_X, BlockAncher_Y);
}

void Rotate_IB::RotateState04(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 3, BlockAncher_Y);
	temp[1]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 2, BlockAncher_Y);
	temp[2]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y);
	temp[3]->SetXYpos(BlockAncher_X, BlockAncher_Y);
}