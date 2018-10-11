#ifndef __SHOPSCENE_SCENE_H__
#define __SHOPSCENE_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <cocos-ext.h>
#include <GUI/CCScrollView/CCTableViewCell.h>
#include "GridView.h"
#include "../cocos2d/extensions/cocos-ext.h"
#include "../cocos2d/extensions/GUI/CCScrollView/CCTableViewCell.h"
#include <string>

using namespace cocos2d;

class ShopScene
        : public cocos2d::Scene,
          public cocos2d::extension::TableViewDataSource,
          public cocos2d::extension::TableViewDelegate {

private:
    const char**    shooter_content;
    const char**    ball_content;
    GridView*       shooter_grid;
    GridView*       ball_grid;
    Sprite*         shooter_button;
    Sprite*         back_button;
    Sprite*         ball_button;
    Label*          points;
    Menu*           asset_menu;
    int             asset_menu_added;
    const char *shooter_achievement[30] = {"DESTROY 300\nBLOCKS OR MORE\nWITH STARTER\nTANK",
                                           "COLLECT 50 POWER\nUP ITEMS WITH\nSTARTER TANK",
                                           "PLAY 30 GAMES\nWITH STARTER\nTANK",
                                           "PLAY 100 GAMES\nWITH STARTER\nTANK",
                                           "COLLECT 100\nPOWER UP ITEMS\nWITH STARTER\nTANK",
                                           "REACH SHOOTING\nPOWER LEVEL 20",
                                           "DESTROY 1000\nBLOCKS OR MORE\nWITH SHOOTING\nPOWER TANK",
                                           "PLAY 150 GAMES\nWITH SHOOTING\nPOWER TANK",
                                           "PLAY 300 GAMES\nWITH SHOOTING\nPOWER TANK",
                                           "DESTROY 5K\nBLOCKS OR MORE\nWITH SHOOTING\nPOWER TANK",
                                           "COLLECT 25 POWER\nUP ITEMS",
                                           "PLAY 50 GAMES\nWITH MOVEMENT\nSPEED TANK",
                                           "COLLECT 100\nPOWER UP ITEMS\nWITH MOVEMENT\nSPEED TANK",
                                           "SCORE 50K OR\nMORE",
                                           "PLAY 200 GAMES\nWITH DOUBLE\nSHOOT TANK",
                                           "DESTROY 20K\nBLOCKS OR MORE\nWITH DOUBLE\nSHOOT TANK",
                                           "PLAY 75 GAMES",
                                           "COLLECT 2OO\nPOWER UP ITEMS\nWITH SHIELD TANK",
                                           "PLAY 200 GAMES\nWITH SHIELD TANK",
                                           "REACH SHOOTING\nSPEED LEVEL 10",
                                           "PLAY 100 GAMES\nWITH SHOOTING\nSPEED TANK",
                                           "COLLECT 200\nPOWER UP ITEMS\nWITH SHOOTING\nSPEED TANK",
                                           "DESTORY 15K\nBLOCKS OR MORE\nWITH SHOOTING\nSPEED TANK",
                                           "DESTROY 7.5K\nBLOCKS OR MORE",
                                           "PLAY 200G AMES\nWITH SIDEWAY\nSHOOTER TANK",
                                           "DESTORY 20K\n BLOCKS OR MORE\nWITH SIDEWAY\nSHOOTER TANK",
                                           "PLAY 200 GAMES",
                                           "PLAY 300 GAMES\nWITH TRIPLE\nSHOOTER TANK",
                                           "DESTROY 30K\nBLOCKS OR MORE\nWITH TRIPLE\nSHOOTER TANK",
                                           "COLLECT 300\nPOWER UP ITEMS\nWITH TRIPLE\nSHOOTER TANK"};

    const char *ball_achievement[7] = {"PLAY 30 GAMES",
                                       "DESTROY 500\nBLOCKS OR MORE",
                                       "PLAY 150 GAMES",
                                       "COLLECT 200\nPOWER UP ITEMS",
                                       "SCORE 10K OR\nMORE",
                                       "PLAY 100 GAMES",
                                       "SCORE 20K OR MORE"};
public:

    CREATE_FUNC(ShopScene);

    static Scene*           createScene();
    virtual bool            init();
    void                    init_shop_grids();
    void                    init_ui_components();
    bool                    is_shooter(Vec2 touch_location);
    bool                    is_ball(Vec2 touch_location);
    bool                    is_back(Vec2 touch_location);
    bool                    onTouchBegan(Touch *touch, Event *event);
    GridView*               init_grid(int);
    Menu*                   get_asset_menu(int, int);


    /* *****************************************GRID MANAGMENT *************************************** */
    virtual void            tableCellTouched(cocos2d::extension::TableView *table,
                                             cocos2d::extension::TableViewCell *cell);
    virtual cocos2d::Size   tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell *
                            tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t         numberOfCellsInTableView(cocos2d::extension::TableView *table);
};
#endif // __SHOPSCENE_SCENE_H__
