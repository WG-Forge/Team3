#include "HexConverter.h"

std::string HexConverter::intToHex(unsigned int n) {
    std::string hex;
    hex.push_back(n & 0xFF);
    hex.push_back((n >> 8) & 0xFF);
    hex.push_back((n >> 16) & 0xFF);
    hex.push_back((n >> 24) & 0xFF);
    return hex;
}

std::string HexConverter::stringToHex(const std::string& s) {
    std::stringstream ss;
    for(auto c : s) {
        char cHex = (int) c & 0xFF;
        ss << std::hex << cHex;
    }
    return(ss.str());
}

int HexConverter::hexToInt(std::string hex) {
    int displayValue = (unsigned char) hex[0];
    displayValue |= (unsigned char) hex[1] << 8;
    displayValue |= (unsigned char) hex[2] << 16;
    displayValue |= (unsigned char) hex[3] << 24;
    return displayValue;
}

std::string HexConverter::hexToString(const std::string& hex) {
    std::string s;
    for(auto c : hex) {
        s.push_back(char(c));
    }
    return s;
}
