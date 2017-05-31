#include "TitleScene.h"
#include "WorldScene.h"


Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);

    return scene;
}


bool TitleScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	winSize = Director::getInstance()->getWinSize();
	canTouch = false;

	GameTouchInit();
	GameSoundInit();
	backGround();
    return true;
}

void TitleScene::GameTouchInit()
{
	auto listener=EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TitleScene::onTouchBegan, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TitleScene::GameSoundInit()
{
	CocosDenshion::SimpleAudioEngine::getInstance() -> playBackgroundMusic("GameScene/Sound/TITEL_BGM.mp3",true);
}

void TitleScene::backGround()
{
	auto sprBG = Sprite::create("GameScene/Title/BG.jpg");
	sprBG->setPosition(winSize.width / 2, winSize.height/ 2);
	sprBG->setTag( TITLE_SPRITE_TAG::WORLD_BG );
	this->addChild(sprBG);

	backGround_Soldier();
}

void TitleScene::backGround_Soldier()
{
	auto sprBG_Soldier = Sprite::create("GameScene/Title/BG_Soldier.png");
	sprBG_Soldier->setPosition(winSize.width / 2, winSize.height/ 2);
	sprBG_Soldier->setOpacity(0);
	this->addChild(sprBG_Soldier);

	auto action = DelayTime::create(0.2);
	auto action1 = FadeIn::create(0.7);
	auto callback = CallFunc::create( CC_CALLBACK_0(TitleScene::backGround_Name, this) );
	auto sequence = Sequence::create(action, action1,action, callback, NULL);
	sprBG_Soldier->runAction(sequence);
}

void TitleScene::backGround_Name()
{
	auto sprBG_Name = Sprite::create("GameScene/Title/BG_Name.png");
	sprBG_Name->setPosition(winSize.width / 2,  winSize.height/ 2 - 300);
	sprBG_Name->setOpacity(0);
	this->addChild(sprBG_Name);

	auto action1 = FadeIn::create(0.7);
	auto action2 = MoveTo::create(1.5, Point(winSize.width / 2, winSize.height/ 2));
	auto spawn = Spawn::create(action1, action2 , NULL);
	auto callback = CallFunc::create( CC_CALLBACK_0(TitleScene::backGround_Text, this) );
	auto sequence = Sequence::create(spawn, callback, NULL);
   
	sprBG_Name->runAction(sequence);
}

void TitleScene::backGround_Text()
{
	auto sprBG_Text = Sprite::create("GameScene/Title/BG_Text.png");
	sprBG_Text->setPosition(Point(0,0));
	sprBG_Text->setAnchorPoint(Point(0,0));
	sprBG_Text->setOpacity(0);
	this->addChild(sprBG_Text);

	auto action1 = FadeIn::create(0.7);
	auto action2 = FadeOut::create(0.7);
	auto spawn = Sequence::create(action1, action2, NULL);
	auto repForever = RepeatForever::create(spawn);

	sprBG_Text->runAction(repForever);
	canTouch = true;
}

bool TitleScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Point location = touch->getLocation();
	if(canTouch)
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		CocosDenshion::SimpleAudioEngine::getInstance() -> stopBackgroundMusic(true);
		auto transition = TransitionFade::create(1.0, WorldScene::createScene());
		Director::getInstance()->replaceScene(transition);
	}
	return true;
}
