#ifndef TEAM3_BINARYCONVERTER_H
#define TEAM3_BINARYCONVERTER_H

#include <string>
#include <sstream>

class BinaryConverter {
public:
    static std::string intToHex(unsigned int n);
    static std::string stringToHex(std::string s);
    static int hexToInt(std::string hex);
    static std::string hexToString(std::string hex);
};


#endif //TEAM3_BINARYCONVERTER_H
