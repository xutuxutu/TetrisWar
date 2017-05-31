#include "Archer.h"

void Archer::SetMapIndex()
{
	Soldier::SetMapIndex();

	for (int i = 0; i < 2; i++)
		m_nRange[i] = Soldier::GetMapIndex() + ((10 * Soldier::GetDirect()) * (i + 1));
}

int Archer::UseSkill(int index)
{
	if (m_nRange[0] == index)
	{
		m_nRange[0] = -1;
		return 1;
	}

	else if (m_nRange[1] == index)
	{
		if (m_nRange[0] == -1)
			return 0;
		else
			return 2;
	}

	return 0;
}