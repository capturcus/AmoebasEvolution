//
// Created by marcin on 17.09.16.
//

#ifndef AMOEBASEVOLUTION_AMOEBAFOOD_H
#define AMOEBASEVOLUTION_AMOEBAFOOD_H

#include <Box2D/Box2D.h>
#include <vector>
#include "Amoeba.h"
#include "main.h"

using namespace global;

class AmoebaFood
        : public Collideable {
public:
    b2Body *boxBody = nullptr;
    static std::vector<AmoebaFood *> toBeDeleted;

    static AmoebaFood *createFood(b2World *boxWorld, b2Vec2 &position);

    void handleCollision(Collideable *other, float32 impulse);

private:
    AmoebaFood() {}
};


#endif //AMOEBASEVOLUTION_AMOEBAFOOD_H
