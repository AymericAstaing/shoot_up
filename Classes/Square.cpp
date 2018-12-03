#include    "Square.h"
#include    "GameScene.h"
#include    "Utils.h"
#include    "ShootUp.h"
#include    "Line.h"

Square::Square(int line_size) {
}

Square::~Square() {
}

Size Square::get_square_size(int line_size) {
    auto winSize = Director::getInstance()->getVisibleSize();

    if (line_size > 5 || line_size < 4)
        return (Size(0, 0));
    if (line_size == SQUARE_SIZE_LINE_OF_4) {
        return (Size(static_cast<float>(winSize.width / 4),
                     static_cast<float>(winSize.height / 9.6)));
    } else if (line_size == SQUARE_SIZE_LINE_OF_5) {
        return (Size(static_cast<float>(winSize.width / 5),
                     static_cast<float>(winSize.height / 11)));
    }
    return (Size(0, 0));
}

float *Square::get_rect_size() {
    return (rect_size);
}

int Square::get_square_pv() {
    return (this->square_pv);
}

void Square::reset_square() {
    this->particle_played = 0;
    this->square_pv = 0;
    std::string st = StringUtils::format("%i", this->square_pv);
    this->points->setString(st);
    if (this->star_bonus == 1)
        detach_square();
}

void Square::detach_square() {
    removeChildByTag(STAR_BONUS_TAG);
    this->points->setPosition(Vec2(this->rect_size[0] / 2, this->rect_size[1] / 2));
    this->star_bonus = 0;
}

void Square::assign_point(int pv) {
    if (pv == 0)
        pv = 1;
    this->initial_pv = pv;
    this->square_pv = pv;
    this->points->setString(Utils::get_reduced_value(square_pv, VALUE_SIMPLE));
}

Square *Square::create(int line_size) {
    auto winSize = Director::getInstance()->getVisibleSize();
    Square *s = new Square(line_size);
    if (s) {
        s->setAnchorPoint(Vec2(0.5, 0.5));
        s->square_pv = 10;
        s->star_bonus = 0;
        s->particle_played = 0;
        s->setContentSize(get_square_size(line_size));
        s->rect_size[0] = s->getContentSize().width;
        s->rect_size[1] = s->getContentSize().height;
        std::string st = StringUtils::format("%i", s->square_pv);
        s->points = Label::createWithSystemFont(st, FIRE_UP_FONT_NAME_NUMBERS, 35);
        s->points->setTextColor(Color4B::WHITE);
        s->points->setPosition(Vec2(s->rect_size[0] / 2, s->rect_size[1] / 2));
        s->addChild(s->points, 100);
        return (s);
    }
    CC_SAFE_DELETE(s);
    return NULL;
}


