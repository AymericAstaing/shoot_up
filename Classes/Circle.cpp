#include    "Circle.h"
#include    "ShootUp.h"


Circle::Circle() {
}

Circle::~Circle() {
}

void Circle::reset() {
    auto winSize = Director::getInstance()->getVisibleSize();
    this->active_circle = false;
    this->setVisible(false);
    this->setPosition(Vec2(getContentSize().width / 2,
                           winSize.height - getContentSize().height / 2));
    auto fadeIn = FadeIn::create(0);
    setScale(0.0f);
    runAction(fadeIn);
}

void Circle::anim_circle(Vec2 pos) {
    this->active_circle = true;
    this->setVisible(true);
    this->setPosition(pos);
    auto callback = CallFuncN::create(
            [&](Node *sender) {
                reset();
            });
    auto move_ease_in = EaseOut::create(ScaleTo::create(1.4f, 2), 2);
    auto fadeOut = FadeOut::create(0.55f);
    runAction(fadeOut);
    runAction(Sequence::create(move_ease_in, callback, nullptr));
}

Circle *Circle::create() {
    auto winSize = Director::getInstance()->getVisibleSize();
    Circle *c = new Circle();
    if (c->initWithFile(HIT_CIRCLE)) {
        c->setScale(0.0f);
        c->setPosition(Vec2(-c->getContentSize().width / 2,
                            winSize.height - c->getContentSize().height / 2));
        c->setVisible(false);
        c->active_circle = false;
        return (c);
    }
    CC_SAFE_DELETE(c);
    return NULL;
}


