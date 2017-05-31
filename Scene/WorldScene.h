#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

namespace WORLD_SPRITE_TAG
{
	const int WORLD_BG		= 21001;
	const int STAGEBUTTON1	= 21002;
	const int STAGEBUTTON2	= 21003;
	const int STAGEBUTTON3	= 21004;
	const int STAGEBUTTON4	= 21005;
	const int STAGEBUTTON5	= 21006;
	const int STAGEBUTTONLOCK = 21007;

	const int MENU_BG			= 21101;
	const int MENU_EXIT			= 21102;
	const int MENU_YESBUTTON	= 21103;
	const int MENU_NOBUTTON		= 21104;
}

#define WORLD_BG_TAG		this->getChildByTag(WORLD_SPRITE_TAG::WORLD_BG)
#define EXITMENU_BG_TAG		this->getChildByTag(WORLD_SPRITE_TAG::WORLD_BG)->getChildByTag(WORLD_SPRITE_TAG::MENU_BG)

struct STAGEPOSTION
{
	int x;
	int y;
};

const STAGEPOSTION stagePostion[MAXSTAGE] = { 360,250, 300,440, 190,630, 240,780, 365,900 };

class WorldScene : public cocos2d::Layer
{
	Size winSize;
	bool isInMenu;
public:

    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(WorldScene);
	void GameTouchInit();
	void GameSoundInit();
	void StageInit();

	void backGround();
	void StageButton();
	void StageStar();
	void StageLine();
	void popUpMenu();
	void onKeyReleased (EventKeyboard::KeyCode keyCode, Event* event);
	bool onTouchBegan(Touch* touch, Event* unused_event);
	
};

#endif
