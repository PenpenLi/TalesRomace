#ifndef __fancyHeart__LoginScene__
#define __fancyHeart__LoginScene__

#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include "Manager.h"
#include "WebHttp.h"
#include "HomeScene.h"
#include "Loading.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
class LoginScene : public BaseUI
{
public:

    static cocos2d::Scene* createScene();
    static LoginScene* create();
    virtual bool init(std::string fileName);
    virtual void onEnter();
    virtual void onExit();
    virtual void resetUI();
    virtual void onDlgClose(rapidjson::Value &data);
    void webSend(std::string str);
private:
    rapidjson::Document sData;
    void initGame();
    void initGameCallback(std::vector<char> *data);
    void initNetEvent();
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    void touchServerEvent(Ref *pSender, Widget::TouchEventType type);
    Vector<Button*> serverItems;//各服务器按钮
    void setSeverItemsMouseEnable(bool isCan);//设置是否可以点击选择服务器按钮
    TextField* accountInput;//账号输入框
    TextField* passwordInput;//密码输入框
    bool isremember;//记录账号和密码是否被记录过
};

#endif // __HELLOWORLD_SCENE_H__
