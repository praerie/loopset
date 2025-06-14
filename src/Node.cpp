#include "Node.hpp"

/**
 * @brief Constructs a Node with the provided Song.
 * 
 * Initializes the song data and sets both next and prev pointers to nullptr.
 * 
 * @param s The Song object to store in this node.
 */
Node::Node(Song s)
    : song(s), next(nullptr), prev(nullptr) {}
