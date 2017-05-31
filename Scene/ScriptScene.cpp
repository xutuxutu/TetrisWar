#include "ScriptScene.h"
#include "GameManager.h"
#include "GameScene.h"

USING_NS_CC;
#define Android

Scene* ScriptScene::createScene()
{
    auto scene = Scene::create();

    auto layer = ScriptScene::create();

    scene->addChild(layer);

    return scene;
}

bool ScriptScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteInit();
	DataInit();
	touchEventInit();

    return true;
}

void ScriptScene::SpriteInit()
{
	GameFrameInit();
	HP_IconInit();
	SetPlayerHP_Bar(5);
	SetEnemyHP_Bar(5);
	TextBoxInit();
}

void ScriptScene::GameFrameInit() 
{
	auto interSpr = Sprite::create("GameScene/GameFrame.png");

	interSpr->setAnchorPoint(Point(0.0, 0.0));
	interSpr->setPosition(0,0);
	interSpr->setOpacity(50);
	interSpr->setTag(SCRIPT_SPRITE_TAG::FRAME);

	this->addChild(interSpr);
}

void ScriptScene::HP_IconInit()
{
	auto pBarSpr = Sprite::create("GameScene/Player/P_HP_ICON.png");
	auto eBarSpr = Sprite::create("GameScene/Enemy/E_HP_ICON.png");

	eBarSpr->setAnchorPoint(Point(0,0));
	pBarSpr->setAnchorPoint(Point(0,0));
	eBarSpr->setPosition(74, 1204);
	pBarSpr->setPosition(74, 185);
	eBarSpr->setOpacity(50);
	pBarSpr->setOpacity(50);
	SCRIPT_FRAME_TAG->addChild(pBarSpr,3);
	SCRIPT_FRAME_TAG->addChild(eBarSpr,3);
}

void ScriptScene::SetPlayerHP_Bar(int width)
{
	auto pBarSpr = Sprite::create("GameScene/Player/P_HP_BAR.png", Rect(0,0,25 + 110 * width,60));

	pBarSpr->setAnchorPoint(Point(0,0));
	pBarSpr->setPosition(100, 179);
	pBarSpr->setOpacity(50);

	SCRIPT_FRAME_TAG->addChild(pBarSpr,2);
}

void ScriptScene::SetEnemyHP_Bar(int width)
{
	auto eBarSpr = Sprite::create("GameScene/Enemy/E_HP_BAR.png", Rect(0,0,25 + 110 * width,60));

	eBarSpr->setAnchorPoint(Point(0,0));
	eBarSpr->setPosition(104, 1199);
	eBarSpr->setOpacity(50);

	SCRIPT_FRAME_TAG->addChild(eBarSpr,2);
}

void ScriptScene::TextBoxInit()
{
	auto tBoxSpr = Sprite::create("GameScene/ChatWindow/TextBox.png");
	tBoxSpr->setAnchorPoint(Point(0,0));
	tBoxSpr->setPosition(Point(20,10));
	tBoxSpr->setOpacity(100);
	tBoxSpr->setTag(SCRIPT_SPRITE_TAG::BOX);
	this->addChild(tBoxSpr);
}

void ScriptScene::DataInit()
{
	Sprite * bgSpr;
	switch(GameManager::GetInstance()->getInStage())
	{
	case 1: 
		bgSpr = Sprite::create("GameScene/BackGround.png");
		sprintf(ChapterName,"0001");
		break;
	case 2: 
		bgSpr = Sprite::create("GameScene/BackGround2.png");
		sprintf(ChapterName,"0002");
		break;
	case 3: 
		bgSpr = Sprite::create("GameScene/BackGround3.png");
		sprintf(ChapterName,"0003");
		break;
	case 4: 
		bgSpr = Sprite::create("GameScene/BackGround4.png");
		sprintf(ChapterName,"0004");
		break;
	case 5: 
		bgSpr = Sprite::create("GameScene/BackGround5.png");
		sprintf(ChapterName,"0005");
		break;
	}

	this->BackGroundInit(bgSpr);
	TextDataInit();
}

void ScriptScene::BackGroundInit(Sprite* bgSpr)
{
	bgSpr->setAnchorPoint(Point(0,0));
	bgSpr->setPosition(Point(0, 260));
	bgSpr->setOpacity(50);
	bgSpr->setTag(SCRIPT_SPRITE_TAG::BG);
	this->addChild(bgSpr);
}

void ScriptScene::TextDataInit()
{
	char *fileName = NULL;

	// ���� �� �÷����� ���� �ؽ�Ʈ������ �ٸ� (ANSI, UTF-8 ���� ����)
	#ifdef Android
		fileName = "GameScene/text_android.txt";	// UTF-8 ����
	#elif defined PC
		fileName = "GameScene/text_pc.txt";		// ANSI ����
	#endif

	if(fileName == NULL)
		return;

	isFirstTalk = true;
	ssize_t bufferSize = 0;
	pBuffer = FileUtils::getInstance()->getFileData(fileName, "rb", &bufferSize);
	pBuffer[bufferSize]='\0';
	pBuffer += 3;
	pBufferTemp = pBuffer;
	SelectChapter(pBuffer, ChapterName);

}

void ScriptScene::SelectChapter(unsigned char *ch, char *chapter)
{
	char chapterBuf[4] = {0, };
	int  statusCh = SCRIPT_STATE::isNULL;
	bool startFileName = true;
	int	 cnt = 0;

	ZeroMemory(characterName,50);
	ZeroMemory(pLabelBuf,200);

	if(isFirstTalk)
	{
		*ch++;

		// �ùٸ� é������ �˻縦 ���� �ӽ� ����
		for(int i=0; i<4;i++)
			chapterBuf[i] = *ch++;

		// ���ϴ� é�Ͱ� �ƴϸ� ��� ȣ��
		if(memcmp(chapterBuf,chapter, 4) != 0)
		{
			// ���� é�Ͱ� ���������� �ݺ�
			while(GetTextToken(*ch) != SCRIPT_STATE::isEndChapter)
				*ch++;
			//  ;,  ����, �ٹٲ�
			*ch++; *ch++; *ch++;
			// ���� é�ͷ�
			SelectChapter(ch, chapter);
			return;
		}
	}

	// é�� ���� ( é�Ͱ� ������ ���� �ݺ� )
	while(GetTextToken(*ch) != SCRIPT_STATE::isEndChapter)
	{
		if(statusCh != SCRIPT_STATE::isTalk && (GetTextToken(*ch) == SCRIPT_STATE::isSpace || GetTextToken(*ch) == SCRIPT_STATE::isEndLine))
			*ch++;

		// �̹��� ȣ���� �����ٸ�
		if(GetTextToken(*ch) == SCRIPT_STATE::isMinus || statusCh == SCRIPT_STATE::isMinus)
		{
			statusCh = SCRIPT_STATE::isMinus;

			// ó�� ���� ���۽�, '-' ��� ����
			if(startFileName)
			{
				startFileName = false;
				this->removeChildByTag(SCRIPT_SPRITE_TAG::CHARACTER);	// ���� �ѷ��� �̹��� ����
				*ch++;
			}

			if(GetTextToken(*ch) == SCRIPT_STATE::isImgPos)
			{
				bool isLeft = true;
				if(*ch == '>')
					isLeft = false;

				*ch++;

				startFileName = true;
				statusCh = SCRIPT_STATE::isNULL;
				PrintCharacter(isLeft);
				cnt = 0;
				ZeroMemory(characterName,20);
			}
			else
				characterName[cnt++] = *ch++;
		}

		// ��ȭ�� �����ٸ�
		if(GetTextToken(*ch) == SCRIPT_STATE::isTalk || statusCh == SCRIPT_STATE::isTalk)
		{
			statusCh = SCRIPT_STATE::isTalk;

			// '*' ����
			if(GetTextToken(*ch) == SCRIPT_STATE::isTalk)
			{
				SCRIPT_BOX_TAG->removeChildByTag(SCRIPT_SPRITE_TAG::LABEL_TAG);	// ���� �ѷ��� ��ȭ ����
				*ch++;
			}

			// '/' �� ������ (��ȭ ��)
			if(GetTextToken(*ch) == SCRIPT_STATE::isEndTalk)
			{
				statusCh = SCRIPT_STATE::isNULL;
				PrintText();
				cnt = 0;
				ZeroMemory(pLabelBuf,200);

				if(*ch++ != SCRIPT_STATE::isEndChapter)
				{
					isFirstTalk = false;
					pBufferTemp = ch;
					return;
				}
			}
			else
			{
				if(GetTextToken(*ch) == SCRIPT_STATE::isString || GetTextToken(*ch) == SCRIPT_STATE::isSpace)
					pLabelBuf[cnt++] = (char)*ch++;
				else
				{
					pLabelBuf[cnt++] = (char)*ch++;
					pLabelBuf[cnt++] = (char)*ch++;
				}
			}

		}

		
		// é�� ���� ������ ����
		if(GetTextToken(*ch) == SCRIPT_STATE::isEndChapter)
		{
			Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
			CocosDenshion::SimpleAudioEngine::getInstance() -> stopBackgroundMusic(true);
			auto transition = TransitionFadeUp::create(0.5, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);

			return;
		}
			
	}
}

int ScriptScene::GetTextToken(unsigned char ch)
{
	if(ch == '[')
		return SCRIPT_STATE::isBracket;
	if(ch == '-')
		return SCRIPT_STATE::isMinus;
	if(ch == '*')
		return SCRIPT_STATE::isTalk;
	if(ch == '\0' || ch == '\n')
		return SCRIPT_STATE::isEndLine;
	if(isalpha(ch) || ch == '_' || ch == ',' || ch == '.' || ch == '?' || ch == '!')
		return SCRIPT_STATE::isString;
	if(isspace(ch))
		return SCRIPT_STATE::isSpace;
	if(ch == '<' || ch == '>')
		return SCRIPT_STATE::isImgPos;
	if(ch == '~')
		return SCRIPT_STATE::isEndTalk;
	if(ch == ';')
		return SCRIPT_STATE::isEndChapter;
	return SCRIPT_STATE::isNULL;
}

void ScriptScene::PrintText()
{
	char pzxBuf[200];
	sprintf(pzxBuf, "%s", pLabelBuf);

	auto pLabel = Label::createWithSystemFont(pzxBuf, "", 30);
	pLabel->setAnchorPoint(Point(0,1));
	pLabel->setPosition(Point(30, 300));
	pLabel->setTag(SCRIPT_SPRITE_TAG::LABEL_TAG);
	SCRIPT_BOX_TAG->addChild(pLabel);
}

void ScriptScene::PrintCharacter(bool isLeft)
{
	auto charSpr = Sprite::create(characterName);
	charSpr->setAnchorPoint(Point(0,0));
	if(isLeft)
		charSpr->setPosition(Point(20,360));
	else
		charSpr->setPosition(Point(410,360));

	charSpr->setTag(SCRIPT_SPRITE_TAG::CHARACTER);
	this->addChild(charSpr);
}

void ScriptScene::touchEventInit()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(ScriptScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);
}

bool ScriptScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Point location = touch->getLocation();

	auto sprTextBox= (Sprite*)this->getChildByTag(SCRIPT_SPRITE_TAG::BOX);
	Rect rectTextBox = sprTextBox->getBoundingBox();

	if(rectTextBox.containsPoint(location))
	{
		SelectChapter(pBufferTemp, ChapterName);
	}

	return true;
}