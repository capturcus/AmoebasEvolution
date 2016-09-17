//
// Created by marcin on 17.09.16.
//

#ifndef AMOEBASEVOLUTION_AMOEBAWORLD_H
#define AMOEBASEVOLUTION_AMOEBAWORLD_H

#include <Box2D/Box2D.h>
#include "Amoeba.h"
#include "AmoebaFood.h"
#include "main.h"

using namespace global;

class AmoebaWorld {
public:
    b2World *boxWorld = nullptr;
    std::vector<Amoeba *> amoebas;
    std::vector<AmoebaFood *> foods;

    AmoebaWorld();

    ~AmoebaWorld();

    Amoeba *createAmoeba(b2Vec2 &position);

    void step();
};


#endif //AMOEBASEVOLUTION_AMOEBAWORLD_H
