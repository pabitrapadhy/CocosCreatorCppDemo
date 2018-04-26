#include "Globals.h"

std::string Globals::toLowerCase(std::string stringToConvert) {
    std::transform(stringToConvert.begin(), stringToConvert.end(), stringToConvert.begin(), ::tolower); 
    return stringToConvert;
}