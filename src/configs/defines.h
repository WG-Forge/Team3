#pragma once

#include <string_view>

namespace defines {
    namespace player_info {
        constexpr std::string_view PLAYER_NAME = "Team 3";
        constexpr std::string_view PASSWORD = "Est' probitie!";
    }

    namespace server_info {
        constexpr std::string_view SERVER_HOSTNAME = "wgforge-srv.wargaming.net";
        constexpr std::string_view PORT = "443";
    }

    namespace render_info {
        constexpr std::string_view NODE_ASSET_PATH =
                "resources/assets/unknown.png";
        constexpr std::string_view TOWN_ASSET_PATH =
                "resources/assets/town.png";
        constexpr std::string_view MARKET_ASSET_PATH =
                "resources/assets/market.png";
        constexpr std::string_view STORAGE_ASSET_PATH =
                "resources/assets/storage.png";
        constexpr std::string_view TRAIN_ASSET_PATH =
                "resources/assets/train.png";
    }

    namespace event_info {
        namespace type {
            constexpr uint32_t TRAIN_COLLISION = 1;
            constexpr uint32_t HIJACKERS_ASSAULT = 2;
            constexpr uint32_t PARASITES_ASSAULT = 3;
            constexpr uint32_t REFUGEES_ARRIVAL = 4;
            constexpr uint32_t RESOURCE_OVERFLOW = 5;
            constexpr uint32_t RESOURCE_LACK = 6;
            constexpr uint32_t GAME_OVER = 100;
        };

        namespace data_key {
            constexpr std::string_view TRAIN_COLLISION_KEY = "train";
            constexpr std::string_view HIJACKERS_ASSAULT_KEY = "hijackers_power";
            constexpr std::string_view PARASITES_ASSAULT_KEY = "parasites_power";
            constexpr std::string_view REFUGEES_ARRIVAL_KEY = "refugees_number";
        };
    }
}