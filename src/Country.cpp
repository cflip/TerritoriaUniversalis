#include "Country.h"

#include "Action.h"
#include "Map.h"
#include <cstdlib>
#include <queue>

Country::Country(int id, Map& map, sf::Vector2i start_pos)
	: m_id(id), m_map(map), m_start_pos(start_pos)
{
	m_colour.r = rand() % 255;
	m_colour.g = rand() % 255;
	m_colour.b = rand() % 255;

	std::vector<sf::Vector2i> thing = { start_pos };
	m_actions.emplace_back(ExpandTerritoryAction(this, &m_map, thing, NO_OWNER));
}

CountryToTileListMap Country::FindNeighbouringCountries()
{
	std::queue<sf::Vector2i> the_queue;
	the_queue.emplace(m_start_pos);

	CountryToTileListMap surrounding_countries;

	while (!the_queue.empty()) {
		auto n = the_queue.back();
		the_queue.pop();

		int current_country_id = m_map.TileOwner(n.x, n.y);
		if (current_country_id != NO_OWNER && current_country_id != m_id) {
			surrounding_countries[current_country_id].emplace_back(n.x, n.y);
		}

		if (m_map.InBounds(n.x, n.y) && m_map.TerrainType(n.x, n.y) == TerrainType::Ground) {
			the_queue.emplace(n.x + 1, n.y);
			the_queue.emplace(n.x - 1, n.y);
			the_queue.emplace(n.x, n.y + 1);
			the_queue.emplace(n.x, n.y - 1);
		}
	}

	return surrounding_countries;
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

	if (m_actions.empty()) {
		printf("%d got cucked\n", m_id);
		auto surrounding_countries = FindNeighbouringCountries();
		if (!surrounding_countries.empty()) {
			auto thing = surrounding_countries.begin();
			if (!thing->second.empty())
				m_actions.emplace_back(ExpandTerritoryAction(this, &m_map, thing->second, thing->first));
		}
	}

	m_population += (int)((float)m_area * 0.05f + 1);
}
