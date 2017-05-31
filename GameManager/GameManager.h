#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

const int MAXSTAGE = 5;


class GameManager
{
private:
    GameManager():openStage(1) {};
    GameManager(const GameManager& other);
    ~GameManager() {};
 
    static GameManager* instance;

	int openStage;
	int inStage;
public:
    static GameManager* GetInstance()
    {
        if(instance == NULL) instance = new GameManager();
        return instance;
    }

	void plusStage() { if(MAXSTAGE != openStage) openStage++; }
	void setStage(int stage) { if(MAXSTAGE != openStage) openStage = stage; }
	int  getOpenStage() { return openStage; }

	void setInStage(int stage) { inStage = stage; }
	int  getInStage() { return inStage; }
};


#endif