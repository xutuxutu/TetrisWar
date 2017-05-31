#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "BlockList.h"
#include "GridMap.h"
#include "WorldScene.h"
#include "GameManager.h"
//#include "KreanUTF_8.h"

USING_NS_CC;
const float DELAY_TIME = 0.4;
const float B_REGEN_TIME = 8.0;
const float B_SCALE_RATIO = 2.83;

typedef struct STAGE_FACTOR
{
	float PLAYER_BLOCK_REGEN_TIME;
	float ENEMY_BLOCK_REGEN_TIME;
	float SUMMON_ENEMY_TIME;
	float MOVE_INTERVAL;
}Stage_Factor;
namespace SPRITE_SIZE
{
	const int HP_BAR_X = 575;
	const int HP_BAR_Y = 60;
	const int DE_AMOUNT = 110;
}

namespace SPRITE_TAG
{
	const int SKILL = 10;
	const int BG = 1000;
	const int MAP = 1001;
	const int FRAME = 1002;
	const int E_HP_BAR = 1003;
	const int P_HP_BAR = 1004;

	const int MENU_BG			= 110100;
	const int MENU_BACK			= 110200;
	const int MENU_YESBUTTON	= 110300;
	const int MENU_NOBUTTON		= 110400;
}

namespace FIRST_B_TAG
{
	const int LAYER = 1500;
	const int P_FIRST = 2000;
	const int P_SECOND = 2001;
	const int P_THIRD = 2002;	
	const int P_FOURTH = 2003;
}

namespace SECOND_B_TAG
{
	const int LAYER = 1501;
	const int P_FIRST = 2000;
	const int P_SECOND = 2011;
	const int P_THIRD = 2012;	
	const int P_FOURTH = 2013;
}

namespace THIRD_B_TAG
{
	const int LAYER = 1502;
	const int P_FIRST = 2020;
	const int P_SECOND = 2021;
	const int P_THIRD = 2022;	
	const int P_FOURTH = 2023;
}

#define BG_TAG this->getChildByTag(SPRITE_TAG::BG)
#define MAP_TAG this->getChildByTag(SPRITE_TAG::BG)->getChildByTag(SPRITE_TAG::MAP)
#define FRAME_TAG  this->getChildByTag(SPRITE_TAG::BG)->getChildByTag(SPRITE_TAG::FRAME)
#define BACKMENU_BG_TAG	this->getChildByTag(SPRITE_TAG::BG)->getChildByTag(SPRITE_TAG::MENU_BG)

class GameScene : public cocos2d::Layer
{
private :
	bool IsOver;
	bool IsInMenu;
	GridMap m_sMap;
	int m_nAttackSoundID[3];
	int m_nTouchLayerTag;
	bool m_bTouchOnce;
	bool m_bUsePlayerSchedule;
	bool m_bUseEnemySchedule;
	Size winSize;
	Stage_Factor m_sStageFactor;
	BlockList m_sBlockList;
	BlockList m_sEnemyBlockList;
public:
	GameScene();

    static cocos2d::Scene* createScene();											//�� ����

	virtual bool init();															//�ʱ�ȭ �Լ�
	void update(float delta);														//������Ʈ �Լ� 
  
	void PrintAllSprite();															//��������Ʈ ��� ���

	//Initialize
	void BackGroundInit();															//��� �ʱ�ȭ
	void GameFrameInit();															//���� ������ �ʱ�ȭ
	void HP_IconInit();
	void SetPlayerHP_Bar(int width);
	void SetEnemyHP_Bar(int width);
	void GameSoundInit();
	void MapImageInit();															//�� �ʱ�ȭ
	void TouchEventInit();															//��ġ �̺�Ʈ ���� �ʱ�ȭ
	void CreatePlayerBlockLayer(int x, int y, int pos);								//��� ���̾� �ʱ�ȭ
	void InitAtkBar(Sprite* sprite, int dir, int atk);

	//Function
	void ListBlockSort();															//��� ������
	void CreatePlayerSoldier(Block& block);											//�÷��̾��� ������� �̹����� ���
	void CreateEnemySoldier(Block& block);											//�� ������ �̹��� ���
	bool BlockSetCheck(Block& block, Sprite* layer);								//�÷��̾ ����� �÷������� ������ ��ġ Ȯ��
	bool SoldierCollisionCheck(Soldier* soldier);									//������� �浹üũ
	void SodierUseSkill();															//������� ��ų ���
	void DestructSoldier(Soldier* temp);
	void DestructSoldier2(Ref* sender, Soldier* temp);

	//Print
	void RunSkillEffect(Sprite* sprite, int type);									//���Ÿ� ���� ����Ʈ
	void RunAttackEffect(Sprite* sprite);											//���� ���� ����Ʈ
	void PlayAttackEffectSound(int type);											//���� ����Ʈ ����
	void RunRegenBlockEffect(Sprite* sprite);										//��� ����� ����Ʈ
	void RunAttackAnimation(Sprite* sprite, int type, int dir);						//���� �ִϸ��̼�
	void RunBeShotAnimation(Sprite* sprite, int type, int dir);						//�ǰ� �ִϸ��̼�
	void RunMoveAnimation(Ref* sender, Soldier* temp);								//�̵� �ִϸ��̼�
	void ShowGameResult(int result);												//���� ���â ���
	void popUpMenu();

	//CALLBACK
	void TimerInit(float delta);
	void SummonEnemySoldier(float delta);
	void MovePlayerSoldier(float delta);
	void MoveEnemySoldier(float delta);
	void CreatePlayerBlock(float delta);
	void CreateEnemyBlock(float delta);
	void TouchTimeOnce(float delte);
	void TouchNumInit(float delta);
	void RemoveEffect(Ref* sender, Sprite* sprite);
	void StopAnimation01(Ref* sender, Sprite* sprite);
	void StopAnimation02(Ref* sender, Sprite* sprite);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);
	void onKeyReleased (EventKeyboard::KeyCode keyCode, Event* event);
    CREATE_FUNC(GameScene);
};

#endif


//������� �̵��Լ� �ϳ��� ��ġ��
//��ġ���� �ذ� - �ѹ� ��ġ������ Moved�� �ҷ����� ����.
