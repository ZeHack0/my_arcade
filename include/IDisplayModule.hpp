/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** IDisplayModule
*/

#pragma once
#include "GenericEvent.hpp"
#include "GameData.hpp"

namespace arcade {

    class IDisplayModule {

        public:
            virtual ~IDisplayModule() = default;

            virtual ArcadeEvent getEvents() = 0;
            virtual void clear() = 0;
            virtual void draw(GameData data) = 0;
            virtual void display() = 0;

    };

}
