#include "Country.h"

#include "Action.h"
#include <algorithm>

Country::Country(int id)
	: m_id(id), m_colour({ static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255), static_cast<sf::Uint8>(rand() % 255) }) { }

void Country::ExpandTerritory(Map& map, int x, int y)
{
	m_actions.emplace_back(ExpandTerritoryAction(*this, map, { x, y }));
}

void Country::populationHandler(int input)
{
	population += int(input * 0.05f + 1);
}

void Country::Tick()
{
	for (auto& action : m_actions)
		if (population > 100) {
			action.Tick();
		}
	populationHandler(pixels);
	printf("%d\n", population);
}
