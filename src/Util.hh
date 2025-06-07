#pragma once

#include <string>

/**
 * This is where we put useful stuff with nowhere else to go.
 */
namespace Util {
    /**
     * Gives you a UUID (not the same thing as a UID don't worry).
     * It is guaranteed that the first 
     * @return a unique numerical id.
     */
    std::string getUuid();
};