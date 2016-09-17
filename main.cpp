#include "Amoeba.h"
#include "AmoebaFood.h"
#include "AmoebaWorld.h"

namespace global {

    float randFloat(float hi) {
        return (float) rand() / (RAND_MAX / hi);
    }

    b2Body *createDynamicCircularBody(b2World *boxWorld, b2Vec2 &position, float radius, float density) {
        auto bodyDef = new b2BodyDef;
        bodyDef->type = b2BodyType::b2_dynamicBody;
        bodyDef->active = true;
        bodyDef->position = position;
        b2Body *body = boxWorld->CreateBody(bodyDef);
        b2Shape *shape;
        shape = new b2CircleShape;
        shape->m_radius = radius;
        b2FixtureDef *fixtureDef = new b2FixtureDef;
        fixtureDef->density = density;
        fixtureDef->friction = 1;
        fixtureDef->restitution = 1;
        fixtureDef->shape = shape;
        body->CreateFixture(fixtureDef);
        body->SetLinearDamping(LINEAR_DAMPING);
        body->SetAngularDamping(ANGULAR_DAMPING);
        delete fixtureDef;
        delete bodyDef;
        delete shape;
        return body;
    }

    void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
        Collideable *a = (Collideable *) contact->GetFixtureA()->GetBody()->GetUserData();
        Collideable *b = (Collideable *) contact->GetFixtureB()->GetBody()->GetUserData();
        float32 impulseValue = impulse->normalImpulses[0];
        a->handleCollision(b, impulseValue);
        b->handleCollision(a, impulseValue);
    }

    void drawCircleAtBody(sf::RenderWindow *window, b2Body *body, sf::Color color, float radius) {
        sf::CircleShape bigCircle(radius);
        sf::CircleShape smallCircle(radius / 5);
        bigCircle.setPosition(body->GetPosition().x - radius, body->GetPosition().y - radius);
        smallCircle.setPosition((float) ((body->GetPosition().x - radius / 5) + 0.8f * radius * cos(body->GetAngle())),
                                (float) ((body->GetPosition().y - radius / 5) + 0.8f * radius * sin(body->GetAngle())));
        bigCircle.setFillColor(color);
        smallCircle.setFillColor(sf::Color::Black);
        window->draw(bigCircle);
        window->draw(smallCircle);
    }
}

using namespace global;

int main() {
    srand((unsigned int) time(0));
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    sf::View view(sf::Vector2f(WORLD_SIZE / 2, WORLD_SIZE / 2), sf::Vector2f(20, 16));

    AmoebaWorld world;

    while (window.isOpen()) {
        sf::Event event;
        world.step();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            view.move(-.005f * view.getSize().x, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            view.move(.005f * view.getSize().x, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            view.move(0, -.005f * view.getSize().x);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            view.move(0, .005f * view.getSize().x);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            view.zoom(0.99);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            view.zoom(1.01);
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.setView(view);
        window.clear();
        for (Amoeba *a : world.amoebas) {
            drawCircleAtBody(&window, a->boxBody, sf::Color::Green, 1.f);
        }
        for (AmoebaFood *af : world.foods) {
            drawCircleAtBody(&window, af->boxBody, sf::Color::Red, .2f);
        }
        window.display();
    }
    return 0;
}