#ifndef __LINE_H__
#define __LINE_H__

#include    "cocos2d.h"
#include    "Square.h"

USING_NS_CC;

class Line : public cocos2d::Node {

public:
    float                           line_size[2];
    int                             line_type;
    bool                            line_active;


    Line(int);
    ~Line();
    static Line*                    create(int);
    static Size                     get_line_size(int);
    int                             get_type();
    void                            move();
    static void                     load_startup_struct(Line*, int);
    static void                     load_square(Line*, int);
    static void                     load_complex_struct(Line*, int);
    static void                     load_simple_line_4(Line*);
    static void                     load_simple_line_5(Line*);
    static const int*               struct_pos(int);
    static int                      struct_element_nbr(int);
    void                            reset();
    static SpriteBatchNode*         get_batch();
    static Sprite*                  get_texture(int, float, float);
    static int                      get_complex_line_type(int);
    static void                     apply_animation(Line*, Sprite*,  Square*, int, int);
    static  void                    apply_full_translation(Square *, Sprite*, float[2], float[2]);
    static void                     apply_middle_left_translation(Square *, Sprite*, float[2], float[2]);
    static void                     apply_middle_right_translation(Square *, Sprite*, float[2], float[2]);
    static void                     apply_double_right_translation(Square *, Sprite*, float[2]);
    static void                     apply_double_left_translation(Square *, Sprite*, float[2]);
    static Vec2                     get_square_grid_pos(int, float[2], int);
private:

};

#endif // __LINE_H__
