#ifndef NODE_HPP
#define NODE_HPP

#include "Song.hpp"

class Node {
public:
    Song song;
    Node* next;
    Node* prev;

    Node(Song s);  // constructor
};

#endif