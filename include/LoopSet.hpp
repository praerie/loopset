#ifndef LOOPSET_HPP
#define LOOPSET_HPP

#include "Node.hpp"
#include <string>

enum class SortBy {
    Title,
    Artist,
    Duration
};

/**
 * @brief Manages a doubly-linked list of songs as a looping playlist.
 */
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
    void sortPlaylist(SortBy by);
    void reversePlaylist();

    Node* getCurrent() const;
    void restoreCurrentByTitle(const std::string& title);
};

#endif
