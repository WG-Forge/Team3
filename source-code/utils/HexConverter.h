#ifndef TEAM3_HEXCONVERTER_H
#define TEAM3_HEXCONVERTER_H

#include <string>
#include <sstream>

class HexConverter {
public:
    static std::string intToHex(unsigned int n);
    static std::string stringToHex(const std::string& s);
    static int hexToInt(unsigned char* hex);
    static std::string hexToString(const std::string& hex);
};


#endif //TEAM3_HEXCONVERTER_H
