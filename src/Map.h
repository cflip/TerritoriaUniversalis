#pragma once

#include "Country.h"
#include <SFML/Graphics/Image.hpp>
#include <cstdint>
#include <vector>
#include <memory>

#define NO_OWNER 1337

enum class TerrainType : uint8_t {
	Water,
	Ground
};

class Map {
public:
	explicit Map(sf::Image& terrain_map);

	~Map()
	{
		delete[] m_terrain_map;
		delete[] m_country_map;
	}

	TerrainType TerrainType(int x, int y) const;
	uint16_t TileOwner(int x, int y) const;
	void SetTileOwner(int x, int y, int id);
	void AddCountry();

	bool IsFreeTile(int x, int y) const { return TerrainType(x, y) == TerrainType::Ground && TileOwner(x, y) == NO_OWNER; };
	bool InBounds(int x, int y) const { return x >= 0 && x < m_width && y >= 0 && y < m_height; }

	void Tick();
	void Draw(sf::Image&);

private:
	unsigned m_width, m_height;
	enum TerrainType* m_terrain_map;
	uint16_t* m_country_map;
	std::vector<std::unique_ptr<Country>> m_countries;
};
