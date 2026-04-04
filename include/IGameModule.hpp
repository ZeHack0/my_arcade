/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** IGameModule
*/

#pragma once
#include "GameData.hpp"
#include "ArcadeEvents.hpp"

namespace arcade {

    class IGameModule {

        public:
            virtual ~IGameModule() = default;

            virtual void update(ArcadeEvents) = 0;
            virtual GameData getGameData() = 0;
    };

}
