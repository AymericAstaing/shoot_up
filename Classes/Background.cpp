#include    "Background.h"

Background::Background(const std::string &, int*, int) {
}

Background::~Background() {
}

void Background::reset() {
    auto winSize = Director::getInstance()->getVisibleSize();
    this->setPositionY(winSize.height + this->getContentSize().height);
    this->alive = false;
}

Background *Background::create(const std::string &filename, int *possible_background, int tag) {
    auto winSize = Director::getInstance()->getVisibleSize();
    Background *background = new Background(filename, possible_background, tag);
    background->initWithFile(filename);
    background->next_possible_background = possible_background;
    background->setContentSize(winSize);
    background->setAnchorPoint(Vec2(0, 1));
    background->setPosition(Vec2(0, winSize.height + background->getContentSize().height));
    background->alive = false;
    background->setTag(tag);
    if (background) {
        return (background);
    }
    CC_SAFE_DELETE(background);
    return nullptr;
}


