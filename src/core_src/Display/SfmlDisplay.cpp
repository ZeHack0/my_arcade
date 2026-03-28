/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** SfmlDisplay
*/

#include "bitmap.hpp"
#include "core.hpp"
#include "Arcade.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace arcade {

    void display_bitmap(sf::RenderWindow &wind, std::map<std::pair<std::size_t, std::size_t>, ACube> &bitmap)
    {
        sf::RectangleShape pixel(sf::Vector2f(1, 1));

        for (auto &[key, val] : bitmap) {
            pixel.setPosition(static_cast<float>(key.first), static_cast<float>(key.second));
            pixel.setFillColor(sf::Color(val.getred(), val.getgreen(), val.getred()));
            wind.draw(pixel);
        }
    }
}