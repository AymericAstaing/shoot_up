#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include    "cocos2d.h"

USING_NS_CC;

class Circle : public  cocos2d::Sprite {

public:
                            Circle();
                            ~Circle();
    static Circle*          create();
    void                    anim_circle(Vec2);
    void                    reset();
    bool                    active_circle;

private:
};

#endif // __CIRCLE_H__
