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
    if (line_size == SQUARE_SIZE_LINE_OF_4)
        return (Size(winSize.width / 4, static_cast<float>(winSize.height / SQUARE_SIZE_4_HEIGHT)));
    else if (line_size == SQUARE_SIZE_LINE_OF_5)
        return (Size(winSize.width / 5, winSize.height / SQUARE_SIZE_5_HEIGHT));

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
    ProgressTimer *progress = ((ProgressTimer *) this->progress_view->getChildByTag(
            PROGRESS_CONTENT_TAG));
    progress->setPercentage(100);
}

void Square::create_asset_views(Square *sq) {
    sq->asset_view = Menu::create();
    sq->asset_view->setContentSize(Size(sq->getContentSize().width,
                                        static_cast<float>(sq->getContentSize().height * 0.80)));
    sq->asset_view->setAnchorPoint(Vec2(0, 1));
    sq->asset_view->setPosition(Vec2(0, sq->getPositionY() + sq->getContentSize().height / 2));
    sq->addChild(sq->asset_view);
    Sprite *border = Sprite::create("gauges/gauge_border.png");
    ProgressTimer *progress = ProgressTimer::create(
            Sprite::create("gauges/gauge_content.png"));
    progress->setTag(PROGRESS_CONTENT_TAG);
    progress->setType(ProgressTimerType::BAR);
    progress->setMidpoint(Vec2(0, 0));
    progress->setBarChangeRate(Vec2(1, 0));
    progress->setPercentage(static_cast<float>(0));
    sq->progress_view = Menu::create();
    sq->progress_view->setAnchorPoint(Vec2(0, 0));
    sq->progress_view->setContentSize(Size(sq->getContentSize().width,
                                           static_cast<float>(sq->getContentSize().height * 0.12)));
    sq->addChild(sq->progress_view);
    sq->progress_view->setPosition(Vec2(0, 0));
    border->setContentSize(
            Size(static_cast<float>(sq->progress_view->getContentSize().width * 0.8),
                 sq->progress_view->getContentSize().height));
    sq->progress_view->addChild(border, 1);
    sq->progress_view->addChild(progress, 2);
    border->setPosition(
            Vec2(sq->progress_view->getContentSize().width / 2, (sq->progress_view->getPositionY() -
                                                                 sq->progress_view->getContentSize().height /
                                                                 2) +
                                                                border->getContentSize().height /
                                                                2));
    progress->setPosition(border->getPosition());
    progress->setScaleX(static_cast<float>(border->getContentSize().width * 0.99 /
                                           progress->getContentSize().width));
    progress->setScaleY(static_cast<float>(border->getContentSize().height * 0.5 /
                                           progress->getContentSize().height));
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
        create_asset_views(s);
        return (s);
    }
    CC_SAFE_DELETE(s);
    return NULL;
}


