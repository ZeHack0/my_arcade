/*
** EPITECH PROJECT, 2026
** arcade
** File description:
** IGameModule
*/

#pragma once
#include "GameData.hpp"
#include "GenericEvent.hpp"

namespace arcade {

    class IGameModule {

        public:
            virtual ~IGameModule() = default;

            virtual void update(ArcadeEvent) = 0;
            virtual GameData getGameData() = 0;
    };

}
