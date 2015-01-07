//
//  Team2.cpp
//  TalesRomance
//
//  Created by qll on 15/1/5.
//
//

#include "Team2.h"
Team2* Team2::create()
{
    Team2* pRet=new Team2();
    if(pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool Team2::init()
{
    if(!BaseUI::init("Team2.csb", "team2.plist")){
        return false;
    }
    for(int i=1000;i<1002;i++){
        Button* btn=(Button*)this->ui->getChildByTag(i);
        btn->addClickEventListener(CC_CALLBACK_1(Team2::onButtonClick, this));
    }
    for(int i=100;i<112;i++){
        Node* item=this->ui->getChildByTag(i);
        this->items.pushBack(item);
       
    }
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true;};
    listener->onTouchEnded = CC_CALLBACK_2(Team2::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this->ui->getChildByName("Button_1"));
    
    this->resetUI();
    this->request();
    
    return true;
}

void Team2::request()
{
    //json_t* msg=json_object();
    //json_object_set(msg, "token", Manager::getInstance()->psocket->token);
    //Manager::getInstance()->psocket->sendMsg("connector.entryHandler.entry", msg);
}

void Team2::resetUI()
{
    //DataManager::getInstance()->teamData;
    
    for(int i=0;i<this->items.size();i++){
        Node* item=this->items.at(i);
        item->getChildByName("itemBg")->setVisible(false);
        item->getChildByName("add")->setVisible(i<2);
        item->getChildByName("lock")->setVisible(i>=2);
    }
}

void Team2::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    for(int i=0;i<this->items.size();i++){
        Node* item=this->items.at(i);
        Size size=item->getContentSize();
        Vec2 itemVec=this->ui->convertToWorldSpace(item->getPosition());
        Rect rect=Rect(itemVec.x,itemVec.y,size.width,size.height);
        if(rect.containsPoint(touch->getLocation())){
            TeamCard* card=TeamCard::create();
            card->show(this);
        }
    }
}

void Team2::onButtonClick(cocos2d::Ref *pSender)
{
    Button* btn=(Button*) pSender;
    switch (btn->getTag()) {
        case 1000:
        {
            Manager::getInstance()->switchScence(HomeScene::createScene());
            break;
        }
        case 1001: //tab1
        {
            this->clear(true);
            break;
        }
    }
}

void Team2::initNetEvent(){
    auto listener = EventListenerCustom::create(NET_MESSAGE, [=](EventCustom* event){
        json_t* msg=(json_t*)event->getUserData();
        const char* route=json_string_value(json_object_get(msg, "route"));
        int msgID=msges[route];
        switch (msgID)
        {
            case GATE_GATEHANDLER_ENTRY:
            {
                break;
            }
            case CONNECTOR_ENTRYHANDLER_ENTRY:
            {
                break;
            }
            default:
                break;
        }

    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
}