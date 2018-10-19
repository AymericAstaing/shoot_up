#ifndef __UTILS_H__
#define __UTILS_H__

#include "cocos2d.h"

USING_NS_CC;

static const char *shooters[31] = {"shooter_asset/game_shooter/shooter_0.png",
                                   "shooter_asset/game_shooter/shooter_1.png",
                                   "shooter_asset/game_shooter/shooter_2.png",
                                   "shooter_asset/game_shooter/shooter_3.png",
                                   "shooter_asset/game_shooter/shooter_4.png",
                                   "shooter_asset/game_shooter/shooter_5.png",
                                   "shooter_asset/game_shooter/shooter_6.png",
                                   "shooter_asset/game_shooter/shooter_7.png",
                                   "shooter_asset/game_shooter/shooter_8.png",
                                   "shooter_asset/game_shooter/shooter_9.png",
                                   "shooter_asset/game_shooter/shooter_10.png",
                                   "shooter_asset/game_shooter/shooter_11.png",
                                   "shooter_asset/game_shooter/shooter_12.png",
                                   "shooter_asset/game_shooter/shooter_13.png",
                                   "shooter_asset/game_shooter/shooter_14.png",
                                   "shooter_asset/game_shooter/shooter_15.png",
                                   "shooter_asset/game_shooter/shooter_16.png",
                                   "shooter_asset/game_shooter/shooter_17.png",
                                   "shooter_asset/game_shooter/shooter_18.png",
                                   "shooter_asset/game_shooter/shooter_19.png",
                                   "shooter_asset/game_shooter/shooter_20.png",
                                   "shooter_asset/game_shooter/shooter_21.png",
                                   "shooter_asset/game_shooter/shooter_22.png",
                                   "shooter_asset/game_shooter/shooter_23.png",
                                   "shooter_asset/game_shooter/shooter_24.png",
                                   "shooter_asset/game_shooter/shooter_25.png",
                                   "shooter_asset/game_shooter/shooter_26.png",
                                   "shooter_asset/game_shooter/shooter_27.png",
                                   "shooter_asset/game_shooter/shooter_28.png",
                                   "shooter_asset/game_shooter/shooter_29.png",
                                   "shooter_asset/game_shooter/shooter_30.png"};

static const char *balls[8] = {"bullets_asset/game_bullet/bullet_0.png",
                               "bullets_asset/game_bullet/bullet_1.png",
                               "bullets_asset/game_bullet/bullet_2.png",
                               "bullets_asset/game_bullet/bullet_3.png",
                               "bullets_asset/game_bullet/bullet_4.png",
                               "bullets_asset/game_bullet/bullet_5.png",
                               "bullets_asset/game_bullet/bullet_6.png",
                               "bullets_asset/game_bullet/bullet_7.png"};


class Utils {

public:
    static float        line_speed_converter(float);
    static int*         get_distribution_points(int*, int, int);
    static int          get_random_number(int, int);
    static bool         is_into_list(int*, int, int);
    static int*         get_complex_distribution_points(int*, int, int, int);
    static int*         get_simple_distribution_points(int*, int, int, int);
    static int          array_sum(int*,int);
    static const char*  get_color(int);
    static int          get_shooter_type(int);
    static int*         get_container_range_research(int);
    static Sprite*      get_player();
    static float        get_spawn_y(int, int, float[2]);
    static int          get_random_line_type();
    static Vec2         get_coordinate_from_id(int, int);

private:
};

#endif // __UTILS_H__
