#pragma once

#include <SFML/Graphics/Color.hpp>
#include <memory>
#include <map>
#include <vector>

#include "Action.h"

class Map;

typedef std::map<int, std::vector<sf::Vector2i>> CountryToTileListMap;

class Country {
public:
	Country(int id, Map& map, sf::Vector2i start_pos);

	void Tick();

	sf::Color Colour() const { return m_colour; }
	int Id() const { return m_id; }

private:
	// We'll just make this a friend class for now, I'll come up with nicer infrastructure later
	friend class ExpandTerritoryAction;

	CountryToTileListMap FindNeighbouringCountries();

	std::vector<ExpandTerritoryAction> m_actions;
	Map& m_map;
	sf::Color m_colour;
	int m_id;

	sf::Vector2i m_start_pos;
	int m_area { 1 };
	int m_population { 100 };
};
