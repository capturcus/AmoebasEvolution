#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

const float32 TIME_STEP = 1.f / 60.f;
const int POSITION_ITERATIONS = 3;
const int VELOCITY_ITERATIONS = 8;

class Amoeba {
public:
    static Amoeba *createAmoeba(b2World *boxWorld) {
        auto bodyDef = new b2BodyDef;
        bodyDef->type = b2BodyType::b2_dynamicBody;
        bodyDef->active = true;
        b2Body *body = boxWorld->CreateBody(bodyDef);
        b2Shape *shape;
        shape = new b2CircleShape;
        shape->m_radius = .5f;
        b2FixtureDef *fixtureDef = new b2FixtureDef;
        fixtureDef->density = 1;
        fixtureDef->friction = 1;
        fixtureDef->restitution = 1;
        fixtureDef->shape = shape;
        body->CreateFixture(fixtureDef);
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

    Amoeba *createAmoeba() {
        return Amoeba::createAmoeba(boxWorld);
    }

    void step() {
        boxWorld->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    }
};

sf::CircleShape amoebaBody(1.f);
sf::CircleShape amoebaEye(0.2f);

void drawAmoebaAtPos(sf::RenderWindow *window, b2Vec2 position, float rotation) {
    amoebaBody.setPosition(position.x, position.y);
    amoebaEye.setPosition((float) (position.x + 0.8f + 0.8*cos(rotation)), (float) (position.y + 0.8f + 0.8*sin(rotation)));
    window->draw(amoebaBody);
    window->draw(amoebaEye);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::View view(sf::Vector2f(100, 100), sf::Vector2f(10, 10));
    amoebaEye.setFillColor(sf::Color::Black);
    amoebaBody.setFillColor(sf::Color::Green);

    AmoebasWorld world;

    float testRot = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    view.move(-1, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    view.move(1, 0);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    view.move(0, -1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    view.move(0, 1);
                }
                if(event.key.code == sf::Keyboard::H){
                    testRot -= 0.1;
                }
                if (event.key.code == sf::Keyboard::L){
                    testRot += 0.1;
                }
            }
        }

        window.setView(view);
        window.clear();
        drawAmoebaAtPos(&window, b2Vec2(101, 101), testRot);
        drawAmoebaAtPos(&window, b2Vec2(99,99), testRot+1);
        window.display();
    }

    return 0;
}