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

	if(mapIndex % 10 > MAP::X_SIZE - 1)															//1���ڸ� �ε��� �κа� üũ
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

int GridMap::CheckDangerousFigure(Block& block, int mapIndex)									//���� �ø��� ���ϸ� -1, �� �ܿ� ���赵 �� �� ��ġ ��ȯ
{
	int i = 0;
	bool isOverlap;
	int blockNum[4]	= { 0 };																	//�� ������ ���� ����
	int dangerFigure = 0;																		//���� ��ġ		
	int indexX[4], indexY[4];
	int arrLayer[4][4] = { 0 };

	if(mapIndex % 10 > MAP::X_SIZE - 1)															//1���ڸ� �ε��� �κа� üũ
		return -1;

	for(Soldier* temp : block.GetPieceArray())													
	{
		isOverlap = false;
		indexX[i] = temp->GetXpos() / PIECE_X_SIZE;												//���� ��ǥ�� �̿��Ͽ� Index���� ���� (��ǥ/�������� = �迭�� �� �ε���)
		indexY[i] = temp->GetYpos() / PIECE_Y_SIZE;

		if(mapIndex % 10 - indexX[i] < 0)														//�� �ε��� ���� �迭�� �ε��� ���� ���Ͽ� ����(x��ǥ)�� ���� ������ Ȯ��.
			return -1;

		if(m_sMap[mapIndex / 10 - indexY[i]][mapIndex%10 - indexX[i]].GetSoldierIsExist())		//���̾ ���簡 ��ġ�� ���� ���� �� ���� �÷��� �ִ� ���縦 ���Ͽ� �ʿ� ���簡 �����ϸ� ����.
			return -1;
		
		
		blockNum[indexX[i]] += 1;

		if(blockNum[indexX[i]] > 1)																//�� ���ο� ���� 1�� �̻��� ���
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

int GridMap::SummonEnemySoldier(Block& block, int mapIndex)									//�ø� ��ġ�� ���� �Ű������� �ް�, �ø� �� �ִ��� ���θ� Ȯ���Ͽ� �� ���� ������� ��ȯ�ϴ� �Լ�.
{
	int i = 0;
	int indexX[4], indexY[4];
	int arrLayer[4][4] = { 0 };

	if(mapIndex % 10 > MAP::X_SIZE - 1)															//1���ڸ� �ε��� �κа� üũ
		return 0;

	for(Soldier* temp : block.GetPieceArray())														//4x4 �迭�� �� ������ ����ְ�, ���� �� ���� �ø� �� �ִ��� üũ.
	{
		indexX[i] = temp->GetXpos() / PIECE_X_SIZE;												//���� ��ǥ�� �̿��Ͽ� Index���� ���� (��ǥ/�������� = �迭�� �� �ε���)
		indexY[i] = temp->GetYpos() / PIECE_Y_SIZE;

		//arrLayer[indexY[i]][indexX[i]] = 1;														//���̾�(4x4)�迭�� �� �ε����� �����Ͽ� ����

		if(mapIndex % 10 - indexX[i] < 0)														//�� �ε��� ���� �迭�� �ε��� ���� ���Ͽ� ����(x��ǥ)�� ���� ������ Ȯ��.
			return 0;

		if(m_sMap[mapIndex / 10 - indexY[i]][mapIndex%10 - indexX[i]].GetSoldierIsExist())		//���̾ ���簡 ��ġ�� ���� ���� �� ���� �÷��� �ִ� ���縦 ���Ͽ� �ʿ� ���簡 �����ϸ� ����.
			return 0;

		i++;
	}

	i = 0;

	for(Soldier* temp : block.GetPieceArray())													//���� ������ �ø��� ����
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