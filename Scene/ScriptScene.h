#ifndef __SCRIPT_SCENE_H__
#define __SCRIPT_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

namespace SCRIPT_SPRITE_TAG
{
	const int BG		= 921101;
	const int BOX		= 921102;
	const int CHARACTER	= 921103;
	const int LABEL_TAG	= 921104;
	const int FRAME		= 921105;
}

namespace SCRIPT_STATE
{
	enum
	{
		isString, isSpace, isLabel, isBracket, isMinus, isEndLine, isNULL, isEndChapter, isTalk, isEndTalk, isImgPos
	};
}

#define SCRIPT_BOX_TAG		this->getChildByTag(SCRIPT_SPRITE_TAG::BOX)
#define SCRIPT_FRAME_TAG	this->getChildByTag(SCRIPT_SPRITE_TAG::FRAME)
//메모리 초기화
#define ZeroMemory(ptr,size) memset((ptr),0,(size))

class ScriptScene : public cocos2d::Layer
{
private :
	char ChapterName[5];
	unsigned char * pBuffer;
	unsigned char * pBufferTemp;
	char pLabelBuf[200];
	char characterName[50];
	bool isFirstTalk;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  

	void SpriteInit();
	void GameFrameInit();
	void HP_IconInit();
	void SetEnemyHP_Bar(int width);
	void SetPlayerHP_Bar(int width);
	void TextBoxInit();
	void BackGroundInit(Sprite* bgSpr);

	void DataInit();
	void TextDataInit();
	void SelectChapter(unsigned char *ch, char *chapter);
	int GetTextToken(unsigned char ch);
	void PrintText();
	void PrintCharacter(bool isLeft);

	void touchEventInit();
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);

    CREATE_FUNC(ScriptScene);
};

#endif 
