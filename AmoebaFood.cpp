//
// Created by marcin on 17.09.16.
//

#include "AmoebaFood.h"

std::vector<AmoebaFood *> AmoebaFood::toBeDeleted;

AmoebaFood *AmoebaFood::createFood(b2World *boxWorld, b2Vec2 &position) {
    auto body = createDynamicCircularBody(boxWorld, position, .2f, 1.f);
    AmoebaFood *ret = new AmoebaFood;
    ret->boxBody = body;
    ret->boxBody->SetUserData(ret);
    return ret;
}

void AmoebaFood::handleCollision(Collideable *other, float32 impulse) {
    Amoeba *a = dynamic_cast<Amoeba *>(other);
    if (a) {
        toBeDeleted.push_back(this);
    }
}