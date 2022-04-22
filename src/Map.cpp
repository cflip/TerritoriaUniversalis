#include "Map.h"

#include <iostream>
#include <cstring>

Map::Map(sf::Image& terrain_map)
{
	// Use the provided image to build the initial terrain
	auto map_size = terrain_map.getSize();

	m_width = map_size.x;
	m_height = map_size.y;
	m_terrain_map = new enum TerrainType[m_width * m_height];
	m_country_map = new uint16_t[m_width * m_height];

	for (int i = 0; i < m_width * m_height; i++)
		m_country_map[i] = NO_OWNER;

	for (int y = 0; y < m_height; y++)
		for (int x = 0; x < m_width; x++)
			m_terrain_map[x + y * m_width] = terrain_map.getPixel(x, y) == sf::Color::White ? TerrainType::Ground : TerrainType::Water;
}

TerrainType Map::TerrainType(int x, int y) const
{
	if (InBounds(x, y))
		return m_terrain_map[x + y * m_width];
	return TerrainType::Water;
}

uint16_t Map::TileOwner(int x, int y) const
{
	if (InBounds(x, y))
		return m_country_map[x + y * m_width];
	return NO_OWNER;
}

void Map::SetTileOwner(int x, int y, int id)
{
	if (InBounds(x, y)) {
		m_country_map[x + y * m_width] = id;
	}
}

void Map::AddCountry()
{
	static uint16_t id_counter = 0;

	int spawn_x = -1, spawn_y = -1;
	int spawn_tries = 0;
	srand(time(nullptr));
	while (!IsFreeTile(spawn_x, spawn_y)) {
		spawn_x = rand() % m_width;
		spawn_y = rand() % m_height;
		spawn_tries++;
		if (spawn_tries >= 40) {
			std::cout << "Took too many tries to find a suitable spawn, aborting...\n";
			return;
		}
	}

	SetTileOwner(spawn_x, spawn_y, id_counter);
	auto& new_country = m_countries.emplace_back(std::make_unique<Country>(id_counter));
	new_country->ExpandTerritory(*this, spawn_x, spawn_y);

	id_counter++;
}

void Map::Tick()
{
	for (auto& country : m_countries)
		country->Tick();
}

void Map::Draw(sf::Image& out_image)
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			sf::Color colour;

			if (TileOwner(x, y) == NO_OWNER)
				m_terrain_map[x + y * m_width] == TerrainType::Water ? colour = sf::Color::Blue : colour = sf::Color::Green;
			else
				colour = m_countries[m_country_map[x + y * m_width]]->Colour();

			out_image.setPixel(x, y, colour);
		}
	}
}
