#include <SFML/Graphics.hpp>
#include "PlayerTank.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

    try {
        PlayerTank player;
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
                player.Update(TimePerFrame);
                player.Render(window);
                window.display();
            }
        }
    }
    catch (std::runtime_error& err) {
        std::cout << err.what() << std::endl;
    }

    return 0;
}