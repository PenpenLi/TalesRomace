//
//  Utils.h
//  fancyHeart
//
//  Created by 秦亮亮 on 14-6-3.
//
//

#ifndef __fancyHeart__Utils__
#define __fancyHeart__Utils__
#include "cocos2d.h"
#include <iostream>
#include <sys/time.h>
using namespace cocos2d;
using namespace std;
class Utils {
    
    
public:
    
    static float random01();
    static long getTime();

    static double distance(Vec2 sp,Vec2 ep);
    
    static void setStar(Vector<Sprite*> vec,int num);
    
    static std::vector<int> randSeveral(int num,bool isRepeat);
    //字符替换如getLang("购买{1},花费{2}金币","武器","10");
    static std::string getLang(std::string arg,std::vector<std::string> params);
    static std::string getLang(std::string str);
    static std::vector<std::string> split(std::string str, std::string match);
    static Sprite* maskedSpriteWithSprite(Sprite* textureSprite, Sprite* maskSprite);
};
#endif /* defined(__fancyHeart__Utils__) */
