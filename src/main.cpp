#include <SFML/Graphics.hpp>

#include "include/PerlinNoise.hpp"

#include <cstdint>

#include <iostream>

constexpr unsigned int WIDTH = 512;
constexpr unsigned int HEIGHT = 512;

int main() {
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Perlin Noise", sf::Style::Close);

	PerlinNoise noise(157230198);

	sf::Image image({ WIDTH, HEIGHT }, sf::Color::Black);

	for (unsigned int y = 0; y < HEIGHT; ++y) {
		for (unsigned int x = 0; x < WIDTH; ++x) {
			float nx = x * 0.02f;
			float ny = y * 0.02f;

			float value = noise.fbm(nx, ny);

			value = ((value + 1.f) * 0.5f);

			std::uint8_t c = static_cast<std::uint8_t>(value * 255);
			image.setPixel({ x, y }, sf::Color(c, c, c));
		}
	}

	sf::Texture texture;
	if (!texture.loadFromImage(image)) {
		std::cerr << "Couldn't load the image.\n";
		return 1;
	};

	sf::Sprite sprite(texture);

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}