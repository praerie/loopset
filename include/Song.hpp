#ifndef SONG_HPP
#define SONG_HPP

#include <string>

class Song {
public:
    std::string title;
    std::string artist;
    int minutes;
    int seconds;

    Song(std::string t, std::string a, int m, int s);
};

#endif
