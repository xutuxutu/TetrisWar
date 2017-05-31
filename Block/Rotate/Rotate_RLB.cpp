#include "Rotate_RLB.h"

void Rotate_RLB::RotateState01(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X, BlockAncher_Y); //(0,0)
	temp[1]->SetXYpos(BlockAncher_X  + PIECE_X_SIZE, BlockAncher_Y); //(30, 0)
	temp[2]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE); //(30,30)
	temp[3]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE * 2); //(30,60)
}

void Rotate_RLB::RotateState02(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE); // (0,30)
	temp[1]->SetXYpos(BlockAncher_X, BlockAncher_Y); //(0, 0)
	temp[2]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y); // ( 30,0)
	temp[3]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 2, BlockAncher_Y); //( 60 ,0) 
}

void Rotate_RLB::RotateState03(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE * 2);
	temp[1]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE * 2);
	temp[2]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE);
	temp[3]->SetXYpos(BlockAncher_X, BlockAncher_Y);
}

void Rotate_RLB::RotateState04(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 2, BlockAncher_Y);
	temp[1]->SetXYpos(BlockAncher_X  + PIECE_X_SIZE * 2, BlockAncher_Y + PIECE_Y_SIZE);
	temp[2]->SetXYpos(BlockAncher_X  + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE);
	temp[3]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE);
}