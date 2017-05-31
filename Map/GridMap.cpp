#include "GridMap.h"

GridMap::GridMap()
{
	for(int y = 0 ; y < MAP::Y_SIZE; y++)
	{
		for(int x = 0; x < MAP::X_SIZE; x++)
		{
			m_sMap[y][x].SetIndex((y * 10) + x);
			m_sMap[y][x].SetXYpos(Point(x + MAP::CELL_X + MAP::LEFT_SPACE, y * MAP::CELL_Y));
		}
	}

	for(int i = 0; i < MAP::X_SIZE; i++)
	{
		m_nDangerousFigure[i][0] = 0;
		m_nDangerousFigure[i][1] = 0;
	}
}

bool GridMap::SummonPlayerSoldier(Block& block, int mapIndex)
{
	int i = 0;
	int indexX[4], indexY[4];

	if(mapIndex % 10 > MAP::X_SIZE - 1)															//1의자리 인덱스 부분과 체크
		return false;

	for(Soldier* temp : block.GetPieceArray())
	{
		indexX[i] = temp->GetXpos() / PIECE_X_SIZE;
		indexY[i] = temp->GetYpos() / PIECE_Y_SIZE;

		if(indexX[i] + mapIndex > MAP::X_SIZE -1)
			return false;

		if(m_sMap[mapIndex/10 + indexY[i]][mapIndex%10 + indexX[i]].GetSoldierIsExist())
			return false;

		i++;
	}

	i = 0;

	for(Soldier* temp : block.GetPieceArray())
	{
		temp->SetXpos(MAP::LEFT_SPACE + (indexX[i] + mapIndex % 10) * MAP::CELL_X);
		temp->SetYpos((indexY[i] + mapIndex / 10) * MAP::CELL_Y);
		temp->SetMapIndex();

		m_sP_Soldier.push_back(temp);
		m_sMap[mapIndex/10 + indexY[i]][mapIndex%10 + indexX[i]].SetSoldierExist(temp->GetDirect());

		i++;
	}

	return true;
}

void GridMap::UpdateDangerousFigure()
{
	for(int i = 0; i < MAP::X_SIZE; i++)
	{
		m_nDangerousFigure[i][0] = 0;
		m_nDangerousFigure[i][1] = 0;
	}

	for(int x = 0; x < MAP::X_SIZE; x++)
	{
		for(int y = 0 ; y < MAP::Y_SIZE; y++)
		{
			if(m_sMap[y][x].GetSoldierIsExist() == 1)
			{
				m_nDangerousFigure[x][0] += y * 2;
				m_nDangerousFigure[x][1] += 1;
			}
			else if(m_sMap[y][x].GetSoldierIsExist() == 0)
				m_nDangerousFigure[x][0] += 0;
		}
	}
}

int GridMap::CheckDangerousFigure(Block& block, int mapIndex)									//블럭을 올리지 못하면 -1, 그 외엔 위험도 총 합 수치 반환
{
	int i = 0;
	bool isOverlap;
	int blockNum[4]	= { 0 };																	//한 라인의 블럭의 갯수
	int dangerFigure = 0;																		//위험 수치		
	int indexX[4], indexY[4];
	int arrLayer[4][4] = { 0 };

	if(mapIndex % 10 > MAP::X_SIZE - 1)															//1의자리 인덱스 부분과 체크
		return -1;

	for(Soldier* temp : block.GetPieceArray())													
	{
		isOverlap = false;
		indexX[i] = temp->GetXpos() / PIECE_X_SIZE;												//블럭의 좌표를 이용하여 Index값을 저장 (좌표/블럭사이즈 = 배열에 들어갈 인덱스)
		indexY[i] = temp->GetYpos() / PIECE_Y_SIZE;

		if(mapIndex % 10 - indexX[i] < 0)														//맵 인덱스 값과 배열의 인덱스 값을 비교하여 영역(x좌표)을 벗어 났는지 확인.
			return -1;

		if(m_sMap[mapIndex / 10 - indexY[i]][mapIndex%10 - indexX[i]].GetSoldierIsExist())		//레이어에 병사가 위치한 값과 현재 맵 위에 올려져 있는 병사를 비교하여 맵에 병사가 존재하면 리턴.
			return -1;
		
		
		blockNum[indexX[i]] += 1;

		if(blockNum[indexX[i]] > 1)																//한 라인에 블럭이 1개 이상일 경우
		{
			if(m_nDangerousFigure[mapIndex % 10 - indexX[i]][1] < blockNum[indexX[i]])
				isOverlap = true;
		}

		if(!isOverlap)
			dangerFigure += m_nDangerousFigure[mapIndex % 10 - indexX[i]][0];
		
		++i;
	}
	return dangerFigure;
}

int GridMap::SummonEnemySoldier(Block& block, int mapIndex)									//올릴 위치와 블럭을 매개변수로 받고, 올릴 수 있는지 여부를 확인하여 맵 위에 병사들을 소환하는 함수.
{
	int i = 0;
	int indexX[4], indexY[4];
	int arrLayer[4][4] = { 0 };

	if(mapIndex % 10 > MAP::X_SIZE - 1)															//1의자리 인덱스 부분과 체크
		return 0;

	for(Soldier* temp : block.GetPieceArray())														//4x4 배열에 블럭 정보를 집어넣고, 블럭을 맵 위에 올릴 수 있는지 체크.
	{
		indexX[i] = temp->GetXpos() / PIECE_X_SIZE;												//블럭의 좌표를 이용하여 Index값을 저장 (좌표/블럭사이즈 = 배열에 들어갈 인덱스)
		indexY[i] = temp->GetYpos() / PIECE_Y_SIZE;

		//arrLayer[indexY[i]][indexX[i]] = 1;														//레이어(4x4)배열에 블럭 인덱스를 참조하여 저장

		if(mapIndex % 10 - indexX[i] < 0)														//맵 인덱스 값과 배열의 인덱스 값을 비교하여 영역(x좌표)을 벗어 났는지 확인.
			return 0;

		if(m_sMap[mapIndex / 10 - indexY[i]][mapIndex%10 - indexX[i]].GetSoldierIsExist())		//레이어에 병사가 위치한 값과 현재 맵 위에 올려져 있는 병사를 비교하여 맵에 병사가 존재하면 리턴.
			return 0;

		i++;
	}

	i = 0;

	for(Soldier* temp : block.GetPieceArray())													//블럭을 맵위에 올리는 과정
	{
		temp->SetXpos(MAP::LEFT_SPACE + ((mapIndex % 10 - indexX[i])  * MAP::CELL_X));
		temp->SetYpos((mapIndex / 10 - indexY[i]) * MAP::CELL_Y);
		temp->SetMapIndex();

		m_sE_Soldier.push_back(temp);
		m_sMap[mapIndex/10 - indexY[i]][mapIndex%10 - indexX[i]].SetSoldierExist(temp->GetDirect());

		i++;
	}

	return 1;
}

void GridMap::ResetDamageStack()
{
	for(int y = 0; y < MAP::Y_SIZE; y++)
	{
		for(int x = 0; x<MAP::X_SIZE; x++)
			m_sMap[y][x].ResetDamageStack();
	}
}