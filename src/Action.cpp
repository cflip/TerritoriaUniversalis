#include "Action.h"

#include "Country.h"
#include "Map.h"

ExpandTerritoryAction::ExpandTerritoryAction(Country& country, Map& map, sf::Vector2i start_pos)
	: m_country(country), m_map(map)
{
	m_position_queue.push_back(start_pos);
}

void ExpandTerritoryAction::Tick()
{
	if (m_complete)
		return;

	const auto check_and_add_tile_to_queue = [&](sf::Vector2i pos) {
		if (m_map.IsFreeTile(pos.x, pos.y)) {
			m_map.SetTileOwner(pos.x, pos.y, m_country.Id());
			m_position_queue.push_back(pos);
		}
	};

	auto old_queue = m_position_queue;
	m_position_queue.clear();
	for (auto pos : old_queue) {
		check_and_add_tile_to_queue({ pos.x + 1, pos.y });
		check_and_add_tile_to_queue({ pos.x - 1, pos.y });
		check_and_add_tile_to_queue({ pos.x, pos.y + 1 });
		check_and_add_tile_to_queue({ pos.x, pos.y - 1 });
	}

	if (m_position_queue.empty())
		m_complete = true;
}
