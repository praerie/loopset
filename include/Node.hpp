#ifndef NODE_HPP
#define NODE_HPP

#include "Song.hpp"

/**
 * @brief A node in the doubly linked list representing a song in the playlist.
 */
class Node {
public:
    Song song;
    Node* next;
    Node* prev;

    /**
     * @brief Constructs a node with the given song.
     * @param s The song to wrap in this node.
     */
    Node(Song s);
};

#endif
