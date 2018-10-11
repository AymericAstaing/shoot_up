#include    "UserLocalStore.h"
#include     "GameScene.h"

#define     SHOOTER_ARRAY   0
#define     BALL_ARRAY      1

#define     LOCKED          0
#define     UNLOCKED        1
#define     SELECTED        2

USING_NS_CC;


/********************* ACHIEVEMENTS / IN GAME VARIABlES (26 vrbls) ****************/

/*********************** SHOOTER ***********************/

namespace GLOBAL {
    const char *KEY_POWER_LEVEL = "POWER_LEVEL";
    const char *KEY_SPEED_LEVEL = "SPEED_LEVEL";
    const char *KEY_SPEED_VALUE = "SPEED_VALUE";
    const char *KEY_POWER_VALUE = "POWER_VALUE";
    const char *KEY_POWER_UP_ITEMS = "POWER_UP_ITEMS";
    const char *KEY_SCORE = "SCORE";
    const char *KEY_POINT = "POINT";
    const char *KEY_SOUND = "SOUND";
    const char *KEY_ITEM_DESTROYED = "ITEM_DESTROYED";
    const char *KEY_GAME_NBR = "GAME_NBR";
    const char *KEY_BLOCK_DESTROYED = "BLOCK_DESTROYED";
    const char *KEY_POWER_LEVEL_PRICE = "POWER_LEVEL_PRICE";
    const char *KEY_SPEED_LEVEL_PRICE = "SPEED_LEVEL_PRICE";
}

namespace STARTER_TANK {
    const char *KEY_BLOCK_STARTER_TANK = "BLOCK_STARTER";
    const char *KEY_ITEM_STARTER_TANK = "ITEM_STARTER";
    const char *KEY_GAME_STARTER_TANK = "GAME_STARTER";
}

namespace POWER_TANK {
    const char *KEY_BLOCK_POWER_TANK = "BLOCK_POWER";
    const char *KEY_GAME_POWER_TANK = "GAME_POWER";
}

namespace MOVEMENT_TANK {
    const char *KEY_ITEM_MOVEMENT_TANK = "ITEM_MOVEMENT";
    const char *KEY_GAME_MOVEMENT_TANK = "GAME_MOVEMENT";
}

namespace DOUBLE_TANK {
    const char *KEY_BLOCK_DOUBLE_TANK = "BLOCK_DOUBLE";
    const char *KEY_GAME_MOVEMENT_TANK = "GAME_DOUBLE";
}

namespace SHIELD_TANK {
    const char *KEY_ITEM_SHIELD_TANK = "ITEM_SHIELD";
    const char *KEY_GAME_SHIELD_TANK = "GAME_SHIELD";
}

namespace SPEED_TANK {
    const char *KEY_GAME_SPEED_TANK = "GAME_SPEED";
    const char *KEY_ITEM_SPEED_TANK = "ITEM_SPEED";
    const char *KEY_BLOCK_SPEED_TANK = "BLOCK_SPEED";
}

namespace SIDEWAY_TANK {
    const char *KEY_GAME_SIDEWAY_TANK = "GAME_SIDEWAY";
    const char *KEY_BLOCK_SIDEWAY_TANK = "BLOCK_SIDEWAY";
}

namespace TRIPLE_TANK {
    const char *KEY_GAME_TRIPLE_TANK = "GAME_TRIPLE";
    const char *KEY_ITEM_TRIPLE_TANK = "ITEM_TRIPLE";
    const char *KEY_BLOCK_TRIPLE_TANK = "BLOCK_TRIPLE";
}


void UserLocalStore::init_achievement_variables() {
    UserDefault *def = UserDefault::sharedUserDefault();
    def->setIntegerForKey(GLOBAL::KEY_ITEM_DESTROYED, 0);
    def->setIntegerForKey(GLOBAL::KEY_POWER_LEVEL, 1);
    def->setIntegerForKey(GLOBAL::KEY_SPEED_LEVEL, 1);
    def->setIntegerForKey(GLOBAL::KEY_POWER_UP_ITEMS, 0);
    def->setIntegerForKey(GLOBAL::KEY_SCORE, 0);
    def->setIntegerForKey(GLOBAL::KEY_GAME_NBR, 0);
    def->setIntegerForKey(GLOBAL::KEY_POINT, 0);
    def->setIntegerForKey(GLOBAL::KEY_BLOCK_DESTROYED, 0);
    def->setIntegerForKey(GLOBAL::KEY_POWER_LEVEL_PRICE, 0);
    def->setIntegerForKey(GLOBAL::KEY_SPEED_LEVEL_PRICE, 0);
    def->setIntegerForKey(GLOBAL::KEY_SOUND, 0);
    def->setIntegerForKey(GLOBAL::KEY_POWER_VALUE, 1);
    def->setIntegerForKey(GLOBAL::KEY_SPEED_VALUE, 1);
    def->setIntegerForKey(STARTER_TANK::KEY_BLOCK_STARTER_TANK, 0);
    def->setIntegerForKey(STARTER_TANK::KEY_ITEM_STARTER_TANK, 0);
    def->setIntegerForKey(STARTER_TANK::KEY_GAME_STARTER_TANK, 0);
    def->setIntegerForKey(POWER_TANK::KEY_BLOCK_POWER_TANK, 0);
    def->setIntegerForKey(POWER_TANK::KEY_GAME_POWER_TANK, 0);
    def->setIntegerForKey(MOVEMENT_TANK::KEY_ITEM_MOVEMENT_TANK, 0);
    def->setIntegerForKey(MOVEMENT_TANK::KEY_GAME_MOVEMENT_TANK, 0);
    def->setIntegerForKey(DOUBLE_TANK::KEY_BLOCK_DOUBLE_TANK, 0);
    def->setIntegerForKey(DOUBLE_TANK::KEY_GAME_MOVEMENT_TANK, 0);
    def->setIntegerForKey(SHIELD_TANK::KEY_ITEM_SHIELD_TANK, 0);
    def->setIntegerForKey(SHIELD_TANK::KEY_GAME_SHIELD_TANK, 0);
    def->setIntegerForKey(SPEED_TANK::KEY_GAME_SPEED_TANK, 0);
    def->setIntegerForKey(SPEED_TANK::KEY_ITEM_SPEED_TANK, 0);
    def->setIntegerForKey(SPEED_TANK::KEY_BLOCK_SPEED_TANK, 0);
    def->setIntegerForKey(SIDEWAY_TANK::KEY_GAME_SIDEWAY_TANK, 0);
    def->setIntegerForKey(SIDEWAY_TANK::KEY_BLOCK_SIDEWAY_TANK, 0);
    def->setIntegerForKey(TRIPLE_TANK::KEY_GAME_TRIPLE_TANK, 0);
    def->setIntegerForKey(TRIPLE_TANK::KEY_ITEM_TRIPLE_TANK, 0);
    def->setIntegerForKey(TRIPLE_TANK::KEY_BLOCK_TRIPLE_TANK, 0);
    def->flush();
}

void UserLocalStore::store_achievement_variable(const char *key, int value) {
    UserDefault *def = UserDefault::sharedUserDefault();
    def->setIntegerForKey(key, value);
    def->flush();
}

int UserLocalStore::get_achievement_variable(const char *key) {
    UserDefault *def = UserDefault::sharedUserDefault();
    return (def->getIntegerForKey(key));
}

int UserLocalStore::get_current_shooter() {
    int *shooter = UserLocalStore::get_asset_shooter();

    for (int i = 0; i < 31; i++){
        if (shooter[i] == SELECTED)
            return (i);
    }
    return (-1);
}

int UserLocalStore::get_current_ball() {
    int *ball = UserLocalStore::get_asset_ball();

    for (int i = 0; i < 8; i++){
        if (ball[i] == SELECTED)
            return (i);
    }
    return (-1);
}

int UserLocalStore::get_shooter_achievement_target(int index) {

    switch (index) {
        case 0:
            return (300);
        case 1:
            return (50);
        case 2:
            return (30);
        case 3:
            return (100);
        case 4:
            return (100);
        case 5:
            return (20);
        case 6:
            return (1000);
        case 7:
            return (150);
        case 8:
            return (300);
        case 9:
            return (5000);
        case 10:
            return (25);
        case 11:
            return (50);
        case 12:
            return (100);
        case 13:
            return (50000);
        case 14:
            return (200);
        case 15:
            return (20000);
        case 16:
            return (75);
        case 17:
            return (200);
        case 18:
            return (200);
        case 19:
            return (10);
        case 20:
            return (100);
        case 21:
            return (200);
        case 22:
            return (15000);
        case 23:
            return (7500);
        case 24:
            return (200);
        case 25:
            return (20000);
        case 26:
            return (200);
        case 27:
            return (300);
        case 28:
            return (30000);
        case 29:
            return (300);
        default:
            break;
    }
    return (0);
}

const char *UserLocalStore::get_shooter_key_with_index(int index) {

    switch (index) {
        case 0:
            return (STARTER_TANK::KEY_BLOCK_STARTER_TANK);
        case 1:
            return (STARTER_TANK::KEY_ITEM_STARTER_TANK);
        case 2:
            return (STARTER_TANK::KEY_GAME_STARTER_TANK);
        case 3:
            return (STARTER_TANK::KEY_GAME_STARTER_TANK);
        case 4:
            return (STARTER_TANK::KEY_ITEM_STARTER_TANK);
        case 5:
            return (GLOBAL::KEY_POWER_LEVEL);
        case 6:
            return (POWER_TANK::KEY_BLOCK_POWER_TANK);
        case 7:
            return (POWER_TANK::KEY_GAME_POWER_TANK);
        case 8:
            return (POWER_TANK::KEY_GAME_POWER_TANK);
        case 9:
            return (POWER_TANK::KEY_BLOCK_POWER_TANK);
        case 10:
            return (GLOBAL::KEY_POWER_UP_ITEMS);
        case 11:
            return (MOVEMENT_TANK::KEY_GAME_MOVEMENT_TANK);
        case 12:
            return (MOVEMENT_TANK::KEY_ITEM_MOVEMENT_TANK);
        case 13:
            return (GLOBAL::KEY_SCORE);
        case 14:
            return (DOUBLE_TANK::KEY_GAME_MOVEMENT_TANK);
        case 15:
            return (DOUBLE_TANK::KEY_BLOCK_DOUBLE_TANK);
        case 16:
            return (GLOBAL::KEY_GAME_NBR);
        case 17:
            return (SHIELD_TANK::KEY_ITEM_SHIELD_TANK);
        case 18:
            return (SHIELD_TANK::KEY_GAME_SHIELD_TANK);
        case 19:
            return (GLOBAL::KEY_SPEED_LEVEL);
        case 20:
            return (SPEED_TANK::KEY_GAME_SPEED_TANK);
        case 21:
            return (SPEED_TANK::KEY_ITEM_SPEED_TANK);
        case 22:
            return (SPEED_TANK::KEY_BLOCK_SPEED_TANK);
        case 23:
            return (GLOBAL::KEY_BLOCK_DESTROYED);
        case 24:
            return (SIDEWAY_TANK::KEY_GAME_SIDEWAY_TANK);
        case 25:
            return (SIDEWAY_TANK::KEY_BLOCK_SIDEWAY_TANK);
        case 26:
            return (GLOBAL::KEY_GAME_NBR);
        case 27:
            return (TRIPLE_TANK::KEY_GAME_TRIPLE_TANK);
        case 28:
            return (TRIPLE_TANK::KEY_BLOCK_TRIPLE_TANK);
        case 29:
            return (TRIPLE_TANK::KEY_ITEM_TRIPLE_TANK);
        default:
            break;
    }
    return (nullptr);
}


const char *UserLocalStore::get_ball_key_with_index(int index) {

    switch (index) {
        case 0:
            return (GLOBAL::KEY_GAME_NBR);
        case 1:
            return (GLOBAL::KEY_BLOCK_DESTROYED);
        case 2:
            return (GLOBAL::KEY_GAME_NBR);
        case 3:
            return (GLOBAL::KEY_POWER_UP_ITEMS);
        case 4:
            return (GLOBAL::KEY_SCORE);
        case 5:
            return (GLOBAL::KEY_GAME_NBR);
        case 6:
            return (GLOBAL::KEY_SCORE);
        default:
            break;
    }
    return (nullptr);
}

int UserLocalStore::get_ball_achievement_target(int index) {

    switch (index) {
        case 0:
            return (30);
        case 1:
            return (500);
        case 2:
            return (150);
        case 3:
            return (200);
        case 4:
            return (10000);
        case 5:
            return (100);
        case 6:
            return (20000);
        default:
            break;
    }
    return (0);
}

const char **UserLocalStore::get_final_shooter_array() {

    const char **shooter_array;

    shooter_array = new const char *[31];
    int *shooter = UserLocalStore::get_asset_shooter();
    for (int i = 0; i < 31; i++) {
        if (shooter[i] == LOCKED)
            shooter_array[i] = shop_shooter_locked[i];
        else if (shooter[i] == UNLOCKED)
            shooter_array[i] = shop_shooter_unlocked[i];
        else if (shooter[i] == SELECTED)
            shooter_array[i] = shop_shooter_selected[i];
    }
    return (shooter_array);
}

const char **UserLocalStore::get_final_ball_array() {
    const char **ball_array;

    ball_array = new const char *[8];

    int *ball = UserLocalStore::get_asset_ball();
    for (int i = 0; i < 8; i++) {
        if (ball[i] == LOCKED)
            ball_array[i] = shop_ball_locked[i];
        else if (ball[i] == UNLOCKED)
            ball_array[i] = shop_ball_unlocked[i];
        else if (ball[i] == SELECTED)
            ball_array[i] = shop_ball_selected[i];
    }
    return (ball_array);
}

int UserLocalStore::get_first_launch() {
    UserDefault *def = UserDefault::sharedUserDefault();
    return (def->getIntegerForKey(FIRST_LAUNCH));
}

void UserLocalStore::set_first_launch() {
    UserDefault *def = UserDefault::sharedUserDefault();
    def->getIntegerForKey(FIRST_LAUNCH, 1);
}

int *UserLocalStore::get_asset_shooter() {
    int shooters[31];
    UserDefault *def = UserDefault::sharedUserDefault();

    for (int i = 0; i < 31; i++)
        shooters[i] = def->getIntegerForKey(shooter_ids[i]);
    return (shooters);
}

int *UserLocalStore::get_asset_ball() {
    int balls[8];
    UserDefault *def = UserDefault::sharedUserDefault();

    for (int i = 0; i < 8; i++)
        balls[i] = def->getIntegerForKey(ball_ids[i]);
    return (balls);
}

void UserLocalStore::store_asset_shooter(int shooters[31]) {

    UserDefault *def = UserDefault::sharedUserDefault();

    for (int i = 0; i < 31; i++) {
        def->setIntegerForKey(shooter_ids[i], shooters[i]);
        def->flush();
    }
}

void UserLocalStore::store_asset_ball(int balls[8]) {
    UserDefault *def = UserDefault::sharedUserDefault();

    for (int i = 0; i < 8; i++) {
        def->setIntegerForKey(ball_ids[i], balls[i]);
        def->flush();
    }
}

void UserLocalStore::init_asset_arrays() {
    int shooters[31] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        0, 0, 0, 0, 0, 0};
    int balls[8] = {2, 0, 0, 0, 0, 0, 0, 0};
    store_asset_ball(balls);
    store_asset_shooter(shooters);
}

