#ifndef SONG_HPP
#define SONG_HPP

#include <string>

/**
 * @brief Represents a single song with a title, artist, and duration.
 */
class Song {
public:
    std::string title;
    std::string artist;
    int minutes;
    int seconds;

    /**
     * @brief Constructs a new Song object.
     * 
     * @param t The title of the song.
     * @param a The artist of the song.
     * @param m The minutes portion of the song's duration.
     * @param s The seconds portion of the song's duration.
     */
    Song(std::string t, std::string a, int m, int s);
};

#endif
