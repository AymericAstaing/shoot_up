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
void Bullet::Reset() {
    auto winSize = Director::getInstance()->getVisibleSize();
    stopAllActions();
    setVisible(false);
    bullet_active = false;
    contact = false;
    contact_index = -1;
    setPosition(Vec2(winSize.width / 2, 0 - getContentSize().height));
}

void Bullet::Launch(int bullet_state, Vec2 player_pos, Size player_size) {
    auto winSize = Director::getInstance()->getVisibleSize();
    if (bullet_state == 0)
        setPosition(player_pos.x + player_size.width / 10,
                    static_cast<float>(player_pos.y + player_size.height / 2.5));
    else
        setPosition(player_pos.x - player_size.width / 10,
                    static_cast<float>(player_pos.y + player_size.height / 2.5));
    auto actionMove = MoveTo::create(1, Vec2(player_pos.x,
                                             winSize.height + getContentSize().height));
    auto callback = CallFuncN::create(
            [&](Node *sender) {
                  Reset();

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


