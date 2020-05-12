#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Texture texture;
    sf::Sprite sprite;
    sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    sprite.setPosition(sf::Vector2f(50, 50));
    while (window.isOpen())
    {
        if (!texture.loadFromFile("../textures/crate.png"))
        {
            // error...
        }
        texture.setSmooth(true);
        sprite.setTexture(texture);
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sprite.move(1.f, 0.f);
        }
        
        window.clear();
        window.draw(shape);
        //window.draw(texture);
        window.draw(sprite);
        sprite.move(100.f, 0.f);
        window.draw(sprite);
        sprite.move(-100.f, 0.f);
        window.display();
    }
    
    return 0;
}

