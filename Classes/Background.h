#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include    "cocos2d.h"

USING_NS_CC;

class Background : public cocos2d::Sprite {

public:
                            Background(const std::string&, int*, int);
                            ~Background();
    static Background*      create(const std::string&, int*, int);
    void                    reset();

    int*                    next_possible_background;
    bool                     alive = 0;


private:
};

#endif // __BACKGROUND_H__
