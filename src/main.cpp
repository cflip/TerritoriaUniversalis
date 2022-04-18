#include <SFML/Graphics.hpp>

#include "Map.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Territorium");

	sf::Texture map_texture;
	if (!map_texture.loadFromFile("res/map.png"))
		return 1;

	sf::Image map_image = map_texture.copyToImage();
	sf::Sprite sprite(map_texture);

	Map map(map_image);
	map.AddCountry();

	float zoom = 2.f;
	int drag_x = 0, drag_y = 0;
	int pan_x = 0, pan_y = 0;
	bool is_dragging = false;

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left && !is_dragging) {
					drag_x = event.mouseButton.x;
					drag_y = event.mouseButton.y;
					is_dragging = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left && is_dragging)
					is_dragging = false;
				break;
			case sf::Event::MouseMoved:
				if (is_dragging) {
					pan_x += event.mouseMove.x - drag_x;
					pan_y += event.mouseMove.y - drag_y;
					drag_x = event.mouseMove.x;
					drag_y = event.mouseMove.y;
				}
				break;
			case sf::Event::MouseWheelScrolled:
				zoom += event.mouseWheelScroll.delta / 4.f;
				if (zoom < 0.25f) zoom = 0.25f;
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		map.Draw(map_image);
		map_texture.loadFromImage(map_image);
		sprite.setPosition((float)pan_x, (float)pan_y);
		sprite.setScale(zoom, zoom);

		window.clear({ 0, 8, 4 });
		window.draw(sprite);
		window.display();
	}

	return 0;
}
