#ifndef __SOLDIER_H_
#define __SOLDIER_H_

#include "cocos2d.h"

USING_NS_CC;

namespace SOLDIER_TYPE
{
	enum { WARRIOR, ARCHER, MAGICIAN };
};

namespace DIRECT
{
	const int UP  = 1;
	const int DOWN = -1;
}

class Soldier //�߻� Ŭ����
{
private :
	Animate* m_sReady;
	Sprite* m_sSprite;
	int m_nSkillDamage;
	int m_nSoldierType;
	int m_nX, m_nY;
	int m_nAtkPoint;
	int m_nDirect; //�� = -1, �Ʊ� = 1
	int m_nMapIndex;
	static const int m_nMoveSpeed = 85;
public :
	Soldier();
	Soldier(int x, int y, int atkPoint, int skillDamage, int type) 
		: m_nX(x), m_nY(y), m_nAtkPoint(atkPoint), m_nDirect(0), m_nSoldierType(type), m_sSprite(NULL),m_sReady(NULL), m_nMapIndex(0), m_nSkillDamage(skillDamage) {}
	virtual ~Soldier();

	bool SoliderBeDamaged(int damage);

	int GetXpos() { return m_nX; }
	int GetYpos() { return m_nY; }
	int GetAtkPoint() { return m_nAtkPoint;}
	int GetSoldierType() { return m_nSoldierType; }
	int GetDirect() { return m_nDirect; }
	int GetMapIndex() { return m_nMapIndex; }
	int GetSkillDamage() { return m_nSkillDamage; }
	Sprite* GetSprite() { return m_sSprite; }
	Animate* GetAnimate() { return m_sReady;  }

	void MoveFront() { m_nY += m_nMoveSpeed*m_nDirect; }										//dir -> ���� = 1 , �Ʒ��� = -1

	void SetXpos(int x) { m_nX = x; }
	void SetYpos(int y) { m_nY = y; }
	void SetXYpos(int x, int y) { SetXpos(x), SetYpos(y); }
	void SetDirect(int x) { m_nDirect = x; }
	void SetSprite(Sprite* soldierSpr) { m_sSprite = soldierSpr; }
	void SetAnimation(Animation* ani) { m_sReady = Animate::create(ani); }
	virtual void SetMapIndex() { m_nMapIndex = (m_nY/85)*10 + m_nX/85; }						//���� ������ �� �ε��� ��ġ ���� �� ���� ���� �缳��
	
	bool operator==(const Soldier& soldier);

	bool IsDead() { return m_nAtkPoint <= 0 ? true : false; }

	virtual int UseSkill(int index) = 0;														//���� �����Լ�.
};

#endif