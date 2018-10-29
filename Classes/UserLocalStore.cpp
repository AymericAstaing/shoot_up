#include    "UserLocalStore.h"
#include    "GameScene.h"

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
    const char *KEY_SCORE = "SCORE";
    const char *KEY_POINT = "POINT";
    const char *KEY_SOUND = "SOUND";
    const char *KEY_POWER_LEVEL_PRICE = "POWER_LEVEL_PRICE";    //  UPGRADE PRICES
    const char *KEY_SPEED_LEVEL_PRICE = "SPEED_LEVEL_PRICE";
    const char *KEY_POWER_UP_ITEMS = "POWER_UP_ITEMS";
    const char *KEY_GAME_NBR = "GAME_NBR";
    const char *KEY_BLOCK_DESTROYED = "BLOCK_DESTROYED";
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
const char *KEY_GAME_DOUBLE_TANK = "GAME_DOUBLE";
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
    def->setFloatForKey(GLOBAL::KEY_SPEED_VALUE, 1); // car de 0.5 en 0.5
    def->setIntegerForKey(STARTER_TANK::KEY_BLOCK_STARTER_TANK, 0);
    def->setIntegerForKey(STARTER_TANK::KEY_ITEM_STARTER_TANK, 0);
    def->setIntegerForKey(STARTER_TANK::KEY_GAME_STARTER_TANK, 0);
    def->setIntegerForKey(POWER_TANK::KEY_BLOCK_POWER_TANK, 0);
    def->setIntegerForKey(POWER_TANK::KEY_GAME_POWER_TANK, 0);
    def->setIntegerForKey(MOVEMENT_TANK::KEY_ITEM_MOVEMENT_TANK, 0);
    def->setIntegerForKey(MOVEMENT_TANK::KEY_GAME_MOVEMENT_TANK, 0);
    def->setIntegerForKey(DOUBLE_TANK::KEY_BLOCK_DOUBLE_TANK, 0);
    def->setIntegerForKey(DOUBLE_TANK::KEY_GAME_DOUBLE_TANK, 0);
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

void
UserLocalStore::update_achievements(int shooter_type, int block_destroyed, int item_collected) {
    UserLocalStore::store_achievement_variable(GLOBAL::KEY_GAME_NBR,
                                               UserLocalStore::get_achievement_variable(
                                                       GLOBAL::KEY_GAME_NBR) +
                                               1);
    UserLocalStore::store_achievement_variable(GLOBAL::KEY_BLOCK_DESTROYED,
                                               UserLocalStore::get_achievement_variable(
                                                       GLOBAL::KEY_BLOCK_DESTROYED) +
                                               block_destroyed);
    UserLocalStore::store_achievement_variable(GLOBAL::KEY_POWER_UP_ITEMS,
                                               UserLocalStore::get_achievement_variable(
                                                       GLOBAL::KEY_POWER_UP_ITEMS) +
                                               item_collected);
    if (shooter_type == TYPE_STARTER) {
        store_achievement_variable(STARTER_TANK::KEY_BLOCK_STARTER_TANK,
                get_achievement_variable(STARTER_TANK::KEY_BLOCK_STARTER_TANK) +
                block_destroyed);
        store_achievement_variable(STARTER_TANK::KEY_ITEM_STARTER_TANK,
                get_achievement_variable(STARTER_TANK::KEY_ITEM_STARTER_TANK) +
                item_collected);
        store_achievement_variable(STARTER_TANK::KEY_GAME_STARTER_TANK,
                get_achievement_variable(STARTER_TANK::KEY_GAME_STARTER_TANK) +
                1);
    } else if (shooter_type == TYPE_POWER) {
        store_achievement_variable(POWER_TANK
        ::KEY_BLOCK_POWER_TANK,
                get_achievement_variable(POWER_TANK
        ::KEY_BLOCK_POWER_TANK) +
                block_destroyed);
        store_achievement_variable(POWER_TANK
        ::KEY_GAME_POWER_TANK,
                get_achievement_variable(POWER_TANK
        ::KEY_GAME_POWER_TANK) +
                1);
    } else if (shooter_type == TYPE_MOVEMENT) {
        store_achievement_variable(MOVEMENT_TANK
        ::KEY_ITEM_MOVEMENT_TANK,
                get_achievement_variable(MOVEMENT_TANK
        ::KEY_ITEM_MOVEMENT_TANK) +
                item_collected);
        store_achievement_variable(POWER_TANK
        ::KEY_GAME_POWER_TANK,
                get_achievement_variable(POWER_TANK
        ::KEY_GAME_POWER_TANK) +
                1);
    } else if (shooter_type == TYPE_DOUBLE) {
        store_achievement_variable(DOUBLE_TANK::KEY_BLOCK_DOUBLE_TANK, get_achievement_variable(DOUBLE_TANK
        ::KEY_BLOCK_DOUBLE_TANK) +
                block_destroyed);
        store_achievement_variable(DOUBLE_TANK
        ::KEY_GAME_DOUBLE_TANK,
                get_achievement_variable(DOUBLE_TANK
        ::KEY_GAME_DOUBLE_TANK) +
                1);
    } else if (shooter_type == TYPE_SHIELD) {
        store_achievement_variable(SHIELD_TANK
        ::KEY_ITEM_SHIELD_TANK,
                get_achievement_variable(SHIELD_TANK
        ::KEY_ITEM_SHIELD_TANK) +
                item_collected);
        store_achievement_variable(SHIELD_TANK
        ::KEY_GAME_SHIELD_TANK,
                get_achievement_variable(SHIELD_TANK
        ::KEY_GAME_SHIELD_TANK) +
                1);
    } else if (shooter_type == TYPE_SPEED) {
        store_achievement_variable(SPEED_TANK
        ::KEY_BLOCK_SPEED_TANK,
                get_achievement_variable(SPEED_TANK
        ::KEY_BLOCK_SPEED_TANK) +
                block_destroyed);
        store_achievement_variable(SPEED_TANK
        ::KEY_ITEM_SPEED_TANK,
                get_achievement_variable(SPEED_TANK
        ::KEY_ITEM_SPEED_TANK) +
                item_collected);
        store_achievement_variable(SPEED_TANK
        ::KEY_GAME_SPEED_TANK,
                get_achievement_variable(SPEED_TANK
        ::KEY_GAME_SPEED_TANK) +
                1);
    } else if (shooter_type == TYPE_SIDEWAY) {
        store_achievement_variable(SIDEWAY_TANK
        ::KEY_BLOCK_SIDEWAY_TANK,
                get_achievement_variable(SIDEWAY_TANK
        ::KEY_BLOCK_SIDEWAY_TANK) +
                block_destroyed);
        store_achievement_variable(SIDEWAY_TANK
        ::KEY_GAME_SIDEWAY_TANK,
                get_achievement_variable(SIDEWAY_TANK
        ::KEY_GAME_SIDEWAY_TANK) +
                1);
    } else {
        store_achievement_variable(TRIPLE_TANK
        ::KEY_BLOCK_TRIPLE_TANK,
                get_achievement_variable(TRIPLE_TANK
        ::KEY_BLOCK_TRIPLE_TANK) +
                block_destroyed);
        store_achievement_variable(TRIPLE_TANK
        ::KEY_ITEM_TRIPLE_TANK,
                get_achievement_variable(TRIPLE_TANK
        ::KEY_ITEM_TRIPLE_TANK) +
                item_collected);
        store_achievement_variable(TRIPLE_TANK
        ::KEY_GAME_TRIPLE_TANK,
                get_achievement_variable(TRIPLE_TANK
        ::KEY_GAME_TRIPLE_TANK) +
                1);
    }
    check_for_shooter_unlocked(shooter_type);
}

void UserLocalStore::check_for_shooter_unlocked(int shooter_type) {
    if (get_achievement_variable(GLOBAL::KEY_GAME_NBR) >= 75 && get_shooter(17 == 0))
        store_shooter(17, 1);
    if (get_achievement_variable(GLOBAL::KEY_SCORE) >= 50000 && get_shooter(14) == 0)
        store_shooter(14, 1);
    if (get_achievement_variable(GLOBAL::KEY_BLOCK_DESTROYED) >= 7500 && get_shooter(24) == 0)
        store_shooter(24, 1);
    if (get_achievement_variable(GLOBAL::KEY_GAME_NBR) >= 200 && get_shooter(27) == 0)
        store_shooter(27, 1);
    if (get_achievement_variable(GLOBAL::KEY_GAME_NBR) == 30 && get_ball(1) == 0)
        store_ball(1, 1);
    if (get_achievement_variable(GLOBAL::KEY_GAME_NBR) == 100 && get_ball(6) == 0)
        store_ball(6, 1);
    if (get_achievement_variable(GLOBAL::KEY_GAME_NBR) == 150 && get_ball(3) == 0)
        store_ball(3, 1);
    if (get_achievement_variable(GLOBAL::KEY_BLOCK_DESTROYED) >= 500 && get_ball(2) == 0)
        store_ball(2, 1);
    if (get_achievement_variable(GLOBAL::KEY_POWER_UP_ITEMS) >= 200 && get_ball(4) == 0)
        store_ball(4, 1);
    if (get_achievement_variable(GLOBAL::KEY_SCORE) >= 20000 && get_ball(7) == 0)
        store_ball(7, 1);
    if (get_achievement_variable(GLOBAL::KEY_SCORE) >= 10000 && get_ball(5) == 0)
        store_ball(5, 1);
    if (shooter_type == TYPE_STARTER) {
        if (get_achievement_variable(STARTER_TANK::KEY_GAME_STARTER_TANK) == 30 &&
                                                                             get_shooter(3) == 0)
        store_shooter(3, 1);
        if (get_achievement_variable(STARTER_TANK::KEY_GAME_STARTER_TANK) == 100 &&
                                                                             get_shooter(4) == 0)
        store_shooter(4, 1);
        if (get_achievement_variable(STARTER_TANK::KEY_BLOCK_STARTER_TANK) >= 300 &&
                                                                              get_shooter(1) == 0) {
            store_shooter(1, 1);
        }
        if (get_achievement_variable(STARTER_TANK::KEY_ITEM_STARTER_TANK) >= 50 &&
                                                                             get_shooter(2) == 0)
        store_shooter(2, 1);
        if (get_achievement_variable(STARTER_TANK::KEY_ITEM_STARTER_TANK) >= 100 &&
                                                                             get_shooter(5) == 0)
        store_shooter(5, 1);
    } else if (shooter_type == TYPE_POWER) {
        if (get_achievement_variable(POWER_TANK::KEY_GAME_POWER_TANK) == 150 && get_shooter(8) == 0)
        store_shooter(8, 1);
        if (get_achievement_variable(POWER_TANK::KEY_GAME_POWER_TANK) == 300 && get_shooter(9) == 0)
        store_shooter(9, 1);
        if (get_achievement_variable(POWER_TANK::KEY_BLOCK_POWER_TANK) >= 1000 &&
                                                                          get_shooter(7) == 0)
        store_shooter(7, 1);
        if (get_achievement_variable(POWER_TANK::KEY_BLOCK_POWER_TANK) >= 5000 &&
                                                                          get_shooter(10) == 0)
        store_shooter(10, 1);
    } else if (shooter_type == TYPE_MOVEMENT) {
        if (get_achievement_variable(MOVEMENT_TANK::KEY_GAME_MOVEMENT_TANK) == 50 &&
                                                                               get_shooter(12) == 0)
        store_shooter(12, 1);
        if (get_achievement_variable(MOVEMENT_TANK::KEY_ITEM_MOVEMENT_TANK) >= 100 &&
                                                                               get_shooter(13) == 0)
        store_shooter(13, 1);
    } else if (shooter_type == TYPE_DOUBLE) {
        if (get_achievement_variable(DOUBLE_TANK::KEY_GAME_DOUBLE_TANK) == 200 &&
                                                                           get_shooter(15) == 0)
        store_shooter(15, 1);
        if (get_achievement_variable(DOUBLE_TANK::KEY_BLOCK_DOUBLE_TANK) >= 20000 &&
                                                                            get_shooter(16) == 0)
        store_shooter(16, 1);
    } else if (shooter_type == TYPE_SHIELD) {
        if (get_achievement_variable(SHIELD_TANK::KEY_ITEM_SHIELD_TANK) >= 200 &&
                                                                           get_shooter(18) == 0)
        store_shooter(18, 1);
        if (get_achievement_variable(SHIELD_TANK::KEY_GAME_SHIELD_TANK) == 200 &&
                                                                           get_shooter(19) == 0)
        store_shooter(19, 1);
    } else if (shooter_type == TYPE_SPEED) {
        if (get_achievement_variable(SPEED_TANK::KEY_GAME_SPEED_TANK) == 100 &&
                                                                         get_shooter(21) == 0)
        store_shooter(21, 1);
        if (get_achievement_variable(SPEED_TANK::KEY_BLOCK_SPEED_TANK) >= 15000 &&
                                                                          get_shooter(23) == 0)
        store_shooter(23, 1);
        if (get_achievement_variable(SPEED_TANK::KEY_ITEM_SPEED_TANK) >= 200 &&
                                                                         get_shooter(24) == 0)
        store_shooter(24, 1);
    } else if (shooter_type == TYPE_SIDEWAY) {
        if (get_achievement_variable(SIDEWAY_TANK::KEY_GAME_SIDEWAY_TANK) == 200 &&
                                                                             get_shooter(25) == 0)
        store_shooter(25, 1);
        if (get_achievement_variable(SIDEWAY_TANK::KEY_BLOCK_SIDEWAY_TANK) >= 20000 &&
                                                                              get_shooter(26) == 0)
        store_shooter(26, 1);
    } else {
        if (get_achievement_variable(TRIPLE_TANK::KEY_GAME_TRIPLE_TANK) == 300 &&
                                                                           get_shooter(28) == 0)
        store_shooter(28, 1);
        if (get_achievement_variable(TRIPLE_TANK::KEY_ITEM_TRIPLE_TANK) >= 30000 &&
                                                                           get_shooter(29) == 0)
        store_shooter(29, 1);
        if (get_achievement_variable(TRIPLE_TANK::KEY_BLOCK_TRIPLE_TANK) >= 300 &&
                                                                            get_shooter(30) == 0)
        store_shooter(30, 1);
    }
}

void UserLocalStore::store_achievement_variable(const char *key, int value) {
    UserDefault *def = UserDefault::sharedUserDefault();
    def->setIntegerForKey(key, value);
    def->flush();
}

void UserLocalStore::store_achievement_variable_float(const char *key, float value) {
    UserDefault *def = UserDefault::sharedUserDefault();
    def->setFloatForKey(key, value);
    def->flush();
}

float UserLocalStore::get_achievement_variable_float(const char *key) {
    UserDefault *def = UserDefault::sharedUserDefault();
    return (def->getFloatForKey(key));
}

int UserLocalStore::get_achievement_variable(const char *key) {
    UserDefault *def = UserDefault::sharedUserDefault();
    return (def->getIntegerForKey(key));
}

int UserLocalStore::get_current_shooter() {
    int *shooter = UserLocalStore::get_asset_shooter();

    for (int i = 0; i < 31; i++) {
        if (shooter[i] == SELECTED)
            return (i);
    }
    return (-1);
}

void UserLocalStore::store_shooter(int index, int value) {
    UserDefault *def = UserDefault::sharedUserDefault();
    def->setIntegerForKey(shooter_ids[index], value);
    def->flush();
}

void UserLocalStore::store_ball(int index, int value) {
    UserDefault *def = UserDefault::sharedUserDefault();
    def->setIntegerForKey(ball_ids[index], value);
    def->flush();
}

int UserLocalStore::get_shooter(int index) {
    UserDefault *def = UserDefault::sharedUserDefault();
    return (def->getIntegerForKey(shooter_ids[index]));
}

int UserLocalStore::get_ball(int index) {
    UserDefault *def = UserDefault::sharedUserDefault();
    return (def->getIntegerForKey(ball_ids[index]));
}

int UserLocalStore::get_current_ball() {
    int *ball = UserLocalStore::get_asset_ball();

    for (int i = 0; i < 8; i++) {
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
            return (STARTER_TANK
            ::KEY_BLOCK_STARTER_TANK);
        case 1:
            return (STARTER_TANK
            ::KEY_ITEM_STARTER_TANK);
        case 2:
            return (STARTER_TANK
            ::KEY_GAME_STARTER_TANK);
        case 3:
            return (STARTER_TANK
            ::KEY_GAME_STARTER_TANK);
        case 4:
            return (STARTER_TANK
            ::KEY_ITEM_STARTER_TANK);
        case 5:
            return (GLOBAL::KEY_POWER_LEVEL);
        case 6:
            return (POWER_TANK
            ::KEY_BLOCK_POWER_TANK);
        case 7:
            return (POWER_TANK
            ::KEY_GAME_POWER_TANK);
        case 8:
            return (POWER_TANK
            ::KEY_GAME_POWER_TANK);
        case 9:
            return (POWER_TANK
            ::KEY_BLOCK_POWER_TANK);
        case 10:
            return (GLOBAL::KEY_POWER_UP_ITEMS);
        case 11:
            return (MOVEMENT_TANK
            ::KEY_GAME_MOVEMENT_TANK);
        case 12:
            return (MOVEMENT_TANK
            ::KEY_ITEM_MOVEMENT_TANK);
        case 13:
            return (GLOBAL::KEY_SCORE);
        case 14:
            return (DOUBLE_TANK
            ::KEY_GAME_DOUBLE_TANK);
        case 15:
            return (DOUBLE_TANK
            ::KEY_BLOCK_DOUBLE_TANK);
        case 16:
            return (GLOBAL::KEY_GAME_NBR);
        case 17:
            return (SHIELD_TANK
            ::KEY_ITEM_SHIELD_TANK);
        case 18:
            return (SHIELD_TANK::KEY_GAME_SHIELD_TANK);
        case 19:
            return (GLOBAL::KEY_SPEED_LEVEL);
        case 20:
            return (SPEED_TANK::KEY_GAME_SPEED_TANK);
        case 21:
            return (SPEED_TANK
            ::KEY_ITEM_SPEED_TANK);
        case 22:
            return (SPEED_TANK
            ::KEY_BLOCK_SPEED_TANK);
        case 23:
            return (GLOBAL::KEY_BLOCK_DESTROYED);
        case 24:
            return (SIDEWAY_TANK
            ::KEY_GAME_SIDEWAY_TANK);
        case 25:
            return (SIDEWAY_TANK
            ::KEY_BLOCK_SIDEWAY_TANK);
        case 26:
            return (GLOBAL::KEY_GAME_NBR);
        case 27:
            return (TRIPLE_TANK
            ::KEY_GAME_TRIPLE_TANK);
        case 28:
            return (TRIPLE_TANK
            ::KEY_BLOCK_TRIPLE_TANK);
        case 29:
            return (TRIPLE_TANK
            ::KEY_ITEM_TRIPLE_TANK);
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

    shooter_array = new const char *[34];
    int asset_shooter_index = 0;
    int *shooter = UserLocalStore::get_asset_shooter();
    for (int i = 0; i < 34; i++) {
        if (i == 11 || i == 25 || i == 26) {
            shooter_array[i] = "shop/empty_cell.png";
        } else {
            if (shooter[asset_shooter_index] == LOCKED)
                shooter_array[i] = shop_shooter_locked[asset_shooter_index];
            else if (shooter[asset_shooter_index] == UNLOCKED)
                shooter_array[i] = shop_shooter_unlocked[asset_shooter_index];
            else if (shooter[asset_shooter_index] == SELECTED)
                shooter_array[i] = shop_shooter_selected[asset_shooter_index];
            asset_shooter_index++;
        }
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
    def->setIntegerForKey(FIRST_LAUNCH, 1);
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
    int shooters[31] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int balls[8] = {2, 0, 0, 0, 0, 0, 0, 0};
    store_asset_ball(balls);
    store_asset_shooter(shooters);
}