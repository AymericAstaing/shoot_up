#ifndef __SQUARE_H__
#define __SQUARE_H__

#include    "cocos2d.h"

USING_NS_CC;

const int pos_struct_0[7] = {0, 2, 4, 6, 8, 12, NULL};
const int pos_struct_1[7] = {2, 6, 8, 10, 12, 14, NULL};
const int pos_struct_2[9] = {0, 2, 4, 6, 8, 10, 12, 14, NULL};
const int pos_struct_3[7] = {0, 2, 4, 5, 9, 10, NULL};
const int pos_struct_4[9] = {0, 2, 4, 6, 8, 10, 12, 14, NULL};
const int pos_struct_5[10] = {2, 3, 4, 6, 7, 8, 10, 11, 12, NULL};
const int pos_struct_6[10] = {0, 1, 2, 6, 7, 8, 12, 13, 14, NULL};
const int pos_struct_7[8] = {1, 3, 5, 7, 9, 11, 13, NULL};

class Square : public  cocos2d::Node {

public:
                            Square(int);
                            ~Square();
    void                    reset_square();
    int                     get_square_pv();
    static Square*          create(int);
    float*                  get_rect_size();
    static Size             get_square_size(int);
    void                    assign_point(int);
    int                     square_pv;
    int                     initial_pv;
    int                     initial_color;
    Label*                  points;

private:
    Color4F *               color;
    float                   rect_size[2];
};

#endif // __SQUARE_H__
