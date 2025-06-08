#include "Spinlist.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

void Spinlist::addSong(std::string title, std::string artist, double duration) {
    Song newSong(title, artist, duration);  // create a Song object
    Node* newNode = new Node(newSong);  // wrap it in a new Node

    if (head == nullptr) {
        // if list is empty, new node is head, tail, and current
        head = tail = current = newNode;
    } else {
        // add new song to end of list
        tail->next = newNode;  // link the last node's "next" to the new one
        newNode->prev = tail;  // link new node's "prev" back to the old tail
        tail = newNode;        // move tail to point to the new node
    }

    std::cout << "Added: \"" << title << "\" by " << artist << " (" << duration << " mins)" << std::endl;
}
