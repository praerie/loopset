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

/**
 * @brief Adds a new song to the end of the playlist.
 * 
 * This function creates a new Song object with the given title, artist, 
 * and duration (mins and secs), wraps it in a Node, and appends it to the playlist.
 * If the playlist is empty, the new song becomes the head, tail, and current.
 * 
 * @param title The title of the song.
 * @param artist The artist of the song.
 * @param minutes The duration of the song in minutes.
 * @param seconds The duration of the song in seconds.
 */
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

/**
 * @brief Displays all songs in the playlist.
 * 
 * Prints each song in the playlist to the console, indicating the currently
 * playing song with a ">>" marker. If the playlist is empty, displays a message
 * stating that the playlist is empty.
 */
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

/**
 * @brief Advances the current pointer to the next song in the playlist.
 * 
 * If at the end of the list, wraps around to the head.
 * Does not print any output.
 */
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

/**
 * @brief Moves the current pointer to the previous song in the playlist.
 * 
 * If at the beginning of the list, wraps around to the tail.
 * Does not print any output.
 */
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

/**
 * @brief Removes a song from the playlist by title (case-insensitive).
 * 
 * The input title is normalized to lowercase for comparison, but the original
 * song title's casing is preserved for display messages. If the song is found,
 * it is removed from the linked list, memory is freed, and a success message
 * is printed. If the song is currently playing, the 'current' pointer is updated
 * to the next song, or to the head if no next exists.
 * 
 * @param titleInput The title of the song to remove, as entered by the user.
 * @return true if the song was successfully removed, false if not found.
 */
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

/**
 * @brief Searches the playlist for a song by title (case-insensitive).
 * 
 * If the song is found, it displays its full details and prompts the user
 * for an action: play the song, remove it, or do nothing. The original
 * casing of the song title is preserved for user-facing messages.
 * 
 * @param titleInput The title of the song to search for, as entered by the user.
 * @return true if the song was found, false otherwise.
 */
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

/**
 * @brief Shuffles the playlist while preserving the current song.
 * 
 * This function randomizes the order of the songs in the playlist
 * using std::shuffle, relinks the nodes accordingly, 
 * and restores the current song by matching its original title.
 * 
 * If the playlist is empty or has only one song, it skips shuffling.
 */
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

/**
 * @brief Converts a SortBy enum value to a lowercase string.
 * 
 * @param by The SortBy enum value.
 * @return A string representation of the sort criterion ("title", "artist", or "duration").
 */
std::string sortByToString(SortBy by) {
    switch (by) {
        case SortBy::Title:    return "title";
        case SortBy::Artist:   return "artist";
        case SortBy::Duration: return "duration";
        default:               return "unknown";
    }
}

/**
 * @brief Sorts the playlist by the specified attribute (title, artist, or duration).
 * 
 * This function extracts all nodes into a vector, sorts them using the selected 
 * attribute, then re-links the list in the new order. It also preserves the 
 * currently playing song by restoring it by title after sorting.
 * 
 * @param by The attribute to sort the playlist by (SortBy::Title, SortBy::Artist, or SortBy::Duration).
 */
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

/**
 * @brief Reverses the order of the songs in the playlist.
 * 
 * This function swaps the next and previous pointers for each node in the playlist
 * to reverse the order. It also preserves the currently playing song by restoring it
 * by title after the reversal.
 * 
 * If the playlist has fewer than two songs, it will print a message and return.
 */
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

/**
 * @brief Returns a pointer to the currently playing song node.
 * 
 * @return Node* Pointer to the current song node, or nullptr if the playlist is empty.
 */
Node* LoopSet::getCurrent() const {
    return current;
}
