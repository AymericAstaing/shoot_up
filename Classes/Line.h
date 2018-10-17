#ifndef __LINE_H__
#define __LINE_H__

#include    "cocos2d.h"
#include    "Square.h"

USING_NS_CC;

static const float line_0[3] = {0.20, 0.30, 0.50};
static const float line_1[4] = {0.10, 0.20, 0.30, 0.40};
static const float line_2[5] = {0.05, 0.10, 0.15, 0.20, 0.50};

class Line : public cocos2d::Node {

public:
    float                           line_size[2];
    int                             line_type;
    int                             square_nbr;
    bool                            line_active;


    Line(int);
    ~Line();
    static Line*                    create(int);
    static Size                     get_line_size(int);
    int                             get_type();
    void                            set_active(int);
    void                            change_square_color(int, int);
    void                            assign_color(int, int, int);
    int                             get_index_random(int*, int);
    static void                     load_startup_struct(Line*);
    static void                     load_square(Line*, int);
    static void                     load_complex_struct(Line*, int);
    static void                     load_simple_line_4(Line*);
    static void                     load_simple_line_5(Line*);
    void                            assign_startup_line_points(int);
    static const int*               struct_pos(int);
    static int                      struct_element_nbr(int);
    void                            reset();
    void                            assign_line_points(int);
    static SpriteBatchNode*         get_batch();
    static Sprite*                  get_texture(int, float, float);
    static int                      get_complex_line_type(int, Line*);
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
