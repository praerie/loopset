#include <iostream>
#include <limits>
#include "LoopSet.hpp"

int main() {
    LoopSet myPlaylist;

    // preload songs
    myPlaylist.addSong("In Camera", "Yumi Zouma", 3, 24);
    myPlaylist.addSong("Mulholland", "Hope Tala, sky", 3, 44);
    myPlaylist.addSong("Peaceful Place", "Leon Bridges", 4, 15);
    myPlaylist.addSong("Bilgewater", "Brown Bird", 3, 55);
    myPlaylist.addSong("ENTROPY", "Daniel Caesar", 4, 21);
    myPlaylist.addSong("Cosmic", "Amber Mark", 4, 35);
    myPlaylist.addSong("Red Bottom Sky", "Yung Lean", 5, 3);
    myPlaylist.addSong("Hazey", "Glass Animals", 4, 26);
    myPlaylist.addSong("Nothing Better", "The Postal Service", 3, 47);
    myPlaylist.addSong("Le Matin", "Yann Tiersen", 1, 59);

    Node* nowPlaying = myPlaylist.getCurrent();  
    if (nowPlaying) {
        std::cout << "\nNow Playing: \"" << nowPlaying->song.title << "\" by "
                << nowPlaying->song.artist << " ("
                << nowPlaying->song.minutes << "m "
                << nowPlaying->song.seconds << "s)\n";
    } else {
        std::cout << "\nNo song is currently playing.\n";
    }

    int choice;

    do {
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
                std::string title, artist;
                int minutes, seconds;

                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter artist: ";
                std::getline(std::cin, artist);

                std::cout << "Enter minutes: ";
                std::cin >> minutes;
                if (std::cin.fail() || minutes < 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid minutes input.\n";
                    break;
                }

                std::cout << "Enter seconds: ";
                std::cin >> seconds;
                if (std::cin.fail() || seconds < 0 || seconds > 59) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid seconds input. Must be 0-59.\n";
                    break;
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                myPlaylist.addSong(title, artist, minutes, seconds);
                break;
            }
            case 5: {
                std::string title;
                std::cout << "Enter song title to remove: ";
                std::getline(std::cin, title);
                myPlaylist.removeSong(title);
                break;
            }
            case 6: {
                std::string title;
                std::cout << "Enter song title to find: ";
                std::getline(std::cin, title);
                myPlaylist.findSong(title);
                break;
            }
            case 7:
                myPlaylist.shufflePlaylist();
                break;
            case 8: {
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
