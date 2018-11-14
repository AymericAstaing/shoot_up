#ifndef __UserLocalStore_H__
#define __UserLocalStore_H__

#include <GUI/CCScrollView/CCTableViewCell.h>
#include "cocos2d.h"

USING_NS_CC;

/******************* ACHIEVEMENT CATEGORIES ***************/
#define TYPE_STARTER                        0
#define TYPE_POWER                          1
#define TYPE_MOVEMENT                       2
#define TYPE_DOUBLE                         3
#define TYPE_SHIELD                         4
#define TYPE_SPEED                          5
#define TYPE_SIDEWAY                        6

/******************* ASSET STATES ***************/
#define LOCK                                0
#define UNLOCK                              1
#define USED                                2

/******************* OTHER ***************/
#define EMPTY_ASSET                         "shop/empty_cell.png"


static const char *FIRST_LAUNCH = "FIRST_LAUNCH";

static const char *shooter_ids[31] = {
        "shooter_0", "shooter_1", "shooter_2", "shooter_3",
        "shooter_4", "shooter_5", "shooter_6", "shooter_7",
        "shooter_8", "shooter_9", "shooter_10", "shooter_11",
        "shooter_12", "shooter_13", "shooter_14", "shooter_15",
        "shooter_16", "shooter_17", "shooter_18", "shooter_19",
        "shooter_20", "shooter_21", "shooter_22", "shooter_23",
        "shooter_24", "shooter_25", "shooter_26", "shooter_27",
        "shooter_28", "shooter_29", "shooter_30"};

static const char *ball_ids[8] = {
        "ball_0", "ball_1", "ball_2", "ball_3",
        "ball_4", "ball_5", "ball_6", "ball_7",
};
static const char *shop_shooter_selected[31] = {
        "shooter_asset/shooter_selected/shooter_selected_0.png",
        "shooter_asset/shooter_selected/shooter_selected_1.png",
        "shooter_asset/shooter_selected/shooter_selected_2.png",
        "shooter_asset/shooter_selected/shooter_selected_3.png",
        "shooter_asset/shooter_selected/shooter_selected_4.png",
        "shooter_asset/shooter_selected/shooter_selected_5.png",
        "shooter_asset/shooter_selected/shooter_selected_6.png",
        "shooter_asset/shooter_selected/shooter_selected_7.png",
        "shooter_asset/shooter_selected/shooter_selected_8.png",
        "shooter_asset/shooter_selected/shooter_selected_9.png",
        "shooter_asset/shooter_selected/shooter_selected_10.png",
        "shooter_asset/shooter_selected/shooter_selected_11.png",
        "shooter_asset/shooter_selected/shooter_selected_12.png",
        "shooter_asset/shooter_selected/shooter_selected_13.png",
        "shooter_asset/shooter_selected/shooter_selected_14.png",
        "shooter_asset/shooter_selected/shooter_selected_15.png",
        "shooter_asset/shooter_selected/shooter_selected_16.png",
        "shooter_asset/shooter_selected/shooter_selected_17.png",
        "shooter_asset/shooter_selected/shooter_selected_18.png",
        "shooter_asset/shooter_selected/shooter_selected_19.png",
        "shooter_asset/shooter_selected/shooter_selected_20.png",
        "shooter_asset/shooter_selected/shooter_selected_21.png",
        "shooter_asset/shooter_selected/shooter_selected_22.png",
        "shooter_asset/shooter_selected/shooter_selected_23.png",
        "shooter_asset/shooter_selected/shooter_selected_24.png",
        "shooter_asset/shooter_selected/shooter_selected_25.png",
        "shooter_asset/shooter_selected/shooter_selected_26.png",
        "shooter_asset/shooter_selected/shooter_selected_27.png",
        "shooter_asset/shooter_selected/shooter_selected_28.png",
        "shooter_asset/shooter_selected/shooter_selected_29.png",
        "shooter_asset/shooter_selected/shooter_selected_30.png"};

static const char *shop_shooter_locked[31] = {
        "shooter_asset/shooter_locked/shooter_locked_0.png",
        "shooter_asset/shooter_locked/shooter_locked_1.png",
        "shooter_asset/shooter_locked/shooter_locked_2.png",
        "shooter_asset/shooter_locked/shooter_locked_3.png",
        "shooter_asset/shooter_locked/shooter_locked_4.png",
        "shooter_asset/shooter_locked/shooter_locked_5.png",
        "shooter_asset/shooter_locked/shooter_locked_6.png",
        "shooter_asset/shooter_locked/shooter_locked_7.png",
        "shooter_asset/shooter_locked/shooter_locked_8.png",
        "shooter_asset/shooter_locked/shooter_locked_9.png",
        "shooter_asset/shooter_locked/shooter_locked_10.png",
        "shooter_asset/shooter_locked/shooter_locked_11.png",
        "shooter_asset/shooter_locked/shooter_locked_12.png",
        "shooter_asset/shooter_locked/shooter_locked_13.png",
        "shooter_asset/shooter_locked/shooter_locked_14.png",
        "shooter_asset/shooter_locked/shooter_locked_15.png",
        "shooter_asset/shooter_locked/shooter_locked_16.png",
        "shooter_asset/shooter_locked/shooter_locked_17.png",
        "shooter_asset/shooter_locked/shooter_locked_18.png",
        "shooter_asset/shooter_locked/shooter_locked_19.png",
        "shooter_asset/shooter_locked/shooter_locked_20.png",
        "shooter_asset/shooter_locked/shooter_locked_21.png",
        "shooter_asset/shooter_locked/shooter_locked_22.png",
        "shooter_asset/shooter_locked/shooter_locked_23.png",
        "shooter_asset/shooter_locked/shooter_locked_24.png",
        "shooter_asset/shooter_locked/shooter_locked_25.png",
        "shooter_asset/shooter_locked/shooter_locked_26.png",
        "shooter_asset/shooter_locked/shooter_locked_27.png",
        "shooter_asset/shooter_locked/shooter_locked_28.png",
        "shooter_asset/shooter_locked/shooter_locked_29.png",
        "shooter_asset/shooter_locked/shooter_locked_30.png"};

static const char *shop_shooter_unlocked[31] = {
        "shooter_asset/shooter_unlocked/shooter_unlocked_0.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_1.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_2.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_3.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_4.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_5.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_6.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_7.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_8.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_9.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_10.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_11.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_12.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_13.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_14.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_15.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_16.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_17.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_18.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_19.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_20.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_21.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_22.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_23.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_24.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_25.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_26.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_27.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_28.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_29.png",
        "shooter_asset/shooter_unlocked/shooter_unlocked_30.png"};

static const char *shop_ball_locked[8] = {
        "bullets_asset/bullet_locked/bullet_locked_0.png",
        "bullets_asset/bullet_locked/bullet_locked_1.png",
        "bullets_asset/bullet_locked/bullet_locked_2.png",
        "bullets_asset/bullet_locked/bullet_locked_3.png",
        "bullets_asset/bullet_locked/bullet_locked_4.png",
        "bullets_asset/bullet_locked/bullet_locked_5.png",
        "bullets_asset/bullet_locked/bullet_locked_6.png",
        "bullets_asset/bullet_locked/bullet_locked_7.png"};

static const char *shop_ball_unlocked[8] = {
        "bullets_asset/bullet_unlocked/bullet_unlocked_0.png",
        "bullets_asset/bullet_unlocked/bullet_unlocked_1.png",
        "bullets_asset/bullet_unlocked/bullet_unlocked_2.png",
        "bullets_asset/bullet_unlocked/bullet_unlocked_3.png",
        "bullets_asset/bullet_unlocked/bullet_unlocked_4.png",
        "bullets_asset/bullet_unlocked/bullet_unlocked_5.png",
        "bullets_asset/bullet_unlocked/bullet_unlocked_6.png",
        "bullets_asset/bullet_unlocked/bullet_unlocked_7.png"};

static const char *shop_ball_selected[8] = {
        "bullets_asset/bullet_selected/bullet_selected_0.png",
        "bullets_asset/bullet_selected/bullet_selected_1.png",
        "bullets_asset/bullet_selected/bullet_selected_2.png",
        "bullets_asset/bullet_selected/bullet_selected_3.png",
        "bullets_asset/bullet_selected/bullet_selected_4.png",
        "bullets_asset/bullet_selected/bullet_selected_5.png",
        "bullets_asset/bullet_selected/bullet_selected_6.png",
        "bullets_asset/bullet_selected/bullet_selected_7.png"};


class UserLocalStore {

public:
    static void init_achievement_variables();

    static int get_current_shooter();

    static int get_current_ball();

    static int get_first_launch();

    static void set_first_launch();

    static void init_asset_arrays();

    static void store_shooter(int, int);

    static void store_ball(int, int);

    static int get_shooter(int);

    static int get_ball(int);

    static void check_for_shooter_unlocked(int);

    static void update_achievements(int, int, int);

    static void store_achievement_variable_float(const char *, float);

    static void store_asset_shooter(int[31]);

    static void store_asset_ball(int[8]);

    static int *get_asset_shooter();

    static int *get_asset_ball();

    static const char **get_final_shooter_array();

    static const char **get_final_ball_array();

    static const char *get_shooter_key_with_index(int);

    static const char *get_ball_key_with_index(int);

    static int get_achievement_variable(const char *);

    static float get_achievement_variable_float(const char *);

    static void store_achievement_variable(const char *, int);

    static int get_shooter_achievement_target(int);

    static int get_ball_achievement_target(int);

private:
};

#endif // __UserLocalStore_H__
