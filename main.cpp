#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float32 TIME_STEP = 1.f / 60.f;
const int POSITION_ITERATIONS = 3;
const int VELOCITY_ITERATIONS = 8;
const float32 LINEAR_DAMPING = 6;
const float32 ANGULAR_DAMPING = 6;

class Amoeba {
public:
    static Amoeba *createAmoeba(b2World *boxWorld, b2Vec2 &position) {
        auto bodyDef = new b2BodyDef;
        bodyDef->type = b2BodyType::b2_dynamicBody;
        bodyDef->active = true;
        bodyDef->position = position;
        b2Body *body = boxWorld->CreateBody(bodyDef);
        b2Shape *shape;
        shape = new b2CircleShape;
        shape->m_radius = 1.f;
        b2FixtureDef *fixtureDef = new b2FixtureDef;
        fixtureDef->density = .1;
        fixtureDef->friction = 1;
        fixtureDef->restitution = 1;
        fixtureDef->shape = shape;
        body->CreateFixture(fixtureDef);
        body->SetLinearDamping(LINEAR_DAMPING);
        body->SetAngularDamping(ANGULAR_DAMPING);
        delete fixtureDef;
        Amoeba *ret = new Amoeba();
        ret->boxBodyDef = bodyDef;
        ret->boxBody = body;
        body->SetUserData(ret);
        return ret;
    }

    b2BodyDef *boxBodyDef = nullptr;
    b2Body *boxBody = nullptr;
private:
    Amoeba() {}
};

struct AmoebasWorld {
    b2World *boxWorld = nullptr;

    AmoebasWorld() {
        boxWorld = new b2World(b2Vec2(0, 0));
    }

    ~AmoebasWorld() {
        delete boxWorld;
    }

    Amoeba *createAmoeba(b2Vec2 &position) {
        return Amoeba::createAmoeba(boxWorld, position);
    }

    void step() {
        boxWorld->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    }
};

sf::CircleShape amoebaBody(1.f);
sf::CircleShape amoebaEye(0.2f);

void drawAmoebaAtPos(sf::RenderWindow *window, b2Vec2 position, float rotation) {
    amoebaBody.setPosition(position.x, position.y);
    amoebaEye.setPosition((float) (position.x + 0.8f + 0.8 * cos(rotation)),
                          (float) (position.y + 0.8f + 0.8 * sin(rotation)));
    window->draw(amoebaBody);
    window->draw(amoebaEye);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    window.setFramerateLimit(60);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(20, 16));
    amoebaEye.setFillColor(sf::Color::Black);
    amoebaBody.setFillColor(sf::Color::Green);

    AmoebasWorld world;

    b2Vec2 vec;
    vec.Set(0, 1.2f);
    Amoeba *a = world.createAmoeba(vec);
    vec.Set(5, 0);
    Amoeba *a2 = world.createAmoeba(vec);

    while (window.isOpen()) {
        sf::Event event;
        world.step();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            view.move(-.1f, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            view.move(.1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            view.move(0, -.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            view.move(0, .1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            view.zoom(0.99);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            view.zoom(1.01);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            a->boxBody->ApplyForceToCenter(b2Vec2(
                    (float32) (cos(a->boxBody->GetAngle()) * 10),
                    (float32) (sin(a->boxBody->GetAngle()) * 10)
            ), true);
            a->boxBody->ApplyTorque(2, true);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            a->boxBody->ApplyForceToCenter(b2Vec2(
                    (float32) (cos(a->boxBody->GetAngle()) * 10),
                    (float32) (sin(a->boxBody->GetAngle()) * 10)
            ), true);
            a->boxBody->ApplyTorque(-2, true);
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.setView(view);
        window.clear();
        drawAmoebaAtPos(&window, a->boxBody->GetPosition(), a->boxBody->GetAngle());
        drawAmoebaAtPos(&window, a2->boxBody->GetPosition(), a2->boxBody->GetAngle());
        window.display();
    }

    return 0;
}