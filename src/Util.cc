#include "Util.hh"

#include <random>
#include <sstream>

static unsigned int random_char() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return dis(gen);
}

static std::string randomHex(unsigned int len) {
    std::stringstream ss;
    for (auto i = 0; i < len; i++) {
        const auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << rc;
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? '0' + hex : hex);
    }
    return ss.str();
}

std::string Util::getUuid() {
    std::stringstream hexstream;
    hexstream << randomHex(4) << "-" << randomHex(2) << "-" << randomHex(2) <<
        "-" << randomHex(2) << "-" << randomHex(6);
    return hexstream.str();
}