#include    "GameScene.h"
#include    "Square.h"
#include    "Line.h"
#include    "Utils.h"
#include    "ShopScene.h"
#include    <vector>
#include    <iomanip>
#include    "cocos2d.h"
#include    "Popup.h"
#include    "GridView.h"
#include    "CustomTableViewCell.h"
#include    "UserLocalStore.h"
#include    "ShootUp.h"

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
    player = Utils::get_player();
    this->addChild(player);
    score = Label::createWithTTF("test", FIRE_UP_FONT_NUMBERS, 100);
    score->setPosition(Vec2(x_screen / 2, static_cast<float>(y_screen - 0.15 * y_screen)));
    score->setVisible(false);
    addChild(score, 10);

    bullet_state = 0;
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, player);

    game_menu = get_main_menu();
    addChild(game_menu);
    if (UserLocalStore::get_achievement_variable(FROM_SHOP) == 0)
        main_menu_coming_animation();
    else
        UserLocalStore::store_achievement_variable(FROM_SHOP, 0);
    init_pool_objects();
    init_options_menu();
}

Menu *GameScene::get_continue_menu() {
    skip_btn = MenuItemImage::create(END_MENU_PATH::SKIP, END_MENU_PATH::SKIP,
                                     CC_CALLBACK_1(GameScene::skip, this));
    skip_btn->setPosition(Vec2(x_screen / 2, static_cast<float>(y_screen / 2 - (0.18 * y_screen))));
    Menu *continue_menu = Menu::create(skip_btn, NULL);
    continue_menu->setContentSize(Size(x_screen, y_screen));
    continue_menu->setPosition(Vec2::ZERO);
    return (continue_menu);
}

void GameScene::init_options_menu() {
    if (UserLocalStore::get_achievement_variable(SOUND) == 0)
        sound = Sprite::create(OPTIONS_SOUND_ON);
    else
        sound = Sprite::create(OPTIONS_SOUND_OFF);
    tuto = Sprite::create(OPTIONS_TUTO);
    sound->setScale(0.9);
    tuto->setScale(0.9);
    sound->setPosition(
            Vec2(static_cast<float>(options_btn->getPosition().x +
                                    1 * (options_btn->getContentSize().height)),
                 options_btn->getPosition().y));
    tuto->setPosition(Vec2(sound->getPosition().x + 1 * (sound->getContentSize().height),
                           options_btn->getPosition().y));
    sound->setVisible(false);
    tuto->setVisible(false);
    this->addChild(tuto);
    this->addChild(sound);
}

void GameScene::end_of_game() {
    game_state = GAME_END;
    score->setVisible(false);
    player->setVisible(false);
    stop_bullet_shoot();
    continue_menu = get_continue_menu();
    addChild(continue_menu);
}

void GameScene::reset_arrays() {
    for (int j = 0; active_lines[j] != NULL; j++)
        active_lines[j] = -1;
}

void GameScene::reset_lines() {
    for (int i = 0; pool_container[i] != NULL; i++) {
        if (pool_container[i]->line_active) {
            pool_container[i]->stopAllActions();
            pool_container[i]->reset();
            pool_container[i]->line_active = false;
            pool_container[i]->setVisible(false);
        }
    }
}

void GameScene::init_pool_objects() {
    int index_struct = 7;
    pool_container = new Line *[27];
    bullet_container = new Bullet *[31];
    active_lines = new int[5];

    pool_container[0] = Line::create(STARTUP_LINE_2);
    pool_container[1] = Line::create(STARTUP_LINE_3);
    pool_container[2] = Line::create(STARTUP_LINE_4);
    pool_container[3] = Line::create(STARTUP_LINE_5);

    for (int i = 0; i < 4; i++)
        active_lines[i] = -1;
    active_lines[4] = NULL;
    for (int j = 0; j < 30; j++) {
        bullet_container[j] = Bullet::create();
        addChild(bullet_container[j], 4);
    }
    bullet_container[30] = NULL;
    for (int i = 4; i < 7; i++)
        pool_container[i] = Line::create(SIMPLE_LINE_4);
    for (int i = 7; i < 10; i++)
        pool_container[i] = Line::create(SIMPLE_LINE_5);
    for (int i = 10; i < 26; i = i + 2, index_struct++) {
        pool_container[i] = Line::create(index_struct);
        pool_container[i + 1] = Line::create(index_struct);
    }
    pool_container[26] = NULL;
    for (int i = 0; pool_container[i] != NULL; i++)
        addChild(pool_container[i]);
}

void GameScene::start_bullet_shoot() {
    this->schedule(schedule_selector(GameScene::launch_bullet), 0.1);
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
                                         Vec2(tuto->getPosition().x + 11, tuto->getPosition().y));
        auto actionMove2 = MoveTo::create(0.1, Vec2(sound->getPosition().x + 11,
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
                                         Vec2(tuto->getPosition().x - 11, tuto->getPosition().y));
        auto actionMove2 = MoveTo::create(0.1, Vec2(sound->getPosition().x - 11,
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
    for (int j = 0; active_lines[j] != NULL; j++) {
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

void GameScene::show_destruction_circle(Vec2 pos, float line_y, int parent_height) {
    auto circle = Sprite::create(HIT_CIRCLE);
    circle->setScale(0.0f);
    auto scale_anim = ScaleTo::create(0.55f, 2.5f);
    auto move_ease_in = EaseOut::create(scale_anim->clone(), 1);
    auto fadeOut = FadeOut::create(0.55f);
    auto actionRemove = RemoveSelf::create();
    circle->setPosition(pos);
    auto actionMove = MoveTo::create(Utils::line_speed_converter(line_y),
                                     Vec2(pos.x, 0 - parent_height));
    CCDirector::sharedDirector()->getRunningScene()->addChild(circle, 1, 1);
    circle->runAction(actionMove);
    circle->runAction(fadeOut);
    circle->runAction(Sequence::create(move_ease_in, actionRemove, nullptr));
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

void GameScene::check_into_line() {
    for (int i = 0; bullet_container[i] != NULL; i++) {
        if (bullet_container[i + 2] != NULL && !bullet_container[i]->bullet_active &&
            !bullet_container[i + 1]->bullet_active)
            return;
        if (bullet_container[i] && bullet_container[i]->bullet_active &&
            bullet_container[i]->contact) {
            int j = 0;
            int index = 0;

            while (j == 0) {
                Line *current_line = pool_container[bullet_container[i]->contact_index];
                auto child = current_line->getChildByTag(index);
                Square *sq = ((Square *) child);
                if (!sq) {
                    j = 1;
                    break;
                }
                Vec2 bullet_pos;
                bullet_pos.x = bullet_container[i]->getPositionX();
                bullet_pos.y = bullet_container[i]->getPositionY() -
                               (current_line->getPositionY());

                if (bullet_pos.y < 0)
                    bullet_pos.y = 0;
                if (point_into_square(sq, bullet_pos) && sq->isVisible()) {
                    if (sq->get_square_pv() == 1) {
                        auto batch = current_line->getChildByTag(LINE_BATCH_ID);
                        if (batch) {
                            auto sprite = batch->getChildByTag(sq->getTag());
                            if (sprite)
                                sprite->setVisible(false);
                        }
                        sq->setVisible(false);
                        Vec2 square_pos;
                        square_pos.x = sq->getPositionX();
                        square_pos.y = current_line->getPositionY() + sq->getPositionY();
                        show_destruction_circle(square_pos, current_line->getPositionY(),
                                                static_cast<int>(current_line->getContentSize().height));
                        update_game_score();
                        break;
                    } else {
                        update_game_score();
                        show_particle(bullet_container[i]->getPosition());
                        sq->square_pv--;
                        char pv[DEFAULT_CHAR_LENGHT];
                        sprintf(pv, "%i", sq->square_pv);
                        sq->points->setString(pv);
                        break;
                    }
                    bullet_container[i]->Reset();
                }
                index++;
            }
        }
    }
}

void GameScene::check_lines_out() {
    for (int i = 0; active_lines[i] != NULL; i++) {
        if (active_lines[i] != -1 && pool_container[active_lines[i]]->getPositionY() +
                                     pool_container[active_lines[i]]->getContentSize().height <
                                     player->getPositionY() - player->getContentSize().height / 2)
            remove_active_line(i);
    }
}

void GameScene::check_player_collision() {
    for (int i = 0; active_lines[i] != NULL; i++) {
        if (active_lines[i] != -1 && pool_container[active_lines[i]]->getPositionY() <
                                     player->getPositionY() + player->getContentSize().height / 2) {
            int j = 0;
            int index = 0;
            float player_y =
                    player->getPositionY() - pool_container[active_lines[i]]->getPositionY();
            while (j == 0) {
                auto child = pool_container[active_lines[i]]->getChildByTag(index);
                Square *sq = ((Square *) child);
                if (!child) {
                    j = 1;
                    break;
                }
                if (sq->isVisible() && sq->getBoundingBox().intersectsRect(
                        Rect(player->getPositionX() - player->getContentSize().width / 2,
                             player_y,
                             player->getContentSize().width,
                             player->getContentSize().height)))
                    if (game_state == GAME_RUNNING) {
                        end_of_game();
                        return;
                    }
                index++;
            }
        }
    }
}

void GameScene::update(float ft) {
    if (game_state == GAME_RUNNING) {
        check_bullet_contact();
        check_into_line();
        check_lines_out();
        check_player_collision();
    }
    if (pool_container[CURRENT_LINE_ID]->getPosition().y <= NEW_SPAWN_Y) {
        pool_container[NEXT_LINE_ID]->move();
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
    for (int i = 0; active_lines[i] != NULL; i++) {
        if (active_lines[i] == -1) {
            active_lines[i] = line_index;
            return;
        }
    }
}

void GameScene::remove_active_line(int line_to_rm) {
    for (int i = 0; active_lines[i] != NULL; i++) {
        if (i == line_to_rm) {
            active_lines[i] = -1;
            return;
        }
    }
}

int GameScene::get_next_line_type() {
    if (LINE_GENERATED < 7)
        return (LINE_TYPE_SIMPLE_OF_4);
    else if (LINE_GENERATED == 7)
        return (LINE_TYPE_SIMPLE_OF_5);
    else
        return (Utils::get_random_line_type());
}

void GameScene::run_game_loop() {
    int indicator = UserLocalStore::get_achievement_variable(POWER_LEVEL) +
                    UserLocalStore::get_achievement_variable(SPEED_LEVEL);
    if (indicator == 2) {
        CURRENT_LINE_ID = 4;
        NEXT_LINE_ID = 5;
        NEW_SPAWN_Y = Utils::get_spawn_y(pool_container[CURRENT_LINE_ID]->get_type(),
                                         pool_container[NEXT_LINE_ID]->get_type(),
                                         pool_container[NEXT_LINE_ID]->line_size);
    } else {
        if (indicator > 2 && indicator < 20) {
            CURRENT_LINE_ID = 0;
            NEXT_LINE_ID = 4;
        } else if (indicator >= 2 && indicator < 40) {
            CURRENT_LINE_ID = 1;
            NEXT_LINE_ID = 4;
        } else if (indicator >= 40 && indicator < 80) {
            CURRENT_LINE_ID = 2;
            NEXT_LINE_ID = 4;
        } else if (indicator >= 80) {
            CURRENT_LINE_ID = 3;
            NEXT_LINE_ID = 4;
        }
        NEW_SPAWN_Y = Utils::get_spawn_y(pool_container[CURRENT_LINE_ID]->get_type(),
                                         pool_container[NEXT_LINE_ID]->get_type(),
                                         pool_container[CURRENT_LINE_ID]->line_size);
    }
    store_active_line(CURRENT_LINE_ID);
    pool_container[CURRENT_LINE_ID]->move();
    LINE_GENERATED++;
    this->scheduleUpdate();
}

void GameScene::stop_game_loop() {
    this->unscheduleUpdate();
}

void GameScene::update_game_score() {
    game_score++;
    char score_value[DEFAULT_CHAR_LENGHT];
    sprintf(score_value, "%i", game_score);
    score->setString(score_value);
}

void GameScene::start_game() {
    game_score = 0;
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

void GameScene::skip(cocos2d::Ref *pSender) {
    removeChild(continue_menu);
    end_menu = get_end_game_menu();
    addChild(end_menu);
}

void GameScene::back_to_menu(cocos2d::Ref *pSender) {
    auto callback = CallFuncN::create(
            [&](Node *sender) {
                if (!player->isVisible())
                    player->setVisible(true);
                player->setPositionX(x_screen / 2);
                stop_game_loop();
                reset_lines();
                reset_arrays();
                game_state = MENU;
                removeChild(end_menu);
                game_menu = get_main_menu();
                addChild(game_menu);
                main_menu_coming_animation();
            });
    auto delay = DelayTime::create(0.2);
    auto delay2 = DelayTime::create(0.2);
    auto move_to_share_0 = MoveTo::create(0.1, Vec2(share->getPositionX(), share->getPositionY() +
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
        touch->getLocation().x < x_screen - player->getContentSize().height / 2)
        player->setPosition(Vec2(touch->getLocation().x, player->getPosition().y));
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

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
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
    for (int i = 0; bullet_container[i] != NULL; i++) {
        if (!bullet_container[i]->bullet_active) {
            bullet_container[i]->Launch(bullet_state, player->getPosition(),
                                        player->getContentSize());
            if (bullet_state == BULLET_LEFT)
                bullet_state = BULLET_RIGHT;
            else
                bullet_state = BULLET_LEFT;
            return;
        }
    }
}

void GameScene::main_menu_coming_animation() {
    menu_stats_img->setOpacity(0);
    menu_anim_img->setOpacity(0);
    menu_anim_img_hand->setOpacity(0);
    options_btn->setOpacity(0);
    menu_best_txt->setOpacity(0);
    menu_best_img->setOpacity(0);

    menu_title->setPositionY(y_screen + menu_title->getContentSize().height);
    menu_surclassement_img->setPositionX(x_screen + menu_surclassement_img->getContentSize().width);
    menu_surclassement_txt->setPositionX(menu_surclassement_img->getPosition().x -
                                         menu_surclassement_img->getContentSize().width / 2);


    auto move_title_0 = MoveTo::create(0.1, Vec2(menu_title->getPositionX(),
                                                 static_cast<float>(static_cast<float>(y_screen -
                                                                                       (y_screen /
                                                                                        5)) -
                                                                    y_screen * 0.05)));
    auto move_title_1 = MoveBy::create(0.1, Vec2(0, static_cast<float>(y_screen * 0.05)));
    auto move_surclassement_img_0 = MoveTo::create(0.1, Vec2(static_cast<float>(x_screen * 0.95 -
                                                                                x_screen * 0.03),
                                                             menu_surclassement_img->getPositionY()));
    auto move_surclassement_img_1 = MoveBy::create(0.1, Vec2(
            static_cast<float>(x_screen * 0.03),
            0));
    auto move_surclassement_txt_0 = MoveTo::create(0.1, Vec2(static_cast<float>(x_screen * 0.95 -
                                                                                x_screen * 0.03) -
                                                             menu_surclassement_img->getContentSize().width /
                                                             2,
                                                             menu_surclassement_txt->getPositionY()));

    auto move_shop_img_0 = MoveTo::create(0.1, Vec2(static_cast<float>(static_cast<float>(
                                                                               menu_shop_img->getContentSize().width /
                                                                               2 +
                                                                               x_screen * 0.05) +
                                                                       x_screen * 0.03),
                                                    menu_shop_img->getPositionY()));
    auto move_shop_img_1 = MoveBy::create(0.1, Vec2(static_cast<float>(-x_screen * 0.03), 0));
    auto fadeIn = FadeIn::create(0.5);
    auto seq0 = Sequence::create(move_surclassement_img_0, move_surclassement_img_1, NULL);
    auto seq1 = Sequence::create(move_surclassement_txt_0, move_surclassement_img_1->clone(), NULL);
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
    sprintf(speed_level, "%i",
            UserLocalStore::get_achievement_variable(SPEED_VALUE));
    char best_score[DEFAULT_CHAR_LENGHT];
    sprintf(best_score, "%i",
            UserLocalStore::get_achievement_variable(SCORE));
    menu_power_level = MenuItemFont::create(power_level);
    menu_speed_level = MenuItemFont::create(speed_level);
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
    menu_title->setFontSizeObj(105);
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
    menu_power_level->setPosition(
            Vec2(menu_stats_img->getPosition().x + menu_stats_img->getContentSize().width / 2,
                 static_cast<float>(menu_stats_img->getPosition().y +
                                    menu_stats_img->getContentSize().height / 2 +
                                    (0.08 * menu_stats_img->getContentSize().height))));
    menu_speed_level->setPosition(
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
    main_menu->setPosition(Point(0, 0));
    return (main_menu);
}

Menu *GameScene::get_end_game_menu() {
    char points[DEFAULT_CHAR_LENGHT];
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
    stats = Layer::create();
    Label *current_point = Label::createWithTTF(points, FIRE_UP_FONT, 40);
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
    MenuItemImage *speed_level_btn = MenuItemImage::create(POPUP_MENU_PATH::SPEED,
                                                           POPUP_MENU_PATH::SPEED_SELECTED,
                                                           CC_CALLBACK_1(
                                                                   GameScene::surclassement,
                                                                   this));
    MenuItemImage *power_level_btn = MenuItemImage::create(POPUP_MENU_PATH::POWER,
                                                           POPUP_MENU_PATH::POWER_SELECTED,
                                                           CC_CALLBACK_1(
                                                                   GameScene::surclassement,
                                                                   this));
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
                                                          current_point->getContentSize().height *
                                                          1.5)));
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