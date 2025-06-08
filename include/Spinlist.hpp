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

    void add_song(std::string title, std::string artist, double duration);
    bool remove_song(std::string title);
    Node* find_song(std::string title);
    void play_next();
    void play_previous();
    void display_playlist();

    void shuffle_playlist();
    void sort_playlist(std::string by);
    void reverse_playlist();
};

#endif
