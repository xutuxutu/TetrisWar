#include "Soldier.h"

Soldier::Soldier()
{
}

Soldier::~Soldier()
{
}


bool Soldier::operator==(const Soldier& soldier)
{
	if(m_nY == soldier.m_nY)
	{
		if(m_nX == soldier.m_nX)
		{
			if(m_nDirect == soldier.m_nDirect)
				return true;
		}
	}

	return false;
}
bool Soldier::SoliderBeDamaged(int damage)
{ 
	int beforeAtk = m_nAtkPoint;
	m_nAtkPoint -= damage; 

	if(beforeAtk > damage)
	{
		for(int i = beforeAtk; i >= m_nAtkPoint; i--)
			m_sSprite->removeChildByTag(i);
	}

	return IsDead(); 
}