#include "Magician.h"

void Magician::SetMapIndex()
{
	Soldier::SetMapIndex();

	for (int i = 0; i<3; i++)
		m_nRange[i] = Soldier::GetMapIndex() + (10 * Soldier::GetDirect()) + (i - 1);				//������ ��ų ���� ����(�ڽ��� �ٷ� �� ��ĭ)

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