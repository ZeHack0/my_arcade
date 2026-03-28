/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** bitmap
*/

#pragma once
#include <cstdio>
#include <SFML/Graphics.hpp>

namespace arcade {

    class ACube {

        private:
            int _red;
            int _blue;
            int _green;

        public:
            ACube();
            ACube(int, int, int);
            ~ACube() {};
            int getblue();
            int getred();
            int getgreen();
            void setPixel(int, int, int);
            void setblue(int);
            void setred(int);
            void setgreen(int);

            bool operator<(const ACube& o) const {
                return _blue <= o._blue;
            }

    };

    void display_bitmap(sf::RenderWindow &, std::map<std::pair<std::size_t, std::size_t>, ACube> &);

}
