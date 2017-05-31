#include "GameScene.h"

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();

    scene->addChild(layer);

    return scene;
}
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	IsInMenu = false;
	TouchEventInit();
	PrintAllSprite();

    return true;
}

GameScene::GameScene() : m_bUsePlayerSchedule(true), m_bUseEnemySchedule(true), m_bTouchOnce(true), IsOver(false)
{
	winSize = Director::getInstance()->getWinSize();										//윈도우 사이즈 측정
	srand(time(NULL));
	this->scheduleOnce(schedule_selector(GameScene::TimerInit), 1.0);

	switch(GameManager::GetInstance()->getInStage())
	{
	case 1:
		m_sStageFactor.MOVE_INTERVAL = 2.0;
		m_sStageFactor.SUMMON_ENEMY_TIME = 4.0;
		m_sStageFactor.ENEMY_BLOCK_REGEN_TIME = 8.0;
		m_sStageFactor.PLAYER_BLOCK_REGEN_TIME = 6.0;
		break;
	case 2:
		m_sStageFactor.MOVE_INTERVAL = 1.9;
		m_sStageFactor.SUMMON_ENEMY_TIME = 3.5;
		m_sStageFactor.ENEMY_BLOCK_REGEN_TIME = 7.5;
		m_sStageFactor.PLAYER_BLOCK_REGEN_TIME = 6.0;
		break;
	case 3:
		m_sStageFactor.MOVE_INTERVAL = 1.8;
		m_sStageFactor.SUMMON_ENEMY_TIME = 2.5;
		m_sStageFactor.ENEMY_BLOCK_REGEN_TIME = 7.0;
		m_sStageFactor.PLAYER_BLOCK_REGEN_TIME = 6.0;
		break;
	case 4:
		m_sStageFactor.MOVE_INTERVAL = 1.7;
		m_sStageFactor.SUMMON_ENEMY_TIME = 1.8;
		m_sStageFactor.ENEMY_BLOCK_REGEN_TIME = 6.5;
		m_sStageFactor.PLAYER_BLOCK_REGEN_TIME = 5.5;
		break;
	case 5:
		m_sStageFactor.MOVE_INTERVAL = 1.5;
		m_sStageFactor.SUMMON_ENEMY_TIME = 1.0;
		m_sStageFactor.ENEMY_BLOCK_REGEN_TIME = 6.0;
		m_sStageFactor.PLAYER_BLOCK_REGEN_TIME = 5.5;
		break;
	}
}

void GameScene::TimerInit(float delta)
{
	CreatePlayerBlock(0);
	CreateEnemyBlock(0);
	this->schedule(schedule_selector(GameScene::CreatePlayerBlock), m_sStageFactor.PLAYER_BLOCK_REGEN_TIME);			//플레이어 블록 생성 스케줄
	this->schedule(schedule_selector(GameScene::CreateEnemyBlock), m_sStageFactor.ENEMY_BLOCK_REGEN_TIME);			//적 블록 생성 스케줄
	this->schedule(schedule_selector(GameScene::MovePlayerSoldier), m_sStageFactor.MOVE_INTERVAL);			//플레이어 병사 이동 스케쥴
	this->schedule(schedule_selector(GameScene::SummonEnemySoldier), m_sStageFactor.SUMMON_ENEMY_TIME);	//적 병사 생성 스케줄
	this->scheduleUpdate();																	//업데이트 스케줄
}

void GameScene::PrintAllSprite()
{
	BackGroundInit();
	GameFrameInit();
	MapImageInit();
	GameSoundInit();
	SetPlayerHP_Bar(5);
	SetEnemyHP_Bar(5);
	HP_IconInit();
}

void GameScene::BackGroundInit()
{
	auto bgSpr = Sprite::create("GameScene/BackGroundLayer.png");						//아무 모양도 없는 빈 이미지 이용.

	bgSpr->setAnchorPoint(Point(0.5,0.5)); 
	bgSpr->setPosition(winSize.width / 2, winSize.height/ 2);
	bgSpr->setTag(SPRITE_TAG::BG);

	this->addChild(bgSpr,0);
}

void GameScene::GameFrameInit()
{
	auto interSpr = Sprite::create("GameScene/GameFrame.png");

	interSpr->setAnchorPoint(Point(0.0, 0.0));
	interSpr->setPosition(0,0);
	interSpr->setTag(SPRITE_TAG::FRAME);

	BG_TAG->addChild(interSpr,1);
}

void GameScene::popUpMenu()
{
	auto sprBgMenu = Sprite::create("GameScene/BackGroundLayer.png");
	sprBgMenu->setAnchorPoint(Point(0,0));
	sprBgMenu->setPosition(Point(0,0));
	sprBgMenu->setOpacity(50);
	sprBgMenu->setTag(SPRITE_TAG::MENU_BG);
	BG_TAG->addChild(sprBgMenu);
	
	auto sprExitMenu = Sprite::create("GameScene/PopUp/BackMenu.jpg");
	sprExitMenu->setAnchorPoint(Point(0.5,0.5));
	sprExitMenu->setPosition(Point(BG_TAG->getContentSize().width / 2, BG_TAG->getContentSize().height / 2));
	sprExitMenu->setTag(SPRITE_TAG::MENU_BACK);
	BACKMENU_BG_TAG->addChild(sprExitMenu,3);

	auto sprYesButton = Sprite::create("GameScene/PopUp/YesButton.jpg");
	sprYesButton->setAnchorPoint(Point(0.5,0.5));
	sprYesButton->setPosition(Point(BACKMENU_BG_TAG->getContentSize().width*0.27,BACKMENU_BG_TAG->getContentSize().height/2.3));
	sprYesButton->setTag(SPRITE_TAG::MENU_YESBUTTON);
	BACKMENU_BG_TAG->addChild(sprYesButton,4);

	auto sprNoButton = Sprite::create("GameScene/PopUp/NoButton.jpg");
	sprNoButton->setAnchorPoint(Point(0.5,0.5));
	sprNoButton->setPosition(Point(BACKMENU_BG_TAG->getContentSize().width*0.73,BACKMENU_BG_TAG->getContentSize().height/2.3));
	sprNoButton->setTag(SPRITE_TAG::MENU_NOBUTTON);
	BACKMENU_BG_TAG->addChild(sprNoButton,5);
	Director::getInstance()->pause();
}

void GameScene::SetPlayerHP_Bar(int width)
{
	auto pBarSpr = Sprite::create("GameScene/Player/P_HP_BAR.png", Rect(0,0,25 + SPRITE_SIZE::DE_AMOUNT * width,60));


	pBarSpr->setAnchorPoint(Point(0,0));
	pBarSpr->setPosition(100, 179);
	pBarSpr->setTag(SPRITE_TAG::P_HP_BAR);

	FRAME_TAG->addChild(pBarSpr,2);
}

void GameScene::SetEnemyHP_Bar(int width)
{
	auto eBarSpr = Sprite::create("GameScene/Enemy/E_HP_BAR.png", Rect(0,0,25 + SPRITE_SIZE::DE_AMOUNT * width,60));

	eBarSpr->setAnchorPoint(Point(0,0));
	eBarSpr->setPosition(104, 1199);
	eBarSpr->setTag(SPRITE_TAG::E_HP_BAR);

	FRAME_TAG->addChild(eBarSpr,2);
}

void GameScene::HP_IconInit()
{
	auto pBarSpr = Sprite::create("GameScene/Player/P_HP_ICON.png");
	auto eBarSpr = Sprite::create("GameScene/Enemy/E_HP_ICON.png");

	eBarSpr->setAnchorPoint(Point(0,0));
	pBarSpr->setAnchorPoint(Point(0,0));
	eBarSpr->setPosition(74, 1204);
	pBarSpr->setPosition(74, 185);

	FRAME_TAG->addChild(pBarSpr,3);
	FRAME_TAG->addChild(eBarSpr,3);
}

void GameScene::MapImageInit()
{
	Sprite* bgSpr;
	switch(GameManager::GetInstance()->getInStage())
	{
	case 1:
		bgSpr = Sprite::create("GameScene/BackGround.png");
		break;
	case 2:
		bgSpr = Sprite::create("GameScene/BackGround2.png");
		break;
	case 3:
		bgSpr = Sprite::create("GameScene/BackGround3.png");
		break;
	case 4:
		bgSpr = Sprite::create("GameScene/BackGround4.png");
		break;
	case 5:
		bgSpr = Sprite::create("GameScene/BackGround2.png");
		break;
	}
	
	bgSpr->setAnchorPoint(Point(0,0)); 
	bgSpr->setPosition(MAP::LOCATE_X, MAP::LOCATE_Y);
	bgSpr->setTag(SPRITE_TAG::MAP);

	BG_TAG->addChild(bgSpr,0);
}

void GameScene::GameSoundInit()
{
	CocosDenshion::SimpleAudioEngine::getInstance() ->playBackgroundMusic("GameScene/Sound/BGM.mp3",true);								//배경음악
	CocosDenshion::SimpleAudioEngine::getInstance() -> preloadEffect("GameScene/Sound/WarriorAttack.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance() -> preloadEffect("GameScene/Sound/ArcherAttack.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance() -> preloadEffect("GameScene/Sound/MagicianAttack.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance() -> preloadEffect("GameScene/Sound/Damage.mp3");
}

void GameScene::TouchEventInit()
{
	this->setKeypadEnabled(1);
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	auto listener2 = EventListenerKeyboard::create();
	listener2->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);
}

void GameScene::PlayAttackEffectSound(int type)
{
	switch(type)
	{
	case SOLDIER_TYPE::WARRIOR :
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameScene/Sound/WarriorAttack.mp3");
		break;
	case SOLDIER_TYPE::ARCHER :
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameScene/Sound/ArcherAttack.mp3");
		break;
	case SOLDIER_TYPE::MAGICIAN :
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameScene/Sound/MagicianAttack.mp3");
		break;
	case 3 :
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameScene/Sound/WarriorAttack.mp3");
		break;
	case 4 :
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("GameScene/Sound/Damage.mp3");
	}
}

void GameScene::RunSkillEffect(Sprite* sprite, int type)
{

	Sprite* effect;
	effect = Sprite::create("GameScene/Effect_Layer.png");
	auto effectAni = Animation::create();

	switch(type)
	{
	case SOLDIER_TYPE::ARCHER :
		for(int i = 0; i<5; i++)
			effectAni->addSpriteFrameWithFile(StringUtils::format("GameScene/A_Effect/Effect%02d.png", i+1));
		break;
	case SOLDIER_TYPE::MAGICIAN :
		for(int i = 0; i<5; i++)
			effectAni->addSpriteFrameWithFile(StringUtils::format("GameScene/M_Effect/Effect%02d.png", i+1));
		break;
	}

	effect->setAnchorPoint(Point(0,0));
	effect->setPosition(0,0);
	effect->setTag(SPRITE_TAG::SKILL);
	effectAni->setDelayPerUnit(0.2);

	auto animate = Animate::create(effectAni);
	auto fadeOut = FadeOut::create(0.5);

	sprite->addChild(effect);

	auto action1 = DelayTime::create(0.6);
	auto action2 = CallFuncN::create(CC_CALLBACK_1(GameScene::RemoveEffect,this,sprite));
	auto action3 = Sequence::create(animate, action1,fadeOut, action2, NULL);

	effect->runAction(action3);
}

void GameScene::RunAttackEffect(Sprite* sprite)
{
	Sprite* effect;
	effect = Sprite::create("GameScene/Effect_Layer.png");
	auto effectAni = Animation::create();

	for(int i = 0; i<5; i++)
			effectAni->addSpriteFrameWithFile(StringUtils::format("GameScene/MA_Effect/Effect%02d.png", i+1));

	effect->setAnchorPoint(Point(0,0));
	effect->setPosition(0,0);
	effect->setTag(SPRITE_TAG::SKILL);
	effectAni->setDelayPerUnit(0.2);

	auto animate = Animate::create(effectAni);

	sprite->addChild(effect);

	auto action2 = CallFuncN::create(CC_CALLBACK_1(GameScene::RemoveEffect,this,sprite));
	auto action3 = Sequence::create(animate, action2, NULL);

	effect->runAction(action3);
}

void GameScene::RunRegenBlockEffect(Sprite* sprite)
{
	Sprite* effect;
	effect = Sprite::create("GameScene/Effect_Layer.png");
	auto effectAni = Animation::create();

	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_367.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_368.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_369.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_370.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_371.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_372.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_373.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_374.png");
	effectAni->addSpriteFrameWithFile("GameScene/E/Effects_375.png");


	effect->setAnchorPoint(Point(0.5,0.5));
	effect->setPosition(42,42);
	effect->setTag(SPRITE_TAG::SKILL);
	effectAni->setDelayPerUnit(0.1);

	auto animate = Animate::create(effectAni);

	sprite->addChild(effect);

	auto action2 = CallFuncN::create(CC_CALLBACK_1(GameScene::RemoveEffect,this,sprite));
	auto action3 = Sequence::create(animate, action2, NULL);

	effect->runAction(action3);
}
void GameScene::RunAttackAnimation(Sprite* sprite, int type, int dir)
{
	auto effectAni = Animation::create();
	auto originalSpr = Animation::create();

	if(dir == 1)
	{
		switch(type)
		{
		case SOLDIER_TYPE::WARRIOR :
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Attack_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Attack_Action02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Attack_Action03.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Player/W_Ready.png");
			break;
		case SOLDIER_TYPE::ARCHER :
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Attack_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Attack_Action02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Attack_Action03.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Player/A_Ready.jpg");
			break;
		case SOLDIER_TYPE::MAGICIAN :
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Attack_Action01.png");
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Attack_Action02.png");
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Attack_Action03.png");
			originalSpr->addSpriteFrameWithFile("GameScene/Player/M_Ready.png");
			break;
		}
	}
	else
	{
		switch(type)
		{
		case SOLDIER_TYPE::WARRIOR :
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Attack_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Attack_Action02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Attack_Action03.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Enemy/W_Ready.jpg");
			break;
		case SOLDIER_TYPE::ARCHER :
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Attack_Action01.png");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Attack_Action02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Attack_Action03.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Enemy/A_Ready.jpg");
			break;
		case SOLDIER_TYPE::MAGICIAN :
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Attack_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Attack_Action02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Attack_Action03.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Enemy/M_Ready.jpg");
			break;
		}
	}

	effectAni->setDelayPerUnit(0.1);
	originalSpr->setDelayPerUnit(0.1);

	auto animate = Animate::create(effectAni);
	auto returnOrigin = Animate::create(originalSpr);
	auto delay = DelayTime::create(0.3);
	animate->setTag(11);
	returnOrigin->setTag(12);

	auto action2 = CallFuncN::create(CC_CALLBACK_1(GameScene::StopAnimation02,this,sprite));
	auto action3 = Sequence::create(animate,delay,returnOrigin,action2, NULL);

	sprite->runAction(action3);
}

void GameScene::RunBeShotAnimation(Sprite* sprite, int type, int dir)
{
	auto effectAni = Animation::create();
	auto originalSpr = Animation::create();

	if(dir == 1)
	{
		switch(type)
		{
		case SOLDIER_TYPE::WARRIOR :
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Be_Shot_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Be_Shot_Action02.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Player/W_Ready.png");
			break;
		case SOLDIER_TYPE::ARCHER :
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Be_Shot_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Be_Shot_Action02.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Player/A_Ready.jpg");
			break;
		case SOLDIER_TYPE::MAGICIAN :
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Be_Shot_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Be_Shot_Action02.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Player/M_Ready.png");
			break;
		}
	}
	else
	{
		switch(type)
		{
		case SOLDIER_TYPE::WARRIOR :
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Be_Shot_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Be_Shot_Action02.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Enemy/W_Ready.jpg");
			break;
		case SOLDIER_TYPE::ARCHER :
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Be_Shot_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Be_Shot_Action02.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Enemy/A_Ready.jpg");
			break;
		case SOLDIER_TYPE::MAGICIAN :
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Be_Shot_Action01.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Be_Shot_Action02.jpg");
			originalSpr->addSpriteFrameWithFile("GameScene/Enemy/M_Ready.jpg");
			break;
		}
	}

	effectAni->setDelayPerUnit(0.1);
	originalSpr->setDelayPerUnit(0.1);

	auto animate = Animate::create(effectAni);
	auto returnOrigin = Animate::create(originalSpr);
	auto delay = DelayTime::create(0.3);
	animate->setTag(11);
	returnOrigin->setTag(12);

	auto action2 = CallFuncN::create(CC_CALLBACK_1(GameScene::StopAnimation02,this,sprite));
	auto action3 = Sequence::create(animate,delay,returnOrigin,action2, NULL);

	sprite->runAction(action3);
}

void GameScene::RunMoveAnimation(Ref* sender, Soldier* temp)
{
	auto effectAni = Animation::create();

	if (temp->GetDirect() == 1)
	{
		switch (temp->GetSoldierType())
		{
		case SOLDIER_TYPE::WARRIOR:
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Move.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Move02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/W_Ready.png");
			break;
		case SOLDIER_TYPE::ARCHER:
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Move.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Move02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/A_Ready.jpg");
			break;
		case SOLDIER_TYPE::MAGICIAN:
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Move.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Move02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Player/M_Ready.png");
			break;
		}
	}
	else
	{
		switch (temp->GetSoldierType())
		{
		case SOLDIER_TYPE::WARRIOR:
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Move.png");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Move02.png");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/W_Ready.jpg");
			break;
		case SOLDIER_TYPE::ARCHER:
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Move.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Move02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/A_Ready.jpg");
			break;
		case SOLDIER_TYPE::MAGICIAN:
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Move.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Move02.jpg");
			effectAni->addSpriteFrameWithFile("GameScene/Enemy/M_Ready.jpg");
			break;
		}
	}

	effectAni->setDelayPerUnit(0.2);

	auto animate = Animate::create(effectAni);
	auto delay = DelayTime::create(0.2);
	animate->setTag(11);

	auto stop = CallFuncN::create(CC_CALLBACK_1(GameScene::StopAnimation01, this, temp->GetSprite()));
	auto action3 = Sequence::create(animate, stop, NULL);

	temp->GetSprite()->runAction(action3);
	

	auto moveAction = MoveBy::create(0.5, Point(0, MAP::CELL_Y*temp->GetDirect()));
	temp->GetSprite()->runAction(moveAction);
}

void GameScene::RemoveEffect(Ref* sender, Sprite* sprite)
{
	sprite->removeChildByTag(SPRITE_TAG::SKILL, true);
}

void GameScene::StopAnimation01(Ref* sender, Sprite* sprite)
{
	sprite->stopActionByTag(11);
}

void GameScene::StopAnimation02(Ref* sender, Sprite* sprite)
{
	sprite->stopActionByTag(11);
	sprite->stopActionByTag(12);
}

void GameScene::update(float delta)
{
	//적 블록 생성 스케줄 관리
	if(m_sEnemyBlockList.GetBlockNum() < 3 && !m_bUseEnemySchedule)							//블록의 갯수가 3개 이하이고 블록 생성 스케줄을 사용 하지 않을때 기동.
	{
		m_bUseEnemySchedule = true;
		this->schedule(schedule_selector(GameScene::CreateEnemyBlock), B_REGEN_TIME);
	}	
	else if(m_sEnemyBlockList.GetBlockNum() >= 3)											//블록 갯수가 3개 이상이되면 스케줄을 멈춤
	{
		unschedule(schedule_selector(GameScene::CreateEnemyBlock));
		m_bUseEnemySchedule = false;
	}
	
	//플레이어 블록 생성 스케줄 관리
	if(m_sBlockList.GetBlockNum() < 3 && !m_bUsePlayerSchedule)								//블록의 갯수가 3개 이하이고 블록 생성 스케줄을 사용 하지 않을때 기동.
	{	
		m_bUsePlayerSchedule = true;
		this->schedule(schedule_selector(GameScene::CreatePlayerBlock), B_REGEN_TIME);
	}	
	else if(m_sBlockList.GetBlockNum() >= 3)												//블록 갯수가 3개 이상이되면 스케줄을 멈춤
	{
		unschedule(schedule_selector(GameScene::CreatePlayerBlock));
		m_bUsePlayerSchedule = false;
	}
}

void GameScene::CreatePlayerBlockLayer(int x, int y, int pos)										//블록의 위치를 잡아줄 투명 레이어
{
	auto blSpr= Sprite::create("GameScene/BlockLayer.png");
	blSpr->setAnchorPoint(Point(0.2, 0.5));
	blSpr->setPosition(Point(x, y));
	blSpr->setTag(pos+FIRST_B_TAG::LAYER);
	FRAME_TAG->addChild(blSpr,5);
}

void GameScene::CreatePlayerBlock(float delta)										//플레이어 블록 생성
{
	int pieceNum = 0;
	int useNum = m_sBlockList.GetBlockNum();
	Block& temp = m_sBlockList.InsertBlock();										//블록을 집어 넣고 집어 넣은 블럭의 포인터를 반환

	CreatePlayerBlockLayer(temp.GetXpos(), temp.GetYpos(), useNum);					//블록 레이어를 생성.
	RunRegenBlockEffect((Sprite*)FRAME_TAG->getChildByTag(useNum+FIRST_B_TAG::LAYER));

	for(auto& i : temp.GetPieceArray())												//받아온 블록 포인터 내부의 조각들의 이미지를 지정.
	{
		Sprite* blockSpr;
		switch(i->GetSoldierType())
		{
		case SOLDIER_TYPE::WARRIOR :
			blockSpr = Sprite::create("GameScene/WarriorPiece.png");
			break;
		case SOLDIER_TYPE ::ARCHER :
			blockSpr = Sprite::create("GameScene/ArcherPiece.png");
			break;
		case SOLDIER_TYPE::MAGICIAN :
			blockSpr = Sprite::create("GameScene/MagicianPiece.png");
			break;
		}
		blockSpr->setPosition(i->GetXpos(),i->GetYpos());
		blockSpr->setAnchorPoint(Point(0,0));
		blockSpr->setOpacity(0);
		blockSpr->setTag(FIRST_B_TAG::P_FIRST + useNum*10 + pieceNum);						
		FRAME_TAG->getChildByTag(useNum+FIRST_B_TAG::LAYER)->addChild(blockSpr,5);
		i->SetSprite(blockSpr);

		auto action = FadeIn::create(1.5);
		blockSpr->runAction(action);

		pieceNum++;
	}
}

void GameScene::CreateEnemyBlock(float delta)												//적 블록생성
{
	m_sEnemyBlockList.InsertBlock();														//이미지를 지정해 줄 필요가 없음.
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	if(IsOver)
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		CocosDenshion::SimpleAudioEngine::getInstance() -> stopBackgroundMusic(true);
		auto transition = TransitionFade::create(1.0, WorldScene::createScene());
		Director::getInstance()->replaceScene(transition);
	}
	this->schedule(schedule_selector(GameScene::TouchTimeOnce),0.1);

	Point location = touch->getLocation();
	
	if(IsInMenu)
	{
		auto sprYesButton = (Sprite*)BACKMENU_BG_TAG->getChildByTag(SPRITE_TAG::MENU_YESBUTTON);
		auto sprNoButton = (Sprite*)BACKMENU_BG_TAG->getChildByTag(SPRITE_TAG::MENU_NOBUTTON);
		Rect rectYesButton = sprYesButton->getBoundingBox();
		Rect rectNoButton = sprNoButton->getBoundingBox();

		if(rectYesButton.containsPoint(location))
		{
			Director::getInstance()->resume();
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			CocosDenshion::SimpleAudioEngine::getInstance() -> stopBackgroundMusic(true);
			auto transition = TransitionFadeUp::create(0.5, WorldScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}

		if(rectNoButton.containsPoint(location))
		{
			Director::getInstance()->resume();
			BACKMENU_BG_TAG->removeAllChildren();
			BG_TAG->removeChildByTag(SPRITE_TAG::MENU_BG);

			IsInMenu = false;
		}
	}
	else
	{
		for(int pos  = 0; pos < m_sBlockList.GetBlockNum(); pos++)
		{
			auto listLayer = (Sprite*)FRAME_TAG->getChildByTag(pos+FIRST_B_TAG::LAYER);
			Rect rect = listLayer->getBoundingBox();

			if(rect.containsPoint(location))													//터치를 했을 때 레이어를 선택했다면 다음 터치 이벤트를 불러옴
			{
				m_nTouchLayerTag = listLayer->getTag();
				return true;
			}
		}
	}
	return false;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event)								//드래그 이벤트. 
{	
		Point location = touch->getLocation();
		auto listLayer = (Sprite*)FRAME_TAG->getChildByTag(m_nTouchLayerTag);


		if(FRAME_TAG->getChildByTag(m_nTouchLayerTag)->getPosition().y > 260)
		{
			listLayer->setScale(B_SCALE_RATIO);
			for(int i = 0 ; i < 4 ; i++)															//투명 레이어위 블록들의 오퍼시티값 조정
				FRAME_TAG->getChildByTag(m_nTouchLayerTag)->getChildByTag(FIRST_B_TAG::P_FIRST + ((m_nTouchLayerTag-1500) *10) + i)->setOpacity(150);
		}
		
		else
		{
			listLayer->setScale(1);
			for(int i = 0 ; i < 4 ; i++)															//투명 레이어위 블록들의 오퍼시티값 조정
				FRAME_TAG->getChildByTag(m_nTouchLayerTag)->getChildByTag(FIRST_B_TAG::P_FIRST + ((m_nTouchLayerTag-1500) *10) + i)->setOpacity(255);
		}

		FRAME_TAG->getChildByTag(m_nTouchLayerTag)->setPosition((FRAME_TAG->getChildByTag(m_nTouchLayerTag)->getPosition())+touch->getDelta());
}

void GameScene::onTouchEnded(Touch* touch, Event* unused_event)
{
	int pieceNum = 0;
	if(m_bTouchOnce == true)													//손가락을 뗐을 때 터치 시간이 짧다면 회전
	{
		

		auto listLayer = (Sprite*)FRAME_TAG->getChildByTag(m_nTouchLayerTag);
		Rect rect = listLayer->getBoundingBox();

		auto temp = m_sBlockList.RotateBlock(m_nTouchLayerTag-1500);						//블록의 위치를 회전.

		for(auto& i : temp.GetPieceArray())													//회전된 조각들의 이미지 좌표를 재설정.
		{
			FRAME_TAG->getChildByTag(m_nTouchLayerTag)->getChildByTag(FIRST_B_TAG::P_FIRST + (m_nTouchLayerTag-1500) * 10 + pieceNum)->
				setPosition(i->GetXpos(),i->GetYpos());
			pieceNum++;
			
		}
		listLayer->setScale(1);															//지정된 곳에 드랍되지 않았다면 원래 상태로 되돌림.
		for(int i = 0 ; i < 4 ; i++)
			FRAME_TAG->getChildByTag(m_nTouchLayerTag)->getChildByTag(FIRST_B_TAG::P_FIRST + ((m_nTouchLayerTag-1500) *10) + i)->setOpacity(255);
	}
	else																					//손가락을 뗐을 때 터치 시간이 길다면 용병 생성
	{
		auto listLayer = (Sprite*)FRAME_TAG->getChildByTag(m_nTouchLayerTag);
		Rect rect = listLayer->getBoundingBox();

		auto temp = m_sBlockList.GetBlock(m_nTouchLayerTag - FIRST_B_TAG::LAYER);

		if(BlockSetCheck(temp, listLayer))													//블록이 드랍된 위치가 적절한지.					
		{
			CreatePlayerSoldier(temp);														//지정된 곳에 드랍됬다면 용병들의 이미지를 출력.
			m_sBlockList.DeleteBlock(m_nTouchLayerTag - FIRST_B_TAG::LAYER);				//리스트내부의 블록을 삭제
			FRAME_TAG->getChildByTag(m_nTouchLayerTag)->removeAllChildren();				//블록 조각 이미지를 삭제
			FRAME_TAG->removeChildByTag(m_nTouchLayerTag);									//투명 레이어 삭제

				for(int i = m_nTouchLayerTag-FIRST_B_TAG::LAYER; i < m_sBlockList.GetBlockNum(); i++)		//블록 리스트의 레이어와 조각들의 태그를 재설정
				{
					FRAME_TAG->getChildByTag(i+FIRST_B_TAG::LAYER + 1)->setTag(i+FIRST_B_TAG::LAYER);
					for(int j = 0 ; j < 4 ; j++)
						FRAME_TAG->getChildByTag(i + FIRST_B_TAG::LAYER)->getChildByTag(FIRST_B_TAG::P_FIRST + ((i+1) *10) + j)->setTag(FIRST_B_TAG::P_FIRST + i *10 + j);
				}
 		}
		else
		{
			listLayer->setScale(1);															//지정된 곳에 드랍되지 않았다면 원래 상태로 되돌림.
			for(int i = 0 ; i < 4 ; i++)
				FRAME_TAG->getChildByTag(m_nTouchLayerTag)->getChildByTag(FIRST_B_TAG::P_FIRST + ((m_nTouchLayerTag-1500) *10) + i)->setOpacity(255);
		}	
	}

	unschedule(schedule_selector(GameScene::TouchTimeOnce));
	ListBlockSort();		
	m_bTouchOnce = true;
}

void GameScene::onKeyReleased (EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && !IsInMenu && !IsOver)
	{
		IsInMenu = true;
		popUpMenu();
	}
}

void GameScene::ListBlockSort()
{
	m_sBlockList.SortBlock();
	int useNum = 0;

	for(auto& temp : m_sBlockList.GetBlockList())
	{
		auto action = MoveTo::create(0.3,Point(temp->GetXpos(),temp->GetYpos()));			//블록의 원래 위치로 레이어를 옮김
		FRAME_TAG->getChildByTag(useNum + FIRST_B_TAG::LAYER)->runAction(action);
		useNum += 1;
	}
}

bool GameScene::BlockSetCheck(Block& block, Sprite* layer)									//지정된 위치에 블록이 드랍됬는지 충돌체크
{
	int x = (int)(layer->getPositionX() - (LAYER_SIZE::X/5)*B_SCALE_RATIO);
	int y = (int)(layer->getPositionY() - (LAYER_SIZE::Y/2)*B_SCALE_RATIO);

	if(MAP::LOCATE_Y - 30 < y && MAP::LOCATE_Y + MAP::CELL_Y +10 > y)
	{
		if(MAP::LOCATE_X < x && MAP::LOCATE_X + 720 > x)
		{
			int index = (int)((x-20) / MAP::CELL_X);
			if(m_sMap.SummonPlayerSoldier(block,index))										//지정된 곳에 드랍됬다면 조각의 정보를 맵 위로 옮김
				return true;
		}
	}

	return false;
}

void GameScene::CreatePlayerSoldier(Block& block)											//맵 위에 옮겨진 정보를 바탕으로 이미지를 출력
{
	auto soldierVector = block.GetPieceArray();

	for(auto& temp : soldierVector)
	{
		temp->SetDirect(DIRECT::UP);

		Sprite* soldierSpr;
		int type = temp->GetSoldierType();
		auto ani = Animation::create();
		switch(type)
		{
		case SOLDIER_TYPE::WARRIOR :
			soldierSpr = Sprite::create("GameScene/Player/W_Ready.png");
			ani->addSpriteFrameWithFile("GameScene/Player/W_Ready.png");
			ani->addSpriteFrameWithFile("GameScene/Player/W_Ready02.png");
			break;
		case SOLDIER_TYPE ::ARCHER :
			soldierSpr = Sprite::create("GameScene/Player/A_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Player/A_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Player/A_Ready02.png");
			break;
		case SOLDIER_TYPE::MAGICIAN :
			soldierSpr = Sprite::create("GameScene/Player/M_Ready.png");
			ani->addSpriteFrameWithFile("GameScene/Player/M_Ready.png");
			ani->addSpriteFrameWithFile("GameScene/Player/M_Ready02.png");
			break;
		}

		soldierSpr->setAnchorPoint(Point(0, 0));
		soldierSpr->setPosition(temp->GetXpos(), temp->GetYpos() + 15);
		soldierSpr->setOpacity(0);
		MAP_TAG->addChild(soldierSpr,3);

		InitAtkBar(soldierSpr, temp->GetDirect(), temp->GetAtkPoint());

		ani->setDelayPerUnit(0.8);
		temp->SetSprite(soldierSpr);
		temp->SetAnimation(ani);

		auto repeat = RepeatForever::create(temp->GetAnimate());
		auto action = FadeIn::create(1.5);

		soldierSpr->runAction(repeat);
		soldierSpr->runAction(action);

		temp->SetMapIndex();
	}
}

void GameScene::CreateEnemySoldier(Block& block)
{
	int dangerFigure[4][MAP::X_SIZE];
	int highFigureIdx = 0;
	int highFigureRot = 0;

	m_sMap.UpdateDangerousFigure();


	for(int rot = 0; rot < 4; rot++)
	{
		for(int idx = 0; idx < MAP::X_SIZE; idx++)														//모든 x좌표를 원점으로 삼아 블럭을 올릴 수 있는 경우의 수를 다 확인하여 위험도 총 합수치를 배열에 저장
			dangerFigure[rot][idx] = m_sMap.CheckDangerousFigure(block,idx+100);
		block.RotateBlock();
	}

	for(int rot = 0; rot < 4; rot++)
	{
		for(int idx = 0; idx < MAP::X_SIZE; idx++)
		{
			if( dangerFigure[highFigureRot][highFigureIdx] < dangerFigure[rot][idx])
			{
				highFigureRot = rot;
				highFigureIdx = idx;
			}
		}
	}

	for(int rot = 0; rot < highFigureRot; rot++)
		block.RotateBlock();

	if(!m_sMap.SummonEnemySoldier(block, highFigureIdx + 100))
		return;

	auto soldierVector = block.GetPieceArray();

	for(auto& temp : soldierVector)
	{
		temp->SetDirect(DIRECT::DOWN);

		Sprite* soldierSpr;
		auto ani = Animation::create();
		int type = temp->GetSoldierType();
		switch(type)
		{
		case SOLDIER_TYPE::WARRIOR :
			soldierSpr = Sprite::create("GameScene/Enemy/W_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Enemy/W_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Enemy/W_Ready02.png");
			break;
		case SOLDIER_TYPE ::ARCHER :
			soldierSpr = Sprite::create("GameScene/Enemy/A_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Enemy/A_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Enemy/A_Ready02.png");
			break;
		case SOLDIER_TYPE::MAGICIAN :
			soldierSpr = Sprite::create("GameScene/Enemy/M_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Enemy/M_Ready.jpg");
			ani->addSpriteFrameWithFile("GameScene/Enemy/M_Ready02.png");
			break;
		}

		InitAtkBar(soldierSpr, temp->GetDirect(), temp->GetAtkPoint());

		soldierSpr->setAnchorPoint(Point(0, 0));
		soldierSpr->setPosition(temp->GetXpos(), temp->GetYpos()+15);
		soldierSpr->setOpacity(0);
		MAP_TAG->addChild(soldierSpr,3);

		ani->setDelayPerUnit(0.8);
		temp->SetSprite(soldierSpr);
		temp->SetAnimation(ani);

		auto repeat = RepeatForever::create(temp->GetAnimate());
		auto action = FadeIn::create(1.5);

		soldierSpr->runAction(action);
		soldierSpr->runAction(repeat);

		temp->SetMapIndex();
	}
}

void GameScene::InitAtkBar(Sprite* sprite, int dir, int atk)
{
	Sprite** hpBlock = new Sprite*[atk];

	for(int i = 0 ; i < atk ; i++)
	{
		switch(dir)
		{
		case -1 :
			hpBlock[i] = Sprite::create("GameScene/Enemy/Soldier_Atk.jpg");
			break;
		case 1 :
			hpBlock[i] = Sprite::create("GameScene/Player/Soldier_Atk.jpg");
			break;
		}

		hpBlock[i]->setPosition(6,5+(12*i));
		hpBlock[i]->setTag(i);
		hpBlock[i]->setOpacity(0);

		auto action = FadeIn::create(1.5);
		hpBlock[i]->runAction(action);

		sprite->addChild(hpBlock[i]);
	}

}

void GameScene::MovePlayerSoldier(float delta)														//플레이어 병사들의 이동 스케줄
{
	unschedule(schedule_selector(GameScene::MovePlayerSoldier));									//플레이어 턴이 되면 스케줄을 멈춤.

	auto soldierList = m_sMap.GetPlayerSoldier();

	std::list<Soldier*>::iterator iter;
	auto delay = DelayTime::create(DELAY_TIME);

	for(iter = soldierList.begin(); iter != soldierList.end(); ++iter)															//맵 위의 모든 병사를 지정
	{
		auto temp = *iter;


		auto soldierSpr = (Sprite*)temp->GetSprite();

		if(SoldierCollisionCheck(temp))																//병사 충돌체크
		{
		}
		else if(temp->GetYpos() < 820)																//맵위에 병사가있는지 체크
		{
			m_sMap.SetSoldierNotExist(temp->GetMapIndex());											//원래 위치의 존재여부를 없애고
			temp->MoveFront();																		//앞으로 이동

			
			auto action2 = CallFuncN::create(CC_CALLBACK_1(GameScene::RunMoveAnimation, this, temp));
			auto moveSeq = Sequence::create(action2, NULL);
			soldierSpr->runAction(moveSeq);
		}
		else
		{
			soldierSpr->stopAllActions();
			PlayAttackEffectSound(4);
			m_sEnemyBlockList.DecreaseHP();
			FRAME_TAG->removeChildByTag(SPRITE_TAG::E_HP_BAR);
			SetEnemyHP_Bar(m_sEnemyBlockList.GetHp());
			DestructSoldier(temp);

			if(m_sEnemyBlockList.IsGameOver())
			{
				ShowGameResult(1);
				// 저장소에 스테이지 정보를 저장함
				// "openStage"라는 키에 저장
				if(GameManager::GetInstance()->getOpenStage() == GameManager::GetInstance()->getInStage())
				{
					UserDefault::getInstance()->setIntegerForKey("openStage",GameManager::GetInstance()->getOpenStage()+1);
					UserDefault::getInstance()->flush();
				}
				return;
			}
		}
	}

	for(auto& temp : m_sMap.GetPlayerSoldier())
	{
		temp->SetMapIndex();
		m_sMap.SetSoldierExist(temp->GetMapIndex(), temp->GetDirect());											
	}

	auto useSkill = CallFuncN::create(CC_CALLBACK_0(GameScene::SodierUseSkill,this));
	auto effect = Sequence::create(delay, useSkill, NULL);
	this->runAction(effect);

	this->schedule(schedule_selector(GameScene::MoveEnemySoldier), m_sStageFactor.MOVE_INTERVAL);					//적 병사들의 이동 스케줄 기동.
}

void GameScene::SummonEnemySoldier(float delta)
{
	int summonLate = rand() % 10;

	if(m_sEnemyBlockList.GetBlockNum() > 0)															//블록을 하나라도 가지고 있으면 실행.
	{
		int num = rand() % m_sEnemyBlockList.GetBlockNum();

		auto temp = m_sEnemyBlockList.GetBlock(num);
		CreateEnemySoldier(temp);
		m_sEnemyBlockList.DeleteBlock(num);

	}
}

void GameScene::MoveEnemySoldier(float delta)
{
	unschedule(schedule_selector(GameScene::MoveEnemySoldier));

	auto soldierList = m_sMap.GetEnemySoldier();

	std::list<Soldier*>::iterator iter;
	auto delay = DelayTime::create(DELAY_TIME);

	for(iter = soldierList.begin(); iter != soldierList.end(); ++iter)								//맵 위의 모든 병사를 지정
	{
		auto temp = *iter;

		auto soldierSpr = (Sprite*)temp->GetSprite();

		if(SoldierCollisionCheck(temp))																//병사 충돌체크
		{
		}
		else if(temp->GetYpos() > 0)																//맵위에 병사가있는지 체크
		{
			m_sMap.SetSoldierNotExist(temp->GetMapIndex());											//원래 위치의 존재여부를 없애고
			temp->MoveFront();																		//앞으로 이동

			auto action2 = CallFuncN::create(CC_CALLBACK_1(GameScene::RunMoveAnimation, this, temp));
			auto moveSeq = Sequence::create(action2, NULL);
			soldierSpr->runAction(moveSeq);
		} 
		else
		{
			soldierSpr->stopAllActions();
			PlayAttackEffectSound(4);
			m_sBlockList.DecreaseHP();
			FRAME_TAG->removeChildByTag(SPRITE_TAG::P_HP_BAR);
			SetPlayerHP_Bar(m_sBlockList.GetHp());
			DestructSoldier(temp);

			if(m_sBlockList.IsGameOver())
			{
				ShowGameResult(2);
				return;
			}
		}
	}

	for(auto& temp : m_sMap.GetEnemySoldier())
	{
		temp->SetMapIndex();
		m_sMap.SetSoldierExist(temp->GetMapIndex(), temp->GetDirect());								
	}

	auto useSkill = CallFuncN::create(CC_CALLBACK_0(GameScene::SodierUseSkill,this));
	auto effect = Sequence::create(delay, useSkill, NULL);
	this->runAction(effect);

	this->schedule(schedule_selector(GameScene::MovePlayerSoldier), m_sStageFactor.MOVE_INTERVAL);
}

bool GameScene::SoldierCollisionCheck(Soldier* soldier)
{
	int nextIndex = (soldier->GetDirect() * 10) + soldier->GetMapIndex();
	
	std::list<Soldier*>* MoveSoldierList;
	std::list<Soldier*>* StaySoldierList;

	if(soldier->GetDirect() == 1)
	{
		MoveSoldierList = &m_sMap.GetPlayerSoldier();
		StaySoldierList = &m_sMap.GetEnemySoldier();
	}
	else
	{
		MoveSoldierList = &m_sMap.GetEnemySoldier();
		StaySoldierList = &m_sMap.GetPlayerSoldier();
	}

	auto delay = DelayTime::create(DELAY_TIME);

	for(auto temp : *StaySoldierList)
	{
		if(temp->GetMapIndex() == nextIndex)
		{
			int moveDamage = soldier->GetAtkPoint();
			int stayDamage = temp->GetAtkPoint();
			PlayAttackEffectSound(3);

			if(temp->SoliderBeDamaged(moveDamage))
			{ 
				RunAttackEffect(temp->GetSprite());
				RunBeShotAnimation(temp->GetSprite(), temp->GetSoldierType(), temp->GetDirect());
				auto disapear = FadeOut::create(DELAY_TIME);
				temp->GetSprite()->runAction(disapear);
				auto useSkill = CallFuncN::create(CC_CALLBACK_1(GameScene::DestructSoldier2,this,temp));
				auto effect = Sequence::create(delay, useSkill, NULL);
				this->runAction(effect);
			}
			if(soldier->SoliderBeDamaged(stayDamage))
			{
				RunAttackEffect(soldier->GetSprite());
				RunBeShotAnimation(soldier->GetSprite(), soldier->GetSoldierType(), soldier->GetDirect());
				auto disapear = FadeOut::create(DELAY_TIME);
				soldier->GetSprite()->runAction(disapear);
				auto useSkill = CallFuncN::create(CC_CALLBACK_1(GameScene::DestructSoldier2,this,soldier));
				auto effect = Sequence::create(delay, useSkill, NULL);
				this->runAction(effect);
				return true;
			}
			return false;
		}
	}

	return false;
}

void GameScene::SodierUseSkill()
{
	int returnVal;
	Soldier* target = NULL;
	for(auto attack : m_sMap.GetPlayerSoldier())
	{
		target = NULL;
		for(auto defence : m_sMap.GetEnemySoldier())
		{
			int index = defence->GetMapIndex();
			if(returnVal = attack->UseSkill(index))
			{
				if (returnVal == 1)
				{
					RunSkillEffect(defence->GetSprite(), attack->GetSoldierType());
					RunBeShotAnimation(defence->GetSprite(), defence->GetSoldierType(), defence->GetDirect());
					PlayAttackEffectSound(attack->GetSoldierType());
					m_sMap.SkillDamageStack(index, attack->GetSkillDamage());

					if (attack->GetSoldierType() == SOLDIER_TYPE::ARCHER)																//바로 앞의 적을 공격할 경우 반복문을 빠져나옴.
					{
						target = NULL;
						break;
					}
				}
				else if (returnVal == 2)
				{
					target = defence;
				}
			}
		}
		if (target != NULL)
		{
			RunSkillEffect(target->GetSprite(), attack->GetSoldierType());
			RunBeShotAnimation(target->GetSprite(), target->GetSoldierType(), target->GetDirect());
			PlayAttackEffectSound(attack->GetSoldierType());
			m_sMap.SkillDamageStack(target->GetMapIndex(), attack->GetSkillDamage());
		}
	}

	for(auto attack : m_sMap.GetEnemySoldier())
	{
		target = NULL;
		for(auto defence : m_sMap.GetPlayerSoldier())
		{
			int index = defence->GetMapIndex();
			if(returnVal = attack->UseSkill(index))
			{
				if (returnVal == 1)
				{
					RunSkillEffect(defence->GetSprite(), attack->GetSoldierType());
					RunBeShotAnimation(defence->GetSprite(), defence->GetSoldierType(), defence->GetDirect());
					PlayAttackEffectSound(attack->GetSoldierType());
					m_sMap.SkillDamageStack(index, attack->GetSkillDamage());

					if (attack->GetSoldierType() == SOLDIER_TYPE::ARCHER)																//바로 앞의 적을 공격할 경우 반복문을 빠져나옴.
					{
						target = NULL;
						break;
					}
				}
				else if (returnVal == 2)
				{
					target = defence;
				}
			}
		}
		if (target != NULL)
		{
			RunSkillEffect(target->GetSprite(), attack->GetSoldierType());
			RunBeShotAnimation(target->GetSprite(), target->GetSoldierType(), target->GetDirect());
			PlayAttackEffectSound(attack->GetSoldierType());
			m_sMap.SkillDamageStack(target->GetMapIndex(), attack->GetSkillDamage());
		}
	}

	auto delay = DelayTime::create(DELAY_TIME);

	auto soldierList = m_sMap.GetPlayerSoldier();
	std::list<Soldier*>::iterator iter;

	for(iter = soldierList.begin(); iter != soldierList.end(); ++iter)											
	{
		auto temp = *iter;

		int damage = m_sMap.GetDamageStack(temp->GetMapIndex());

		if(temp->SoliderBeDamaged(damage))
		{ 
			auto disapear = FadeOut::create(DELAY_TIME);
			temp->GetSprite()->runAction(disapear);
			auto useSkill = CallFuncN::create(CC_CALLBACK_1(GameScene::DestructSoldier2,this,temp));
			auto effect = Sequence::create(delay, useSkill, NULL);
			this->runAction(effect);
		}
	}


	soldierList = m_sMap.GetEnemySoldier();

	for(iter = soldierList.begin(); iter != soldierList.end(); ++iter)
	{
		auto temp = *iter;

		int damage = m_sMap.GetDamageStack(temp->GetMapIndex());

		if(temp->SoliderBeDamaged(damage))
		{ 
			auto disapear = FadeOut::create(DELAY_TIME);
			temp->GetSprite()->runAction(disapear);
			auto useSkill = CallFuncN::create(CC_CALLBACK_1(GameScene::DestructSoldier2,this,temp));
			auto effect = Sequence::create(delay, useSkill, NULL);
			this->runAction(effect);
		}
	}

	m_sMap.ResetDamageStack();
}

void GameScene::DestructSoldier(Soldier* soldier)
{
	std::list<Soldier*>* soldierList;
	if(soldier->GetDirect() == 1)
		soldierList = &m_sMap.GetPlayerSoldier();
	else if(soldier->GetDirect() == -1)
		soldierList = &m_sMap.GetEnemySoldier();

	m_sMap.SetSoldierNotExist(soldier->GetMapIndex());
	soldier->GetSprite()->removeAllChildren();
	MAP_TAG->removeChild(soldier->GetSprite(),true);
	soldierList->remove(soldier);
	delete soldier;
}

void GameScene::DestructSoldier2(Ref* sender, Soldier* soldier)
{
	std::list<Soldier*>* soldierList;
	if(soldier->GetDirect() == 1)
		soldierList = &m_sMap.GetPlayerSoldier();
	else if(soldier->GetDirect() == -1)
		soldierList = &m_sMap.GetEnemySoldier();

	m_sMap.SetSoldierNotExist(soldier->GetMapIndex());
	soldier->GetSprite()->removeAllChildren();
	MAP_TAG->removeChild(soldier->GetSprite(),true);
	soldierList->remove(soldier);
	delete soldier;
}


void GameScene::ShowGameResult(int result)
{
	unscheduleAllSelectors();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	Label* resultLabel;
	Sprite* starSpr[3];
	int starCount = 0;

	auto frameSpr = Sprite::create("GameScene/Result/RESULT.png");

	switch(result)
	{
	case 1 :
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("GameScene/Sound/Victory.mp3",true);
		resultLabel = Label::createWithSystemFont("You Win", "Thonburi", 40);
		break;
	case 2 :
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("GameScene/Sound/Lose.mp3",true);
		resultLabel = Label::createWithSystemFont("You Lose", "Thonburi", 40);
		break; 
	}

	switch(m_sBlockList.GetHp())
	{
	case 0 :
		starSpr[0] = Sprite::create("GameScene/Result/NON_STAR.png");
		starSpr[1] = Sprite::create("GameScene/Result/NON_STAR.png");
		starSpr[2] = Sprite::create("GameScene/Result/NON_STAR.png");
		starCount = 0;
		break;
	case 1 :
	case 2 :
		starSpr[0] = Sprite::create("GameScene/Result/STAR.png");
		starSpr[1] = Sprite::create("GameScene/Result/NON_STAR.png");
		starSpr[2] = Sprite::create("GameScene/Result/NON_STAR.png");
		starCount = 1;
		break;
	case 3 :
	case 4 :
		starSpr[0] = Sprite::create("GameScene/Result/STAR.png");
		starSpr[1] = Sprite::create("GameScene/Result/STAR.png");
		starSpr[2] = Sprite::create("GameScene/Result/NON_STAR.png");
		starCount = 2;
		break;
	case 5:
		starSpr[0] = Sprite::create("GameScene/Result/STAR.png");
		starSpr[1] = Sprite::create("GameScene/Result/STAR.png");
		starSpr[2] = Sprite::create("GameScene/Result/STAR.png");
		starCount = 3;
		break;
	}

	switch(GameManager::GetInstance()->getInStage())
	{
	case 1:
		if(UserDefault::getInstance()->getIntegerForKey("Stage1Star",0) < starCount)
		UserDefault::getInstance()->setIntegerForKey("Stage1Star", starCount);
		break;
	case 2:
		if(UserDefault::getInstance()->getIntegerForKey("Stage2Star",0) < starCount)
		UserDefault::getInstance()->setIntegerForKey("Stage2Star", starCount);
		break;
	case 3:
		if(UserDefault::getInstance()->getIntegerForKey("Stage3Star",0) < starCount)
		UserDefault::getInstance()->setIntegerForKey("Stage3Star", starCount);
		break;
	case 4:
		if(UserDefault::getInstance()->getIntegerForKey("Stage41Star",0) < starCount)
		UserDefault::getInstance()->setIntegerForKey("Stage4Star", starCount);
		break;
	case 5:
		if(UserDefault::getInstance()->getIntegerForKey("Stage5Star",0) < starCount)
		UserDefault::getInstance()->setIntegerForKey("Stage5Star", starCount);
		break;
	}

	resultLabel->setPosition(frameSpr->getContentSize().width / 2 ,frameSpr->getContentSize().height / 2 - 100);
	starSpr[0]->setPosition(frameSpr->getContentSize().width / 2 - 120, frameSpr->getContentSize().height / 2);
	starSpr[1]->setPosition(frameSpr->getContentSize().width / 2 ,frameSpr->getContentSize().height / 2);
	starSpr[2]->setPosition(frameSpr->getContentSize().width / 2 + 120, frameSpr->getContentSize().height / 2);

	frameSpr->setPosition(FRAME_TAG->getContentSize().width / 2 ,700);

	//FRAME_TAG->addChild(resultSpr);
	FRAME_TAG->addChild(frameSpr);
	frameSpr->addChild(resultLabel);
	frameSpr->addChild(starSpr[0]);
	frameSpr->addChild(starSpr[1]);
	frameSpr->addChild(starSpr[2]);
	IsOver = true;
}

void GameScene::TouchTimeOnce(float delta)
{
	m_bTouchOnce = false;
}
