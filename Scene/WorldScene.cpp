#include "WorldScene.h"
#include "ScriptScene.h"


Scene* WorldScene::createScene()
{
    auto scene = Scene::create();
    auto layer = WorldScene::create();
    scene->addChild(layer);

    return scene;
}

bool WorldScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }


	winSize = Director::getInstance()->getWinSize();
	this->setKeypadEnabled(1);
	isInMenu = false;

	StageInit();
	GameTouchInit();
	GameSoundInit();
	backGround();
	StageButton();
	StageStar();
	//StageLine();

    return true;
}

void WorldScene::StageInit()
{
	// 저장소에 있는 정보(스테이지)를 불러옴
	int temp = UserDefault::getInstance()->getIntegerForKey("openStage");
	if(temp > 0 && temp <= 5)
		GameManager::GetInstance()->setStage(temp);
	else
		GameManager::GetInstance()->setStage(1);
}

void WorldScene::GameTouchInit()
{
	auto listener  = EventListenerTouchOneByOne::create();
	auto listener2 = EventListenerKeyboard::create();
	
	listener->onTouchBegan = CC_CALLBACK_2(WorldScene::onTouchBegan, this);
	listener2->onKeyReleased = CC_CALLBACK_2(WorldScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void WorldScene::GameSoundInit()
{
	CocosDenshion::SimpleAudioEngine::getInstance() -> playBackgroundMusic("GameScene/Sound/WORLDMAP_BGM.mp3",true);
}

void WorldScene::popUpMenu()
{
	auto sprBgMenu = Sprite::create("GameScene/BackGroundLayer.png");
	sprBgMenu->setAnchorPoint(Point(0,0));
	sprBgMenu->setPosition(Point(0,0));
	sprBgMenu->setOpacity(50);
	sprBgMenu->setTag(WORLD_SPRITE_TAG::MENU_BG);
	WORLD_BG_TAG->addChild(sprBgMenu,4);
	
	auto sprExitMenu = Sprite::create("GameScene/PopUp/ExitMenu.jpg");
	sprExitMenu->setAnchorPoint(Point(0.5,0.5));
	sprExitMenu->setPosition(Point(WORLD_BG_TAG->getContentSize().width / 2, WORLD_BG_TAG->getContentSize().height / 2));
	sprExitMenu->setTag(WORLD_SPRITE_TAG::MENU_EXIT);
	EXITMENU_BG_TAG->addChild(sprExitMenu,5);

	auto sprYesButton = Sprite::create("GameScene/PopUp/YesButton.jpg");
	sprYesButton->setAnchorPoint(Point(0.5,0.5));
	sprYesButton->setPosition(Point(EXITMENU_BG_TAG->getContentSize().width*0.27,EXITMENU_BG_TAG->getContentSize().height/2.3));
	sprYesButton->setTag(WORLD_SPRITE_TAG::MENU_YESBUTTON);
	EXITMENU_BG_TAG->addChild(sprYesButton,6);

	auto sprNoButton = Sprite::create("GameScene/PopUp/NoButton.jpg");
	sprNoButton->setAnchorPoint(Point(0.5,0.5));
	sprNoButton->setPosition(Point(EXITMENU_BG_TAG->getContentSize().width*0.73,EXITMENU_BG_TAG->getContentSize().height/2.3));
	sprNoButton->setTag(WORLD_SPRITE_TAG::MENU_NOBUTTON);
	EXITMENU_BG_TAG->addChild(sprNoButton,7);
}

void WorldScene::backGround()
{
	auto sprBackGround = Sprite::create("GameScene/WorldMap/WorldMap.png");
	sprBackGround->setPosition(Point(0,0));
	sprBackGround->setAnchorPoint(Point(0,0));
	sprBackGround->setTag(WORLD_SPRITE_TAG::WORLD_BG);
	this->addChild(sprBackGround);

}

void WorldScene::StageButton()
{
	for(int i = 0; i < MAXSTAGE; i++)
	{
		if(GameManager::GetInstance()->getOpenStage() >= i+1)
		{
			auto sprStageButton = Sprite::create("GameScene/WorldMap/openStage.png");
			//auto sprStageButton = Sprite::create(StringUtils::format("GameScene/WorldMap/openStage%d.png", i+1));
			sprStageButton->setPosition(Point(stagePostion[i].x, stagePostion[i].y));
			sprStageButton->setAnchorPoint(Point(0.5,0.5));
			sprStageButton->setTag(WORLD_SPRITE_TAG::STAGEBUTTON1+i);
			WORLD_BG_TAG->addChild(sprStageButton);
		}
		else
		{
			auto sprStageButton = Sprite::create("GameScene/WorldMap/lockStage.png");
			auto sprStageLocker = Sprite::create("GameScene/WorldMap/locker.png");
			//auto sprStageButton = Sprite::create(StringUtils::format("GameScene/WorldMap/LockStage%d.png", i+1));
			sprStageButton->setPosition(Point(stagePostion[i].x, stagePostion[i].y));
			sprStageLocker->setPosition(Point(stagePostion[i].x, stagePostion[i].y));
			sprStageButton->setAnchorPoint(Point(0.5,0.5));
			sprStageLocker->setAnchorPoint(Point(0.5,0.8));
			sprStageButton->setTag(WORLD_SPRITE_TAG::STAGEBUTTON1+i);
			WORLD_BG_TAG->addChild(sprStageButton);
			WORLD_BG_TAG->addChild(sprStageLocker);
		}
	}
}

void WorldScene::StageStar()
{
	for(int i = 0; i < MAXSTAGE; i++)
	{

			Sprite* starSpr[3];
			char stageStarCount[11];
			sprintf(stageStarCount, "Stage%dStar", i+1);
			switch(UserDefault::getInstance()->getIntegerForKey(stageStarCount))
			{
			case 0 :
				starSpr[0] = Sprite::create("GameScene/WorldMap/NoStar.png");
				starSpr[1] = Sprite::create("GameScene/WorldMap/NoStar.png");
				starSpr[2] = Sprite::create("GameScene/WorldMap/NoStar.png");		
				break;
			case 1 :
				starSpr[0] = Sprite::create("GameScene/WorldMap/Start.png");
				starSpr[1] = Sprite::create("GameScene/WorldMap/NoStar.png"); 
				starSpr[2] = Sprite::create("GameScene/WorldMap/NoStar.png"); 
			case 2 :
				starSpr[0] = Sprite::create("GameScene/WorldMap/Start.png");
				starSpr[1] = Sprite::create("GameScene/WorldMap/Start.png");
				starSpr[2] = Sprite::create("GameScene/WorldMap/NoStar.png"); 
				break;
			case 3 :
				starSpr[0] = Sprite::create("GameScene/WorldMap/Start.png");
				starSpr[1] = Sprite::create("GameScene/WorldMap/Start.png");
				starSpr[2] = Sprite::create("GameScene/WorldMap/Start.png");
				break;
			}

			for(int i = 0; i < 3; i++)
				starSpr[i]->setAnchorPoint(Point(0.5,0.5));

			starSpr[0]->setPosition(stagePostion[i].x - 30,stagePostion[i].y + 30);
			starSpr[1]->setPosition(stagePostion[i].x,stagePostion[i].y + 50);
			starSpr[2]->setPosition(stagePostion[i].x + 30,stagePostion[i].y + 30);

			WORLD_BG_TAG->addChild(starSpr[0],3);
			WORLD_BG_TAG->addChild(starSpr[1],3);
			WORLD_BG_TAG->addChild(starSpr[2],3);
		
	}
}

void WorldScene::StageLine()
{
	Sprite* lineSprS1[4];
	Sprite* lineSprS2[10];
	for(int i = 0; i < 4; i++)
	{
		lineSprS1[i] = Sprite::create("GameScene/WorldMap/VisitLine.png");
		lineSprS1[i]->setPosition(500 - (30 * i), 200 + (10 * i));
	}

	for(int i = 0; i < 10; i++)
		lineSprS2[i] = Sprite::create("GameScene/WorldMap/VisitLine.png");

	lineSprS2[0]->setPosition(310, 265);
	lineSprS2[1]->setPosition(280, 275);
	lineSprS2[2]->setPosition(250, 290);
	lineSprS2[3]->setPosition(225, 305);
	lineSprS2[4]->setPosition(215, 325);
	lineSprS2[5]->setPosition(235, 335);
	lineSprS2[6]->setPosition(260, 342);
	lineSprS2[7]->setPosition(280, 355);
	lineSprS2[8]->setPosition(295, 370);
	lineSprS2[9]->setPosition(300, 390);

	for(int i = 0; i < 4; i++)
		WORLD_BG_TAG->addChild(lineSprS1[i]);

	for(int i = 0; i < 10; i++)
		WORLD_BG_TAG->addChild(lineSprS2[i]);
}

bool WorldScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Point location = touch->getLocation();

	// 메뉴 진입 상황일때
	if(isInMenu)
	{
		auto sprYesButton = (Sprite*)EXITMENU_BG_TAG->getChildByTag(WORLD_SPRITE_TAG::MENU_YESBUTTON);
		auto sprNoButton = (Sprite*)EXITMENU_BG_TAG->getChildByTag(WORLD_SPRITE_TAG::MENU_NOBUTTON);
		Rect rectYesButton = sprYesButton->getBoundingBox();
		Rect rectNoButton = sprNoButton->getBoundingBox();

		if(rectYesButton.containsPoint(location))
		{
			CCDirector::sharedDirector()->end();
		}

		if(rectNoButton.containsPoint(location))
		{
			EXITMENU_BG_TAG->removeAllChildren();
			WORLD_BG_TAG->removeChildByTag(WORLD_SPRITE_TAG::MENU_BG);

			isInMenu = false;
		}
	}
	// 스테이지 선택
	else
	{
		for(int i = 0; i < MAXSTAGE; i++)
		{
			auto sprStageButton = (Sprite*)WORLD_BG_TAG->getChildByTag(WORLD_SPRITE_TAG::STAGEBUTTON1+i); 
			Rect rectStageButton = sprStageButton->getBoundingBox();

			if(rectStageButton.containsPoint(location))
			{
				if(GameManager::GetInstance()->getOpenStage() < i+1)
					break;
			
				GameManager::GetInstance()->setInStage(i+1);

				Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
				CocosDenshion::SimpleAudioEngine::getInstance() -> stopBackgroundMusic(true);
//				auto transition = TransitionFadeUp::create(0.5, GameScene::createScene());
				auto transition = TransitionFadeUp::create(0.5, ScriptScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		}
	}
	
	return false;
}

void WorldScene::onKeyReleased (EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && !isInMenu)
	{
		isInMenu = true;
		popUpMenu();
	}
}