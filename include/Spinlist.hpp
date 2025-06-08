#ifndef SPINLIST_HPP
#define SPINLIST_HPP

#include "Node.hpp"
#include <string>

class Spinlist {
private:
    Node* head;
    Node* tail;
    Node* current;

public:
    Spinlist();
    ~Spinlist();

    void addSong(std::string title, std::string artist, double duration);
    bool removeSong(std::string title);
    Node* findSong(std::string title);
    void playNext();
    void playPrevious();
    void displayPlaylist();

    void shufflePlaylist();
    void sortPlaylist(std::string by);
    void reversePlaylist();
};

#endif
