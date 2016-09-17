//
// Created by marcin on 17.09.16.
//

#include "AmoebaWorld.h"

SINGLETON_CPP(AmoebaWorld)

AmoebaWorld::AmoebaWorld() {
    boxWorld = new b2World(b2Vec2(0, 0));
    b2Vec2 startPosition;
    for (int i = 0; i < START_AMOEBA_COUNT; ++i) {
        startPosition.Set(randFloat(WORLD_SIZE), randFloat(WORLD_SIZE));
        amoebas.push_back(createAmoeba(startPosition));
    }
    for (int j = 0; j < START_FOOD_COUNT; ++j) {
        startPosition.Set(randFloat(WORLD_SIZE), randFloat(WORLD_SIZE));
        foods.push_back(AmoebaFood::createFood(boxWorld, startPosition));
    }
    boxWorld->SetContactListener(new ContactListener());
}

AmoebaWorld::~AmoebaWorld() {
    delete boxWorld;
    for (Amoeba *a : amoebas) {
        delete a;
    }
}

Amoeba *AmoebaWorld::createAmoeba(b2Vec2 &position) {
    return Amoeba::createAmoeba(boxWorld, position);
}

void AmoebaWorld::step() {
    boxWorld->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    for (AmoebaFood *fa : AmoebaFood::toBeDeleted) {
        boxWorld->DestroyBody(fa->boxBody);
        foods.erase(std::remove(foods.begin(), foods.end(), fa), foods.end());
        delete fa;
    }
    AmoebaFood::toBeDeleted.clear();
    for (Amoeba *a : amoebas) {
        a->step();
    }
}