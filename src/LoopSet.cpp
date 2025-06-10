#include "LoopSet.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>

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

bool LoopSet::findSong(const std::string& title) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->song.title == title) {
            std::cout << "Found: \"" << temp->song.title << "\" by "
                      << temp->song.artist << " ("
                      << temp->song.minutes << "m "
                      << temp->song.seconds << "s)\n";
            return true;
        }
        temp = temp->next;
    }

    std::cout << "Song \"" << title << "\" not found in playlist.\n";
    return false;
}

void LoopSet::shufflePlaylist() {
    if (!head || !head->next) {
        std::cout << "Not enough songs to shuffle.\n";
        return;
    }

    // step 1: copy nodes to vector
    std::vector<Node*> nodes;
    Node* temp = head;
    while (temp) {
        nodes.push_back(temp);  // append temp to nodes vector
        temp = temp->next;
    }

    // step 2: shuffle the vector
    // shuffle the order of the node pointers using a random seed based on the current time
    // - nodes.begin() and nodes.end() define the range of elements to shuffle.
    // - std::default_random_engine generates pseudo-random numbers.
    // - static_cast<unsigned>(std::time(nullptr)) seeds the engine with the current time to ensure different results on each run.
    std::shuffle(nodes.begin(), nodes.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

    // step 3: relink nodes in shuffled order
    for (size_t i = 0; i < nodes.size(); ++i) {
        // set previous pointer: if this is the first node, prev is null; else point to the previous node in the list
        nodes[i]->prev = (i == 0) ? nullptr : nodes[i - 1];
        // set next pointer: if this is the last node, next is null; else point to the next node in the list
        nodes[i]->next = (i == nodes.size() - 1) ? nullptr : nodes[i + 1];
    }

    // step 4: update head, tail, and current
    head = nodes.front();
    tail = nodes.back();
    current = head;

    std::cout << "Playlist shuffled.\n";
}


// for testing purposes
Node* LoopSet::getHead() const {
    return head;
}
