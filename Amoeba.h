//
// Created by marcin on 17.09.16.
//

#ifndef AMOEBASEVOLUTION_AMOEBA_H
#define AMOEBASEVOLUTION_AMOEBA_H

#include "main.h"
#include <Box2D/Box2D.h>

using namespace global;

class Amoeba :
        public Collideable {
public:
    static Amoeba *createAmoeba(b2World *boxWorld, b2Vec2 &position);

    void stepTurn(float32 speed, float32 turn);

    void step();

    ~Amoeba() {}

    void handleCollision(Collideable *other, float32 impulse);

    b2Body *boxBody = nullptr;
    int foodEaten = 0;
    float testSpeed = randFloat(2.f);
    float testDir = randFloat(6.f) - 3.f;
private:
    Amoeba() {}
};


#endif //AMOEBASEVOLUTION_AMOEBA_H
