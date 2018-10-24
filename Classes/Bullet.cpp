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
    stopAllActions();
    setScale(1);
    setVisible(false);
    bullet_active = false;
    contact = false;
    contact_index = -1;
    setPosition(Vec2(winSize.width / 2, 0 - getContentSize().height));
}

void Bullet::launch(int bullet_state, Vec2 player_pos, Size player_size, int launch_mode) {
    auto winSize = Director::getInstance()->getVisibleSize();

    float x_pos = player_pos.x;
    float x_pos_start = player_pos.x;;

    if (launch_mode == BONUS_LAUNCH_LEFT)
        x_pos = static_cast<float>(x_pos - (2.5 * player_size.width));
    else if (launch_mode == BONUS_LAUNCH_RIGHT)
        x_pos = static_cast<float>(x_pos + (2.5 * player_size.width));

    if (launch_mode == NORMAL_LAUNCH) {
        if (bullet_state == 0)
            x_pos_start = player_pos.x + player_size.width / 20;
        else
            x_pos_start = player_pos.x - player_size.width / 20;
    }

    setPosition(x_pos_start,
                static_cast<float>(player_pos.y + player_size.height / 2.5));
    auto actionMove = MoveTo::create(1, Vec2(x_pos,
                                             winSize.height + getContentSize().height));
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
    if (bullet->initWithFile(balls[current_bullet])) {
        bullet->bullet_active = false;
        bullet->contact = false;
        bullet->setPosition(Vec2(winSize.width / 2, 0 - bullet->getContentSize().height));
        bullet->setTag(1);
        bullet->setVisible(false);
        return (bullet);
    }
    CC_SAFE_DELETE(bullet);
}


