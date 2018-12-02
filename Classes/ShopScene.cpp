#include    "ShopScene.h"
#include    "GameScene.h"
#include    "Square.h"
#include    <vector>
#include    <iomanip>
#include    "cocos2d.h"
#include    "Popup.h"
#include    "Utils.h"
#include    "GridView.h"
#include    "CustomTableViewCell.h"
#include    "UserLocalStore.h"
#include    "ShootUp.h"

using namespace std;

namespace GRID_SELECTOR {
    const char *BALL_SELECTED = "shop/ball_selected.png";
    const char *BALL_UNSELECTED = "shop/ball_unselected.png";
    const char *SHOOTER_SELECTED = "shop/shooter_selected.png";
    const char *SHOOTER_UNSELECTED = "shop/shooter_unselected.png";
}

namespace MENU_ASSET {
    const char *BACKGROUND = "asset_menu/background.png";
    const char *PROGRESS_BAR = "asset_menu/progress_bar.png";
    const char *PROGRESS_BAR_CONTENT = "asset_menu/progress_bar_content.png";
    const char *OK_BUTTON = "asset_menu/ok_button.png";
}

namespace SHOP_SCENE {
    const char *BACK_BUTTON = "shop/back_button.png";
}

USING_NS_CC;


Scene *ShopScene::createScene() {
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    auto layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
}

bool ShopScene::init() {
    if (!Scene::init())
        return false;
    init_ui_components();
    init_shop_grids();
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(ShopScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void ShopScene::init_shop_grids() {
    shooter_content = UserLocalStore::get_final_shooter_array();
    ball_content = UserLocalStore::get_final_ball_array();
    shooter_grid = init_grid(SHOOTER_ARRAY);
    ball_grid = init_grid(BALL_ARRAY);
}

void ShopScene::init_ui_components() {
    auto winSize = Director::getInstance()->getVisibleSize();
    back_button = Sprite::create(SHOP_SCENE::BACK_BUTTON);
    back_button->setPosition(Vec2(static_cast<float>(0 + back_button->getContentSize().width / 1.3),
                                  static_cast<float>(winSize.height - (1.2 *
                                                                       back_button->getContentSize().height))));
    this->addChild(back_button);
    float point_value = UserLocalStore::get_achievement_variable(POINT);
    points = Label::createWithTTF(Utils::get_reduced_value(point_value, VALUE_WITH_POINT),
                                  FIRE_UP_FONT_NAME, (50));
    points->setPosition(Vec2(static_cast<float>(winSize.width / 1.8), back_button->getPosition().y -
                                                                      back_button->getContentSize().height /
                                                                      2));
    this->addChild(points);
    shooter_button = Sprite::create(GRID_SELECTOR::SHOOTER_SELECTED);
    ball_button = Sprite::create(GRID_SELECTOR::BALL_UNSELECTED);

    auto midle = winSize.width / 2;
    float shooter_width = shooter_button->getContentSize().width;
    float ball_width = ball_button->getContentSize().width;
    float both = shooter_width + ball_width;
    shooter_button->setPosition(Point(midle - both / 2 + (shooter_width / 2 - shooter_width / 8),
                                      static_cast<float>(back_button->getPosition().y -
                                                         (back_button->getContentSize().height *
                                                          1.5))));
    ball_button->setPosition(Point(midle + both / 2 - (ball_width / 2 - shooter_width / 8),
                                   shooter_button->getPosition().y));
    ball_button->setScale(1.0f);
    shooter_button->setScale(1.0f);
    this->addChild(shooter_button);
    this->addChild(ball_button);
}

cocos2d::extension::TableViewCell *
ShopScene::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    cocos2d::extension::TableViewCell *cell = table->dequeueCell();
    auto winSize = Director::getInstance()->getVisibleSize();
    if (!cell) {
        cell = new(std::nothrow) CustomTableViewCell();
        cell->autorelease();

        Sprite *sprite = nullptr;
        if (table->getTag() == SHOOTER_ARRAY)
            sprite = Sprite::create(shooter_content[idx]);
        else
            sprite = Sprite::create(ball_content[idx]);
        sprite->setScale(static_cast<float>((winSize.width / 3.2) / sprite->getContentSize().width));
        sprite->setTag(2);
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(Vec2::ZERO);
        cell->addChild(sprite);
    } else {
        auto sprite = (Sprite *) cell->getChildByTag(2);
        if (table->getTag() == SHOOTER_ARRAY)
            sprite->setTexture(shooter_content[idx]);
        else
            sprite->setTexture(ball_content[idx]);
    }
    return cell;
}

GridView *ShopScene::init_grid(int tag) {
    auto winSize = Director::getInstance()->getVisibleSize();
    GridView *gv = GridView::create(this, Size(winSize.width,
                                               static_cast<float>(winSize.height / 1.6)), tag);
    gv->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    gv->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);
    gv->setPosition(Vec2(0, static_cast<float>(winSize.height / 9.5)));
    gv->setColNum(3);
    gv->setDelegate(this);
    this->addChild(gv);
    if (tag == BALL_ARRAY)
        gv->setVisible(false);
    gv->reloadData();
    return (gv);
}

bool ShopScene::is_ball(Vec2 touch_location) {
    float x_pos = ball_button->getPosition().x - ball_button->getContentSize().width / 2;
    float y_pos = ball_button->getPosition().y - ball_button->getContentSize().height / 2;
    return touch_location.x >= x_pos &&
           touch_location.x <= x_pos + ball_button->getContentSize().width &&
           touch_location.y >= y_pos &&
           touch_location.y <= y_pos + ball_button->getContentSize().height;
}

bool ShopScene::is_shooter(Vec2 touch_location) {
    float x_pos = shooter_button->getPosition().x - shooter_button->getContentSize().width / 2;
    float y_pos = shooter_button->getPosition().y - shooter_button->getContentSize().height / 2;
    return touch_location.x >= x_pos &&
           touch_location.x <= x_pos + shooter_button->getContentSize().width &&
           touch_location.y >= y_pos &&
           touch_location.y <= y_pos + shooter_button->getContentSize().height;
}

bool ShopScene::is_back(Vec2 touch_location) {
    float x_pos = back_button->getPosition().x - back_button->getContentSize().width / 2;
    float y_pos = back_button->getPosition().y - back_button->getContentSize().height / 2;
    return touch_location.x >= x_pos &&
           touch_location.x <= x_pos + back_button->getContentSize().width &&
           touch_location.y >= y_pos &&
           touch_location.y <= y_pos + back_button->getContentSize().height;
}

Size ShopScene::tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) {
    auto winSize = Director::getInstance()->getVisibleSize();
    return Size(static_cast<float>(winSize.width / 2.98), static_cast<float>(winSize.width / 2.98));
}

void ShopScene::tableCellTouched(cocos2d::extension::TableView *table,
                                 cocos2d::extension::TableViewCell *cell) {
    if ((table->getTag() == SHOOTER_ARRAY && cell->getIdx() == 11) || cell->getIdx() == 25 ||
        cell->getIdx() == 26)
        return;
    int cell_id = cell->getIdx();
    if (table->getTag() == SHOOTER_ARRAY) {
        if (cell_id > 11 && cell_id < 26)
            cell_id = cell_id - 1;
        if (cell_id > 25)
            cell_id = cell_id - 3;
    }
    if (asset_menu_added == 1 ||
        (mode == SHOOTER && cell->getIdx() == 0 &&
         UserLocalStore::get_shooter(cell_id) != 1) ||
        (mode == BALL && cell_id == 0 && UserLocalStore::get_ball(cell_id) != 1))
        return;
    if (mode == SHOOTER && UserLocalStore::get_shooter(cell_id) != 0) {
        if (UserLocalStore::get_shooter(cell_id) != 2) {
            UserLocalStore::store_shooter(UserLocalStore::get_current_shooter(), 1);
            UserLocalStore::store_shooter(cell_id, 2);
            shooter_content = UserLocalStore::get_final_shooter_array();
            for (int i = 0; i < numberOfCellsInTableView(shooter_grid); i++) {
                shooter_grid->updateCellAtIndex(i);
            }
        }
        return;
    } else if (mode == BALL && UserLocalStore::get_ball(cell->getIdx()) != 0) {
        if (UserLocalStore::get_ball(cell->getIdx()) != 2) {
            UserLocalStore::store_ball(UserLocalStore::get_current_ball(), 1);
            UserLocalStore::store_ball(cell->getIdx(), 2);
            ball_content = UserLocalStore::get_final_ball_array();
            for (int i = 0; i < numberOfCellsInTableView(ball_grid); i++) {
                ball_grid->updateCellAtIndex(i);
            }
        }
        return;
    }
    asset_menu = get_asset_menu(cell_id - 1,
                                table->getTag()); // -1 car on enleve le premier (pas de data)
    addChild(asset_menu);
    asset_menu_added = 1;
}

ssize_t ShopScene::numberOfCellsInTableView(cocos2d::extension::TableView *table) {

    if (table->getTag() == SHOOTER_ARRAY)
        return (34);
    else if (table->getTag() == BALL_ARRAY)
        return (8);
    return 0;
}

Menu *ShopScene::get_asset_menu(int grid_pos, int table_tag) {
    auto winSize = Director::getInstance()->getVisibleSize();
    const char *achievement_txt = NULL;
    if (table_tag == SHOOTER_ARRAY)
        achievement_txt = shooter_achievement[grid_pos];
    else
        achievement_txt = ball_achievement[grid_pos];
    Label *ach_infos = Label::createWithTTF(achievement_txt,
                                            FIRE_UP_FONT_NAME, 40);

    Label *ach_progress = Label::createWithTTF("empty",
                                               FIRE_UP_FONT_NAME, 30);
    ach_infos->setHorizontalAlignment(TextHAlignment::CENTER);
    MenuItemLabel *achievement_info = MenuItemLabel::create(ach_infos, nullptr);
    MenuItemLabel *achievement_progress = MenuItemLabel::create(ach_progress, nullptr);
    int ach_score = 0;
    int ach_target = 0;
    double percent = 0;
    if (table_tag == SHOOTER_ARRAY) {
        ach_score = UserLocalStore::get_achievement_variable(
                UserLocalStore::get_shooter_key_with_index(
                        grid_pos));
        ach_target = UserLocalStore::get_shooter_achievement_target(
                grid_pos);
    } else {
        ach_score = UserLocalStore::get_achievement_variable(
                UserLocalStore::get_ball_key_with_index(
                        grid_pos));
        ach_target = UserLocalStore::get_ball_achievement_target(
                grid_pos);
    }
    percent = ((double) ach_score / ach_target) * 100;
    __String *progress = __String::createWithFormat("(%i/%i)", ach_score, ach_target);
    achievement_progress->setString(progress->getCString());
    achievement_progress->setPosition(Vec2(winSize / 2));
    auto menu_background = MenuItemImage::create(MENU_ASSET::BACKGROUND,
                                                 MENU_ASSET::BACKGROUND);
    auto menu_progress_bar_base = MenuItemImage::create(MENU_ASSET::PROGRESS_BAR,
                                                        MENU_ASSET::PROGRESS_BAR);
    ProgressTimer *progressTimer = ProgressTimer::create(
            Sprite::create(MENU_ASSET::PROGRESS_BAR_CONTENT));
    progressTimer->setType(ProgressTimerType::BAR);
    progressTimer->setMidpoint(Vec2(0, 0));
    progressTimer->setBarChangeRate(Vec2(1, 0));
    progressTimer->setPercentage(static_cast<float>(percent));
    progressTimer->setPosition(Vec2(winSize / 2));
    menu_progress_bar_base->setPosition(Size(winSize / 2));
    menu_background->setContentSize(Size(winSize));
    auto menu_ok_button = MenuItemImage::create(MENU_ASSET::OK_BUTTON, MENU_ASSET::OK_BUTTON,
                                                [=](Ref *sender) {
                                                    removeChild(asset_menu);
                                                    asset_menu_added = 0;
                                                });
    achievement_info->setPosition(Vec2(winSize.width / 2, static_cast<float>(winSize.height / 2 +
                                                                             achievement_info->getContentSize().height /
                                                                             2 + (2.7 *
                                                                                  progressTimer->getContentSize().height))));
    menu_ok_button->setPosition(Vec2(winSize.width / 2,
                                     static_cast<float>(progressTimer->getPosition().y - (3 *
                                                                                          progressTimer->getContentSize().height))));
    auto main_menu = Menu::create(menu_background, menu_ok_button, menu_progress_bar_base,
                                  progressTimer, achievement_info, achievement_progress, NULL);
    main_menu->setPosition(Point(0, 0));
    return (main_menu);
}

bool ShopScene::onTouchBegan(Touch *touch, Event *event) {
    if (asset_menu_added == 1)
        return false;
    Vec2 touch_pos = touch->getLocation();

    if (is_ball(touch_pos)) {
        mode = BALL;
        ball_button->setTexture(GRID_SELECTOR::BALL_SELECTED);
        shooter_button->setTexture(GRID_SELECTOR::SHOOTER_UNSELECTED);
        ball_grid->setVisible(true);
        shooter_grid->setVisible(false);
    } else if (is_shooter(touch_pos)) {
        mode = SHOOTER;
        ball_button->setTexture(GRID_SELECTOR::BALL_UNSELECTED);
        shooter_button->setTexture(GRID_SELECTOR::SHOOTER_SELECTED);
        ball_grid->setVisible(false);
        shooter_grid->setVisible(true);
    } else if (is_back(touch_pos)) {
        if (UserLocalStore::get_achievement_variable(NEW_SHOP_ELEMENT) == 1)
            UserLocalStore::store_achievement_variable(NEW_SHOP_ELEMENT, 0);
        UserLocalStore::store_achievement_variable(FROM_SHOP, 1);
        auto main = GameScene::createScene();
        Director::getInstance()->replaceScene(main);
    }
    return true;
}