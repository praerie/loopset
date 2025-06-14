#include "LoopSet.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <limits>
#include <cctype>

/**
 * @brief Handles the user interface and control flow for the playlist manager.
 * 
 * The main function runs an interactive loop that allows users to manage a playlist 
 * through a text-based menu. It supports displaying, adding, removing, shuffling, 
 * sorting, reversing, and navigating songs in the playlist. It also handles input 
 * validation and maintains the current song state throughout the session.
 * 
 * @return int Exit status code.
 */
int main() {
    LoopSet myPlaylist;

    // preload songs
    myPlaylist.addSong("ENTROPY", "Daniel Caesar", 4, 21);
    myPlaylist.addSong("Cosmic", "Amber Mark", 4, 35);
    myPlaylist.addSong("Red Bottom Sky", "Yung Lean", 5, 3);
    myPlaylist.addSong("Hazey", "Glass Animals", 4, 26);
    myPlaylist.addSong("Nothing Better", "The Postal Service", 3, 47);
    myPlaylist.addSong("Le Matin", "Yann Tiersen", 1, 59);
    myPlaylist.addSong("In Dreams", "Roy Orbison", 3, 24);
    myPlaylist.addSong("Mulholland", "Hope Tala, sky", 3, 44);
    myPlaylist.addSong("Peaceful Place", "Leon Bridges", 4, 15);
    myPlaylist.addSong("Bilgewater", "Brown Bird", 3, 55);

    int choice;

    do {
        // currently playing song display
        Node* nowPlaying = myPlaylist.getCurrent();  
        if (nowPlaying) {
            std::cout << "\n>> Currently playing: \"" << nowPlaying->song.title << "\" by "
                    << nowPlaying->song.artist << " ("
                    << nowPlaying->song.minutes << "m "
                    << nowPlaying->song.seconds << "s)\n";
        } else {
            std::cout << "\nNo song is currently playing.\n";
        }
        
        std::cout << "\nMenu:\n";
        std::cout << "1. Display playlist\n";
        std::cout << "2. Play next\n";
        std::cout << "3. Play previous\n";
        std::cout << "4. Add song\n";
        std::cout << "5. Remove song\n";
        std::cout << "6. Find song\n";
        std::cout << "7. Shuffle playlist\n";
        std::cout << "8. Sort playlist\n";
        std::cout << "9. Reverse playlist\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                myPlaylist.displayPlaylist();
                break;
            case 2:
                myPlaylist.playNext();
                break;
            case 3:
                myPlaylist.playPrevious();
                break;
            case 4: {
                // get title
                std::string title = getValidatedInput("Enter title (or leave blank to cancel): ");
                if (title.empty()) break;

                // get artist
                std::string artist = getValidatedInput("Enter artist (or leave blank to cancel): ");
                if (artist.empty()) break;

                std::string input;
                int minutes = -1, seconds = -1;

                // get minutes
                while (true) {
                    std::cout << "Enter minutes: ";
                    std::getline(std::cin, input);
                    std::stringstream ss(input);
                    if ((ss >> minutes) && minutes >= 0) break;
                    std::cout << "Invalid input. Try again.\n";
                }

                // get seconds
                while (true) {
                    std::cout << "Enter seconds: ";
                    std::getline(std::cin, input);
                    std::stringstream ss(input);
                    if ((ss >> seconds) && seconds >= 0 && seconds < 60) break;
                    std::cout << "Invalid input. Try again.\n";
                }

                myPlaylist.addSong(title, artist, minutes, seconds);
                break;
            }
            case 5: {
                while (true) {
                    std::string title = getValidatedInput("Enter song title to remove (or leave blank to cancel): ");
                    if (title.empty()) break;

                    if (myPlaylist.removeSong(title)) {
                        break;  // found and handled
                    } else {
                        std::cout << "Try again or press enter to cancel.\n";
                    }
                }
                break;
            }
            case 6: {
                std::string title;
                while (true) {
                    title = getValidatedInput("Enter song title to find (or leave blank to cancel): ");
                    if (title.empty()) break;

                    if (myPlaylist.findSong(title)) {
                        break;  // found and handled
                    } else {
                        std::cout << "Try again or press enter to cancel.\n";
                    }
                }
                break;
            }
            case 7:
                myPlaylist.shufflePlaylist();
                break;
            case 8: {
                if (!myPlaylist.getCurrent()) {
                    std::cout << "The playlist is empty.\n";
                    break;
                }

                int sortOption;

                while (true) {
                    std::cout << "Sort by: 1) Title  2) Artist  3) Duration  (0 to cancel): ";
                    std::string input;
                    std::getline(std::cin, input);

                    if (input.empty() || input == "0") {
                        std::cout << "Sort cancelled.\n";
                        break;
                    }

                    try {
                        sortOption = std::stoi(input);
                        if (sortOption >= 1 && sortOption <= 3) {
                            SortBy sortType = (sortOption == 1) ? SortBy::Title
                                            : (sortOption == 2) ? SortBy::Artist
                                            : SortBy::Duration;
                            myPlaylist.sortPlaylist(sortType);
                            myPlaylist.displayPlaylist();
                            break;
                        } else {
                            std::cout << "Invalid option. Please enter 1, 2, 3, or 0 to cancel.\n";
                        }
                    } catch (...) {
                        std::cout << "Invalid input. Please enter a number.\n";
                    }
                }
                break;
            }
            case 9:
                myPlaylist.reversePlaylist();
                break;
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
