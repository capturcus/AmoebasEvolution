//
// Created by marcin on 17.09.16.
//

#ifndef AMOEBASEVOLUTION_MAIN_H
#define AMOEBASEVOLUTION_MAIN_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace global {

    const float32 TIME_STEP = 1.f / 60.f;
    const int POSITION_ITERATIONS = 3;
    const int VELOCITY_ITERATIONS = 8;
    const float32 LINEAR_DAMPING = 6;
    const float32 ANGULAR_DAMPING = 6;
    const float32 WORLD_SIZE = 100;
    const int START_AMOEBA_COUNT = 50;
    const int START_FOOD_COUNT = 100;

    b2Body *createDynamicCircularBody(b2World *boxWorld, b2Vec2 &position, float radius, float density);

    float randFloat(float hi);

    class Collideable {
    public:
        virtual void handleCollision(Collideable *other, float32 impulse) = 0;
    };

    class ContactListener
            : public b2ContactListener {
        void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
    };

    void drawCircleAtBody(sf::RenderWindow *window, b2Body *body, sf::Color color, float radius);
}

#endif //AMOEBASEVOLUTION_MAIN_H
