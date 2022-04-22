#include "Map.h"
#include <SFML/Graphics.hpp>
int main()
{
	int country_population = 1;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Territoria Universalis");
	window.setFramerateLimit(60);
	sf::View view = window.getDefaultView();

	sf::Texture map_texture;
	if (!map_texture.loadFromFile("res/map.png"))
		return 1;

	sf::Image map_image = map_texture.copyToImage();
	sf::Sprite sprite(map_texture);

	Map map(map_image);

	for (int j = 0; j < country_population; j++) {
		map.AddCountry();
	}

	int drag_x = 0, drag_y = 0;
	bool is_dragging = false;
	float zoomFactor = 0.25f;

	sf::Clock clock;
	constexpr int TicksPerSecond = 10;
	constexpr float MillisPerTick = 1000.f / (float)TicksPerSecond;
	float unprocessed_ticks = 0;
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
					float delta_x = event.mouseMove.x - drag_x;
					float delta_y = event.mouseMove.y - drag_y;
					drag_x = event.mouseMove.x;
					drag_y = event.mouseMove.y;

					view.move(-delta_x  * zoomFactor, -delta_y * zoomFactor);
					window.setView(view);
				}
				break;
			case sf::Event::MouseWheelMoved: {
				if (event.mouseWheel.delta < 0) {
					view.zoom(2.0f);
					zoomFactor *= 2.0f;
				} else {
					view.zoom(0.5f);
					zoomFactor *= 0.5f;
				}
				window.setView(view);
				break;
			}
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		unprocessed_ticks += (float)clock.getElapsedTime().asMilliseconds() / MillisPerTick;
		clock.restart();

		while (unprocessed_ticks >= 1) {
			map.Tick();
			unprocessed_ticks -= 1;
		}

		map.Draw(map_image);
		map_texture.loadFromImage(map_image);

		window.clear({ 0, 8, 4 });
		window.draw(sprite);
		window.display();
	}

	return 0;
}