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
#include    "Background.h"
#include    "Bullet.h"
#include    "Line.h"

static const char *explode_plist[4] = {"spritesheet/explode_square_red.plist",
                                       "spritesheet/explode_square_orange.plist",
                                       "spritesheet/explode_square_yellow.plist",
                                       "spritesheet/explode_square_green.plist"};

static const char *explode_bonus_plist[3] =
                                        {"spritesheet/explode_bonus_bullet.plist",
                                         "spritesheet/explode_bonus_power.plist",
                                            "spritesheet/explode_bonus_speed.plist"};

static const char *default_bonus_texture[3] =
                                        {"bonus_bullet_0.png",
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
    /******************* RUNTIME VARIABLES ***************/
    SpriteBatchNode*        bullet_batch_node;
    SimpleAudioEngine*      game_audio;
    ParticleSystemQuad**    pool_particle;
    Sprite**                pool_coins;
    Label*                  score;
    Background**            pool_background_scroll;
    Sprite*                 sound;
    Sprite*                 player;
    Sprite*                 tuto;
    Sprite*                 best_img;
    Sprite*                 shield_rect;
    bool                    shield_live_used = false;
    bool                    game_already_resumed = false;
    bool                    shooter_never_updated = true;
    float                   x_screen;
    float                   y_screen;
    float                   game_duration;
    int                     highter_background_id = -1;
    int                     game_block_destroyed = 0;
    int                     game_power_up_collected = 0;
    int                     current_factor_h = 0;
    int                     last_line_hited_id;
    int                     bullet_state;
    int                     game_score;
    int                     game_shooter_type = 0;
    int                     line_id_before_chest_attempts = -1;

    /******************* END MENU ***************/
    Sprite*                 next_button;
    Sprite*                 continue_button;
    Sequence*               wait_sequence;
    MenuItemImage*          back_to_main;
    MenuItemImage*          rate;
    MenuItemImage*          share;
    Label*                  earned_point;
    Layer*                  stats;
    Menu*                   end_menu;

    /******************* (ALL) BONUS MANAGMENT ***************/
    Sprite**                bonus_container;
    Sprite**                rect_container;
    bool                    star_bonus_active = false;
    bool                    bonus_selected = false;
    bool                    bonus_displayed = false;
    bool                    rect_animated = false;
    float                   bonus_time = 0;
    int                     star_line_id = -1;
    int                     chest_gen_state = -1;
    int                     bonus_active = 0;
    int                     bonus_id = -1;
    int                     current_message = -1;
    int                     next_bonus_spawn = 0;

    /******************* MAIN MENU ***************/
    int                     options_state = 0;
    Menu*                   game_menu;
    MenuItemFont*           menu_title;
    MenuItemFont*           menu_power_level;
    MenuItemFont*           menu_speed_level;
    MenuItemFont*           menu_surclassement_txt;
    MenuItemFont*           menu_best_txt;
    MenuItemImage*          menu_surclassement_img;
    MenuItemImage*          options_btn;
    MenuItemImage*          menu_shop_img;
    MenuItemImage*          menu_best_img;
    MenuItemImage*          menu_anim_img_hand;
    MenuItemImage*          menu_anim_img;
    MenuItemImage*          menu_stats_img;

    /******************* POOL MANAGMENT ***************/
    Line**                  pool_container;
    Bullet**                bullet_container;
    Circle**                pool_circle;
    int*                    active_lines;

    /******************* LINE MANAGMENT ***************/
    int                     CURRENT_LINE_ID;
    int                     NEXT_LINE_ID;
    int                     LINE_GENERATED;
    float                   NEW_SPAWN_Y;

    /******************* SOUND MANAGMENT ***************/
    int                     sound_hit_played = 0;
    int                     sound_shot_played = 0;
    bool                    sound_activated = true;

    /******************* HUD ***************/
    Sprite**                hud_bonus_messages;


public:
    /******************* END MENU PUBLIC ***************/
    MenuItemImage*          bonus_x2;

    /******************* RUNTIME VARIABLES PUBLIC ***************/
    int                     game_state;
    bool                    reward_possible = false;

    CREATE_FUNC(GameScene);
    static cocos2d::Scene*  createScene();
    virtual bool            init();
    void                    store_active_line(int);
    void                    remove_active_line(int);
    void                    init_bonus_components();
    void                    reset_arrays();
    void                    runtime_checks();
    void                    destroy_complete_line(int, float);
    void                    main_menu_coming_animation();
    void                    update_game_score(int);
    float                   get_shoot_interval();
    bool                    is_touch_on_player_zone(Vec2);
    bool                    is_normal_launch();
    void                    line_flow_checks();
    void                    select_next_line();
    void                    init_scrolling_background();
    void                    background_scroll_managment();
    int                     find_available_background(int*);
    void                    play_particle_fall(int, int, Vec2);
    bool                    new_line_need_be_generate();
    bool                    is_bonus_launch();
    void                    show_bonus_particle_explode(Vec2);
    void                    check_full_destruction_bonus(Line*, int);
    void                    show_destruction_bonus(int, int);
    void                    update_chest_texture(Square*, Line*);
    void                    play_bullet_impact();
    void                    play_square_explode();
    void                    open_end_menu();
    void                    shooter_dead_animation();
    void                    init_hud_components();
    void                    menuCloseCallback(cocos2d::Ref*);
    void                    show_particle(Vec2, Square*);
    void                    bonus_collision();
    void                    load_bonus();
    void                    destroy_all_lines();
    void                    remove_bonus();
    void                    move_bonus();
    void                    bonus_managment();
    void                    check_begining_of_session();
    void                    active_bonus();
    void                    move_circles();
    void                    scale_animation();
    void                    play_bullet_sound();
    void                    destroy_square(Square*, Line*, int, int);
    void                    update_square_data(Line*, Square*, int, int);
    void                    show_particle_explode(Square*, Vec2);
    void                    start_game();
    void                    generate_chest();
    void                    score_animation();
    bool                    is_sound_button_touched(Vec2);
    bool                    is_next_button_touched(Vec2);
    bool                    is_continue_button_touched(Vec2);
    void                    init_options_menu();
    void                    init_ui_components();
    int                     get_next_line_type();
    void                    end_of_game();
    void                    init_listeners();
    int                     get_h_value();
    int                     get_line_in_contact(int);
    void                    check_bullet_collision();
    void                    resume_game();
    bool                    collison_need_detection(Line*);
    void                    generate_star_bonus();
    void                    run_game_loop();
    void                    stop_game_loop();
    void                    move_active_lines();
    void                    check_into_line(int, int);
    void                    multiply_game_score_adbonus();
    int                     get_free_particle_pool_index();
    void                    move_particles();
    void                    increase_speed(Label*, Label*, Label *);
    void                    increase_power(Label*, Label*, Label *);
    void                    check_lines_out();
    bool                    point_into_square(Square*, Vec2);
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
