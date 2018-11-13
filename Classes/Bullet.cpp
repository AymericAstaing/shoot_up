#include    "Square.h"
#include    "GameScene.h"
#include    "Utils.h"
#include    "ShootUp.h"
#include    "Bullet.h"
#include    "UserLocalStore.h"


Bullet::Bullet() {
}

Bullet::~Bullet() {
}

void Bullet::reset() {
    auto winSize = Director::getInstance()->getVisibleSize();
    this->stopAllActions();
    if (getScale() != NORMAL_BULLET_SIZE)
        setScale(NORMAL_BULLET_SIZE);
    this->setVisible(false);
    this->bullet_active = false;
    this->contact = false;
    this->contact_index = -1;
    this->setPosition(Vec2(winSize.width / 2, 0 - getContentSize().height));
}


void Bullet::launch(int bullet_state, Vec2 player_pos, Size player_size, int launch_mode) {
    auto winSize = Director::getInstance()->getVisibleSize();

    float x_pos = player_pos.x;
    float y_pos = winSize.height - getContentSize().height / 2;
    float x_pos_start = player_pos.x;;
    float y_pos_start = static_cast<float>(player_pos.y + player_size.height / 2.5);
    float time_factor = 1;

    if (launch_mode == NORMAL_LAUNCH) {
        if (bullet_state == 0)
            x_pos_start = player_pos.x + player_size.width / 20;
        else
            x_pos_start = player_pos.x - player_size.width / 20;
        x_pos = x_pos_start;
    } else if (launch_mode == BONUS_LAUNCH_LEFT) {
        x_pos = static_cast<float>(x_pos - (2 * player_size.width));
    } else if (launch_mode == BONUS_LAUNCH_RIGHT) {
        x_pos = static_cast<float>(x_pos + (2 * player_size.width));
    } else {
        switch (launch_mode) {
            case DOUBLE_LAUNCH_LEFT:
                x_pos_start = static_cast<float>(player_pos.x - player_size.width / 4.5);
                x_pos = x_pos_start;
                break;
            case DOUBLE_LAUNCH_RIGHT:
                x_pos_start = static_cast<float>(player_pos.x + player_size.width / 4.5);
                x_pos = x_pos_start;
                break;
            case SIDEWAY_LAUNCH_LEFT:
                x_pos_start = (player_pos.x - player_size.width / 2) + getContentSize().width / 2;
                y_pos_start = (player_pos.y - player_size.height / 2) + getContentSize().height / 2;
                x_pos = -getContentSize().width;
                y_pos = y_pos_start;
                time_factor = (x_pos_start - x_pos) /
                              ((winSize.height + getContentSize().height) - player_pos.y);
                break;
            case SIDEWAY_LAUNCH_RIGHT:
                x_pos_start = (player_pos.x + player_size.width / 2) - getContentSize().width / 2;
                y_pos_start = (player_pos.y - player_size.height / 2) + getContentSize().height / 2;
                x_pos = winSize.width + getContentSize().width;
                y_pos = y_pos_start;
                time_factor = (x_pos - x_pos_start) /
                              ((winSize.height + getContentSize().height) - player_pos.y);
                break;
            case TRIPLE_LAUNCH_LEFT:
                x_pos_start = static_cast<float>(player_pos.x - player_size.width / 2 +
                                                 (1.2 * getContentSize().width / 2));
                y_pos_start = player_pos.y + player_size.height / 10;
                x_pos = x_pos_start;
                break;
            case TRIPLE_LAUNCH_RIGHT:
                x_pos_start = static_cast<float>(player_pos.x + player_size.width / 2 -
                                                 (1.2 * getContentSize().width / 2));
                y_pos_start = player_pos.y + player_size.height / 10;
                x_pos = x_pos_start;
                break;
            default:
                break;
        }
    }
    setPosition(x_pos_start, y_pos_start);
    auto actionMove = MoveTo::create(1 * time_factor, Vec2(x_pos,
                                                           y_pos));
    auto callback = CallFuncN::create(
            [&](Node *sender) {
                reset();

            });
    runAction(Sequence::create(actionMove, callback, nullptr));
    bullet_active = true;
    setVisible(true);
}

Bullet *Bullet::create() {
    auto winSize = Director::getInstance()->getVisibleSize();
    Bullet *bullet = new Bullet();
    int current_bullet = UserLocalStore::get_current_ball();
    if (bullet->initWithSpriteFrameName(balls[current_bullet])) {
        bullet->bullet_active = false;
        bullet->contact = false;
        bullet->setPosition(Vec2(winSize.width / 2, 0 - bullet->getContentSize().height));
        bullet->setTag(1);
        bullet->setVisible(false);
        return (bullet);
    }
    CC_SAFE_DELETE(bullet);
    return nullptr;
}


