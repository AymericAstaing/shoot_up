#ifndef __LINE_H__
#define __LINE_H__

#include    "cocos2d.h"
#include    "Square.h"

USING_NS_CC;

static const float line_0[3] = {0.20, 0.30, 0.50};
static const float line_1[4] = {0.10, 0.20, 0.30, 0.40};
static const float line_2[5] = {0.05, 0.10, 0.15, 0.20, 0.50};


static const float DISTRIB_COMPLEX[8][9] = {{0.2, 0.06, 0.2, 0.17, 0.17, 0.2},
                                            {0.17, 0.2, 0.2, 0.17, 0.1, 0.17},
                                            {0.1, 0.13, 0.1, 0.2, 0.2, 0.1, 0.1, 0.06},
                                            { 0.13, 0.2, 0.13, 0.17, 0.2, 0.17},
                                            { 0.13, 0.06, 0.17, 0.17, 0.1, 0.13, 0.06, 0.17 },
                                            { 0.1, 0.13, 0.17, 0.13, 0.03, 0.1, 0.13, 0.06, 0.13 },
                                            { 0.17, 0.13, 0.06, 0.1, 0.17, 0.03, 0.03, 0.13, 0.17 },
                                            { 0.17, 0.13, 0.17, 0.2, 0.2, 0.03, 0.1 }};

static const float DISTRIB_SIMPLE[2][5] = {{0.27, 0.3, 0.23, 0.2}, {0.23, 0.23, 0.2, 0.2, 0.13}};


static const char *COLOR_HIT[4][5] = {{"hit_red_0.png", "hit_red_1.png", "hit_red_2.png", "hit_red_3.png", "hit_red_4.png"},
                                            {"hit_orange_0.png", "hit_orange_1.png", "hit_orange_2.png", "hit_orange_3.png", "hit_orange_4.png"},
                                            {"hit_yellow_0.png", "hit_yellow_1.png", "hit_yellow_2.png", "hit_yellow_3.png", "hit_yellow_4.png"},
                                            { "hit_green_0.png", "hit_green_1.png", "hit_green_2.png", "hit_green_3.png", "hit_green_4.png"}};



        class Line :
        public cocos2d::Node {

            public:
            float line_size[2];
            int line_type;
            int square_nbr;
            bool line_active;


            Line(int);
            ~Line();
            static Line*                create(int);
            static Size                 get_line_size(int);
            int                         get_type();
            void                        set_active(int, int);
            void                        change_square_color(int, int);
            void                        assign_color(int, int, int);
            int                         get_index_random(int *, int);
            static void                 load_startup_struct(Line *);
            static void                 load_square(Line *, int);
            static void                 load_complex_struct(Line *, int);
            static void                 load_simple_line_4(Line *);
            static void                 load_simple_line_5(Line *);
            void                        assign_line_points_complex(int, int);
            void                        assign_startup_line_points(int);
            static const int*           struct_pos(int);
            static int                  struct_element_nbr(int);
            void                        reset();
            void                        assign_line_points(int, int);
            static SpriteBatchNode*     get_batch();
            static Sprite*              get_texture(int, float, float);
            static int                  get_complex_line_type(int, Line *);
            static void                 apply_animation(Line *, Sprite *, Square *, int, int);
            static void                 apply_full_translation(Square *, Sprite *, float[2], float[2]);
            static void                 apply_middle_left_translation(Square *, Sprite *, float[2], float[2]);
            static void                 apply_middle_right_translation(Square *, Sprite *, float[2], float[2]);
            static void                 apply_double_right_translation(Square *, Sprite *, float[2]);
            static void                 apply_double_left_translation(Square *, Sprite *, float[2]);
            static Vec2                 get_square_grid_pos(int, float[2], int);
            private:

        };

#endif // __LINE_H__
