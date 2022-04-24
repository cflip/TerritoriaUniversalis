#include "Country.h"

#include "Action.h"
#include <cstdlib>

Country::Country(int id)
	: m_id(id), m_colour({ static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255) }) { }

void Country::ExpandTerritory(Map& map, int x, int y)
{
	m_actions.emplace_back(ExpandTerritoryAction(this, &map, { x, y }));
}

void Country::Tick()
{
	for (auto it = m_actions.begin(); it != m_actions.end();) {
		if (it->IsComplete()) {
			it = m_actions.erase(it);
		} else {
			if (m_population > 100)
				it->Tick();
			it++;
		}
	}
	m_population += (int)((float)m_area * 0.05f + 1);
}
