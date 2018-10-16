#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <cocos-ext.h>
#include <GUI/CCScrollView/CCTableViewCell.h>
#include "GridView.h"
#include "Square.h"
#include "Bullet.h"
#include "Line.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene {

private:
    Line**              pool_container;
    Bullet**            bullet_container;
    Sprite*             player;
    MenuItemImage*      skip_btn;
    MenuItemImage*      back_to_main;
    MenuItemImage*      rate;
    MenuItemImage*      share;
    Label*              score;
    Sprite*             sound;
    Sprite*             best_img;
    Sprite*             tuto;
    Menu*               game_menu;
    Menu*               continue_menu;
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
    float               x_screen;
    float               y_screen;
    int                 game_score;
    int                 *active_lines;
    int                 options_state = 0;
    int                 bullet_state;
    int                 game_state;
    int                 current_factor_h = 0;
    int                 current_max = 0;
    int                 current_min = 0;

    /******************* LINE MANAGMENT ***************/
    int                 CURRENT_LINE_ID;
    int                 NEXT_LINE_ID;
    int                 LINE_GENERATED;
    float               NEW_SPAWN_Y;


public:
    CREATE_FUNC(GameScene);
    static cocos2d::Scene*  createScene();
    virtual bool            init();
    void                    skip(cocos2d::Ref*);
    void                    store_active_line(int);
    void                    remove_active_line(int);
    void                    reset_arrays();
    void                    main_menu_coming_animation();
    void                    update_game_score(int);
    float                   get_shoot_interval();
    void                    menuCloseCallback(cocos2d::Ref*);
    void                    show_particle(Vec2);
    void                    start_game();
    void                    score_animation();
    bool                    is_sound_button_touched(Vec2);
    void                    init_options_menu();
    int                     get_next_line_type();
    void                    end_of_game();
    void                    play(cocos2d::Ref *);
    int                     get_h_value();
    void                    run_game_loop();
    void                    stop_game_loop();
    void                    move_active_lines();
    void                    check_into_line();
    Menu*                   get_continue_menu();
    void                    check_lines_out();
    bool                    point_into_square(Square*, Vec2);
    void                    check_bullet_contact();
    void                    check_player_collision();
    void                    value_to_update();
    void                    back_to_menu(cocos2d::Ref *);
    void                    update(float) override;
    void                    surclassement(cocos2d::Ref *);
    void                    reset_lines();
    int                     get_line_index(int);
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
    void                    show_destruction_circle(Vec2, float, int);
    void                    start_bullet_shoot();
    void                    stop_bullet_shoot();

};

#endif // __GameScene_SCENE_H__
