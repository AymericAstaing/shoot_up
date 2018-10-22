#include        <iostream>
#include        <random>
#include        "Utils.h"
#include        "GameScene.h"
#include        "UserLocalStore.h"
#include        "ShootUp.h"

USING_NS_CC;


Sprite *Utils::get_player() {
    auto winSize = Director::getInstance()->getVisibleSize();
    int current_shooter = UserLocalStore::get_current_shooter();
    Sprite *player = Sprite::create(shooters[current_shooter]);
    player->
            setPosition(Vec2(static_cast<float>(winSize.width * 0.5),
                             static_cast<float>(winSize.height * 0.25)));
    return (player);
}


int Utils::array_sum(int *array, int size) {
    int sum = 0;

    for (int a = 0; a < size; a++)
        sum += array[a];
    return (sum);
}

bool Utils::is_into_list(int *list, int list_size, int value) {
    for (int i = 0; i < list_size; i++) {
        if (list[i] == value)
            return (true);
    }
    return (false);
}

int *Utils::get_complex_distribution_points(int *distribution, int total_nbr, int line_type,
                                            int sq_nbr) {
    int type = line_type - 6;
    for (int i = 0; i < sq_nbr; i++)
        distribution[i] = static_cast<int>(DISTRIB_COMPLEX[type][i] * total_nbr);
    return (distribution);
}


int *Utils::get_simple_distribution_points(int *distribution, int total_nbr, int line_type,
                                           int sq_nbr) {
    int type = line_type - 4;
    for (int i = 0; i < sq_nbr; i++)
        distribution[i] = static_cast<int>(DISTRIB_SIMPLE[type][i] * total_nbr);
    return (distribution);
}

int *Utils::get_distribution_points(int *distribution, int total_number, int nbr_of_group) {
    int t = 0;
    int loose_pcc = total_number / nbr_of_group;

    for (int i = 1; i < nbr_of_group; i++, t++) {
        int ten_pcc = static_cast<int>(loose_pcc * 0.1);
        int rand_num = cocos2d::RandomHelper::random_int((loose_pcc - ten_pcc),
                                                         (loose_pcc + ten_pcc));
        distribution[t] = rand_num;
    }
    int numbers_total = array_sum(distribution, nbr_of_group - 1);
    distribution[t] = total_number - numbers_total;
    return (distribution);
}

float Utils::get_spawn_y(int current_type, int next_type, float next_line_size[2]) {
    auto screen_height = Director::getInstance()->getVisibleSize().height;

    auto line_height = next_line_size[HEIGHT] / 2;
    if (current_type >= LINE_TYPE_STARTUP_2 && current_type <= LINE_TYPE_STARTUP_5)
        return (-line_height);
    if (current_type == LINE_TYPE_SIMPLE_OF_4 && next_type == LINE_TYPE_SIMPLE_OF_4)
        return static_cast<float>(screen_height * 0.62 + line_height);
    if (current_type == LINE_TYPE_SIMPLE_OF_4 && next_type == LINE_TYPE_SIMPLE_OF_5)
        return static_cast<float>(screen_height * 0.30 + line_height);
    if (current_type == LINE_TYPE_SIMPLE_OF_5 && next_type == LINE_TYPE_SIMPLE_OF_5)
        return static_cast<float>(screen_height * 0.50 + line_height);
    if (current_type > LINE_TYPE_SIMPLE_OF_5 && next_type == LINE_TYPE_SIMPLE_OF_5)
        return static_cast<float>(screen_height * 0.52 + line_height);
    if (current_type == LINE_TYPE_SIMPLE_OF_5 && next_type > LINE_TYPE_SIMPLE_OF_5)
        return static_cast<float>(screen_height * 0.23 + line_height);
    if (current_type > LINE_TYPE_SIMPLE_OF_5 && next_type > LINE_TYPE_SIMPLE_OF_5)
        return static_cast<float>(screen_height * 0.25 + line_height);
    return (-1);
}

const char *Utils::get_color(int color_id) {
    switch (color_id) {
        case 0:
            return (BASIC_COLOR_RED);
        case 1:
            return (BASIC_COLOR_ORANGE);
        case 2:
            return (BASIC_COLOR_YELLOW);
        case 3:
            return (BASIC_COLOR_GREEN);
        default:
            break;
    }
    return (nullptr);
}

int Utils::get_shooter_type(int shooter_id) {

    if (shooter_id <= 0 && shooter_id < 5) {
        return (STARTER_TANK);
    } else if (shooter_id >= 6 && shooter_id < 9) {
        return (POWER_TANK);
    } else if (shooter_id >= 11 && shooter_id < 13) {
        return (MOVEMENT_TANK);
    } else if (shooter_id >= 14 && shooter_id < 16) {
        return (DOUBLE_TANK);
    } else if (shooter_id >= 17 && shooter_id < 18) {
        return (SHIELD_TANK);
    } else if (shooter_id >= 20 && shooter_id < 23) {
        return (SPEED_TANK);
    } else if (shooter_id >= 24 && shooter_id < 25) {
        return (SIDEWAY_TANK);
    } else if (shooter_id >= 27 && shooter_id < 30) {
        return (TRIPLE_TANK);
    }
    return (NULL);
}

int Utils::get_random_line_type() {
    int result = get_random_number(0, 20);
    if (result > 7)
        return (LINE_TYPE_SIMPLE_OF_5);
    else
        return (random_type[result]);
}

int Utils::get_random_number(int min, int max) {
    return (cocos2d::RandomHelper::random_int(min, max));
}

int *Utils::get_container_range_research(int type) {
    int *range = new int[2];

    switch (type) {
        case 4:
            range[0] = 4;
            range[1] = 6;
            break;
        case 5:
            range[0] = 7;
            range[1] = 9;
            break;
        case 6:
            range[0] = 10;
            range[1] = 11;
            break;
        case 7:
            range[0] = 12;
            range[1] = 13;
            break;
        case 8:
            range[0] = 14;
            range[1] = 15;
            break;
        case 9:
            range[0] = 16;
            range[1] = 17;
            break;
        case 10:
            range[0] = 18;
            range[1] = 19;
            break;
        case 11:
            range[0] = 20;
            range[1] = 21;
            break;
        case 12:
            range[0] = 22;
            range[1] = 23;
            break;
        case 13:
            range[0] = 24;
            range[1] = 25;
            break;
        default:
            break;
    }
    return (range);
}

Vec2 Utils::get_coordinate_from_id(int id, int column) {
    return (Vec2(id % column, id / column));
}

float Utils::get_finger_move_factor(float x) {
    auto winSize = Director::getInstance()->getVisibleSize();
    float old_min = 0;
    float old_max = winSize.width;
    float new_min = -winSize.width / 2;
    float new_max = winSize.width / 2;
    return ((((x - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min);
}

float Utils::line_speed_converter(float y_value) {
    auto winSize = Director::getInstance()->getVisibleSize();
    float old_min = winSize.height;
    float old_max = -300;
    float new_max = 0;
    float new_min = 3.3;
    return ((((y_value - old_min) * (new_max - new_min)) / (old_max - old_min)) + new_min);
}

