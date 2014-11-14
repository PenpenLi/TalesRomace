//
//  BattleScene.h
//  fancyHeart
//
//  Created by 秦亮亮 on 14/11/13.
//
//

#ifndef __fancyHeart__BattleScene__
#define __fancyHeart__BattleScene__

#include <iostream>
#include "cocos2d.h"
#include "Manager.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "external/json/rapidjson.h"
#include "BattleMgr.h"
#include "Clip.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
class FData;
class FighterMgr;
class SkillIcon;
class BattleScene:public BaseUI{
public:
	static Scene* createScene();
    static BattleScene* create();
	virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void initNetEvent();
    virtual void touchButtonEvent(cocos2d::Ref *pSender, Widget::TouchEventType type);
    void interceptTouchEvent(Widget::TouchEventType event, Widget *sender, Touch *touch);

    void resetProgress();
    void setNpcIcon(int num,bool isKill);
    void initNpcIcon(int num);
private:
    int duration=180;
    bool isPause;
public:
    Widget* heroNode;
    Widget* bossInfo;
    Widget* npcInfo;
    Widget* progress;
    Widget* skillNode;
    Widget* top;
    
    
    Sprite* bg;
    void bounceTo(FighterMgr* mf);
    void tick(float dt);
};
#endif /* defined(__fancyHeart__BattleScene__) */
