#include "Country.h"

#include "Action.h"
#include "Map.h"

Country::Country(int id)
	: m_id(id), m_colour({ static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255) }) { }

void Country::ExpandTerritory(Map& map, int x, int y)
{
	m_actions.emplace_back(ExpandTerritoryAction(*this, map, { x, y }, NO_OWNER));
}

void Country::Tick()
{
	for (auto& action : m_actions)
		if (m_population > 100)
			action.Tick();
	m_population += (int)((float)m_area * 0.05f + 1);
}
