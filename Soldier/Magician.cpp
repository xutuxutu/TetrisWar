#include "Magician.h"

void Magician::SetMapIndex()
{
	Soldier::SetMapIndex();

	for (int i = 0; i<3; i++)
		m_nRange[i] = Soldier::GetMapIndex() + (10 * Soldier::GetDirect()) + (i - 1);				//마법사 스킬 범위 지정(자신의 바로 앞 세칸)

}
int Magician::UseSkill(int index)
{

	for(int i = 0; i<3; i++)
	{
		if(index == m_nRange[i])
			return 1;
	}

	return 0;
}