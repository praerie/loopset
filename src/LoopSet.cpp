#include "LoopSet.hpp"
#include "utils.hpp"
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

void LoopSet::restoreCurrentByTitle(const std::string& title) {
    current = head;
    while (current && current->song.title != title) {
        current = current->next;
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
        std::cout << (temp == current ? ">> " : "   ");
        std::cout << "\"" << temp->song.title << "\" by " << temp->song.artist
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
}

bool LoopSet::removeSong(std::string titleInput) {
    std::string originalTitle = "";
    std::string loweredTitle = toLower(titleInput);
    Node* temp = head;

    while (temp != nullptr) {
        if (toLower(temp->song.title) == loweredTitle) {
            originalTitle = temp->song.title;  // capture original casing

            if (temp == head) {
                head = temp->next;
                if (head) head->prev = nullptr;
            } else {
                temp->prev->next = temp->next;
            }

            if (temp == tail) {
                tail = temp->prev;
                if (tail) tail->next = nullptr;
            } else {
                if (temp->next) temp->next->prev = temp->prev;
            }

            if (temp == current) {
                current = temp->next ? temp->next : head;
            }

            delete temp;
            std::cout << "Removed: \"" << originalTitle << "\" from the playlist.\n";
            return true;
        }
        temp = temp->next;
    }

    std::cout << "Song \"" << originalTitle << "\" not found in playlist.\n";
    return false;
}

bool LoopSet::findSong(const std::string& titleInput) {
    std::string originalTitle = "";
    std::string loweredTitle = toLower(titleInput);
    Node* temp = head;

    while (temp != nullptr) {
        if (toLower(temp->song.title) == loweredTitle) {
            originalTitle = temp->song.title;  // capture original casing

            std::cout << "Found: \"" << temp->song.title << "\" by "
                      << temp->song.artist << " ("
                      << temp->song.minutes << "m "
                      << temp->song.seconds << "s)\n";

            std::string choice;
            while (true) {
                std::cout << "What would you like to do? (p = play, r = remove, enter = nothing): ";
                std::getline(std::cin, choice);
                if (choice.empty()) {
                    std::cout << "No action was taken.";
                    break;
                }

                if (choice == "p" || choice == "P") {
                    current = temp;
                    break;
                } else if (choice == "r" || choice == "R") {
                    removeSong(temp->song.title); 
                    break;
                } else {
                    std::cout << "Invalid input. Try again.\n";
                }
            }

            return true;
        }
        temp = temp->next;
    }

    std::cout << "Song \"" << originalTitle << "\" not found in playlist.\n";
    return false;
}

void LoopSet::shufflePlaylist() {
    //step 0: save current song before changes
    std::string currentTitle = current ? current->song.title : "";

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
    restoreCurrentByTitle(currentTitle);

    std::cout << "Playlist shuffled.\n";
}

std::string sortByToString(SortBy by) {
    switch (by) {
        case SortBy::Title:    return "title";
        case SortBy::Artist:   return "artist";
        case SortBy::Duration: return "duration";
        default:               return "unknown";
    }
}

void LoopSet::sortPlaylist(SortBy by) {
    //step 0: save current song before changes
    std::string currentTitle = current ? current->song.title : "";

    if (!head) return;

    // step 1: extract all nodes into a vector
    std::vector<Node*> nodes;
    Node* temp = head;
    while (temp) {
        nodes.push_back(temp);  // append temp to nodes vector
        temp = temp->next;
    }

    // step 2: sort based on selected attribute
    switch (by) {
        case SortBy::Title:
            std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
                return a->song.title < b->song.title;
            });
            break;
        case SortBy::Artist:
            std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
                return a->song.artist < b->song.artist;
            });
            break;
        case SortBy::Duration:
            std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
                int aTotal = a->song.minutes * 60 + a->song.seconds;
                int bTotal = b->song.minutes * 60 + b->song.seconds;
                return aTotal < bTotal;
            });
            break;
    }

    // step 3: reconnect the nodes
    for (size_t i = 0; i < nodes.size(); ++i) {
        // set previous pointer: if this is the first node, prev is null; else point to the previous node in the list
        nodes[i]->prev = (i == 0) ? nullptr : nodes[i - 1];
        // set next pointer: if this is the last node, next is null; else point to the next node in the list
        nodes[i]->next = (i == nodes.size() - 1) ? nullptr : nodes[i + 1];
    }

    // step 4: update head, tail, and current
    head = nodes[0];
    tail = nodes.back();
    restoreCurrentByTitle(currentTitle);

    std::cout << "Playlist sorted by \"" << sortByToString(by) << "\".\n";
}

void LoopSet::reversePlaylist() {
    //step 0: save current song before changes
    std::string currentTitle = current ? current->song.title : "";

    if (!head || !head->next) {
        std::cout << "Playlist is too short to reverse.\n";
        return;
    }

    Node* temp = nullptr;
    Node* currentNode = head;

    // swap next and prev for all nodes
    while (currentNode) {
        temp = currentNode->prev;
        currentNode->prev = currentNode->next;
        currentNode->next = temp;
        currentNode = currentNode->prev;  // previously currentNode->next
    }

    // swap head and tail
    temp = head;
    head = tail;
    tail = temp;

    restoreCurrentByTitle(currentTitle);

    std::cout << "Playlist order has been reversed.\n";
}

Node* LoopSet::getCurrent() const {
    return current;
}
