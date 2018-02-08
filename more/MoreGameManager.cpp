
#include "MoreGameManager.h"
#include "FileUtility.h"
#include "UpgradeDelegate.h"

void MoreGameManager::loadFile(std::string path)
{
    FileUtils *fu= FileUtils::getInstance();
    ValueMap vm;
    
    vm = fu->getValueMapFromFile(path);//dictionary,如果是vector,使用fu->getValueVectorFromFile(const std::string &filename)
    for (auto it = vm.begin(); it != vm.end();++it)
    {
        log("===%s",typeid(it->second).name());
        m_Map.insert(ValueMap::value_type(it->first,Value(it->second)));
    }
    auto it = m_Map.find("more");
    if (it==m_Map.end()) {
        return;
    }
    m_MoreData.clear();
    
    ValueVector tempMap = it->second.asValueVector();
    for_each(tempMap.begin(),tempMap.end(),[=](Value cur){
        ValueMap map = cur.asValueMap();
        MGConfigData data;
        data.init();
        
        auto itAppleId = map.find("");
        if (itAppleId!=map.end()) {
            data.appleId = itAppleId->second.asString();
        }
        
        auto itGooleId = map.find("");
        if (itGooleId!=map.end()) {
            data.googleId = itGooleId->second.asString();
        }
        
        auto itName = map.find("");
        if (itName!=map.end()) {
            data.iconName = itName->second.asString();
        }
        
        auto itNum = map.find("");
        if (itName!=map.end()) {
            data.num = itNum->second.asInt();
        }
        data.display();
        m_MoreData.push_back(data);
    });
}

AssetsManager* MoreGameManager::getAssetManager()
{
    static AssetsManager *assetManager = NULL;
    if (!assetManager)
    {
        std::string _pathToSave;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        _pathToSave = FileUtility::getStoragePath()+"more";
#else
        _pathToSave = FileUtility::getStoragePath()+"/more";
#endif
        bool succeed = FileUtils::getInstance()->createDirectory(_pathToSave);
//        FileUtils::getInstance()->createDirectory(_pathToSave+"");
//        assetManager = new AssetsManager("https://pan.baidu.com/s/1kV2gXxH/more.zip",
//                                         "https://pan.baidu.com/s/1kV2gXxH/version",
//                                         _pathToSave.c_str());
        UpgradeDelegate* delegate = UpgradeDelegate::getInstance();
        assetManager = AssetsManager::create("https://pan.baidu.com/s/1kV2gXxH/mg_upgrage/more.zip", "https://pan.baidu.com/s/1kV2gXxH/mg_upgrage/version", _pathToSave.c_str(), nullptr, nullptr, nullptr);
        assetManager->setDelegate(new UpgradeDelegate());
        assetManager->setConnectionTimeout(8);
    }
    return assetManager;
}

AssetsManagerEx* MoreGameManager::getAssetManagerEx()
{
    static AssetsManagerEx *assetManager = NULL;
    if (!assetManager)
    {
        std::string _pathToSave;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        _pathToSave = FileUtility::getStoragePath()+"more";
#else
        _pathToSave = FileUtility::getStoragePath()+"/more";
#endif
        bool succeed = FileUtils::getInstance()->createDirectory(_pathToSave);
        //        https://pan.baidu.com/s/1miASyLy
        assetManager = AssetsManagerEx::create("https://pan.baidu.com/s/1miASyLy", _pathToSave);
//        assetManager
    }
    return assetManager;
}
void MoreGameManager::upgrade()
{
    getAssetManagerEx()->update();
}