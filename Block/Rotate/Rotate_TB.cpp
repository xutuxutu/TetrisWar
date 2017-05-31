#include "Rotate_TB.h"

void Rotate_TB::RotateState01(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X , BlockAncher_Y);
	temp[1]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y);
	temp[2]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 2, BlockAncher_Y);
	temp[3]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE);
}

void Rotate_TB::RotateState02(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X , BlockAncher_Y + PIECE_Y_SIZE * 2); //( 0 ,60)
	temp[1]->SetXYpos(BlockAncher_X , BlockAncher_Y + PIECE_Y_SIZE); //(0 ,30)
	temp[2]->SetXYpos(BlockAncher_X, BlockAncher_Y); //(0,0)
	temp[3]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE); //( 30,30)
}

void Rotate_TB::RotateState03(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X + PIECE_X_SIZE * 2, BlockAncher_Y + PIECE_Y_SIZE);
	temp[1]->SetXYpos(BlockAncher_X + PIECE_X_SIZE , BlockAncher_Y + PIECE_Y_SIZE);
	temp[2]->SetXYpos(BlockAncher_X , BlockAncher_Y  + PIECE_Y_SIZE);
	temp[3]->SetXYpos(BlockAncher_X + PIECE_X_SIZE , BlockAncher_Y);
}

void Rotate_TB::RotateState04(std::array<Soldier*,4>& temp)
{
	temp[0]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y); //(30,0)
	temp[1]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE); //(30,30)
	temp[2]->SetXYpos(BlockAncher_X + PIECE_X_SIZE, BlockAncher_Y + PIECE_Y_SIZE * 2); //(30,60)
	temp[3]->SetXYpos(BlockAncher_X, BlockAncher_Y + PIECE_Y_SIZE); // (0,30)
}