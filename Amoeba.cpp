//
// Created by marcin on 17.09.16.
//

#include "Amoeba.h"
#include "main.h"
#include "AmoebaFood.h"
#include "AmoebaWorld.h"

Amoeba * Amoeba::createAmoeba(b2World *boxWorld, b2Vec2 &position) {
    Amoeba *ret = new Amoeba();
    ret->boxBody = global::createDynamicCircularBody(boxWorld, position, 1.f, .1f);
    ret->boxBody->SetUserData(ret);
    return ret;
}

void Amoeba::stepTurn(float32 speed, float32 turn) {
    boxBody->ApplyForceToCenter(speed * b2Vec2(
            (float32) (cos(boxBody->GetAngle()) * 10),
            (float32) (sin(boxBody->GetAngle()) * 10)
    ), true);
    boxBody->ApplyTorque(turn, true);
}

void Amoeba::step() {
    for (AmoebaFood* af : AmoebaWorld::getInstance()->foods) {
        float32 dist = b2Distance(boxBody->GetPosition(), af->boxBody->GetPosition());
    }
    //one input, angle to nearest food
    //n hidden neurons - subjects to genetic algorithm
    //two outputs, tracks
    stepTurn(testSpeed, testDir);
}

void Amoeba::handleCollision(global::Collideable *other, float32 impulse) {
    AmoebaFood* af = dynamic_cast<AmoebaFood*>(other);
    if(af){
        foodEaten++;
    }
}