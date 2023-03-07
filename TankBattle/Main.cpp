#include <SFML/Graphics.hpp>
#include <iostream>

#include "PlayerTank.h"
#include "GameWorld.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    try {
        Map::ParseCommon();
        Map* map1 = new Map();
        GameWorld gameWorld(map1);

        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        std::cout << TimePerFrame.asSeconds() << std::endl;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            timeSinceLastUpdate += clock.restart();

            while (timeSinceLastUpdate > TimePerFrame){
                timeSinceLastUpdate -= TimePerFrame;
                window.clear();
                gameWorld.Update(TimePerFrame, event);
                gameWorld.Render(window);
                window.display();
            }
        }
    }
    catch (std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }

    return 0;
}