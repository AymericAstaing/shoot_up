#include    <math.h>
#include    <vector>
#include    <iomanip>
#include    "cocos2d.h"
#include    "GameScene.h"
#include    "Square.h"
#include    "Line.h"
#include    "Utils.h"
#include    "ShopScene.h"
#include    "Popup.h"
#include    "GridView.h"
#include    "CustomTableViewCell.h"
#include    "UserLocalStore.h"
#include    "ShootUp.h"
#include    "Circle.h"

using namespace std;

namespace POPUP_MENU_PATH {
    const char *POWER = "pop_up/power.png";
    const char *POWER_SELECTED = "pop_up/power_selected.png";
    const char *SPEED = "pop_up/speed.png";
    const char *SPEED_SELECTED = "pop_up/speed_selected.png";
}

namespace END_MENU_PATH {
    const char *SKIP = "continue_menu/continue_btn.png";
}

USING_NS_CC;

Scene *GameScene::createScene() {
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init() {
    if (!Scene::init())
        return false;
    init_main_variable();
    return true;
}

void GameScene::init_main_variable() {
    auto winSize = Director::getInstance()->getVisibleSize();
    check_first_launch();
    game_state = MENU;
    x_screen = winSize.width;
    y_screen = winSize.height;
    options_state = OPTIONS_HIDE;
    bullet_state = 0;
    init_ui_components();
    init_listeners();
    init_pool_objects();
    game_menu = get_main_menu();
    addChild(game_menu);
    if (UserLocalStore::get_achievement_variable(FROM_SHOP) == NOT_FROM_SHOP)
        main_menu_coming_animation();
    else
        UserLocalStore::store_achievement_variable(FROM_SHOP, NOT_FROM_SHOP);
    init_options_menu();
    init_bonus_components();
}

void GameScene::init_ui_components() {
    player = Utils::get_player();
    this->addChild(player);
    score = Label::createWithTTF("test", FIRE_UP_FONT_NUMBERS, 100);
    score->setPosition(Vec2(x_screen / 2, static_cast<float>(y_screen - 0.15 * y_screen)));
    score->setVisible(false);
    addChild(score, 10);
    best_img = Sprite::create(BEST_SCORE_IMG);
    best_img->setPosition(Vec2(x_screen + best_img->getContentSize().height,
                               static_cast<float>(score->getPositionY() -
                                                  (score->getContentSize().height / 2 +
                                                   best_img->getContentSize().height / 3))));
    best_img->setVisible(false);
    addChild(best_img, 20);
}

void GameScene::init_listeners() {
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, player);
}

void GameScene::init_pool_objects() {
    int index_struct = COMPLEX_STRUCT_ELMTS;
    pool_container = new Line *[27];
    pool_circle = new Circle *[15];
    bullet_container = new Bullet *[101];
    active_lines = new int[5];

    pool_container[0] = Line::create(STARTUP_LINE_2);
    pool_container[1] = Line::create(STARTUP_LINE_3);
    pool_container[2] = Line::create(STARTUP_LINE_4);
    pool_container[3] = Line::create(STARTUP_LINE_5);

    for (int i = 0; i < 15; i++) {
        pool_circle[i] = Circle::create();
        addChild(pool_circle[i]);
    }
    pool_circle[15] = NULL;
    for (int i = 0; i < 4; i++)
        active_lines[i] = EMPTY_VALUE;
    active_lines[4] = '\0';
    for (int j = 0; j < 100; j++) {
        bullet_container[j] = Bullet::create();
        addChild(bullet_container[j], 4);
    }
    bullet_container[100] = NULL;
    for (int i = 4; i < 7; i++)
        pool_container[i] = Line::create(SIMPLE_LINE_4);
    for (int i = 7; i < 10; i++)
        pool_container[i] = Line::create(SIMPLE_LINE_5);
    for (int i = 10; i < 26; i += 2, index_struct++) {
        pool_container[i] = Line::create(index_struct);
        pool_container[i + 1] = Line::create(index_struct);
    }
    pool_container[26] = NULL;
    for (int i = 0; pool_container[i] != NULL; i++)
        addChild(pool_container[i]);
}

void GameScene::init_bonus_components() {
    bonus_container = new Sprite *[3];
    rect_container = new Sprite *[3];
    shield_rect = Sprite::create(SHIELD_RECT_TEXTURE);
    shield_rect->setScale(static_cast<float>(player->getContentSize().height * 0.95 /
                                             shield_rect->getContentSize().height));
    bonus_container[BONUS_BULLET] = Sprite::createWithSpriteFrameName(DEFAULT_BULLET_TEXTURE);
    bonus_container[BONUS_POWER] = Sprite::createWithSpriteFrameName(DEFAULT_POWER_TEXTURE);
    bonus_container[BONUS_SPEED] = Sprite::createWithSpriteFrameName(DEFAULT_SPEED_TEXTURE);
    rect_container[RECT_BULLET] = Sprite::create(BULLET_RECT);
    rect_container[RECT_POWER] = Sprite::create(POWER_RECT);
    rect_container[RECT_SPEED] = Sprite::create(SPEED_RECT);
    addChild(shield_rect);
    shield_rect->setVisible(false);
    for (int i = 0; i < 3; i++) {
        bonus_container[i]->setVisible(false);
        rect_container[i]->setVisible(false);
        rect_container[i]->setScale(1.1);
        addChild(bonus_container[i]);
        addChild(rect_container[i], 15);
    }
}

void GameScene::init_options_menu() {
    if (UserLocalStore::get_achievement_variable(SOUND) == SOUND_OFF)
        sound = Sprite::create(OPTIONS_SOUND_ON);
    else
        sound = Sprite::create(OPTIONS_SOUND_OFF);
    tuto = Sprite::create(OPTIONS_TUTO);
    sound->setScale(0.9);
    tuto->setScale(0.9);
    sound->setPosition(
            Vec2(static_cast<float>(options_btn->getPosition().x +
                                    options_btn->getContentSize().height),
                 options_btn->getPosition().y));
    tuto->setPosition(Vec2(sound->getPosition().x + sound->getContentSize().height,
                           options_btn->getPosition().y));
    sound->setVisible(false);
    tuto->setVisible(false);
    this->addChild(tuto);
    this->addChild(sound);
}

void GameScene::value_to_update() {
    if (game_score > UserLocalStore::get_achievement_variable(SCORE))
        UserLocalStore::store_achievement_variable(SCORE, game_score);
    UserLocalStore::store_achievement_variable(POINT,
                                               UserLocalStore::get_achievement_variable(POINT) +
                                               game_score);
}

void GameScene::end_of_game() {
    if (game_state != GAME_RUNNING)
        return;
    if (game_shooter_type == SHIELD_TANK && !shield_live_used) {
        shield_live_used = true;
        shield_rect->runAction(Utils::get_shield_blink_animation());
        return;
    }
    if (game_shooter_type == SHIELD_TANK) {
        shield_live_used = false;
        shield_rect->setOpacity(100);
        shield_rect->setVisible(false);
    }
    player->setScale(1);
    remove_bonus();
    value_to_update();
    game_state = GAME_END;
    score->setVisible(false);
    player->setVisible(false);
    if (best_img->isVisible()) {
        best_img->setVisible(false);
        best_img->setPositionX(x_screen + best_img->getContentSize().height);
    }
    stop_bullet_shoot();
    end_menu = get_end_game_menu();
    addChild(end_menu);
}

void GameScene::reset_arrays() {
    for (int j = 0; active_lines[j] != NULL; j++)
        active_lines[j] = EMPTY_VALUE;
    for (int i = 0; bullet_container[i] != NULL; i++)
        if (bullet_container[i]->bullet_active)
            bullet_container[i]->reset();
    for (int i = 0; pool_container[i] != NULL; i++) {
        if (pool_container[i]->line_active) {
            pool_container[i]->stopAllActions();
            pool_container[i]->reset();
        }
    }
}

void GameScene::start_bullet_shoot() {
    float interval = get_shoot_interval();
    if (game_shooter_type == SPEED_TANK) {
        interval -= (interval / 1.5);
    }
    if (bonus_active == BONUS_SPEED)
        interval /= 2;
    this->schedule(schedule_selector(GameScene::launch_bullet), interval);
}

void GameScene::stop_bullet_shoot() {
    unschedule(schedule_selector(GameScene::launch_bullet));
}

void GameScene::surclassement(cocos2d::Ref *pSender) {
    UICustom::Popup *popup = UICustom::Popup::create("Test 3", "", [=]() {});
    popup->setScale(0);
    auto scaleTo = ScaleTo::create(0.1f, 1.0f);
    addChild(popup);
    popup->runAction(scaleTo);
}

void GameScene::options(cocos2d::Ref *pSender) {
    if (options_state == OPTIONS_HIDE) {
        DelayTime *delayTime = DelayTime::create(0.08);
        tuto->setOpacity(0);
        sound->setOpacity(0);
        auto actionMove = MoveTo::create(0.1,
                                         Vec2(tuto->getPosition().x +
                                              (tuto->getContentSize().width / 6),
                                              tuto->getPosition().y));
        auto actionMove2 = MoveTo::create(0.1, Vec2(sound->getPosition().x +
                                                    (sound->getContentSize().width / 6),
                                                    sound->getPosition().y));
        auto actionRotate = RotateTo::create(0.1, 90);
        options_btn->runAction(Sequence::create(actionRotate, nullptr));
        options_state = OPTIONS_DISPLAYED;
        tuto->setVisible(true);
        sound->setVisible(true);
        auto action = FadeIn::create(0.1);
        auto action2 = FadeIn::create(0.1);
        auto sequence_action = Sequence::create(delayTime, action, NULL);
        tuto->runAction(sequence_action);
        sound->runAction(action2);
        tuto->runAction(actionMove);
        sound->runAction(actionMove2);
    } else {
        DelayTime *delayTime = DelayTime::create(0.1);
        auto actionMove = MoveTo::create(0.1,
                                         Vec2(tuto->getPosition().x -
                                              (tuto->getContentSize().width / 6),
                                              tuto->getPosition().y));
        auto actionMove2 = MoveTo::create(0.1, Vec2(sound->getPosition().x -
                                                    (sound->getContentSize().width / 6),
                                                    sound->getPosition().y));
        auto action = FadeOut::create(0.1);
        auto action2 = FadeOut::create(0.1);
        auto sequence_action = Sequence::create(delayTime, action, NULL);
        tuto->runAction(action2);
        sound->runAction(sequence_action);
        tuto->runAction(actionMove);
        sound->runAction(actionMove2);
        auto actionRotate = RotateTo::create(0.1, 0);
        options_btn->runAction(Sequence::create(actionRotate, nullptr));
        options_state = OPTIONS_HIDE;
    }
}

void GameScene::run_start_animation() {
    auto callback = CallFuncN::create(
            [&](Node *sender) {
                game_menu->cleanup();
                this->removeChild(game_menu);
            });
    auto fadeout = FadeTo::create(0.5, 0);
    auto actionMove1 = MoveBy::create(0.2, Vec2(static_cast<float>(-x_screen * 0.03), 0));
    auto actionMove2 = MoveBy::create(0.2, Vec2(static_cast<float>(x_screen * 0.5), 0));
    auto seq = Sequence::create(actionMove1, actionMove2, nullptr);
    auto actionMove5 = MoveBy::create(0.2, Vec2(static_cast<float>(x_screen * 0.03), 0));
    auto actionMove6 = MoveBy::create(0.2, Vec2(static_cast<float>(-x_screen * 0.5), 0));
    auto actionMove7 = MoveBy::create(0.2, Vec2(0, static_cast<float>(-y_screen * 0.05)));
    auto actionMove8 = MoveBy::create(0.2, Vec2(0, static_cast<float>(y_screen * 0.5)));
    auto seq3 = Sequence::create(actionMove5, actionMove6, nullptr);
    auto seq4 = Sequence::create(actionMove7, actionMove8, nullptr);
    auto seq_callback = Sequence::create(fadeout->clone(), callback, nullptr);
    menu_surclassement_txt->runAction(seq);
    menu_surclassement_img->runAction(seq->clone());
    menu_shop_img->runAction(seq3);
    menu_title->runAction(seq4);
    options_btn->runAction(seq4->clone());
    menu_best_img->runAction(fadeout);
    menu_best_txt->runAction(fadeout->clone());
    menu_anim_img->runAction(fadeout->clone());
    menu_anim_img_hand->runAction(fadeout->clone());
    menu_power_level->runAction(fadeout->clone());
    menu_speed_level->runAction(fadeout->clone());
    menu_stats_img->runAction(seq_callback);
}

int GameScene::get_line_index(int type) {
    int *range = Utils::get_container_range_research(type);
    for (int i = range[0]; i <= range[1]; i++) {
        if (pool_container[i]->get_type() == type && !pool_container[i]->line_active)
            return (i);
    }
    return -1;
}

void GameScene::check_bullet_contact() {
    for (int j = 0; active_lines[j] != '\0'; j++) {
        for (int i = 0; bullet_container[i] != NULL; i++) {
            if (bullet_container[i]->bullet_active) {
                int id = active_lines[j];
                if (id != -1) {
                    float line_position_y = pool_container[id]->getPositionY();
                    float bullet_position_y = bullet_container[i]->getPositionY();
                    if (bullet_position_y >= line_position_y &&
                        bullet_position_y <=
                        line_position_y +
                        pool_container[id]->getContentSize().height) {
                        //IN CONTACT
                        if (!bullet_container[i]->contact) {
                            // ENTER CONTACT ZONE
                            bullet_container[i]->contact = true;
                            bullet_container[i]->contact_index = id;
                        }
                    } else {
                        if (bullet_container[i]->contact &&
                            id == bullet_container[i]->contact_index) {
                            // EXIT CONTACT ZONE
                            bullet_container[i]->contact = false;
                            bullet_container[i]->contact_index = false;
                        }
                    }
                }
            }
        }
    }
}

bool GameScene::point_into_square(Square *sq, Vec2 bullet_pos) {
    Vec2 sq_top_left;
    float sq_width = sq->getContentSize().width;
    float sq_height = sq->getContentSize().height;
    sq_top_left.x = sq->getPositionX() - sq_width / 2;
    sq_top_left.y = sq->getPositionY() + sq_height / 2;

    return bullet_pos.x >= sq_top_left.x &&
           bullet_pos.x <= sq_top_left.x + sq_width &&
           bullet_pos.y <= sq_top_left.y &&
           bullet_pos.y >= sq_top_left.y - sq_height;
}

void GameScene::show_destruction_circle(Vec2 pos) {
    int i = 0;
    for (; pool_circle[i]->active_circle; i++);
    if (!pool_circle[i]->active_circle)
        pool_circle[i]->anim_circle(pos);
}

void GameScene::show_particle(Vec2 pos) {
    auto fileUtil = FileUtils::getInstance();
    auto plistData = fileUtil->getValueMapFromFile(PARTICLE_ANIM);
    auto stars = ParticleSystemQuad::create(plistData);
    stars->setScale(1);
    stars->setDuration(0.2);
    stars->setPosition(pos);
    stars->setTotalParticles(2);
    stars->setAutoRemoveOnFinish(true);
    addChild(stars, 1, 1);
}

void GameScene::show_particle_explode(Vec2 square_pos, int default_color_code) {
    auto fileUtil = FileUtils::getInstance();
    if (!fileUtil || !explode_plist[default_color_code])
        return;
    auto plistData = fileUtil->getValueMapFromFile(explode_plist[default_color_code]);
    ParticleSystemQuad *stars = ParticleSystemQuad::create(plistData);
    if (!stars)
        return;
    stars->setScale(1);
    stars->setDuration(0.3);
    stars->setPosition(square_pos);
    stars->setTotalParticles(30);
    stars->setAutoRemoveOnFinish(true);
    addChild(stars, 2, 1);
}

void GameScene::show_bonus_particle_explode(Vec2 bonus_pos) {
    auto fileUtil = FileUtils::getInstance();
    auto plistData = fileUtil->getValueMapFromFile(explode_bonus_plist[bonus_active]);
    ParticleSystemQuad *stars = ParticleSystemQuad::create(plistData);
    stars->setScale(1);
    stars->setDuration(0.4);
    stars->setPosition(bonus_pos);
    stars->setTotalParticles(10);
    stars->setAutoRemoveOnFinish(true);
    addChild(stars, 3, 1);
}

void GameScene::check_hit_color_change(Line *l, Square *sq) {
    int default_color_code = sq->initial_color;
    int default_pv_value = sq->initial_pv;
    int pv = sq->square_pv;
    int step = 0;

    auto batch = l->getChildByTag(LINE_BATCH_ID);
    Sprite *e = ((Sprite *) batch->getChildByTag(sq->getTag()));

    if (pv < default_pv_value && pv >= default_pv_value * (0.8))
        step = 0;
    else if (pv >= default_pv_value * 0.6)
        step = 1;
    else if (pv >= default_pv_value * 0.4)
        step = 2;
    else if (pv >= default_pv_value * 0.2)
        step = 3;
    else
        step = 4;
    SpriteFrame *tmp = (SpriteFrame *) COLOR_HIT[default_color_code][step];
    if (e->getSpriteFrame() != tmp)
        e->setSpriteFrame(COLOR_HIT[default_color_code][step]);
}

void GameScene::destroy_complete_line(int line_id, float line_y) {
    int i = 0;
    auto batch = pool_container[line_id]->getChildByTag(LINE_BATCH_ID);
    while (1) {
        auto child = pool_container[line_id]->getChildByTag(i);
        if (!child)
            break;
        Square *sq = ((Square *) child);
        auto sprite = batch->getChildByTag(sq->getTag());
        show_destruction_circle(Vec2(sq->getPositionX(), line_y));
        sq->setVisible(false);
        sprite->setVisible(false);
        i++;
    }
    star_bonus_active = false;
    star_line_id = -1;
}

void GameScene::check_into_line() {
    for (int i = 0; bullet_container[i] != NULL; i++) {
        if (bullet_container[i] && bullet_container[i]->bullet_active &&
            bullet_container[i]->contact) {
            int index = 0;
            Line *current_line = pool_container[bullet_container[i]->contact_index];
            auto batch = current_line->getChildByTag(LINE_BATCH_ID);
            while (1) {
                Square *sq = ((Square *) current_line->getChildByTag(index));
                if (!sq)
                    break;
                Vec2 bullet_pos;
                bullet_pos.x = bullet_container[i]->getPositionX();
                bullet_pos.y = bullet_container[i]->getPositionY() -
                               (current_line->getPositionY());
                if (bullet_pos.y < 0)
                    bullet_pos.y = 0;
                if (sq->isVisible() && point_into_square(sq, bullet_pos)) {
                    int bullet_hit = UserLocalStore::get_achievement_variable(POWER_VALUE);
                    if (game_shooter_type == POWER_TANK)
                        bullet_hit *= 1.5;
                    if (bonus_active == BONUS_POWER)
                        bullet_hit *= 2;
                    if (sq->get_square_pv() - bullet_hit <= 1) {
                        auto sprite = batch->getChildByTag(sq->getTag());
                        sprite->setVisible(false);
                        sq->setVisible(false);
                        Vec2 square_pos;
                        square_pos.x = sq->getPositionX();
                        square_pos.y = current_line->getPositionY() + sq->getPositionY();
                        if (sq->star_bonus == 1) {
                            destroy_complete_line(bullet_container[i]->contact_index,
                                                  static_cast<int>(current_line->getPositionY() +
                                                                   current_line->getContentSize().height /
                                                                   2));
                            game_block_destroyed++;
                            bullet_container[i]->reset();
                            return;
                        }
                        show_destruction_circle(square_pos);
                        /*show_particle_explode(
                                Vec2(square_pos.x, square_pos.y - sq->getContentSize().height),
                                sq->initial_color);*/
                        game_block_destroyed++;
                        update_game_score(sq->square_pv);
                    } else {
                        update_game_score(bullet_hit);
                        show_particle(bullet_container[i]->getPosition());
                        sq->square_pv -= bullet_hit;
                        char pv[DEFAULT_CHAR_LENGHT];
                        if (sq->square_pv > 1000)
                            sprintf(pv, "%.1f", static_cast<float>(sq->square_pv / 1000));
                        else
                            sprintf(pv, "%i", sq->square_pv);
                        if (current_line->get_type() > LINE_TYPE_STARTUP_5)
                            check_hit_color_change(current_line, sq);
                        sq->points->setString(pv);
                    }
                    bullet_container[i]->reset();
                    break;
                }
                index++;
            }
        }
    }
}

void GameScene::check_lines_out() {
    for (int i = 0; active_lines[i] != '\0'; i++) {
        if (active_lines[i] != EMPTY_VALUE && pool_container[active_lines[i]]->getPositionY() +
                                              pool_container[active_lines[i]]->getContentSize().height <=
                                              0) {
            if (pool_container[active_lines[i]]->getScale() == 0.85f) {
                pool_container[active_lines[i]]->setScale(1);
                pool_container[active_lines[i]]->setAnchorPoint(Vec2(0, 0));
            }
            if (active_lines[i] == star_line_id) {
                star_line_id = -1;
                star_bonus_active = false;
            }
            pool_container[active_lines[i]]->reset();
            remove_active_line(i);
        }
    }
}

void GameScene::move_active_lines() {
    for (int i = 0; active_lines[i] != '\0'; i++) {
        if (active_lines[i] != EMPTY_VALUE)
            pool_container[active_lines[i]]->setPositionY(
                    pool_container[active_lines[i]]->getPositionY() - LINE_SPEED);
    }
}

void GameScene::check_player_collision() {
    for (int i = 0; active_lines[i] != NULL; i++) {
        if (active_lines[i] != -1 && pool_container[active_lines[i]]->getPositionY() <
                                     player->getPositionY() +
                                     (1.1 * player->getContentSize().height / 2)) {
            Vec2 player_pos = player->getPosition();
            int index = 0;
            float player_y =
                    player_pos.y - pool_container[active_lines[i]]->getPositionY();
            while (1) {
                auto child = pool_container[active_lines[i]]->getChildByTag(index);
                Square *sq = ((Square *) child);
                if (!child)
                    break;
                float sq_width = sq->getContentSize().width;
                float sq_height = sq->getContentSize().height;
                float player_width = player->getContentSize().width;
                float player_height = player->getContentSize().height;

                Rect player_left_side = Rect(
                        player_pos.x - player_width / 2,
                        player_y,
                        static_cast<float>(player_width * 0.05),
                        static_cast<float>(player_height * 0.95));
                Rect player_right_side = Rect(
                        player_pos.x + player_width / 2,
                        player_y,
                        static_cast<float>(player_width * 0.05),
                        static_cast<float>(player_height * 0.95));
                Rect player_top_side = Rect(
                        player_pos.x - player_width / 2,
                        static_cast<float>(player_y + sq_height / 2 +
                                           (0.08 * sq_height)),
                        player_width,
                        static_cast<float>(player_height * 0.10));
                Rect sq_bounding_box = Rect(sq->getPositionX() - sq_width / 2,
                                            sq->getPositionY() + sq_height / 2, sq_width,
                                            sq_height);
                Rect sq_bottom_side = Rect(sq->getPositionX() - sq_width / 2,
                                           sq->getPositionY() - sq_height / 2,
                                           sq_width,
                                           static_cast<float>(sq_height *
                                                              0.15));
                if (sq->isVisible() && sq_bottom_side.intersectsRect(
                        player_top_side)) {
                    end_of_game();
                } else if (sq->isVisible() &&
                           sq_bounding_box.intersectsRect(player_left_side)) {
                    player->setPositionX(sq->getPositionX() + sq_width / 2 +
                                         player_width / 2);
                    if (player_pos.x + player_width / 2 > x_screen)
                        end_of_game();
                } else if (sq->isVisible() &&
                           sq_bounding_box.intersectsRect(player_right_side)) {
                    player->setPositionX(sq->getPositionX() - sq_width / 2 -
                                         player_width / 2);
                    if (player_pos.y - player_width / 2 < 0)
                        end_of_game();
                }
                index++;
            }
        }
    }
}

void GameScene::move_circles() {
    for (int i = 0; pool_circle[i]; i++) {
        if (pool_circle[i]->active_circle)
            pool_circle[i]->setPositionY(pool_circle[i]->getPositionY() - LINE_SPEED);
    }
}

void GameScene::load_bonus() {
    int type = Utils::get_random_number(0, 2);
    Vec2 initial_pos = Vec2(
            Utils::get_random_number(
                    static_cast<int>(bonus_container[BONUS_BULLET]->getContentSize().width / 2),
                    static_cast<int>(x_screen -
                                     bonus_container[BONUS_BULLET]->getContentSize().width /
                                     2)),
            y_screen + bonus_container[BONUS_BULLET]->getContentSize().height / 2);
    bonus_container[type]->setTag(BONUS_HIDE);
    bonus_container[type]->setPosition(initial_pos);
    bonus_id = type;
    bonus_selected = true;
}

void GameScene::active_bonus() {
    bonus_container[bonus_id]->setTag(BONUS_IN_GAME);
    bonus_container[bonus_id]->setVisible(true);
    bonus_container[bonus_id]->runAction(Utils::get_bonus_animation(bonus_id));
    bonus_displayed = true;
    next_bonus_spawn = LINE_GENERATED + 5 + Utils::get_random_number(0, 5);
}

void GameScene::remove_bonus() {
    float initial_y_pos = y_screen + bonus_container[BONUS_BULLET]->getContentSize().height / 2;
    if (bonus_id >= 0 && bonus_id <= 2) {
        bonus_container[bonus_id]->setTag(BONUS_HIDE);
        bonus_container[bonus_id]->stopAllActions();
        bonus_container[bonus_id]->setVisible(false);
        bonus_container[bonus_id]->setPositionY(initial_y_pos);
        rect_container[bonus_id]->setVisible(false);
        rect_container[bonus_id]->stopAllActions();
    }
    bonus_id = -1;
    bonus_active = -1;
    bonus_time = 0;
    bonus_selected = false;
    bonus_displayed = false;
    rect_animated = false;
}

void GameScene::move_bonus() {
    Vec2 player_pos = player->getPosition();
    if (bonus_active != -1) {
        rect_container[bonus_id]->setPosition(player->getPosition());
    } else {
        bonus_container[bonus_id]->setPositionY(
                bonus_container[bonus_id]->getPositionY() - LINE_SPEED);
        if (bonus_container[bonus_id]->getPositionY() +
            bonus_container[bonus_id]->getContentSize().height / 2 <= 0)
            remove_bonus();
    }
}

void GameScene::bonus_collision() {
    float player_width = player->getContentSize().width;
    float player_height = player->getContentSize().height;
    Rect player_bounding_box = Rect(player->getPositionX() - player_width / 2,
                                    player->getPositionY() + player_height / 2, player_width,
                                    player_height);
    float bonus_width = bonus_container[bonus_id]->getContentSize().width;
    float bonus_height = bonus_container[bonus_id]->getContentSize().height;

    Rect bonus_bounding_box = Rect(
            bonus_container[bonus_id]->getPositionX() - bonus_width / 2,
            bonus_container[bonus_id]->getPositionY() + bonus_height / 2, bonus_width,
            bonus_height);
    if (player_bounding_box.intersectsRect(bonus_bounding_box)) {
        float initial_y_pos = y_screen + bonus_container[BONUS_BULLET]->getContentSize().height / 2;
        if (bonus_id == BONUS_SPEED) {
            stop_bullet_shoot();
            bonus_active = bonus_id;
            start_bullet_shoot();
        } else if (bonus_id == BONUS_POWER) {
            bonus_active = bonus_id;
            game_power_up_collected++;
        } else {
            bonus_active = bonus_id;
        }
        bonus_container[bonus_id]->setTexture(default_bonus_texture[bonus_id]);
        rect_container[bonus_id]->setVisible(true);
        rect_container[bonus_id]->setScale(player->getScale());
        rect_container[bonus_id]->setPosition(player->getPosition());
        bonus_container[bonus_id]->setVisible(false);
        show_destruction_circle(bonus_container[bonus_id]->getPosition());
        show_bonus_particle_explode(Vec2(bonus_container[bonus_id]->getPosition().x,
                                         bonus_container[bonus_id]->getPosition().y -
                                         bonus_container[bonus_id]->getContentSize().width));
        bonus_container[bonus_id]->setPositionY(initial_y_pos);
    }
}

void GameScene::bonus_managment() {
    if (LINE_GENERATED == next_bonus_spawn && !bonus_selected)
        load_bonus();
    if (bonus_id != -1 && !bonus_displayed &&
        (pool_container[CURRENT_LINE_ID]->getPosition().y +
         pool_container[CURRENT_LINE_ID]->getContentSize().height) <=
        (NEW_SPAWN_Y + ((y_screen - NEW_SPAWN_Y) / 2)))
        active_bonus();
    if (bonus_displayed) {
        bonus_collision();
        move_bonus();
        if (bonus_active != -1) {
            if (bonus_time >= BONUS_TIME_MIDLE && !rect_animated) {
                rect_animated = true;
                rect_container[bonus_id]->runAction(Utils::get_blink_animation());
            } else if (bonus_time >= BONUS_TIME_LIMIT) {
                rect_container[bonus_id]->setOpacity(100);
                if (bonus_active == BONUS_SPEED) {
                    stop_bullet_shoot();
                    remove_bonus();
                    start_bullet_shoot();
                    return;
                }
                remove_bonus();
            }
        }
    }
}

void GameScene::scale_animation() {
    auto scaleto = ScaleTo::create(1.3, 0.85f);
    player->runAction(scaleto);
    pool_container[CURRENT_LINE_ID]->setAnchorPoint(Vec2(0.5, 0.5));
    pool_container[CURRENT_LINE_ID]->setPositionX(x_screen / 2);
    pool_container[CURRENT_LINE_ID]->runAction(scaleto->clone());
}

void GameScene::update(float ft) {
    if (bonus_active != -1)
        bonus_time += ft;
    if (game_shooter_type == SHIELD_TANK && shield_rect->isVisible())
        shield_rect->setPosition(player->getPosition());
    check_lines_out();
    move_active_lines();
    if (LINE_GENERATED == TRANSITION_FROM_4_TO_5 && shooter_never_updated == 0 &&
        player->getScale() != 0.85)
        scale_animation();
    if (game_state == GAME_RUNNING) {
        move_circles();
        bonus_managment();
        check_bullet_contact();
        check_into_line();
        check_player_collision();
    }
    if (pool_container[CURRENT_LINE_ID]->getPosition().y <= NEW_SPAWN_Y) {
        if (pool_container[NEXT_LINE_ID]->get_type() == LINE_TYPE_SIMPLE_OF_5 &&
            Utils::get_random_number(0, 5) == 5 && !star_bonus_active) {
            pool_container[NEXT_LINE_ID]->attach_star_bonus();
            star_bonus_active = true;
            star_line_id = NEXT_LINE_ID;
        }
        pool_container[NEXT_LINE_ID]->set_active(current_factor_h, LINE_GENERATED);
        store_active_line(NEXT_LINE_ID);
        CURRENT_LINE_ID = NEXT_LINE_ID;
        NEXT_LINE_ID = get_line_index(get_next_line_type());
        LINE_GENERATED++;
        if (NEXT_LINE_ID != -1)
            NEW_SPAWN_Y = Utils::get_spawn_y(pool_container[CURRENT_LINE_ID]->get_type(),
                                             pool_container[NEXT_LINE_ID]->get_type(),
                                             pool_container[NEXT_LINE_ID]->line_size);
    }
    if (NEXT_LINE_ID == -1) {
        NEXT_LINE_ID = get_line_index(get_next_line_type());
        if (NEXT_LINE_ID != -1)
            NEW_SPAWN_Y = Utils::get_spawn_y(pool_container[CURRENT_LINE_ID]->get_type(),
                                             pool_container[NEXT_LINE_ID]->get_type(),
                                             pool_container[NEXT_LINE_ID]->line_size);
    }
}

void GameScene::store_active_line(int line_index) {
    for (int i = 0; active_lines[i] != '\0'; i++) {
        if (active_lines[i] == EMPTY_VALUE) {
            active_lines[i] = line_index;
            return;
        }
    }
}

void GameScene::remove_active_line(int line_to_rm) {
    active_lines[line_to_rm] = EMPTY_VALUE;
}

int GameScene::get_next_line_type() {
    if (shooter_never_updated)
        return (LINE_TYPE_SIMPLE_OF_4);
    if (LINE_GENERATED < SIMPLE_LINE_NBR)
        return (LINE_TYPE_SIMPLE_OF_4);
    else if (LINE_GENERATED == SIMPLE_LINE_NBR)
        return (LINE_TYPE_SIMPLE_OF_5);
    else
        return (Utils::get_random_line_type());
}

void GameScene::run_game_loop() {
    int indicator = UserLocalStore::get_achievement_variable(POWER_LEVEL) +
                    UserLocalStore::get_achievement_variable(SPEED_LEVEL);
    if (indicator == NO_SHOOTER_UPGRADE)
        shooter_never_updated = 1;
    else
        shooter_never_updated = 0;
    if (shooter_never_updated == 1) {
        CURRENT_LINE_ID = 4;
        NEXT_LINE_ID = 5;
        NEW_SPAWN_Y = Utils::get_spawn_y(pool_container[CURRENT_LINE_ID]->get_type(),
                                         pool_container[NEXT_LINE_ID]->get_type(),
                                         pool_container[NEXT_LINE_ID]->line_size);
    } else {
        if (current_factor_h < STARTUP_OF_3) {
            CURRENT_LINE_ID = 1;
            NEXT_LINE_ID = 4;
        } else if (current_factor_h < STARTUP_OF_4) {
            CURRENT_LINE_ID = 2;
            NEXT_LINE_ID = 4;
        } else {
            CURRENT_LINE_ID = 3;
            NEXT_LINE_ID = 4;
        }
        NEW_SPAWN_Y = Utils::get_spawn_y(pool_container[CURRENT_LINE_ID]->get_type(),
                                         pool_container[NEXT_LINE_ID]->get_type(),
                                         pool_container[CURRENT_LINE_ID]->line_size);
    }
    bonus_selected = false;
    next_bonus_spawn = MIN_LINE_BEFORE_BONUS_SPAWN + Utils::get_random_number(0, 5);
    store_active_line(CURRENT_LINE_ID);
    pool_container[CURRENT_LINE_ID]->set_active(
            current_factor_h, LINE_GENERATED);
    LINE_GENERATED++;
    this->scheduleUpdate();
}

void GameScene::stop_game_loop() {
    this->unscheduleUpdate();
}

void GameScene::score_animation() {
    auto scale_up = ScaleTo::create(0.05, 1.2f);
    auto scale_down = ScaleTo::create(0.05, 1.0f);
    auto sequence = Sequence::create(scale_up, scale_down, nullptr);
    score->runAction(sequence);
    if (best_img->isVisible())
        best_img->runAction(sequence->clone());
}

void GameScene::update_game_score(int points) {
    int best = UserLocalStore::get_achievement_variable(SCORE);
    score_animation();
    game_score += points;
    if (!best_img->isVisible() && game_score > best) {
        best_img->setVisible(true);
        auto move = MoveTo::create(0.2, Vec2(x_screen / 2, best_img->getPositionY()));
        best_img->runAction(move);
    }
    char score_value[DEFAULT_CHAR_LENGHT];
    if (game_score < 1000)
        sprintf(score_value, "%i", game_score);
    else
        sprintf(score_value, "%.1fK", static_cast<float>(game_score) / 1000);
    score->setString(score_value);
}

float GameScene::get_shoot_interval() {
    float factor = 5 * UserLocalStore::get_achievement_variable_float(SPEED_VALUE);
    return static_cast<float>(1.0 / factor);
}

int GameScene::get_h_value() {
    return static_cast<int>(
            (DEFAULT_BULLET_NBR * UserLocalStore::get_achievement_variable_float(SPEED_VALUE)) *
            UserLocalStore::get_achievement_variable(POWER_VALUE));
}

void GameScene::start_game() {
    game_shooter_type = Utils::get_shooter_type(UserLocalStore::get_current_shooter());
    if (game_shooter_type == SHIELD_TANK) {
        shield_rect->setVisible(true);
        shield_rect->setPosition(player->getPosition());
    }
    if (options_state == OPTIONS_DISPLAYED)
        options(nullptr);
    game_score = 0;
    bonus_active = -1;
    current_factor_h = get_h_value();
    char score_value[DEFAULT_CHAR_LENGHT];
    sprintf(score_value, "%i", game_score);
    game_state = GAME_RUNNING;
    score->setVisible(true);
    score->setString(score_value);
    run_start_animation();
    start_bullet_shoot();
    run_game_loop();
}

void GameScene::shop(cocos2d::Ref *pSender) {
    auto shop = ShopScene::create();
    Director::getInstance()->replaceScene(shop);
}

void GameScene::play(cocos2d::Ref *pSender) {
    // auto scene = HelloWorld::createScene();
    // Director::getInstance()->pushScene(scene);
}

void GameScene::back_to_menu(cocos2d::Ref *pSender) {
    auto callback = CallFuncN::create(
            [&](Node *sender) {
                UserLocalStore::update_achievements(
                        Utils::get_shooter_type(UserLocalStore::get_current_shooter()),
                        game_block_destroyed, game_power_up_collected);
                game_block_destroyed = 0;
                game_power_up_collected = 0;
                LINE_GENERATED = 0;
                if (!player->isVisible())
                    player->setVisible(true);
                player->setPositionX(x_screen / 2);
                stop_game_loop();
                reset_arrays();
                game_state = MENU;
                removeChild(end_menu);
                game_menu = get_main_menu();
                addChild(game_menu);
                main_menu_coming_animation();
            });
    auto delay = DelayTime::create(0.2);
    auto delay2 = DelayTime::create(0.2);
    auto move_to_share_0 = MoveTo::create(0.1,
                                          Vec2(share->getPositionX(), share->getPositionY() +
                                                                      share->getContentSize().height));
    auto move_to_rate_0 = MoveTo::create(0.1, Vec2(rate->getPositionX(), rate->getPositionY() +
                                                                         rate->getContentSize().height));
    auto move_to_share_1 = MoveTo::create(0.1, Vec2(share->getPositionX(),
                                                    0 - share->getContentSize().height));
    auto move_to_rate_1 = MoveTo::create(0.1, Vec2(rate->getPositionX(),
                                                   0 - rate->getContentSize().height));
    auto move_to_stats = MoveTo::create(0.1, Vec2(stats->getPositionX(),
                                                  y_screen + stats->getContentSize().height));
    auto move_to_back = MoveTo::create(0.1, Vec2(back_to_main->getPositionX(),
                                                 0 - back_to_main->getContentSize().height));

    auto sequence_share = Sequence::create(move_to_share_0, move_to_share_1, nullptr);
    auto sequence_rate = Sequence::create(move_to_rate_0, move_to_rate_1, nullptr);
    auto sequence_stats = Sequence::create(delay, move_to_stats, nullptr);
    auto sequence_back = Sequence::create(delay2, move_to_back, callback, nullptr);
    share->runAction(sequence_share);
    rate->runAction(sequence_rate);
    stats->runAction(sequence_stats);
    back_to_main->runAction(sequence_back);
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (touch->getLocation().x > 0 + player->getContentSize().width / 2 &&
        touch->getLocation().x < x_screen - player->getContentSize().height / 2) {
        if (game_state == MENU)
            return;
        float current_location = touch->getLocation().x;
        float future_x = current_location +
                         Utils::get_finger_move_factor(current_location, game_shooter_type);
        player->setPositionX(future_x);
        if (player->getPositionX() - player->getContentSize().width / 2 < 0)
            player->setPositionX(player->getContentSize().width / 2);
        if (player->getPositionX() + player->getContentSize().width / 2 > x_screen)
            player->setPositionX(x_screen - player->getContentSize().width / 2);
    }
}

void GameScene::manage_options() {
    if (UserLocalStore::get_achievement_variable(SOUND) == SOUND_ON) {
        UserLocalStore::store_achievement_variable(SOUND, SOUND_OFF);
        sound->setTexture(OPTIONS_SOUND_OFF);
    } else {
        UserLocalStore::store_achievement_variable(SOUND, SOUND_ON);
        sound->setTexture(OPTIONS_SOUND_ON);
    }
}

bool GameScene::is_touch_on_player_zone(Vec2 touch_position) {
    Vec2 player_pos = player->getPosition();
    Size player_size = player->getContentSize();
    float gap_x = player_size.width / 2 + (2 * player_size.width);
    float gap_y = player_size.height / 2 + (2 * player_size.width);

    return touch_position.x >= player_pos.x - gap_x &&
           touch_position.x <= player_pos.x + gap_x &&
           touch_position.y <= player_pos.y + gap_y && player_pos.y >= player_pos.y - gap_y;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
    if (game_state == GAME_RUNNING && !is_touch_on_player_zone(touch->getLocation()))
        return false;
    if (options_state == OPTIONS_DISPLAYED && is_sound_button_touched(touch->getLocation())) {
        manage_options();
        return true;
    }
    if (game_state == MENU)
        start_game();
    return true;
}

bool GameScene::is_sound_button_touched(Vec2 touch_location) {
    float x_pos = sound->getPosition().x - sound->getContentSize().width / 2;
    float y_pos = sound->getPosition().y - sound->getContentSize().height / 2;
    return touch_location.x >= x_pos &&
           touch_location.x <= x_pos + sound->getContentSize().width &&
           touch_location.y >= y_pos &&
           touch_location.y <= y_pos + sound->getContentSize().height;
}

void GameScene::launch_bullet(float dt) {
    if (game_shooter_type != DOUBLE_TANK && game_shooter_type != SIDEWAY_TANK &&
        game_shooter_type != TRIPLE_TANK && bonus_active != BONUS_BULLET) {
        for (int i = 0; bullet_container[i] != NULL; i++) {
            if (!bullet_container[i]->bullet_active) {
                bullet_container[i]->launch(bullet_state, player->getPosition(),
                                            player->getContentSize(), NORMAL_LAUNCH);
                if (bonus_active == BONUS_POWER)
                    bullet_container[i]->setScale(1.3f);
                if (bullet_state == BULLET_LEFT)
                    bullet_state = BULLET_RIGHT;
                else
                    bullet_state = BULLET_LEFT;
                return;
            }
        }
    } else if (bonus_active == BONUS_BULLET) {
        int bullet_founded = 0;
        for (int i = 0; bullet_container[i] != NULL; i++) {
            if (!bullet_container[i]->bullet_active) {
                bullet_container[i]->launch(bullet_state, player->getPosition(),
                                            player->getContentSize(), bullet_founded);
                bullet_founded++;
                if (bullet_founded == 3)
                    return;
            }
        }
        return;
    } else {
        int bullet_founded = 0;
        int bullet_nbr = Utils::get_bullet_nbr(game_shooter_type);
        int *bullet_ids = new int[bullet_nbr + 1];
        for (int i = 0; bullet_founded != bullet_nbr; i++) {
            if (!bullet_container[i]->bullet_active) {
                bullet_ids[bullet_founded] = i;
                bullet_founded++;
            }
        }
        bullet_ids[bullet_founded] = '\0';
        int type = Utils::get_bullet_shoot_index(game_shooter_type);
        for (int i = 0; i < bullet_nbr; i++) {
            bullet_container[bullet_ids[i]]->launch(bullet_state, player->getPosition(),
                                                    player->getContentSize(),
                                                    BULLET_SHOOT[type][i]);
            if (bonus_active == BONUS_POWER)
                bullet_container[i]->setScale(BIG_BULLET_SIZE);
        }
        return;
    }
    return;
}

void GameScene::main_menu_coming_animation() {
    menu_stats_img->setOpacity(0);
    menu_anim_img->setOpacity(0);
    menu_anim_img_hand->setOpacity(0);
    options_btn->setOpacity(0);
    menu_best_txt->setOpacity(0);
    menu_best_img->setOpacity(0);

    menu_title->setPositionY(y_screen + menu_title->getContentSize().height);
    menu_surclassement_img->setPositionX(
            x_screen + menu_surclassement_img->getContentSize().width);
    menu_surclassement_txt->setPositionX(menu_surclassement_img->getPosition().x -
                                         menu_surclassement_img->getContentSize().width / 2);


    auto move_title_0 = MoveTo::create(0.1, Vec2(menu_title->getPositionX(),
                                                 static_cast<float>(
                                                         static_cast<float>(y_screen -
                                                                            (y_screen /
                                                                             5)) -
                                                         y_screen * 0.05)));
    auto move_title_1 = MoveBy::create(0.1, Vec2(0, static_cast<float>(y_screen * 0.05)));
    auto move_surclassement_img_0 = MoveTo::create(0.1,
                                                   Vec2(static_cast<float>(x_screen * 0.95 -
                                                                           x_screen * 0.03),
                                                        menu_surclassement_img->getPositionY()));
    auto move_surclassement_img_1 = MoveBy::create(0.1, Vec2(
            static_cast<float>(x_screen * 0.03),
            0));
    auto move_surclassement_txt_0 = MoveTo::create(0.1,
                                                   Vec2(static_cast<float>(x_screen * 0.95 -
                                                                           x_screen * 0.03) -
                                                        menu_surclassement_img->getContentSize().width /
                                                        2,
                                                        menu_surclassement_txt->getPositionY()));

    auto move_shop_img_0 = MoveTo::create(0.1, Vec2(static_cast<float>(static_cast<float>(
                                                                               menu_shop_img->getContentSize().width /
                                                                               2 +
                                                                               x_screen *
                                                                               0.05) +
                                                                       x_screen * 0.03),
                                                    menu_shop_img->getPositionY()));
    auto move_shop_img_1 = MoveBy::create(0.1, Vec2(static_cast<float>(-x_screen * 0.03), 0));
    auto fadeIn = FadeIn::create(0.5);
    auto seq0 = Sequence::create(move_surclassement_img_0, move_surclassement_img_1, NULL);
    auto seq1 = Sequence::create(move_surclassement_txt_0, move_surclassement_img_1->clone(),
                                 NULL);
    auto seq2 = Sequence::create(move_shop_img_0, move_shop_img_1, NULL);
    auto seq3 = Sequence::create(move_title_0, move_title_1, NULL);
    menu_surclassement_img->runAction(seq0);
    menu_surclassement_txt->runAction(seq1);
    menu_shop_img->runAction(seq2);
    menu_title->runAction(seq3);
    menu_stats_img->runAction(fadeIn);
    menu_anim_img->runAction(fadeIn->clone());
    menu_anim_img_hand->runAction(fadeIn->clone());
    options_btn->runAction(fadeIn->clone());
    menu_best_txt->runAction(fadeIn->clone());
    menu_best_img->runAction(fadeIn->clone());
}

Menu *GameScene::get_main_menu() {
    menu_title = MenuItemFont::create(TITLE, CC_CALLBACK_1(GameScene::play, this));
    char power_level[DEFAULT_CHAR_LENGHT];
    sprintf(power_level, "%i",
            UserLocalStore::get_achievement_variable(POWER_VALUE));
    char speed_level[DEFAULT_CHAR_LENGHT];
    sprintf(speed_level, "%.1f",
            UserLocalStore::get_achievement_variable_float(SPEED_VALUE));
    char best_score[DEFAULT_CHAR_LENGHT];
    if (UserLocalStore::get_achievement_variable(SCORE) > 1000)
        sprintf(best_score, "%.1fk",
                static_cast<float>(UserLocalStore::get_achievement_variable(SCORE)) / 1000);
    else
        sprintf(best_score, "%i", UserLocalStore::get_achievement_variable(SCORE));
    menu_power_level = MenuItemFont::create(power_level);
    menu_power_level->setTag(POWER_LEVEL_BTN_TAG);
    menu_speed_level = MenuItemFont::create(speed_level);
    menu_speed_level->setTag(SPEED_LEVEL_BTN_TAG);
    menu_surclassement_txt = MenuItemFont::create(SURCLASSEMENT,
                                                  CC_CALLBACK_1(GameScene::surclassement,
                                                                this));
    menu_surclassement_img = MenuItemImage::create(SURCLASSEMENT_UNSELECTED,
                                                   SURCLASSEMENT_SELECTED,
                                                   CC_CALLBACK_1(GameScene::surclassement,
                                                                 this));
    options_btn = MenuItemImage::create(OPTIONS,
                                        OPTIONS,
                                        CC_CALLBACK_1(GameScene::options, this));
    menu_stats_img = MenuItemImage::create(STATS, STATS);
    menu_anim_img_hand = MenuItemImage::create(HAND,
                                               HAND);
    menu_anim_img = MenuItemImage::create(HAND_RAIL, HAND_RAIL);
    menu_best_img = MenuItemImage::create(BEST_IMG, BEST_IMG);
    menu_best_txt = MenuItemFont::create(best_score);
    menu_shop_img = MenuItemImage::create(SHOP_UNSELECTED,
                                          SHOP_SELECTED,
                                          CC_CALLBACK_1(GameScene::shop, this));
    menu_title->setFontNameObj(FIRE_UP_FONT);
    menu_power_level->setFontNameObj(FIRE_UP_FONT);
    menu_power_level->setFontSizeObj(20);
    menu_speed_level->setFontNameObj(FIRE_UP_FONT);
    menu_speed_level->setFontSizeObj(20);
    menu_surclassement_txt->setFontNameObj(FIRE_UP_FONT);
    menu_anim_img_hand->setAnchorPoint(Vec2(0.45, 0.75));
    menu_title->setFontSizeObj(85);
    menu_best_txt->setFontSizeObj(30);
    menu_surclassement_txt->setFontSizeObj(20);
    menu_surclassement_img->setAnchorPoint(Vec2(1, 1));
    menu_surclassement_img->setPosition(
            Vec2(static_cast<float>(x_screen * 0.95),
                 player->getPosition().y +
                 player->getContentSize().height));
    menu_shop_img->setPosition(
            Vec2(static_cast<float>(menu_shop_img->getContentSize().width / 2 +
                                    x_screen * 0.05),
                 player->getPosition().y + player->getContentSize().height / 2));
    menu_surclassement_txt->setPosition(Vec2(menu_surclassement_img->getPosition().x -
                                             menu_surclassement_img->getContentSize().width / 2,
                                             menu_surclassement_img->getPosition().y -
                                             menu_surclassement_img->getContentSize().height /
                                             2));
    menu_anim_img->setPosition(Vec2(static_cast<float>(x_screen * 0.5),
                                    static_cast<float>(y_screen * 0.17)));
    menu_anim_img_hand->setPosition(Vec2(
            static_cast<float>(menu_anim_img->getPosition().x +
                               0.20 * (0.5 * menu_anim_img->getContentSize().width)),
            static_cast<float>(y_screen * 0.17)));
    menu_title->setPosition(Point(x_screen / 2,
                                  static_cast<float>(y_screen - (y_screen / 5))));
    options_btn->setPosition(
            static_cast<float>(0 + (options_btn->getContentSize().height / 2) +
                               (0.3 * options_btn->getContentSize().height)),
            static_cast<float>(y_screen - (0.3 * options_btn->getContentSize().height +
                                           (options_btn->getContentSize().height / 2))));
    menu_best_txt->setFontNameObj(FIRE_UP_FONT);
    auto midle = x_screen / 2;
    float img_width = menu_best_img->getContentSize().width;
    float txt_width = menu_best_txt->getContentSize().width;
    float both = img_width + txt_width;
    menu_best_img->setPosition(Point(midle - both / 2 + (img_width / 2 - img_width / 8),
                                     static_cast<float>(menu_title->getPosition().y -
                                                        (menu_title->getContentSize().height *
                                                         0.8))));
    menu_best_txt->setPosition(Point(midle + both / 2 - (txt_width / 2 - img_width / 8),
                                     static_cast<float>(menu_title->getPosition().y -
                                                        ((menu_title->getContentSize().height *
                                                          0.8) +
                                                         menu_best_img->getContentSize().height *
                                                         0.16))));
    auto actionMove1 = MoveTo::create(0.6, Vec2(menu_anim_img->getPosition().x -
                                                (menu_anim_img->getContentSize().width / 2 -
                                                 menu_anim_img->getContentSize().width / 6),
                                                menu_anim_img_hand->getPosition().y));
    auto actionMove2 = MoveTo::create(0.6, Vec2(menu_anim_img->getPosition().x +
                                                (menu_anim_img->getContentSize().width / 2 -
                                                 menu_anim_img->getContentSize().width / 6),
                                                menu_anim_img_hand->getPosition().y));
    menu_stats_img->setAnchorPoint(Vec2(0, 0));
    menu_stats_img->setPosition(Vec2(x_screen / 2 + player->getContentSize().width / 2,
                                     menu_shop_img->getPosition().y +
                                     menu_shop_img->getContentSize().height / 2));
    menu_speed_level->setPosition(
            Vec2(menu_stats_img->getPosition().x + menu_stats_img->getContentSize().width / 2,
                 static_cast<float>(menu_stats_img->getPosition().y +
                                    menu_stats_img->getContentSize().height / 2 +
                                    (0.08 * menu_stats_img->getContentSize().height))));
    menu_power_level->setPosition(
            menu_stats_img->getPosition().x + menu_stats_img->getContentSize().width / 2,
            static_cast<float>(menu_stats_img->getPosition().y +
                               (0.27 * menu_stats_img->getContentSize().height)));
    auto seq = Sequence::create(actionMove1, actionMove2, nullptr);
    menu_anim_img_hand->runAction(RepeatForever::create(seq));
    auto main_menu = Menu::create(menu_title, menu_surclassement_img, menu_surclassement_txt,
                                  menu_shop_img, menu_anim_img, menu_anim_img_hand,
                                  menu_best_img,
                                  menu_best_txt, options_btn, menu_stats_img, menu_power_level,
                                  menu_speed_level,
                                  NULL);
    main_menu->setTag(MAIN_MENU_TAG);
    main_menu->setPosition(Point(0, 0));
    return (main_menu);
}

Menu *GameScene::get_end_game_menu() {
    char points[DEFAULT_CHAR_LENGHT];
    if (UserLocalStore::get_achievement_variable(POINT) > 1000)
        sprintf(points, "%.1fk",
                static_cast<float>(UserLocalStore::get_achievement_variable(POINT)) / 1000);
    else
        sprintf(points, "%i PTS",
                UserLocalStore::get_achievement_variable(POINT));
    char power_price[DEFAULT_CHAR_LENGHT];
    sprintf(power_price, "%i PTS",
            UserLocalStore::get_achievement_variable(POWER_LEVEL_PRICE));
    char speed_price[DEFAULT_CHAR_LENGHT];
    sprintf(speed_price, "%i PTS",
            UserLocalStore::get_achievement_variable(SPEED_LEVEL_PRICE));
    char current_power[DEFAULT_CHAR_LENGHT];
    sprintf(current_power, "LEVEL %i",
            UserLocalStore::get_achievement_variable(POWER_LEVEL));
    char current_speed[DEFAULT_CHAR_LENGHT];
    sprintf(current_speed, "LEVEL %i",
            UserLocalStore::get_achievement_variable(SPEED_LEVEL));
    stats = Menu::create();
    Label *current_point = Label::createWithTTF(points, FIRE_UP_FONT, 60);
    char earned[DEFAULT_CHAR_LENGHT];
    if (game_score > 1000)
        sprintf(earned, "+ %.1fk pts", static_cast<float>(game_score) / 1000);
    else
        sprintf(earned, "+ %ipts", game_score);
    Label *earned_point = Label::createWithTTF(earned, FIRE_UP_FONT, 25);
    Label *speed_price_txt = Label::createWithTTF(speed_price, FIRE_UP_FONT, 20);
    Label *power_price_txt = Label::createWithTTF(power_price, FIRE_UP_FONT, 20);
    Label *speed_info = Label::createWithTTF("SHOOTING SPEED", FIRE_UP_FONT, 24);
    Label *power_info = Label::createWithTTF("SHOOTING POWER", FIRE_UP_FONT, 24);
    Label *speed_current_level = Label::createWithTTF(current_speed, FIRE_UP_FONT, 25);
    Label *power_current_level = Label::createWithTTF(current_power, FIRE_UP_FONT, 25);
    back_to_main = MenuItemImage::create("end_of_game_menu/replay_btn.png",
                                         "end_of_game_menu/replay_btn.png",
                                         CC_CALLBACK_1(GameScene::back_to_menu, this));
    share = MenuItemImage::create
            ("end_of_game_menu/share_btn.png",
             "end_of_game_menu/share_btn.png",
             CC_CALLBACK_1(GameScene::back_to_menu, this));
    rate = MenuItemImage::create("end_of_game_menu/rate_btn.png",
                                 "end_of_game_menu/rate_btn.png",
                                 CC_CALLBACK_1(GameScene::back_to_menu, this));
    Sprite *background = Sprite::create("end_of_game_menu/background.png");
    speed_current_level->setColor(Color3B(124, 184, 255));
    power_current_level->setColor(Color3B(255, 124, 124));
    auto move_to_stats = MoveTo::create(0.2, Vec2(x_screen / 2,
                                                  static_cast<float>(y_screen / 1.75)));
    MenuItemImage *speed_level_btn = MenuItemImage::create(POPUP_MENU_PATH::
                                                           SPEED,
                                                           POPUP_MENU_PATH::SPEED_SELECTED,
                                                           [=](Ref *sender) {
                                                               GameScene::increase_speed(
                                                                       speed_current_level);
                                                           });
    MenuItemImage *power_level_btn = MenuItemImage::create(POPUP_MENU_PATH::
                                                           POWER,
                                                           POPUP_MENU_PATH::POWER_SELECTED,
                                                           [=](Ref *sender) {
                                                               GameScene::increase_power(
                                                                       power_current_level);
                                                           });
    stats->setPosition(Size(x_screen / 2, static_cast<float>(y_screen +
                                                             stats->getContentSize().height *
                                                             1.3)));
    stats->setContentSize(Size(static_cast<float>(x_screen * 0.88),
                               static_cast<float>(y_screen / 2.5)));
    back_to_main->setPosition(Vec2(x_screen / 2, -2 * back_to_main->getContentSize().height));
    share->setPosition(
            Vec2(static_cast<float>(x_screen / 2 - back_to_main->getContentSize().width),
                 -2 * back_to_main->getContentSize().height));
    rate->setPosition(
            Vec2(static_cast<float>(x_screen / 2 + back_to_main->getContentSize().width),
                 -2 * back_to_main->getContentSize().height));
    auto move_to_skip = MoveTo::create(0.2, Vec2(x_screen / 2,
                                                 static_cast<float>(
                                                         (static_cast<float>(y_screen /
                                                                             1.75)) -
                                                         stats->getContentSize().height / 2 -
                                                         1.5 *
                                                         back_to_main->getContentSize().height)));
    auto move_to_share_0 = MoveTo::create(0.2, Vec2(
            static_cast<float>(x_screen / 2 - back_to_main->getContentSize().width),
            static_cast<float>(static_cast<float>(
                                       (static_cast<float>(y_screen / 1.75)) -
                                       stats->getContentSize().height / 2 -
                                       1.5 * back_to_main->getContentSize().height) +
                               0.5 * back_to_main->getContentSize().height)));
    auto move_to_share_1 = MoveTo::create(0.1, Vec2(static_cast<float>(x_screen / 2 -
                                                                       back_to_main->getContentSize().width),
                                                    static_cast<float>(
                                                            (static_cast<float>(y_screen /
                                                                                1.75)) -
                                                            stats->getContentSize().height / 2 -
                                                            1.5 *
                                                            back_to_main->getContentSize().height)));
    auto move_to_rate_0 = MoveTo::create(0.2, Vec2(
            static_cast<float>(x_screen / 2 + back_to_main->getContentSize().width),
            static_cast<float>(static_cast<float>(
                                       (static_cast<float>(y_screen / 1.75)) -
                                       stats->getContentSize().height / 2 -
                                       1.5 * back_to_main->getContentSize().height) +
                               0.5 * back_to_main->getContentSize().height)));
    auto move_to_rate_1 = MoveTo::create(0.1, Vec2(static_cast<float>(x_screen / 2 +
                                                                      back_to_main->getContentSize().width),
                                                   static_cast<float>(
                                                           (static_cast<float>(y_screen /
                                                                               1.75)) -
                                                           stats->getContentSize().height / 2 -
                                                           1.5 *
                                                           back_to_main->getContentSize().height)));
    auto sequence_share = Sequence::create(move_to_share_0, move_to_share_1, nullptr);
    auto sequence_rate = Sequence::create(move_to_rate_0, move_to_rate_1, nullptr);
    speed_level_btn->setPosition(Vec2(0 - stats->getContentSize().width / 4,
                                      static_cast<float>(-(stats->getContentSize().height / 2) +
                                                         speed_level_btn->getContentSize().height *
                                                         0.7)));
    power_level_btn->setPosition(Vec2(0 + stats->getContentSize().width / 4,
                                      static_cast<float>(-(stats->getContentSize().height / 2) +
                                                         power_level_btn->getContentSize().height *
                                                         0.7)));
    current_point->setPosition(Vec2(0, static_cast<float>(stats->getContentSize().height / 2 -
                                                          (1.1 *
                                                           current_point->getContentSize().height))));
    earned_point->setPosition(Vec2(0, static_cast<float>(current_point->getPositionY() - (1.2 *
                                                                                          current_point->getContentSize().height /
                                                                                          2))));
    speed_price_txt->setPosition(Vec2(speed_level_btn->getPosition().x,
                                      static_cast<float>(speed_level_btn->getPosition().y -
                                                         (0.25 *
                                                          speed_level_btn->getContentSize().height))));
    power_price_txt->setPosition(Vec2(power_level_btn->getPosition().x,
                                      static_cast<float>(speed_level_btn->getPosition().y -
                                                         (0.25 *
                                                          power_level_btn->getContentSize().height))));
    speed_current_level->setPosition(Vec2(speed_level_btn->getPosition().x,
                                          static_cast<float>(speed_level_btn->getPosition().y +
                                                             speed_level_btn->getContentSize().height /
                                                             2 * 1.4)));
    power_current_level->setPosition(Vec2(power_level_btn->getPosition().x,
                                          static_cast<float>(power_level_btn->getPosition().y +
                                                             power_level_btn->getContentSize().height /
                                                             2 * 1.4)));
    speed_info->setPosition(Vec2(speed_current_level->getPosition().x,
                                 static_cast<float>(speed_current_level->getPosition().y +
                                                    1.6 *
                                                    speed_current_level->getContentSize().height)));
    power_info->setPosition(Vec2(power_current_level->getPosition().x,
                                 static_cast<float>(power_current_level->getPosition().y +
                                                    1.6 *
                                                    power_current_level->getContentSize().height)));
    background->setContentSize(stats->getContentSize());
    stats->addChild(background);
    stats->addChild(earned_point);
    stats->addChild(current_point);
    stats->addChild(power_level_btn);
    stats->addChild(speed_level_btn);
    stats->addChild(speed_price_txt);
    stats->addChild(power_price_txt);
    stats->addChild(speed_info);
    stats->addChild(power_info);
    stats->addChild(speed_current_level);
    stats->addChild(power_current_level);
    back_to_main->runAction(move_to_skip);
    share->runAction(sequence_share);
    rate->runAction(sequence_rate);
    stats->runAction(move_to_stats);
    addChild(stats);
    auto end_menu = Menu::create(back_to_main, share, rate, NULL);
    end_menu->setAnchorPoint(Vec2(0.5, 0.5));
    end_menu->setPosition(Vec2(0, 0));
    end_menu->setContentSize(Size(x_screen, y_screen));
    return (end_menu);
}

void GameScene::increase_speed(Label *speed) {
    UserLocalStore::store_achievement_variable_float(SPEED_VALUE,
                                                     static_cast<float>(
                                                             UserLocalStore::get_achievement_variable_float(
                                                                     SPEED_VALUE) + 0.5));
    UserLocalStore::store_achievement_variable(
            SPEED_LEVEL,
            UserLocalStore::get_achievement_variable(
                    SPEED_LEVEL) +
            1);
    if (UserLocalStore::get_achievement_variable(SPEED_LEVEL) ==
        10)
        UserLocalStore::store_shooter(20, 1);
    char s[DEFAULT_CHAR_LENGHT];
    sprintf(s, "SPEED %i",
            UserLocalStore::get_achievement_variable(
                    SPEED_LEVEL));
    speed->setString(s);
}

void GameScene::increase_power(Label *power) {
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
    if (UserLocalStore::get_achievement_variable(POWER_LEVEL) ==
        20)// DEBLOCAGE D'UN SHOOTER (5:)
        UserLocalStore::store_shooter(6, 1);
    char p[DEFAULT_CHAR_LENGHT];
    sprintf(p, "LEVEL %i",
            UserLocalStore::get_achievement_variable(POWER_LEVEL));
    power->setString(p);
}

void GameScene::check_first_launch() {
    if (UserLocalStore::get_first_launch() == 0) {
        UserLocalStore::set_first_launch();
        UserLocalStore::init_asset_arrays();
        UserLocalStore::init_achievement_variables();
    }
}

void GameScene::menuCloseCallback(Ref *pSender) {
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}