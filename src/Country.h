#pragma once

#include <SFML/Graphics/Color.hpp>
#include <memory>
#include <vector>

#include "Action.h"

class Map;

class Country {
public:
	Country(int id);

	void ExpandTerritory(Map& map, int x, int y);
	void Tick();

	sf::Color Colour() const {
		if (m_actions[0].IsComplete())
			return m_colour;
		return sf::Color::Yellow;
	}
	int Id() const { return m_id; }

private:
	std::vector<ExpandTerritoryAction> m_actions;
	sf::Color m_colour;
	int m_id;
};
