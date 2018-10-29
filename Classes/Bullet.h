#ifndef __BULLET_H__
#define __BULLET_H__

#include    "cocos2d.h"

USING_NS_CC;

class Bullet : public cocos2d::Sprite {

public:
                        Bullet();
                        ~Bullet();
    static Bullet*      create();
    void                launch(int, Vec2, Size, int);
    void                reset();
    bool                bullet_active = false;
    bool                contact = false;
    int                 contact_index = -1;

private:
};

#endif // __BULLET_H__
