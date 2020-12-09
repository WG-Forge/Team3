#pragma once

#include <string_view>

namespace defines {
    namespace player_info {
        constexpr std::string_view PLAYER_NAME = "Team 3";
        constexpr std::string_view PASSWORD = "Est' probitie!";
    }

    namespace server_info {
        constexpr static std::string_view SERVER_HOSTNAME = "wgforge-srv.wargaming.net";
        constexpr static std::string_view PORT = "443";
    }
}