#ifndef SONG_HPP
#define SONG_HPP

#include <string>

class Song {
public:
    std::string title;
    std::string artist;
    double duration;

    Song(std::string t, std::string a, double d);
};

#endif
