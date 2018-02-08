//
//  UpgradeDelegate.h
//  MLABS1069_Pizza
//
//  Created by wuguiling on 16/8/23.
//
//

#ifndef UpgradeDelegate_h
#define UpgradeDelegate_h

#include "SingleTon.h"
#include <stdio.h>
#include "cocos2d.h"
#include <iostream>
#include "extensions/cocos-ext.h"

using namespace cocos2d::extension;
class UpgradeDelegate :public cocos2d::extension::AssetsManagerDelegateProtocol{
    
    
public:
    static UpgradeDelegate* getInstance()
    {
        static UpgradeDelegate *pManager = NULL;
        if (!pManager)
        {
            pManager = new UpgradeDelegate();
        }
        return pManager;
    }
    
    virtual void onError(AssetsManager::ErrorCode errorCode);
    virtual void onProgress(int percent);
    virtual void onSuccess();
};

#endif /* UpgradeDelegate_h */
