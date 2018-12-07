#ifndef __LINE_H__
#define __LINE_H__

#include    "cocos2d.h"
#include    "Square.h"

USING_NS_CC;

static const float LINE_DIVISION[3][5] = {{0.20, 0.30, 0.50}, {0.10, 0.20, 0.30, 0.40}, {0.05, 0.10, 0.15, 0.20, 0.50}};

static const float DISTRIB_COMPLEX[8][9] = {{0.2, 0.06, 0.2, 0.17, 0.17, 0.2},
                                            {0.17, 0.2, 0.2, 0.17, 0.1, 0.17},
                                            {0.17, 0.13, 0.1, 0.13, 0.17, 0.13, 0.06, 0.1},
                                            { 0.13, 0.2, 0.13, 0.17, 0.2, 0.17},
                                            { 0.13, 0.06, 0.17, 0.17, 0.1, 0.13, 0.06, 0.17 },
                                            { 0.1, 0.13, 0.17, 0.13, 0.03, 0.1, 0.13, 0.06, 0.13 },
                                            { 0.17, 0.13, 0.06, 0.1, 0.17, 0.03, 0.03, 0.13, 0.17 },
                                            { 0.17, 0.13, 0.17, 0.2, 0.2, 0.03, 0.1 }};

static const float DISTRIB_SIMPLE[2][5] = {{0.27, 0.3, 0.23, 0.2}, {0.23, 0.23, 0.2, 0.2, 0.13}};

static const int SQUARE_NBR_PER_LINE[8] = {6, 6, 8, 6, 8, 9, 9, 7};



        class Line :
        public cocos2d::Node {
            public:
            float                       line_size[2];
            int                         line_type;
            int                         half_total;
            bool                        line_animated;
            int                         square_nbr;
            bool                        line_active;
            Vec2                        initial_pos;


            Line(int);
            ~Line();
            static Line*                create(int);
            static Size                 get_line_size(int);
            int                         get_line_type();
            void                        attach_star_bonus();
            void                        set_active(int, int);
            void                        attach_chest_bonus();
            int                         get_special_shooter_total_point(int);
            void                        change_square_color(int, int);
            void                        assign_color(int, int, int);
            int                         get_random_index(int *, int);
            static void                 load_startup_struct(Line *);
            static void                 load_squares_into_line(Line *, int);
            static void                 load_complex_struct(Line *, int);
            static void                 load_simple_line_4(Line *);
            static void                 load_simple_line_5(Line *);
            void                        assign_complex_line_points(int, int);
            void                        assign_startup_line_points(int);
            void                        reset();
            void                        check_for_transition_line();
            void                        assign_line_points(int, int);
            static SpriteBatchNode*     get_batch();
            static Sprite*              get_texture(int, float*);
            static int                  get_square_nbr_per_line(int);
            static void                 apply_animation(Line *, Sprite *, Square *, int, int);
            static void                 apply_full_translation(Square *, Sprite *, float[2], float[2]);
            static void                 apply_middle_left_translation(Square *, Sprite *, float[2], float[2]);
            static void                 apply_middle_right_translation(Square *, Sprite *, float[2], float[2]);
            static void                 apply_double_right_translation(Square *, Sprite *, float[2]);
            static void                 apply_double_left_translation(Square *, Sprite *, float[2]);
            static Vec2                 get_square_pos_into_line(int, float[2], int);
            private:

        };

#endif // __LINE_H__
