#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

class Country;
class Map;

class ExpandTerritoryAction {
public:
	ExpandTerritoryAction(Country* m_country, Map* map, std::vector<sf::Vector2i>& start_positions, int target);

	bool IsComplete() const { return m_complete; }
	void Tick();

private:
	std::vector<sf::Vector2i> m_position_queue;
	Country* m_country;
	Map* m_map;

	bool m_complete { false };
	int m_target;
};
