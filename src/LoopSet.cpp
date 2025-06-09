#include "LoopSet.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

LoopSet::LoopSet()
    : head(nullptr), tail(nullptr), current(nullptr) {}

LoopSet::~LoopSet() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

void LoopSet::addSong(std::string title, std::string artist, int minutes, int seconds) {
    Song newSong(title, artist, minutes, seconds);  // create a Song object
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

    std::cout << "Added: \"" << title << "\" by " << artist
          << " (" << minutes << "m " << seconds << "s)" << std::endl;

}

void LoopSet::displayPlaylist() {
    Node* temp = head;
    if (!temp) {
        std::cout << "The playlist is empty.\n";
        return;
    }

    std::cout << "Current Playlist:\n";
    while (temp) {
        std::cout << "- \"" << temp->song.title << "\" by " << temp->song.artist
                  << " (" << temp->song.minutes << "m " << temp->song.seconds << "s)\n";
        temp = temp->next;
    }
}

void LoopSet::playNext() {
    if (!current) {
        std::cout << "Playlist is empty.\n";
        return;
    }

    if (current->next) {
        current = current->next;  // move to next song
    } else {
        current = head;  // loop back to start
    }

    std::cout << "Now playing: \"" << current->song.title << "\" by "
              << current->song.artist << " (" 
              << current->song.minutes << "m "
              << current->song.seconds << "s)\n";
}
