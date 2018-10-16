#include    "Popup.h"
#include    "ShootUp.h"
#include    "GameScene.h"
#include    "UserLocalStore.h"

USING_NS_CC;

using namespace ui;

namespace POPUP_PATH {
    const char *BACKGROUND_IMAGE = "pop_up/popUpBase.png";
    const char *POWER = "pop_up/power.png";
    const char *POWER_SELECTED = "pop_up/power_selected.png";
    const char *SPEED = "pop_up/speed.png";
    const char *SPEED_SELECTED = "pop_up/speed_selected.png";
}

namespace {
    cocos2d::Size CONFIRM_DIALOGUE_SIZE_OFFSET = Size(100, 150);
    const float ANIMATION_TIME = 0.15f;
    const float FADE_RATIO = 150;
}

namespace UICustom {


    PopupDelegates *PopupDelegates::create() {
        PopupDelegates *node = new(std::nothrow)PopupDelegates();
        if (node && node->init()) {
            node->autorelease();
            return node;
        }
        CC_SAFE_DELETE(node);
        return nullptr;
    }

    bool PopupDelegates::init() {
        Size winSize = Director::getInstance()->getVisibleSize();
        if (!LayerRadialGradient::initWithColor(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, 0),
                                                (static_cast<float>(winSize.width / 1.10)) / 2,
                                                winSize / 2, 0.075f))
            return false;
        this->setOpacity(0);
        show(true);
        this->setUpTouches();
        return true;
    }

    void PopupDelegates::show(const bool animated) {
        if (animated) {
            this->runAction(FadeTo::create(ANIMATION_TIME, 1));
        } else {
            this->setOpacity(FADE_RATIO);
        }
    }

    void PopupDelegates::dismiss(const bool animated) {
        if (animated) {
            this->runAction(
                    Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(),
                                     NULL));
        } else {
            this->removeFromParentAndCleanup(true);
        }
    }

    void PopupDelegates::setUpTouches() {

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch *touch, Event *event) {
            if (_bg) {
                if (!_bg->getBoundingBox().containsPoint(
                        this->convertToNodeSpace(touch->getLocation()))) {
                    auto scaleTo = ScaleTo::create(0.1f, 0);
                    runAction(scaleTo);
                    Menu *menu = ((Menu *) getParent()->getChildByTag(MAIN_MENU_TAG));
                    MenuItemFont *power = ((MenuItemFont *) menu->getChildByTag(
                            POWER_LEVEL_BTN_TAG));
                    MenuItemFont *speed = ((MenuItemFont *) menu->getChildByTag(
                            SPEED_LEVEL_BTN_TAG));
                    char power_value[DEFAULT_CHAR_LENGHT];
                    sprintf(power_value, "%i",
                            UserLocalStore::get_achievement_variable(POWER_VALUE));
                    char speed_value[DEFAULT_CHAR_LENGHT];
                    sprintf(speed_value, "%.1f",
                            UserLocalStore::get_achievement_variable_float(SPEED_VALUE));
                    if (speed && power) {
                        speed->setString(speed_value);
                        power->setString(power_value);
                    }
                    this->dismiss(true);
                }
            } else {
                this->dismiss(true);
            }
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }

    Popup *Popup::create(const std::string &title, const std::string &msg,
                         const std::function<void()> &YesFunc) {
        Popup *node = new(std::nothrow)Popup();
        Size winSize = Director::getInstance()->getVisibleSize();

        double popup_width = winSize.width / 1.10;
        double popup_height = winSize.height / 2.58;

        if (node && node->init()) {
            if (YesFunc) {
                char user_points[DEFAULT_CHAR_LENGHT];
                sprintf(user_points, "%i pts", UserLocalStore::get_achievement_variable(POINT));
                MenuItemFont *point_nbr = MenuItemFont::create(user_points,
                                                               [=](Ref *sender) {
                                                               });
                char power_level[DEFAULT_CHAR_LENGHT];
                sprintf(power_level, "LEVEL %i",
                        UserLocalStore::get_achievement_variable(POWER_LEVEL));
                char speed_level[DEFAULT_CHAR_LENGHT];
                sprintf(speed_level, "LEVEL %i",
                        UserLocalStore::get_achievement_variable(SPEED_LEVEL));
                MenuItemFont *power_level_txt = MenuItemFont::create(power_level,
                                                                     [=](Ref *sender) {
                                                                     });
                MenuItemFont *speed_level_txt = MenuItemFont::create(speed_level,
                                                                     [=](Ref *sender) {
                                                                     });
                point_nbr->setFontNameObj(FIRE_UP_FONT);
                point_nbr->setFontSizeObj(70);
                MenuItemImage *power_btn = MenuItemImage::create(POPUP_PATH::POWER,
                                                                 POPUP_PATH::POWER_SELECTED,
                                                                 [=](Ref *sender) {
                                                                     Popup::increase_power(
                                                                             power_level_txt);
                                                                 });

                MenuItemImage *speed_btn = MenuItemImage::create(POPUP_PATH::SPEED,
                                                                 POPUP_PATH::SPEED_SELECTED,
                                                                 [=](Ref *sender) {
                                                                     Popup::increase_speed(
                                                                             speed_level_txt);
                                                                 });
                speed_btn->setPosition(Vec2(
                        static_cast<float>(speed_btn->getPosition().x - popup_width / 4),
                        static_cast<float>(speed_btn->getPosition().y - popup_height / 4)));
                power_btn->setPosition(Vec2(
                        static_cast<float>(power_btn->getPosition().x + popup_width / 4),
                        static_cast<float>(power_btn->getPosition().y - popup_height / 4)));
                point_nbr->setPosition(Vec2(point_nbr->getPosition().x,
                                            static_cast<float>(point_nbr->getPosition().y +
                                                               (popup_height / 2 -
                                                                point_nbr->getContentSize().height *
                                                                0.9))));
                char power_price[DEFAULT_CHAR_LENGHT];
                sprintf(power_price, "%i pts",
                        UserLocalStore::get_achievement_variable(POWER_LEVEL_PRICE));
                char speed_price[DEFAULT_CHAR_LENGHT];
                sprintf(speed_price, "%i pts",
                        UserLocalStore::get_achievement_variable(SPEED_LEVEL_PRICE));

                MenuItemFont *power_price_txt = MenuItemFont::create(speed_price,
                                                                     [=](Ref *sender) {
                                                                     });
                MenuItemFont *speed_price_txt = MenuItemFont::create(power_price,
                                                                     [=](Ref *sender) {
                                                                     });
                Label *power_info_label = Label::createWithTTF("SHOOTING\nPOWER",
                                                               FIRE_UP_FONT, 24);
                power_info_label->setHorizontalAlignment(TextHAlignment::CENTER);
                Label *speed_info_label = Label::createWithTTF("SHOOTING\nSPEED",
                                                               FIRE_UP_FONT, 24);
                speed_info_label->setHorizontalAlignment(TextHAlignment::CENTER);
                MenuItemLabel *power_info_txt = MenuItemLabel::create(power_info_label,
                                                                      [=](Ref *sender) {
                                                                      });
                MenuItemLabel *speed_info_txt = MenuItemLabel::create(speed_info_label,
                                                                      [=](Ref *sender) {
                                                                      });
                power_price_txt->setFontNameObj(FIRE_UP_FONT);
                power_price_txt->setFontSizeObj(25);
                power_price_txt->setPosition(Vec2(power_btn->getPosition().x,
                                                  power_btn->getPosition().y -
                                                  (power_btn->getContentSize().height / 6)));
                speed_price_txt->setFontNameObj(FIRE_UP_FONT);
                speed_price_txt->setFontSizeObj(25);
                speed_price_txt->setPosition(Vec2(speed_btn->getPosition().x,
                                                  speed_btn->getPosition().y -
                                                  (speed_btn->getContentSize().height / 6)));
                power_level_txt->setFontNameObj(FIRE_UP_FONT);
                power_level_txt->setFontSizeObj(28);
                power_level_txt->setColor(Color3B(255, 124, 124));
                power_level_txt->setPosition(Vec2(power_btn->getPosition().x,
                                                  power_btn->getPosition().y +
                                                  (power_btn->getContentSize().height / 2 + 20)));
                speed_level_txt->setFontNameObj(FIRE_UP_FONT);
                speed_level_txt->setColor(Color3B(124, 184, 255));
                speed_level_txt->setFontSizeObj(28);
                speed_level_txt->setPosition(Vec2(speed_btn->getPosition().x,
                                                  speed_btn->getPosition().y +
                                                  (speed_btn->getContentSize().height / 2 + 20)));
                power_info_txt->setPosition(Vec2(power_btn->getPosition().x,
                                                 static_cast<float>(
                                                         power_level_txt->getPosition().y +
                                                         (power_level_txt->getContentSize().height *
                                                          1.5))));
                speed_info_txt->setPosition(Vec2(speed_btn->getPosition().x,
                                                 static_cast<float>(
                                                         speed_level_txt->getPosition().y +
                                                         (speed_level_txt->getContentSize().height *
                                                          1.5))));
                Menu *menu = Menu::create(power_btn, speed_btn, point_nbr, power_price_txt,
                                          speed_price_txt, power_level_txt, speed_level_txt,
                                          power_info_txt, speed_info_txt, NULL);
                node->addChild(menu, 2);
                menu->setPosition(winSize.width / 2, winSize.height / 2);
                CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
            }
            node->initBg();
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }

    void Popup::increase_speed(MenuItemFont *pFont) {
        UserLocalStore::store_achievement_variable_float(SPEED_VALUE,
                                                         (UserLocalStore::get_achievement_variable_float(
                                                                 SPEED_VALUE) + 0.5));
        UserLocalStore::store_achievement_variable(
                SPEED_LEVEL,
                UserLocalStore::get_achievement_variable(
                        SPEED_LEVEL) +
                1);
        char s[DEFAULT_CHAR_LENGHT];
        sprintf(s, "SPEED %i",
                UserLocalStore::get_achievement_variable(
                        SPEED_LEVEL));
        pFont->setString(s);
    }

    void Popup::increase_power(MenuItemFont *pFont) {
        UserLocalStore::store_achievement_variable(
                POWER_VALUE,
                UserLocalStore::get_achievement_variable(
                        POWER_VALUE) +
                2);
        UserLocalStore::store_achievement_variable(
                POWER_LEVEL,
                UserLocalStore::get_achievement_variable(
                        POWER_LEVEL) +
                1);
        char p[DEFAULT_CHAR_LENGHT];
        sprintf(p, "LEVEL %i",
                UserLocalStore::get_achievement_variable(POWER_LEVEL));
        pFont->setString(p);
    }

    void Popup::initBg() {

        Size winSize = Director::getInstance()->getVisibleSize();

        _bg = ui::ImageView::create(POPUP_PATH::BACKGROUND_IMAGE);
        this->addChild(_bg);
        _bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
        _bg->setScale9Enabled(true);
        _bg->setContentSize(Size(static_cast<float>(winSize.width / 1.10),
                                 static_cast<float>(winSize.height / 2.58)));
    }


}

