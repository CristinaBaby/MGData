//
//  UpgradeDelegate.cpp
//  MLABS1069_Pizza
//
//  Created by wuguiling on 16/8/23.
//
//

#include "UpgradeDelegate.h"

USING_NS_CC;

void UpgradeDelegate::onError(AssetsManager::ErrorCode errorCode)
{
    log("UpgradeDelegate::onError   %d",errorCode);
}
void UpgradeDelegate::onProgress(int percent)
{
    log("UpgradeDelegate::onProgress %d",percent);
}
void UpgradeDelegate::onSuccess()
{
    log("UpgradeDelegate::onSuccess");
}
