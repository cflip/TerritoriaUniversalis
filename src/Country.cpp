#include "Country.h"

#include <cstdlib>

Country::Country()
	: m_colour({ static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255) }) { }
