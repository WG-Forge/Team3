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
}