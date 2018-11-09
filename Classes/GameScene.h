#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include    <vector>
#include    <cocos2d.h>
#include    <cocos-ext.h>
#include    <GUI/CCScrollView/CCTableViewCell.h>
#include    <audio/android/jni/cddandroidAndroidJavaEngine.h>
#include    "GridView.h"
#include    "Square.h"
#include    "ShootUp.h"
#include    "Circle.h"
#include    "Bullet.h"
#include    "Line.h"

static const char *explode_plist[4] = {"spritesheet/explode_square_red.plist",
                                       "spritesheet/explode_square_orange.plist",
                                       "spritesheet/explode_square_yellow.plist",
                                       "spritesheet/explode_square_green.plist"};

static const char *explode_bonus_plist[3] = {"spritesheet/explode_bonus_bullet.plist",
                                       "spritesheet/explode_bonus_power.plist",
                                       "spritesheet/explode_bonus_speed.plist"};

static const char *default_bonus_texture[3] = {"bonus_bullet_0.png",
                                               "bonus_power_0.png",
                                               "bonus_speed_0.png"};

static const float speed_price[5] = {50, 100, 850, 1700, 7500};
static const float power_price[5] = {50, 150, 700, 1600, 7200};

static const int BULLET_SHOOT[3][3] = {{DOUBLE_LAUNCH_LEFT, DOUBLE_LAUNCH_RIGHT},
                                            {SIDEWAY_LAUNCH_LEFT, SIDEWAY_LAUNCH_CENTER, SIDEWAY_LAUNCH_RIGHT},
                                            {TRIPLE_LAUNCH_LEFT, TRIPLE_LAUNCH_CENTER, TRIPLE_LAUNCH_RIGHT}};

using namespace cocos2d;
using namespace CocosDenshion;

class GameScene : public cocos2d::Scene {

private:
    Line**              pool_container;
    Bullet**            bullet_container;
    SpriteBatchNode*    bullet_batch_node;
    Sprite*             player;
    Sprite**            bonus_container;
    Sprite**            rect_container;
    Circle**            pool_circle;
    MenuItemImage*      back_to_main;
    MenuItemImage*      rate;
    MenuItemImage*      share;
    Label*              score;
    Sprite*             sound;
    Sprite*             best_img;
    Sprite*             shield_rect;
    Sprite*             tuto;
    Sprite*             next_button;
    Sprite*             continue_button;
    Menu*               game_menu;
    SimpleAudioEngine*  game_audio;
    MenuItemImage*      options_btn;
    MenuItemFont*       menu_title;
    MenuItemFont*       menu_surclassement_txt;
    MenuItemImage*      menu_surclassement_img;
    MenuItemImage*      menu_shop_img;
    MenuItemImage*      menu_best_img;
    MenuItemFont*       menu_best_txt;
    MenuItemFont*       menu_power_level;
    MenuItemFont*       menu_speed_level;
    MenuItemImage*      menu_anim_img_hand;
    MenuItemImage*      menu_anim_img;
    MenuItemImage*      menu_stats_img;
    Menu*               end_menu;
    Layer*              stats;
    Sequence*           wait_sequence;
    float               bonus_time = 0;
    bool                bonus_selected = false;
    bool                bonus_displayed = false;
    bool                rect_animated = false;
    bool                shield_live_used = false;
    bool                star_bonus_active = false;
    bool                game_already_resumed = false;
    int                 star_line_id = -1;
    int                 bonus_active = 0;
    int                 bonus_id = -1;
    float               x_screen;
    float               y_screen;
    int                 game_score;
    int                 game_shooter_type = 0;
    int                 *active_lines;
    int                 options_state = 0;
    int                 next_bonus_spawn = 0;
    int                 bullet_state;
    int                 game_state;
    int                 game_block_destroyed = 0;
    int                 game_power_up_collected = 0;
    int                 current_factor_h = 0;
    int                 shooter_never_updated = 0;

    /******************* LINE MANAGMENT ***************/
    int                 CURRENT_LINE_ID;
    int                 NEXT_LINE_ID;
    int                 LINE_GENERATED;
    float               NEW_SPAWN_Y;

    /******************* SOUND MANAGMENT ***************/
    int                 hit_played = 0;
    int                 launch_played = 0;
    bool                sound_activated = true;


public:
    CREATE_FUNC(GameScene);
    static cocos2d::Scene*  createScene();
    virtual bool            init();
    void                    store_active_line(int);
    void                    remove_active_line(int);
    void                    init_bonus_components();
    void                    reset_arrays();
    void                    destroy_complete_line(int, float);
    void                    main_menu_coming_animation();
    void                    update_game_score(int);
    float                   get_shoot_interval();
    bool                    is_touch_on_player_zone(Vec2);
    void                    show_bonus_particle_explode(Vec2);
    void                    check_full_destruction_bonus(Line*, int);
    void                    show_destruction_bonus(int, int);
    void                    check_hit_color_change(Line*, Square*);
    void                    play_bullet_impact();
    void                    play_square_explode();
    void                    menuCloseCallback(cocos2d::Ref*);
    void                    show_particle(Vec2, Square*);
    void                    bonus_collision();
    void                    load_bonus();
    void                    destroy_all_lines();
    void                    remove_bonus();
    void                    move_bonus();
    void                    bonus_managment();
    void                    check_first_open();
    void                    active_bonus();
    void                    move_circles();
    void                    scale_animation();
    void                    play_bullet_sound();
    void                    show_particle_explode(Vec2, int);
    void                    start_game();
    void                    score_animation();
    bool                    is_sound_button_touched(Vec2);
    bool                    is_next_button_touched(Vec2);
    bool                    is_continue_button_touched(Vec2);
    void                    init_options_menu();
    void                    init_ui_components();
    int                     get_next_line_type();
    void                    end_of_game();
    void                    init_listeners();
    void                    play(cocos2d::Ref *);
    int                     get_h_value();
    void                    resume_game();
    void                    run_game_loop();
    void                    stop_game_loop();
    void                    move_active_lines();
    void                    check_into_line();
    void                    increase_speed(Label*, Label*, Label *);
    void                    increase_power(Label*, Label*, Label *);
    void                    check_lines_out();
    bool                    point_into_square(Square*, Vec2);
    void                    check_bullet_contact();
    void                    check_player_collision();
    void                    value_to_update();
    void                    back_to_menu(cocos2d::Ref *);
    void                    update(float) override;
    void                    display_end_menu();
    void                    surclassement(cocos2d::Ref *);
    int                     get_next_line_id(int);
    void                    init_pool_objects();
    void                    manage_options();
    void                    run_start_animation();
    void                    options(cocos2d::Ref *);
    void                    shop(cocos2d::Ref *);
    void                    launch_bullet(float);
    void                    check_first_launch();
    void                    init_main_variable();
    Menu*                   get_main_menu();
    Menu*                   get_end_game_menu();
    void                    onTouchMoved(Touch*, Event*);
    bool                    onTouchBegan(Touch*, Event*);
    void                    show_destruction_circle(Vec2);
    void                    start_bullet_shoot();
    void                    stop_bullet_shoot();
};

#endif // __GameScene_SCENE_H__
