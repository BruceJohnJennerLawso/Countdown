#include <iostream>
#include <time.h>
#include <algorithm>
#include <string>

#include "TTxt_File.cpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	sf::SoundBuffer buffer;
	std::string file_name;
	file_name = "Example_sound.ogg";
	std::string file_path;
	file_path = "./Data/Audio/";
	file_path.append(file_name);
	if(!(buffer.loadFromFile(file_path)))
	{    shape.setFillColor(sf::Color::Red);
	}
	else
	{	shape.setFillColor(sf::Color::Blue);
	}
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}


