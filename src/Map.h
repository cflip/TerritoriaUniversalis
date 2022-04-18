#pragma once

#include "Country.h"
#include <SFML/Graphics/Image.hpp>
#include <cstdint>
#include <map>
#include <memory>

class Map {
public:
	explicit Map(sf::Image& terrain_map);
	~Map() { delete m_tiles; }

	void AddCountry();
	void Draw(sf::Image&);

private:
	unsigned m_width, m_height;
	uint8_t* m_tiles;
	std::map<unsigned, std::unique_ptr<Country>> m_country_map;
};
