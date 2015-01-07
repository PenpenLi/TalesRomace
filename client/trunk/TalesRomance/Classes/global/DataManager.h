//
//  DataManager.h
//  TalesRomance
//
//  Created by qll on 14/12/8.
//
//

#ifndef __TalesRomance__DataManager__
#define __TalesRomance__DataManager__

#include <stdio.h>
#include "cocos2d.h"
#include "pomelo.h"

using namespace cocos2d;

class DataManager : public Ref {
    
    
public:
    static DataManager* getInstance();
    json_t* teamData;
};

#endif /* defined(__TalesRomance__DataManager__) */
