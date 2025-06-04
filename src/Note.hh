#pragma once

#include <stdint.h>

/**
 * Ok so this is a representation of a note with the usual tracker bells and
 * whistles.
 * Channel is a way of referencing this note later, as some notes
 * are actually just effects that are meant to affect whatever note is playing
 * in that same channel.
 * Pitch is a numerical reference to the note played but it is more like C-1
 * C#-1 etc, not actual pitch in Hz. 0 can be considered a non note if need be.
 * Type's highest bit is whether this is a note on or a note off, the other 7
 * bits represent effect types. Worth noting that effects are DSP specific.
 * Effect is a parameter to the effect if there is one.
 * NB: I think synths can just maintain a list of active notes and iterate on
 * it when they need to find a specific one, at realistic polyphony levels this
 * would be faster than trying to get smart about it I think.
 */
class Note {
    public:
        uint16_t channel;
        uint16_t pitch;
        uint8_t type;
        uint8_t effect;
}
