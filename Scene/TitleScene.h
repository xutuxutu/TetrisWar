#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

namespace TITLE_SPRITE_TAG
{
	const int WORLD_BG		= 11001;
	const int STARTBUTTON	= 11002;
}

#define TITLE_BG_TAG this->getChildByTag(TITLE_SPRITE_TAG::WORLD_BG)

class TitleScene : public cocos2d::Layer
{
private:
	Size winSize;
	bool canTouch;
public:

    static cocos2d::Scene* createScene();

    virtual bool init();  
    
    CREATE_FUNC(TitleScene);
	void GameTouchInit();
	void GameSoundInit();

	void backGround();
	void backGround_Soldier();
	void backGround_Name();
	void backGround_Text();

	bool onTouchBegan(Touch* touch, Event* unused_event);
};

#endif
