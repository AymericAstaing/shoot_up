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

void Line::move() {
    setVisible(true);
    line_active = true;
    auto callback = CallFuncN::create(
            [&](Node *sender) {
                reset();
                line_active = false;
                setVisible(false);
            });
    auto actionMove = MoveTo::create(Utils::line_speed_converter(getPositionY()),
                                     Vec2(getPosition().x, 0 - getContentSize().height));
    runAction(Sequence::create(actionMove, callback, nullptr));
}

Size Line::get_line_size(int type) {
    auto winSize = Director::getInstance()->getVisibleSize();
    if (type == SIMPLE_LINE_4)
        return (Size((static_cast<float>(winSize.width / 3.95)) * 4,
                     static_cast<float>(winSize.height / 9.6)));
    else if (type == SIMPLE_LINE_5)
        return (Size((static_cast<float>(winSize.width / 4.95)) * 5,
                     static_cast<float>(winSize.height / 10.5)));
    else
        return (Size((static_cast<float>(winSize.width / 4.95)) * 5,
                     (static_cast<float>(winSize.height / 10.5)) * 3));
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
Line::apply_full_translation(Square *s, Sprite *sprite, float rect_size[2], float line_size[2]) {
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
    auto winSize = Director::getInstance()->getVisibleSize();
    return (Size((rect_size[WIDTH] / 2) + (req_pos.x * rect_size[WIDTH]),
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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spritesheet/atlas_blocks.plist");
    spriteBatchNode = SpriteBatchNode::create("spritesheet/atlas_blocks.png");
    spriteBatchNode->setAnchorPoint(Vec2(0, 0));
    spriteBatchNode->setTag(LINE_BATCH_ID);
    return (spriteBatchNode);
}

Sprite *Line::get_texture(int i, float square_height, float square_width) {
    auto sprite = Sprite::createWithSpriteFrameName("block_green.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setTag(i);
    float sprite_height = sprite->getContentSize().height;
    float sprite_width = sprite->getContentSize().width;
    sprite->setScaleY(square_height / sprite_height);
    sprite->setScaleX(static_cast<float>(square_width * 1.05 / sprite_width));
    return (sprite);
}

void Line::load_startup_struct(Line *l, int line_nbr) {
    int total_square = line_nbr * 5;

    for (int i = 0; i < total_square; i++) {
        Square *sq = Square::create(SQUARE_SIZE_LINE_OF_5);
        if (sq) {
            sq->setTag(i);
            sq->setPosition(get_square_grid_pos(i, sq->get_rect_size(), SQUARE_SIZE_LINE_OF_5));
            l->addChild(sq);
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
                    get_square_grid_pos(pos_struct[i], sq->get_rect_size(), SQUARE_SIZE_LINE_OF_5));
            l->addChild(sq);
            auto sprite = get_texture(i, sq->getContentSize().height, sq->getContentSize().width);
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
            auto sprite = get_texture(i, sq->getContentSize().height, sq->getContentSize().width);
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
            auto sprite = get_texture(i, sq->getContentSize().height, sq->getContentSize().width);
            sprite->setPosition(sq->getPosition());
            spriteBatchNode->addChild(sprite);

        }
    }
}

int Line::get_type() {
    return (line_type);
}

int Line::get_complex_line_type(int type) {
    switch (type) {
        case 7:
            return (LINE_TYPE_COMPLEX_0);
        case 8:
            return (LINE_TYPE_COMPLEX_1);
        case 9:
            return (LINE_TYPE_COMPLEX_2);
        case 10:
            return (LINE_TYPE_COMPLEX_3);
        case 11:
            return (LINE_TYPE_COMPLEX_4);
        case 12:
            return (LINE_TYPE_COMPLEX_5);
        case 13:
            return (LINE_TYPE_COMPLEX_6);
        case 14:
            return (LINE_TYPE_COMPLEX_7);
        default:
            break;
    }
    return (-1);
}

void Line::load_square(Line *l, int type) {

    if (type > STARTUP_LINE_5) {
        l->line_type = get_complex_line_type(type);
        load_complex_struct(l, type);
        return;
    }
    switch (type) {
        case SIMPLE_LINE_4:
            l->line_type = LINE_TYPE_SIMPLE_OF_4;
            load_simple_line_4(l);
            break;
        case SIMPLE_LINE_5:
            l->line_type = LINE_TYPE_SIMPLE_OF_5;
            load_simple_line_5(l);
            break;
        case STARTUP_LINE_2:
            l->line_type = LINE_TYPE_STARTUP_2;
            load_startup_struct(l, 2);
            break;
        case STARTUP_LINE_3:
            l->line_type = LINE_TYPE_STARTUP_3;
            load_startup_struct(l, 3);
            break;
        case STARTUP_LINE_4:
            l->line_type = LINE_TYPE_STARTUP_4;
            load_startup_struct(l, 4);
            break;
        case STARTUP_LINE_5:
            l->line_type = LINE_TYPE_STARTUP_5;
            load_startup_struct(l, 5);
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


