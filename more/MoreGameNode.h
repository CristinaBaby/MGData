
#ifndef __MoreGameNode__
#define __MoreGameNode__


#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class MoreGameNode : public Node
{
public:
    MoreGameNode();
    ~MoreGameNode();
    
    CREATE_FUNC(MoreGameNode);
    
    enum MGPostion{
        eTopLeft,
        eTopRight,
        eBottomLeft,
        eBottomRight,
    };
    virtual bool init();
    
    virtual bool ccTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void ccTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void ccTouchEnded(Touch *pTouch, Event *pEvent);
    virtual void ccTouchCancelled(Touch *pTouch, Event *pEvent);
    
    void showMoreGameIcon(MoreGameNode::MGPostion po);
    
    std::function<void(MoreGameNode* item)>onItemClicked;
    std::function<void(MoreGameNode* item)>onItemTouchBegin;
    
    Sprite* getContentSprite(){return m_pContentSrite;}
    
    void setItemTouchEnable(bool enable = true){
        m_bTouchEnable = enable;
    }
protected:
    Sprite* m_pBgSrite;
    Sprite* m_pContentSrite;
 
    bool m_bTouchEnable;
};

#endif