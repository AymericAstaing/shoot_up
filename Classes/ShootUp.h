#ifndef __SHOOTUP_H__
#define __SHOOTUP_H__

#include "cocos2d.h"

USING_NS_CC;

/********************* GLOBAL VARIABLES ***********************/
#define WIDTH                           0
#define HEIGHT                          1
#define EMPTY_VALUE                     -1
#define GAME_MENU_NAME                  "S H O O T  U P !"
#define NBR_LINE_BEFORE_DOWN_SCALING    8
#define APP_INITIAL_OPEN                0
#define APP_ALREADY_OPEN                1
#define NOT_FROM_SHOP                   0
#define INCREASE_POINTS_FACTOR          15
#define DEFAULT_CHAR_LENGHT             10
#define SOUND_ON                        0
#define SOUND_OFF                       1

/********************* FONT ***********************/
#define FIRE_UP_FONT_NAME               "fonts/fire_up.ttf"
#define FIRE_UP_FONT_NAME_NUMBERS       "fonts/numbers.ttf"

/********************* END OF GAME MENUS ***********************/
#define POPUP_POWER                     "pop_up/power.png"
#define POPUP_POWER_SELECTED            "pop_up/power_selected.png"
#define POPUP_SPEED                     "pop_up/speed.png"
#define POPUP_SPEED_SELECTED            "pop_up/speed_selected.png"
#define BONUS_X2                        "end_of_game_menu/bonusx2.png"
#define REPLAY_TEXTURE                  "end_of_game_menu/replay_btn.png"
#define SHARE_TEXTURE                   "end_of_game_menu/share_btn.png"
#define RATE_TEXTURE                    "end_of_game_menu/rate_btn.png"
#define BACKGROUND_TEXTURE              "end_of_game_menu/background.png"
#define NEXT_BUTTON_TEXTURE             "continue_menu/continue_btn.png"
#define DEFAULT_CONTINUE_TEXTURE        "continue_0.png"

/********************* MAIN GAME MENU ***********************/
#define SURCLASSEMENT                   "SURCLASSEMENT"
#define SHOP_ASSET_SELECTED(X)          (X == 0 ? SHOP_SELECTED : SHOP_SELECTED_NEW)
#define SHOP_ASSET_UNSELECTED(X)        (X == 0 ? SHOP_UNSELECTED : SHOP_UNSELECTED_NEW)
#define OPTIONS_HIDE                    0
#define OPTIONS_DISPLAYED               1
#define SURCLASSEMENT_UNSELECTED        "menu/surclassement.png"
#define SURCLASSEMENT_SELECTED          "menu/surclassement_selected.png"
#define OPTIONS_SOUND_ON                "menu/options/sound_on.png"
#define OPTIONS_SOUND_OFF               "menu/options/sound_off.png"
#define OPTIONS_TUTO                    "menu/options/tuto.png"
#define OPTIONS                         "menu/options.png"
#define STATS                           "menu/stats.png"
#define HAND                            "menu/play_anim_hand.png"
#define HAND_RAIL                       "menu/play_anim.png"
#define BEST_IMG                        "menu/best_score.png"
#define SHOP_UNSELECTED                 "menu/shop.png"
#define SHOP_SELECTED                   "menu/shop_selected.png"
#define SHOP_UNSELECTED_NEW             "menu/shop_new.png"
#define SHOP_SELECTED_NEW               "menu/shop_selected_new.png"

/********************* HUD (GAME FLOW) ***********************/
#define BEST_SCORE_IMG                  "hud/best_img.png"
#define HIT_CIRCLE                      "hud/hit_circle.png"
#define BONUS_MESSAGE_SPEED             "hud/mega_speed.png"
#define BONUS_MESSAGE_POWER             "hud/mega_power.png"
#define MESSAGE_SPEED                   0
#define MESSAGE_POWER                   1
#define MESSAGE_BULLETS                 2

/********************* TEXT SIZE ***********************/
#define SIZE_GAME_NAME                  85
#define SIZE_BEST_SCORE_MENU            30
#define SIZE_SURCLASSEMENT_TXT_BTN_MENU 20
#define SIZE_UPGRADE_VALUES_MENU        20
#define SIZE_CURRENT_SCORE_END_MENU     60
#define SIZE_EARNED_POINTS_END_MENU     25
#define SIZE_UPGRADE_PRICE_END_MENU     25
#define SIZE_CURRENT_LEVEL_END_MENU     25
#define SIZE_NAME_ITEMS_END_MENU        24

/********************* SPLASH_SCREEN ***********************/
#define SPLASH_BACKGROUND_TEXTURE       "splash_screen/splash_background.png"
#define SPLASH_TRIPLEA_LOGO             "splash_screen/tripleAlogo.png"


/********************* STANDARD SQUARE ***********************/
#define DEFAULT_SQUARE_TEXTURE          "green.png"
#define SQUARE_SIZE_4_WIDTH             3.95
#define SQUARE_SIZE_5_WIDTH             4.95
#define SQUARE_SIZE_4_HEIGHT            7.5
#define SQUARE_SIZE_5_HEIGHT            9.5

/********************* UTILS ***********************/
#define VALUE_SIMPLE                    0
#define VALUE_WITH_POINT                1
#define VALUE_WITH_PLUS                 2
#define VALUE_BONUS_COMMENT             3

/********************* TAGS ***********************/
#define BULLET_BATCH_TAG                12
#define POWER_LEVEL_BTN_TAG             34
#define SPEED_LEVEL_BTN_TAG             35
#define MAIN_MENU_TAG                   36
#define STAR_BONUS_TAG                  7
#define LINE_BATCH_TAG                  42
#define SHOOTER_ARRAY_TAG               0
#define BALL_ARRAY_TAG                  1
#define PROGRESS_CONTENT_TAG            37
#define PROGRESS_BORDER_TAG             38

/******************* PLIST SPRITESHEETS ***************/
#define PARTICLE_ANIM_PLIST             "spritesheet/hit.plist"
#define BLOCK_COLOR_PLIST               "spritesheet/block_color.plist"
#define BULLETS_PLIST                   "spritesheet/bullets_game.plist"
#define CONTINUE_PLIST                  "spritesheet/continue_animation.plist"
#define BONUS_POWER_PLIST               "spritesheet/bonus_power.plist"
#define BONUS_SPEED_PLIST               "spritesheet/bonus_speed.plist"
#define BONUS_BULLET_PLIST              "spritesheet/bonus_bullet.plist"
#define SPRITESHEET_BULLETS             "spritesheet/bullets_game.png"
#define SPRITESHEET_BLOCK_COLORS        "spritesheet/block_color.png"

/******************* SOUND FILES ***************/
#define SOUND_LAUNCH                    "sound/bullet_launch.wav"
#define SOUND_HITED                     "sound/square_hited.wav"
#define SOUND_EXPLODE                   "sound/square_explode.wav"

/******************* SCALES ***************/
#define NORMAL_BULLET_SCALE             1.0f
#define BIG_BULLET_SCALE                1.3f
#define CIRCLE_SCALE                    0.5f

/******************* ACHIEVEMENT CATEGORIES ***************/
#define STARTER_TANK                    0
#define POWER_TANK                      1
#define MOVEMENT_TANK                   2
#define DOUBLE_TANK                     3
#define SHIELD_TANK                     4
#define SPEED_TANK                      5
#define SIDEWAY_TANK                    6
#define TRIPLE_TANK                     7

/******************* ASSET STATES ***************/
#define LOCK                            0
#define UNLOCK                          1
#define USED                            2

/******************* ADS (ADMOB) ***************/
#define GAME_DURATION_LIMIT_FOR_ADS     30.0f
#define END_OF_GAME_AD                  "end_of_game"
#define TEST_AD                         "test_ad"
#define CONTINUE_REWARD_AD              "continue_reward"
#define CONTINUE_REWARD_AD_TEST         "continue_reward_test"
#define BONUSX2_AD                      "bonusx2"
#define BONUSX2_AD_TEST                 "bonusx2_test"

/******************* SHOT MANAGMENT ***************/
#define BULLET_SIDE_LEFT                0
#define BULLET_SIDE_RIGHT               1
#define NORMAL_LAUNCH                   0
#define BONUS_LAUNCH_LEFT               1
#define BONUS_LAUNCH_RIGHT              2
#define TRIPLE_LAUNCH_LEFT              3
#define TRIPLE_LAUNCH_CENTER            4
#define TRIPLE_LAUNCH_RIGHT             5
#define DOUBLE_LAUNCH_LEFT              6
#define DOUBLE_LAUNCH_RIGHT             7
#define SIDEWAY_LAUNCH_LEFT             8
#define SIDEWAY_LAUNCH_CENTER           9
#define SIDEWAY_LAUNCH_RIGHT            10

/******************* BONUS ***************/
#define MIN_LINE_BEFORE_BONUS_SPAWN     5
#define STAR_BONUS_TEXTURE              "spritesheet/star_bonus.png"
#define DEFAULT_BONUS_SPEED_TEXTURE     "bonus_speed_0.png"
#define DEFAULT_BONUS_POWER_TEXTURE     "bonus_power_0.png"
#define DEFAULT_BONUS_BULLET_TEXTURE    "bonus_bullet_0.png"
#define SHIELD_RECT_TEXTURE             "player_effect/shield_effect.png"
#define SPEED_RECT                      "player_effect/speed_effect.png"
#define POWER_RECT                      "player_effect/power_effect.png"
#define BULLET_RECT                     "player_effect/bullet_effect.png"
#define BONUS_TIME_LIMIT                5.0f
#define BONUS_TIME_MIDLE                2.5f
#define BONUS_BULLET                    0
#define BONUS_POWER                     1
#define BONUS_SPEED                     2
#define BONUS_HIDE                      0
#define BONUS_IN_GAME                   1
#define RECT_BULLET                     0
#define RECT_POWER                      1
#define RECT_SPEED                      2

/******************* GAME STATES ***************/
#define MENU                            0
#define GAME_RUNNING                    1
#define GAME_END                        2
#define RESUME                          3

/******************* GAME PLAY MANAGMENT ***************/
#define LINE_SPEED                      4
#define SHOOTER_NEVER_UPDATED(X, Y)     ((X + Y) == 2 ? true : false)
#define H_FACTORE_STARTUP_STRUCT(X)     (X < 25 ? 25 : X)
#define DEFAULT_BULLET_NBR              16 //default bullet nbr shooted in 2sec (middle time between 2 lines, + donne des points plus élevés vice versa)

/******************* LINE INIT AND MANAGMENT  ***************/
#define H_LIMIT_STARTUP_3               819
#define H_LIMIT_STARTUP_4               2829
#define SQUARE_SIZE_LINE_OF_4           4
#define SQUARE_SIZE_LINE_OF_5           5
#define COMPLEX_STRUCT_NBR              6


/******************* LINE TYPE INDEX ***************/
#define LINE_TYPE_STARTUP_2             0
#define LINE_TYPE_STARTUP_3             1
#define LINE_TYPE_STARTUP_4             2
#define LINE_TYPE_STARTUP_5             3
#define LINE_TYPE_SIMPLE_OF_4           4
#define LINE_TYPE_SIMPLE_OF_5           5
#define LINE_TYPE_COMPLEX_0             6
#define LINE_TYPE_COMPLEX_1             7
#define LINE_TYPE_COMPLEX_2             8
#define LINE_TYPE_COMPLEX_3             9
#define LINE_TYPE_COMPLEX_4             10
#define LINE_TYPE_COMPLEX_5             11
#define LINE_TYPE_COMPLEX_6             12
#define LINE_TYPE_COMPLEX_7             13

/******************* ACHIEVEMENT VARIABLES KEY ***************/
#define POWER_LEVEL                     "POWER_LEVEL"
#define APP_FIRST_OPEN                  "FIRST_OPEN"
#define SPEED_LEVEL                     "SPEED_LEVEL"
#define POWER_VALUE                     "POWER_VALUE"
#define SPEED_VALUE                     "SPEED_VALUE"
#define NEW_SHOP_ELEMENT                "NEW_SHOP_ELEMENT"
#define POWER_LEVEL_PRICE               "POWER_LEVEL_PRICE"
#define SPEED_LEVEL_PRICE               "SPEED_LEVEL_PRICE"
#define SCORE                           "SCORE"
#define SOUND                           "SOUND"
#define POINT                           "POINT"
#define FROM_SHOP                       "FROM_SHOP"

/******************* COLORS ***************/
#define BASIC_COLOR_GREEN               "green.png"
#define BASIC_COLOR_RED                 "red.png"
#define BASIC_COLOR_YELLOW              "yellow.png"
#define BASIC_COLOR_ORANGE              "orange.png"

/******************* DEFAULT COLOR CODE ***************/
#define GREEN                           3
#define YELLOW                          2
#define ORANGE                          1
#define RED                             0


class ShootUp {

public:

private:
};

#endif // __SHOOTUP_H__