#include <SFML/Graphics.hpp>

#include "Map.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Territoria Universalis");
	sf::View view = window.getDefaultView();

	sf::Texture map_texture;
	if (!map_texture.loadFromFile("res/map.png"))
		return 1;

	sf::Image map_image = map_texture.copyToImage();
	sf::Sprite sprite(map_texture);

	Map map(map_image);
	map.AddCountry();

	int drag_x = 0, drag_y = 0;
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
					// TODO: This should take into account the current zoom level
					float delta_x = event.mouseMove.x - drag_x;
					float delta_y = event.mouseMove.y - drag_y;
					drag_x = event.mouseMove.x;
					drag_y = event.mouseMove.y;

					view.move(-delta_x, -delta_y);
					window.setView(view);
				}
				break;
			case sf::Event::MouseWheelScrolled: {
				// TODO: This should zoom relative to the mouse pointer's location,
				//       rather than the center of the screen.
				float delta = event.mouseWheelScroll.delta + 1.5f;
				view.zoom(1.f / delta);
				window.setView(view);
				break;
			}
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		map.Draw(map_image);
		map_texture.loadFromImage(map_image);

		window.clear({ 0, 8, 4 });
		window.draw(sprite);
		window.display();
	}

	return 0;
}
