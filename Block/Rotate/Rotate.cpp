#include "Rotate.h"

void Rotate::RotateBlock(std::array<Soldier*,4>& temp)
{
	if(m_nB_RotateState == 4)
		m_nB_RotateState = 0;
		
	m_nB_RotateState++;

		switch (m_nB_RotateState)
		{
		case 1 :
			RotateState01(temp);
			break;
		case 2 :
			RotateState02(temp);
			break;
		case 3 :
			RotateState03(temp);
			break;
		case 4 :
			RotateState04(temp);
			break;
		}
}