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

void LoopSet::playPrevious() {
    if (!current) {
        std::cout << "Playlist is empty.\n";
        return;
    }

    if (current->prev) {
        current = current->prev;  // go back to previous song 
    } else {
        current = tail;  // play last song in list 
    }

    std::cout << "Now playing: \"" << current->song.title << "\" by "
              << current->song.artist << " (" 
              << current->song.minutes << "m "
              << current->song.seconds << "s)\n";
}

bool LoopSet::removeSong(std::string title) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->song.title == title) {
            if (temp == head) {
                head = temp->next;  // move head forward if removing the first song
                if (head) head->prev = nullptr;  // update new head's prev pointer
            } else {
                temp->prev->next = temp->next;  // bridge the previous node to the next
            }

            if (temp == tail) {
                tail = temp->prev;  // update tail if we're removing the last song
                if (tail) tail->next = nullptr;  // ensure the new tail has no next node
            } else {
                if (temp->next) temp->next->prev = temp->prev;  // link next node back to temp's previous node
            }

            if (temp == current) {
                current = temp->next ? temp->next : head;  // move current forward, or loop to head if at end
            }

            delete temp;
            std::cout << "Removed: \"" << title << "\" from the playlist.\n";
            return true;
        }
        temp = temp->next;
    }

    std::cout << "Song \"" << title << "\" not found.\n";
    return false;
}

// for testing purposes
Node* LoopSet::getHead() const {
    return head;
}
