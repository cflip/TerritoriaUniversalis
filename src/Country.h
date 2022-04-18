#pragma once

#include <SFML/Graphics/Color.hpp>

class Country {
public:
	Country();

	sf::Color Colour() { return m_colour; }
private:
	sf::Color m_colour;
};
