//Project by: Robert Parrish, Ryan Parker

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>

sf::Vector2f betweenPoint(sf::Vector2f point1, sf::Vector2f point2, float between);

sf::Text textSettings(const sf::Font& font, sf::String str, int charSize, const sf::Color& color, const sf::Uint32 style = sf::Text::Regular);

short runMainMenu(sf::RenderWindow& window, sf::Event& event);

void runChaosTriangle(sf::RenderWindow& window, sf::Event& event);

void runChaos5orMoreVerts(sf::RenderWindow& window, sf::Event& event);

void runChaosFern(sf::RenderWindow& window, sf::Event& event);
