#include "Song.hpp"

/**
 * @brief Constructs a Song with the given title, artist, and duration.
 * 
 * @param t The title of the song.
 * @param a The artist of the song.
 * @param m Duration minutes.
 * @param s Duration seconds.
 */
Song::Song(std::string t, std::string a, int m, int s)
    : title(t), artist(a), minutes(m), seconds(s) {}

