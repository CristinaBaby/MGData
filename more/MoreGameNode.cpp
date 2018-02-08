
#include "MoreGameNode.h"
#include "MoreGameManager.h"
#include "FileUtility.h"
#include "CMVisibleRect.h"

//http://pan.baidu.com/s/1kVPhAFt

MoreGameNode::MoreGameNode()
{
    m_pBgSrite = nullptr;
    m_pContentSrite = nullptr;
    onItemClicked = nullptr;
    onItemTouchBegin = nullptr;
}

MoreGameNode::~MoreGameNode()
{
}
bool MoreGameNode::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    m_bTouchEnable = true;
    
    
    std::string exPath;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exPath = FileUtility::getStoragePath()+"more/";
#else
    exPath = FileUtility::getStoragePath()+"/more/";
#endif
    MoreGameManager* pManager = MoreGameManager::getInstance();
    pManager->loadFile(exPath+"config.plist");
    std::vector<MGConfigData> dataVector = pManager->getMoreGameDataVector();
    
    m_pBgSrite = Sprite::create(exPath+"icon/frame.png");
    if (m_pBgSrite) {
        this->addChild(m_pBgSrite,10);
    }
    this->setContentSize(Size::ZERO);
    
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    listener->onTouchBegan = CC_CALLBACK_2(MoreGameNode::ccTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MoreGameNode::ccTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MoreGameNode::ccTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MoreGameNode::ccTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


bool MoreGameNode::ccTouchBegan(Touch *pTouch, Event *pEvent)
{
    if (!m_bTouchEnable) {
        return false;
    }
    if (m_pContentSrite) {
        Vec2 point = pTouch->getLocation();
        
        Rect rect = Rect(-_contentSize.width*m_pContentSrite->getAnchorPoint().x, -_contentSize.height*m_pContentSrite->getAnchorPoint().y, _contentSize.width, _contentSize.height);
        Rect boundBox = RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
        boundBox.origin = this->getParent()->convertToWorldSpace(boundBox.origin);
        
        if (boundBox.containsPoint(point)) {
            if(onItemTouchBegin){
                onItemTouchBegin(this);
            }
            return true;
        }
    }
    return false;
}
void MoreGameNode::ccTouchMoved(Touch *pTouch, Event *pEvent)
{
    
}
void MoreGameNode::ccTouchEnded(Touch *pTouch, Event *pEvent)
{
    if (m_pContentSrite) {
        Vec2 point = pTouch->getLocation();
        
        Rect rect = Rect(-_contentSize.width*m_pContentSrite->getAnchorPoint().x, -_contentSize.height*m_pContentSrite->getAnchorPoint().y, _contentSize.width, _contentSize.height);
        Rect boundBox = RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
        boundBox.origin = this->getParent()->convertToWorldSpace(boundBox.origin);
        
        if (boundBox.containsPoint(point)) {
            if (onItemClicked) {
                onItemClicked(this);
            }
        }
    }
}
void MoreGameNode::ccTouchCancelled(Touch *pTouch, Event *pEvent)
{
    
}

void MoreGameNode::showMoreGameIcon(MoreGameNode::MGPostion po)
{
    MoreGameManager* pManager = MoreGameManager::getInstance();
    std::vector<MGConfigData> dataVector = pManager->getMoreGameDataVector();
    int total = dataVector.size();
    if (total<=0) {
        log("this is no moregame infomations");
        return;
    }
    static int num = arc4random()%total;
    MGConfigData dat = dataVector.at(num);
    
    std::string exPath;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exPath = FileUtility::getStoragePath()+"more/icon/";
#else
    exPath = FileUtility::getStoragePath()+"/more/icon/";
#endif
    
    std::stringstream path;
    path<<exPath<<num<<".png";
    if (!m_pContentSrite) {
        m_pContentSrite = Sprite::create(path.str());
        this->addChild(m_pContentSrite);
    }else{
        m_pContentSrite->setTexture(path.str());
    }
    if (m_pContentSrite) {
        this->setContentSize(m_pContentSrite->getContentSize());
        Director::getInstance()->getRunningScene()->addChild(this,1000);
        switch (po) {
            case eTopLeft:{
                CMVisibleRect::setPosition(this, 18, 18,kBorderLeft,kBorderTop);
                this->setPosition(this->getPosition()-Vec2(300, 0));
                this->runAction(EaseBackOut::create(MoveBy::create(1, Vec2(300, 0))));
            }
                break;
            case eTopRight:{
                CMVisibleRect::setPosition(this, 18, 18,kBorderRight,kBorderTop);
                this->setPosition(this->getPosition()+Vec2(300, 0));
                this->runAction(EaseBackOut::create(MoveBy::create(1, Vec2(-300, 0))));
            }
                break;
            case eBottomLeft:{
                CMVisibleRect::setPosition(this, 18, 18,kBorderLeft,kBorderBottom);
                this->setPosition(this->getPosition()-Vec2(300, 0));
                this->runAction(EaseBackOut::create(MoveBy::create(1, Vec2(300, 0))));
            }
                break;
            case eBottomRight:{
                CMVisibleRect::setPosition(this, 18, 18,kBorderRight,kBorderBottom);
                CMVisibleRect::setPosition(this, 18, 18,kBorderRight,kBorderTop);
                this->setPosition(this->getPosition()+Vec2(300, 0));
                this->runAction(EaseBackOut::create(MoveBy::create(1, Vec2(-300, 0))));
            }
                break;
                
            default:
                break;
        }
    }
}