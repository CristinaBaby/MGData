
#ifndef __MoreGameManager__
#define __MoreGameManager__


#include "SingleTon.h"
#include "cocos2d.h"
#include <iostream>
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

class MGConfigData {
    
public:
    std::string appleId;
    std::string googleId;
    std::string iconName;
    int num;
    std::vector<std::string> unlockItem;
    void init(){
        appleId = "";
        googleId = "";
        iconName = "";
        num = 0;
    }
    void display(){
        std::cout<<"appleId:"<<appleId<<std::endl<<"googleId:"<<googleId<<std::endl<<"iconName:"<<iconName<<std::endl<<"num:"<<num<<std::endl;
        for_each(unlockItem.begin(), unlockItem.end(), [=](std::string item){
            std::cout<<item<<std::endl;
        });
    }
    void copyData(MGConfigData data){
        appleId = data.appleId;
        googleId = data.googleId;
        iconName = data.iconName;
        num = data.num;
    }
    
    static MGConfigData copy(MGConfigData data){
        MGConfigData copyData;
        copyData.appleId = data.appleId;
        copyData.googleId = data.googleId;
        copyData.iconName = data.iconName;
        copyData.num = data.num;
        return copyData;
    }
};


using namespace cocos2d::ui;

class MoreGameManager : public SingleTon<MoreGameManager>
{
public:
    void loadFile(std::string path);
    inline std::vector<MGConfigData> getMoreGameDataVector()
    {
        return m_MoreData;
    }
    AssetsManager* getAssetManager();
    AssetsManagerEx* getAssetManagerEx();
    void upgrade();
protected:
    std::vector<MGConfigData> m_MoreData;
    ValueMap m_Map;
};

#endif