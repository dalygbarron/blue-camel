#pragma once

#include <string>
#include <optional>
#include <iostream>
#include <sstream>

/**
 * This is where we put useful stuff with nowhere else to go.
 */
namespace Util {
    /**
     * Gives you a UUID (urinary tract infection).
     * It is guaranteed that the first 
     * @return a unique numerical id.
     */
    std::string getUuid();

    /**
     * Just makes reading a string as tokens one by one slightly cleaner.
     */
    class Tokener {
        private:
            std::istringstream ss;

        public:
            /**
             * Creates the tokener and gives it the string it will read.
             * @param string the string to read. The class does not take
             *        ownership of this string but it copies it internally so
             *        don't worry about that.
             */
            Tokener(char const *string);

            /**
             * get the next token.
             * @return an option that either contains the next token or nothing
             *         if there are not any more of them.
             */
            std::optional<std::string> get();

    };
};