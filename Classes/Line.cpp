/*
##
## STAINDIO PROJECT, 2018
## shootup
## File description:
## line object class, lines contains Square Object
*/

#include    "Line.h"
#include    "Square.h"
#include    "Utils.h"
#include    "ShootUp.h"
#include "GameScene.h"

Line::Line(int type) {
}

Line::~Line() {
}


void Line::set_active(int factor_h) {
    setVisible(true);
    line_active = true;
    if (get_type() <= LINE_TYPE_STARTUP_5) // STARTUP LINES
        assign_startup_line_points(factor_h);
    else if (get_type() < LINE_TYPE_COMPLEX_0) //STRUCT LINE OF 4 / 5
        assign_line_points(factor_h);
    else // STRUCT COMPLEX
        assign_line_points_complex(factor_h);
}

int Line::get_index_random(int *choosen, int max) {
    while (1) {
        int rand = Utils::get_random_number(0, max);
        if (!Utils::is_into_list(choosen, max, rand))
            return (rand);
    }
    return (0);
}

void Line::change_square_color(int index, int color) {
    auto batchnode = getChildByTag(LINE_BATCH_ID);
    if (batchnode) {
        auto sprite = batchnode->getChildByTag(index);
        Sprite *e = ((Sprite *) sprite);
        SpriteFrame *tmp = (SpriteFrame *) Utils::get_color(color);
        if (e->getSpriteFrame() != tmp)
            e->setSpriteFrame(Utils::get_color(color));
    }
}

void Line::assign_color(int sq_id, int m_factor, int current_point) {

    float point = static_cast<float>(current_point);
    if (point <= static_cast<float>(m_factor * 0.9))
        change_square_color(sq_id, 3);
    else if (point <= static_cast<float>(m_factor * 0.95))
        change_square_color(sq_id, 2);
    else if (point <= static_cast<float>(m_factor * 1.05))
        change_square_color(sq_id, 1);
    else
        change_square_color(sq_id, 0);
}

void Line::assign_line_points(int h_factor) { // TMP
    int type = get_type();
    int total = 0;
    if (type == LINE_TYPE_SIMPLE_OF_4) {
        total = static_cast<int>(0.6 * h_factor);
    } else {
        int min_h = static_cast<int>(h_factor +
                                     ceil(static_cast<float>(h_factor * 0.3)));
        int max_h = static_cast<int>(h_factor +
                                     ceil(static_cast<float>(h_factor * 0.4)));
        total = Utils::get_random_number(min_h, max_h);
    }
    int *distrib = new int[this->square_nbr];
    int *choosen = new int[this->square_nbr];
    distrib = Utils::get_simple_distribution_points(distrib, total, type, this->square_nbr);
    int i = 0;
    int index = 0;

    while (i == 0) {
        auto child = getChildByTag(index);
        Square *sq = ((Square *) child);
        if (!child || !sq) {
            i = 1;
        } else {
            choosen[index] = get_index_random(choosen, this->square_nbr - 1);
            sq->assign_point(distrib[choosen[index]]);
            assign_color(index, total / this->square_nbr, distrib[choosen[index]]);

        }
        index++;
    }
}

void Line::assign_line_points_complex(int h_factor) { // POINTS FOR COMPLEX STRUCT (MARTIN'S SYSTEM)
    int type = get_type();

    int min_h = static_cast<int>(h_factor +
                                 ceil(static_cast<float>(h_factor * 0.3)));
    int max_h = static_cast<int>(h_factor +
                                 ceil(static_cast<float>(h_factor * 0.4)));
    int total = Utils::get_random_number(min_h, max_h);
    int *distrib = new int[this->square_nbr];
    distrib = Utils::get_complex_distribution_points(distrib, total, type, this->square_nbr);
    int i = 0;
    int index = 0;

    while (i == 0) {
        auto child = getChildByTag(index);
        Square *sq = ((Square *) child);
        if (!child || !sq) {
            i = 1;
        } else {
            sq->assign_point(distrib[index]);
            assign_color(index, total / this->square_nbr, distrib[index]);
        }
        index++;
    }
}

void Line::assign_startup_line_points(int h_factor) {  // POINTS FOR STARTUP STRUCT (MARTIN'S SYSTEM)
    int type = get_type();
    int lines_nbr = square_nbr / 5;
    if (h_factor < 25)
        h_factor = 25;

    for (int i = 0; i < lines_nbr; i++) {
        float ratio = 0;
        if (type == LINE_TYPE_STARTUP_3)
            ratio = line_0[i];
        if (type == LINE_TYPE_STARTUP_4)
            ratio = line_1[i];
        if (type == LINE_TYPE_STARTUP_5)
            ratio = line_2[i];
        int *distrib = new int[5];

        distrib = Utils::get_distribution_points(distrib, static_cast<int>(h_factor * ratio),
                                                 5);

        int index = i * 5;
        int k = 0;
        for (int j = index; j < (i * 5 + 5); j++, k++) {
            auto child = getChildByTag(j);
            Square *sq = ((Square *) child);
            if (!child || !sq) {
                break;
            } else {
                sq->assign_point(distrib[k]);
            }
        }
    }
}

Size Line::get_line_size(int type) {
    auto winSize = Director::getInstance()->getVisibleSize();
    if (type == SIMPLE_LINE_4)
        return (Size((static_cast<float>(winSize.width / SQUARE_SIZE_4)) * 4,
                     static_cast<float>(winSize.height / 9.6)));
    else if (type == SIMPLE_LINE_5)
        return (Size((static_cast<float>(winSize.width / SQUARE_SIZE_5)) * 5,
                     static_cast<float>(winSize.height / 10.5)));
    else {
        int line_nbr = 0;
        switch (type) {
            case LINE_TYPE_STARTUP_3:
                line_nbr = 3;
                break;
            case LINE_TYPE_STARTUP_4:
                line_nbr = 4;
                break;
            case LINE_TYPE_STARTUP_5:
                line_nbr = 5;
                break;
            default:
                line_nbr = 5;
                break;
        }
        return (Size((static_cast<float>(winSize.width / 4.95)) * 5,
                     (static_cast<float>(winSize.height / 10.5)) * line_nbr));
    }
}

/********************************** BLOCKS TRANSLATIONS ****************************/

void Line::apply_animation(Line *l, Sprite *s, Square *square, int struct_nbr, int index) {
    if (struct_nbr == 3) {
        if (index == 3)
            apply_middle_left_translation(square, s, square->get_rect_size(), l->line_size);
        if (index == 4)
            apply_middle_right_translation(square, s, square->get_rect_size(), l->line_size);
        if (index == 5)
            apply_full_translation(square, s, square->get_rect_size(), l->line_size);
    } else if (struct_nbr == 4) {
        if (index == 0)
            apply_double_left_translation(square, s, square->get_rect_size());
        if (index == 2)
            apply_double_right_translation(square, s, square->get_rect_size());
        if (index == 5)
            apply_double_left_translation(square, s, square->get_rect_size());
        if (index == 7)
            apply_double_right_translation(square, s, square->get_rect_size());
    }
}

void
Line::apply_full_translation(Square *s, Sprite *sprite, float rect_size[2],
                             float line_size[2]) {
    float block_width = rect_size[WIDTH];

    auto actionMove1 = MoveBy::create(0.9,
                                      Vec2((line_size[WIDTH] - block_width / 2) -
                                           s->getPosition().x, 0));
    auto actionMove2 = MoveBy::create(0.9,
                                      Vec2(-((line_size[WIDTH] - block_width / 2) -
                                             s->getPosition().x),
                                           0));
    auto actionMove3 = MoveBy::create(0.9,
                                      Vec2((line_size[WIDTH] - block_width / 2) -
                                           s->getPosition().x, 0));
    auto actionMove4 = MoveBy::create(0.9,
                                      Vec2(-((line_size[WIDTH] - block_width / 2) -
                                             s->getPosition().x),
                                           0));
    auto seq = Sequence::create(actionMove1, actionMove2, nullptr);
    auto seq2 = Sequence::create(actionMove3, actionMove4, nullptr);
    s->runAction(RepeatForever::create(seq));
    sprite->runAction(RepeatForever::create(seq2));
}

void Line::apply_middle_left_translation(Square *s, Sprite *sprite, float rect_size[2],
                                         float line_size[2]) {
    float block_width = rect_size[0];
    auto winSize = Director::getInstance()->getVisibleSize();
    int distance = static_cast<int>(((line_size[WIDTH] / 2) - block_width));
    auto actionMove1 = MoveBy::create(0.8, Vec2(distance,
                                                0));
    auto actionMove2 = MoveBy::create(0.8, Vec2(-distance, 0));
    auto seq = Sequence::create(actionMove1, actionMove2, nullptr);
    auto actionMove3 = MoveBy::create(0.8, Vec2(distance,
                                                0));
    auto actionMove4 = MoveBy::create(0.8, Vec2(-distance, 0));
    auto seq2 = Sequence::create(actionMove3, actionMove4, nullptr);
    s->runAction(RepeatForever::create(seq));
    sprite->runAction(RepeatForever::create(seq2));
}

void Line::apply_middle_right_translation(Square *s, Sprite *sprite, float rect_size[2],
                                          float line_size[2]) {
    float block_width = rect_size[0];
    auto winSize = Director::getInstance()->getVisibleSize();
    int distance = static_cast<int>((line_size[WIDTH] - block_width / 2) -
                                    (line_size[WIDTH] / 2 + block_width / 2));
    auto actionMove1 = MoveBy::create(0.8, Vec2(-distance, 0));
    auto actionMove2 = MoveBy::create(0.8, Vec2(distance, 0));
    auto seq = Sequence::create(actionMove1, actionMove2, nullptr);
    auto actionMove3 = MoveBy::create(0.8, Vec2(-distance, 0));
    auto actionMove4 = MoveBy::create(0.8, Vec2(distance, 0));
    auto seq2 = Sequence::create(actionMove3, actionMove4, nullptr);
    s->runAction(RepeatForever::create(seq));
    sprite->runAction(RepeatForever::create(seq2));
}

void Line::apply_double_left_translation(Square *s, Sprite *sprite, float rect_size[2]) {
    float block_width = rect_size[0];
    auto actionMove1 = MoveBy::create(0.8, Vec2(block_width, 0));
    auto actionMove2 = MoveBy::create(0.8, Vec2(-block_width, 0));
    auto seq = Sequence::create(actionMove1, actionMove2, nullptr);
    auto actionMove3 = MoveBy::create(0.8, Vec2(block_width, 0));
    auto actionMove4 = MoveBy::create(0.8, Vec2(-block_width, 0));
    auto seq2 = Sequence::create(actionMove3, actionMove4, nullptr);
    s->runAction(RepeatForever::create(seq));
    sprite->runAction(RepeatForever::create(seq2));
}

void Line::apply_double_right_translation(Square *s, Sprite *sprite, float rect_size[2]) {
    float block_width = rect_size[0];
    auto winSize = Director::getInstance()->getVisibleSize();
    auto actionMove1 = MoveBy::create(0.8, Vec2(-block_width, 0));
    auto actionMove2 = MoveBy::create(0.8, Vec2(block_width, 0));
    auto seq = Sequence::create(actionMove1, actionMove2, nullptr);
    auto actionMove3 = MoveBy::create(0.8, Vec2(-block_width, 0));
    auto actionMove4 = MoveBy::create(0.8, Vec2(block_width, 0));
    auto seq2 = Sequence::create(actionMove3, actionMove4, nullptr);
    s->runAction(RepeatForever::create(seq));
    sprite->runAction(RepeatForever::create(seq2));
}
/********************************** BLOCKS TRANSLATIONS ****************************/


/********************************** LINE STRUCTURES *****************************/
Vec2 Line::get_square_grid_pos(int requiered_pos, float rect_size[2], int line_size) {
    Vec2 req_pos;
    if (line_size == SQUARE_SIZE_LINE_OF_5)
        req_pos = Utils::get_coordinate_from_id(requiered_pos, SQUARE_SIZE_LINE_OF_5);
    else
        req_pos = Utils::get_coordinate_from_id(requiered_pos, SQUARE_SIZE_LINE_OF_4);
    return (Vec2((rect_size[WIDTH] / 2) + (req_pos.x * rect_size[WIDTH]),
                 ((rect_size[HEIGHT]) / 2) + (req_pos.y * (rect_size[HEIGHT]))));
}

const int *Line::struct_pos(int id) {
    switch (id) {
        case 0:
            return (pos_struct_0);
        case 1:
            return (pos_struct_1);
        case 2:
            return (pos_struct_2);
        case 3:
            return (pos_struct_3);
        case 4:
            return (pos_struct_4);
        case 5:
            return (pos_struct_5);
        case 6:
            return (pos_struct_6);
        case 7:
            return (pos_struct_7);
        default:
            break;
    }
    return (nullptr);
}

int Line::struct_element_nbr(int id) {
    switch (id) {
        case 0:
            return (6);
        case 1:
            return (6);
        case 2:
            return (8);
        case 3:
            return (6);
        case 4:
            return (8);
        case 5:
            return (9);
        case 6:
            return (9);
        case 7:
            return (7);
        default:
            break;
    }
    return (0);
}
/********************************** LINE STRUCTURES *****************************/

/********************************** SQUARES LOADING *****************************/

SpriteBatchNode *Line::get_batch() {
    SpriteBatchNode *spriteBatchNode;
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
            "spritesheet/default_colors.plist");
    spriteBatchNode = SpriteBatchNode::create("spritesheet/default_colors.png");
    spriteBatchNode->setAnchorPoint(Vec2(0, 0));
    spriteBatchNode->setTag(LINE_BATCH_ID);
    return (spriteBatchNode);
}

Sprite *Line::get_texture(int i, float square_height, float square_width) {
    auto sprite = Sprite::createWithSpriteFrameName("green_b.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setTag(i);
    float sprite_height = sprite->getContentSize().height;
    float sprite_width = sprite->getContentSize().width;
    sprite->setScaleY(square_height / sprite_height);
    sprite->setScaleX(static_cast<float>(square_width * 1.05 / sprite_width));
    return (sprite);
}

void Line::load_startup_struct(Line *l) {
    SpriteBatchNode *spriteBatchNode = get_batch();
    spriteBatchNode->setContentSize(l->getContentSize());
    l->addChild(spriteBatchNode);

    int total_square = l->square_nbr;

    for (int i = 0; i < total_square; i++) {
        Square *sq = Square::create(SQUARE_SIZE_LINE_OF_5);
        if (sq) {
            sq->setTag(i);
            sq->setPosition(get_square_grid_pos(i, sq->get_rect_size(), SQUARE_SIZE_LINE_OF_5));
            l->addChild(sq);
            auto sprite = get_texture(i, sq->getContentSize().height,
                                      sq->getContentSize().width);
            sprite->setPosition(sq->getPosition());
            spriteBatchNode->addChild(sprite);
        }
    }
}


void Line::load_complex_struct(Line *l, int struct_number) {
    SpriteBatchNode *spriteBatchNode = get_batch();
    spriteBatchNode->setContentSize(l->getContentSize());
    l->addChild(spriteBatchNode);

    struct_number -= 7; // REMOVE OTHER LINE TYPES
    const int *pos_struct = struct_pos(struct_number);
    int size = struct_element_nbr(struct_number);

    for (int i = 0; i < size; i++) {
        Square *sq = Square::create(SQUARE_SIZE_LINE_OF_5);
        if (sq) {
            sq->setTag(i);
            sq->setPosition(
                    get_square_grid_pos(pos_struct[i], sq->get_rect_size(),
                                        SQUARE_SIZE_LINE_OF_5));
            l->addChild(sq);
            auto sprite = get_texture(i, sq->getContentSize().height,
                                      sq->getContentSize().width);
            sprite->setPosition(sq->getPosition());
            spriteBatchNode->addChild(sprite);
            if (struct_number == 3 || struct_number == 4)
                apply_animation(l, sprite, sq, struct_number, i);
        }
    }
}

void Line::load_simple_line_5(Line *l) {
    SpriteBatchNode *spriteBatchNode = get_batch();
    spriteBatchNode->setContentSize(l->getContentSize());
    l->addChild(spriteBatchNode);

    for (int i = 0; i < 5; i++) {
        Square *sq = Square::create(SQUARE_SIZE_LINE_OF_5);
        if (sq) {
            sq->setTag(i);
            sq->setPosition(get_square_grid_pos(i, sq->get_rect_size(), SQUARE_SIZE_LINE_OF_5));
            l->addChild(sq);
            auto sprite = get_texture(i, sq->getContentSize().height,
                                      sq->getContentSize().width);
            sprite->setPosition(sq->getPosition());
            spriteBatchNode->addChild(sprite);
        }
    }
}

void Line::load_simple_line_4(Line *l) {
    SpriteBatchNode *spriteBatchNode = get_batch();
    spriteBatchNode->setContentSize(l->getContentSize());
    l->addChild(spriteBatchNode);

    for (int i = 0; i < 4; i++) {
        Square *sq = Square::create(SQUARE_SIZE_LINE_OF_4);
        if (sq) {
            sq->setPosition(get_square_grid_pos(i, sq->get_rect_size(), SQUARE_SIZE_LINE_OF_4));
            sq->setTag(i);
            l->addChild(sq);
            auto sprite = get_texture(i, sq->getContentSize().height,
                                      sq->getContentSize().width);
            sprite->setPosition(sq->getPosition());
            spriteBatchNode->addChild(sprite);

        }
    }
}

int Line::get_type() {
    return (line_type);
}

int Line::get_complex_line_type(int type, Line *l) {
    switch (type) {
        case 7:
            l->square_nbr = 6;
            return (LINE_TYPE_COMPLEX_0);
        case 8:
            l->square_nbr = 6;
            return (LINE_TYPE_COMPLEX_1);
        case 9:
            l->square_nbr = 8;
            return (LINE_TYPE_COMPLEX_2);
        case 10:
            l->square_nbr = 6;
            return (LINE_TYPE_COMPLEX_3);
        case 11:
            l->square_nbr = 8;
            return (LINE_TYPE_COMPLEX_4);
        case 12:
            l->square_nbr = 9;
            return (LINE_TYPE_COMPLEX_5);
        case 13:
            l->square_nbr = 9;
            return (LINE_TYPE_COMPLEX_6);
        case 14:
            l->square_nbr = 7;
            return (LINE_TYPE_COMPLEX_7);
        default:
            break;
    }
    return (-1);
}

void Line::load_square(Line *l, int type) {

    if (type > STARTUP_LINE_5) {
        l->line_type = get_complex_line_type(type, l);
        load_complex_struct(l, type);
        return;
    }
    switch (type) {
        case SIMPLE_LINE_4:
            l->square_nbr = 4;
            l->line_type = LINE_TYPE_SIMPLE_OF_4;
            load_simple_line_4(l);
            break;
        case SIMPLE_LINE_5:
            l->square_nbr = 5;
            l->line_type = LINE_TYPE_SIMPLE_OF_5;
            load_simple_line_5(l);
            break;
        case STARTUP_LINE_2:
            l->square_nbr = 10;
            l->line_type = LINE_TYPE_STARTUP_2;
            load_startup_struct(l);
            break;
        case STARTUP_LINE_3:
            l->square_nbr = 15;
            l->line_type = LINE_TYPE_STARTUP_3;
            load_startup_struct(l);
            break;
        case STARTUP_LINE_4:
            l->square_nbr = 20;
            l->line_type = LINE_TYPE_STARTUP_4;
            load_startup_struct(l);
            break;
        case STARTUP_LINE_5:
            l->square_nbr = 25;
            l->line_type = LINE_TYPE_STARTUP_5;
            load_startup_struct(l);
            break;
        default:
            break;
    }
}

/********************************** SQUARES LOADING *****************************/

void Line::reset() {
    int i = 0;
    int j = 0;
    int index = 0;
    int batch_index = 0;
    auto batchnode = getChildByTag(LINE_BATCH_ID);

    while (j == 0) {
        if (batchnode) {
            auto sprite = batchnode->getChildByTag(batch_index);
            if (sprite && !sprite->isVisible())
                sprite->setVisible(true);
            else if (!sprite)
                j = 1;

        } else {
            j = 1;
        }
        batch_index++;
    }
    while (i == 0) {
        auto child = getChildByTag(index);
        if (!child) {
            i = 1;
        } else {
            ((Square *) child)->reset_square();
            child->setVisible(true);
        }
        index++;
    }
    line_active = false;
    setVisible(false);
    auto winSize = Director::getInstance()->getVisibleSize();
    setPosition(Vec2(0, static_cast<float>(winSize.height + getContentSize().height)));
}

Line *Line::create(int type) {
    auto winSize = Director::getInstance()->getVisibleSize();
    Line *l = new Line(type);
    l->setAnchorPoint(Vec2(0, 0));
    auto size = get_line_size(type);
    l->line_size[WIDTH] = size.width;
    l->line_size[HEIGHT] = size.height;
    l->line_active = false;
    l->setContentSize(Size(l->line_size[WIDTH], l->line_size[HEIGHT]));
    l->setPosition(Vec2(0, static_cast<float>(winSize.height + l->line_size[HEIGHT])));
    load_square(l, type);
    l->setVisible(false);
    return (l);
    CC_SAFE_DELETE(l);
}


