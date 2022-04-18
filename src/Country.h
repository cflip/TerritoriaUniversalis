#pragma once

#include <SFML/Graphics/Color.hpp>

class Country {
public:
	sf::Color Colour() { return m_colour; }

private:
	sf::Color m_colour { 255, 127, 255 };
};
