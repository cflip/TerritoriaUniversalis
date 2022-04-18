#include "Map.h"

#include <iostream>

Map::Map(sf::Image& terrain_map)
{
	// Use the provided image to build the initial terrain
	auto map_size = terrain_map.getSize();

	m_width = map_size.x;
	m_height = map_size.y;
	m_tiles = new uint8_t[m_width * m_height];

	for (int i = 0; i < m_width * m_height; i++)
		m_tiles[i] = terrain_map.getPixelsPtr()[i * 4] == 0 ? 0 : 1;

	m_tiles[10 + 10 * m_width] = 2;
}

void Map::AddCountry()
{
	static int id_counter = 0;
	if (id_counter >= 254) {
		std::cout << "Can't add any more countries!\n";
		return;
	}
	m_country_map.emplace(id_counter++, std::make_unique<Country>());
}

void Map::Draw(sf::Image& out_image)
{
	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			sf::Color colour;
			auto current_tile = m_tiles[x + y * m_width];
			if (current_tile < 2)
				current_tile == 0 ? colour = { 0, 0, 255 } : colour = { 0, 255, 0 };
			else
				colour = m_country_map[current_tile - 2]->Colour();
			out_image.setPixel(x, y, colour);
		}
	}
}
