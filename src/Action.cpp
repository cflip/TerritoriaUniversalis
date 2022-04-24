#include "Action.h"

#include "Country.h"
#include "Map.h"

ExpandTerritoryAction::ExpandTerritoryAction(Country* country, Map* map, std::vector<sf::Vector2i>& start_positions, int target)
	: m_country(country), m_map(map), m_position_queue(start_positions), m_target(target)
{
}

void ExpandTerritoryAction::Tick()
{
	if (m_complete)
		return;

	const auto check_and_add_tile_to_queue = [&](sf::Vector2i pos) {
		if (m_map->TileOwner(pos.x, pos.y) == m_target && m_map->TerrainType(pos.x, pos.y) == TerrainType::Ground) {
			m_country->m_area++;
			m_country->m_population--;
			m_map->SetTileOwner(pos.x, pos.y, m_country->Id());
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
