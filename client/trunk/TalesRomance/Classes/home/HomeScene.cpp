//
//  HomeScene.cpp
//  fancyHeart
//
//  Created by 秦亮亮 on 14-5-12.
//
//

#include "HomeScene.h"
Scene* HomeScene::createScene(){
	auto scene = Scene::create();
    auto layer = HomeScene::create();
    scene->addChild(layer);
	return scene;
}

HomeScene* HomeScene::create()
{
    HomeScene* homeScene=new HomeScene();
    if (homeScene && homeScene->init("publish/homeUi/homeUI.ExportJson",false))
    {
        homeScene->autorelease();
        return homeScene;
    }
    CC_SAFE_DELETE(homeScene);
    return nullptr;
}

bool HomeScene::init(std::string fileName,bool isScence)
{
	if(!BaseUI::init(fileName,isScence))
    {
		return false;
	}
    Size dSize(1136,640);
    Size size=Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
    float scale=fmin(size.width/dSize.width,size.height/dSize.height);
//    scale=1;
    std::vector<std::string> buildNames={"img_hecheng","img_tiaozhan","img_hero","img_shichang","img_zhaohuan","img_fuben"};

    comLayout=layout;
    for (int i=1; i<4; i++) {
        float random=1+CCRANDOM_0_1();
        Vec2 p=Vec2(size.width-100*i, size.height-80-10*i*scale);
        this->intAnimation("effect/home_bird.plist", "home_bird", 5*random, 5*random, 0.3*random,p,Vec2(0, size.height-80*i*scale));
    }
    
    this->intAnimation("effect/airship.plist", "airship", 8, 50, 1,Vec2(-100, size.height/2+100),Vec2(size.width+100, size.height/2+100));
    
    auto widget=static_cast<Widget*>(comLayout->getChildByName("home_botom"));
    widget->setLocalZOrder(3);
    widget->setPosition(Vec2(size.width/2, 0+widget->getContentSize().height*scale/2));
    widget->setScale(scale);
    
    
    
    Button* btnProp = (Button*)widget->getChildByName("btn_prop");
    btnProp->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchButtonEvent, this));
    
    Button* btnGroup = (Button*)widget->getChildByName("btn_group");
    btnGroup->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchButtonEvent, this));
    
    Button* btn_dower=(Button*)widget->getChildByName("btn_dower");
    btn_dower->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchButtonEvent, this));
    
    Widget* homeTop=static_cast<Widget*>(comLayout->getChildByName("home_top"));
//    widget->setPosition(Vec2(0, (size.height-widget->getContentSize().height*scale/2)));
    homeTop->setPosition(Vec2(0, (size.height-homeTop->getContentSize().height*scale)));//
    homeTop->setLocalZOrder(3);
    homeTop->setScale(scale);
    
    Widget*centerPg = static_cast<Widget*>(homeTop->getChildByName("centerPg"));//
    
    Widget* currencyIcon=static_cast<Widget*>(centerPg->getChildByName("currencyIcon"));//
    currencyIcon->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchIconEvent, this));//
    
    Widget* diamondIcon=static_cast<Widget*>(centerPg->getChildByName("diamondIcon"));//
    diamondIcon->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchIconEvent, this));//
                                       
    Widget* staminaIcon=static_cast<Widget*>(centerPg->getChildByName("staminaIcon"));//
    staminaIcon->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchIconEvent, this));//
  
    widget=static_cast<Widget*>(comLayout->getChildByName("home_build"));
    widget->setLocalZOrder(2);
    widget->setPosition(Vec2((size.width-widget->getContentSize().width)/2, (size.height-widget->getContentSize().height)/2));
    for (std::string name : buildNames)
    {
        ImageView* image=(ImageView*)widget->getChildByName(name);
        image->setTouchEnabled(true);
        image->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchBuildEvent, this));
    }
    widget=(Widget*)comLayout->getChildByName("btnChat");
    widget->setPosition(Vec2(widget->getContentSize().width*scale/2, 200));
    widget->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchButtonEvent, this));
    widget->setLocalZOrder(2);
    widget->setScale(scale);
    this->setTouchEnabled(true);
    this->setEnabled(true);
    this->addTouchEventListener(CC_CALLBACK_2(HomeScene::touchBuildEvent, this));
    
    
    this->initUi();
    this->chat=Chat::create();
    this->addChild(this->chat,CHAT_LAY);//
    this->chat->setVisible(false);
    
	return true;
}

void HomeScene::intAnimation(string plist,string effectName,int fps,int moveSpeed,float scale,Vec2 starP,Vec2 endP)
{
    Clip* clip=Clip::create(plist,effectName,fps);
    comLayout->addChild(clip,1);
    clip->setScale(scale);
    clip->play(true);
    clip->setPosition(starP);
    auto move = MoveBy::create(abs(endP.x-starP.x)/moveSpeed, Vec2(endP.x-starP.x,0));
    auto moveBack=move->reverse();
    auto delay=DelayTime::create(2);
    auto seq = Sequence::create(
                                CallFuncN::create(CC_CALLBACK_0(Clip::setScaleX, clip,scale)),
                                move,
                                delay,
                                CallFuncN::create(CC_CALLBACK_0(Clip::setScaleX, clip,-scale)),
                                moveBack,
                                delay->clone(),NULL);
    clip->runAction(RepeatForever::create(seq));

}

void HomeScene::initUi()
{
    PRole role=Manager::getInstance()->getRoleData()->role();
    auto widget=static_cast<Widget*>(comLayout->getChildByName("home_top"));
    
    Widget* leftPg = static_cast<Widget*>(widget->getChildByName("leftPg"));
    static_cast<Text*>(leftPg->getChildByName("txt_name"))->setString(role.rolename());
    
    static_cast<TextAtlas*>(leftPg->getChildByName("vipLevelLabel"))->setString(Value(role.viplvl()).asString());
    static_cast<TextAtlas*>(leftPg->getChildByName("levelLabel"))->setString(Value(role.level()).asString());
    
    widget=static_cast<Widget*>(widget->getChildByName("centerPg"));
    static_cast<Text*>(widget->getChildByName("txt_currency"))->setString(Value(role.rmb()).asString());
    static_cast<Text*>(widget->getChildByName("txt_diamond"))->setString(Value(role.coin()).asString());
    static_cast<Text*>(widget->getChildByName("txt_stamina"))->setString(Value(role.stamina()).asString());
    
}

void HomeScene::onEnter()
{
    BaseUI::onEnter();
}

void HomeScene::touchButtonEvent(Ref* pSender,TouchEventType type)
{
    auto button=static_cast<Button*>(pSender);
    if (!button) {
        return;
    }
    switch(type)
    {
        case TouchEventType::BEGAN:
            
            break;
        case TouchEventType::MOVED:
            break;
        case TouchEventType::ENDED:
            switch (button->getTag()) {
                case 10065://聊天按钮
                {
                    this->chat->show();//
                    break;
                }
                case 10037://下面最右边的按钮
                {
//                    Bag* bag = Bag::create();
//                    bag->show();
                    break;
                }
                case 10034:
                {
//                    Formation::create(this)->show();
                    break;
                }
                case 10036:
                {
//                    Compose::create()->show();
                    break;
                }
                    
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void HomeScene::touchBuildEvent(cocos2d::Ref *pSender, TouchEventType type)
{
    auto sprite=static_cast<Sprite*>(pSender);
    switch (type)
    {
        case TouchEventType::BEGAN:
            sprite->stopAllActions();
            sprite->runAction(Sequence::create(ScaleTo::create(0.15,1.1),ScaleTo::create(0.15, 1),NULL) );
            break;
        case TouchEventType::MOVED:
            break;
        case TouchEventType::ENDED:
        {
            switch (sprite->getTag())
            
            {
                case 10001: //竞技场
                {
                    
                    //gate->setPosition(Vec2(0,0));
                    break;

                }
                case 10002: //市场
                {                
                    
                    break;

                }
                case 10003: //战场pve
                {
//                    Gate* gate = Gate::create();
//                    gate->show();
                    //this->addChild(gate);
//                    GateMap* gateMap=GateMap::create(this, "100");
//                    gateMap->show();
                    break;
                }
                case 10004: //英雄编队（卡组）
                {
                    
                    break;
                }
                case 10005: //英雄属性
                {
//                    RoleAllList*roleAllList = RoleAllList::create();
//                    roleAllList->show();
                        break;
                }
                case 10006: //召唤
                {
//                    RoleList* roleList = RoleList::create();
//                    roleList->show();
                    break;
                }
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
}

void HomeScene::touchIconEvent(Ref *pSender, TouchEventType type)
{
    auto sprite=static_cast<Sprite*>(pSender);
    switch (type)
    {
        case TouchEventType::BEGAN:
            sprite->stopAllActions();
            sprite->runAction(Sequence::create(ScaleTo::create(0.15,1.1),ScaleTo::create(0.15, 1),NULL) );
            break;
        case TouchEventType::ENDED:
            break;
        default:
            break;
    }

}

void HomeScene::initNetEvent()
{
    auto listener = EventListenerCustom::create(NET_MESSAGE, [=](EventCustom* event)
    {
        NetMsg* msg = static_cast<NetMsg*>(event->getUserData());
        log("Custom event 1 received:%d,%d",msg->msgId,msg->len);
        switch (msg->msgId)
        {
            case C_UPROLE:
            {
                this->initUi();
//                LoginResp pm;
//                pm.ParseFromArray(msg->bytes, msg->len);
            }
                break;
            default:
                break;
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HomeScene::onExit()
{
    BaseUI::onExit();
    this->removeAllChildrenWithCleanup(true);
    TextureCache::getInstance()->removeAllTextures();
}