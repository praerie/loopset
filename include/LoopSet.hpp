#ifndef LOOPSET_HPP
#define LOOPSET_HPP

#include "Node.hpp"
#include <string>

class LoopSet {
private:
    Node* head;
    Node* tail;
    Node* current;

public:
    LoopSet(); // constructor
    ~LoopSet(); // deconstructor

    void addSong(std::string title, std::string artist, int minutes, int seconds);
    bool removeSong(std::string title);
    bool findSong(const std::string& title);
    void playNext();
    void playPrevious();
    void displayPlaylist();

    void shufflePlaylist();
    void sortPlaylist(std::string by);
    void reversePlaylist();

    // for testing purposes
    Node* getHead() const;
};

#endif
