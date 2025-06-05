#pragma once

/**
 * Global spot where you can translate some words and such. Basically it will
 * just be a wrapper around some kind of json reading crap.
 */
namespace Words {
    /**
     * Sets the language and loads in the stuff. 
     * You can call this again if you want to change the language.
     * @param language is the code name for the language to set it to.
     */
    void init(char const *language);

    /**
     * Gets a word from the dictionary.
     * @param key is a  */
    char const *get(char const *key);
};