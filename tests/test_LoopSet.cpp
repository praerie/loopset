#include "LoopSet.hpp"
#include <cassert>
#include <iostream>

void testAddSongs() {
    LoopSet testPlaylist;

    testPlaylist.addSong("In Camera", "Yumi Zouma", 3, 24);
    testPlaylist.addSong("Mulholland", "Hope Tala, sky", 3, 44);

    Node* head = testPlaylist.getHead();

    assert(head != nullptr);
    assert(head->song.title == "In Camera");
    assert(head->next != nullptr);
    assert(head->next->song.title == "Mulholland");
    assert(head->next->prev == head);
}

void testDisplayPlaylist() {
    LoopSet testPlaylist;

    testPlaylist.addSong("In Camera", "Yumi Zouma", 3, 24);
    testPlaylist.addSong("Mulholland", "Hope Tala, sky", 3, 44);

    testPlaylist.displayPlaylist();
}

void testPlayNavigation() {
    LoopSet testPlaylist;
    testPlaylist.addSong("Song A", "Artist", 3, 30);
    testPlaylist.addSong("Song B", "Artist", 3, 30);
    testPlaylist.addSong("Song C", "Artist", 3, 30);

    testPlaylist.playNext(); // song B
    testPlaylist.playNext(); // song C
    testPlaylist.playNext(); // wrap to Song A

    testPlaylist.playPrevious(); // song C again
}

void testRemoveSong() {
    LoopSet testPlaylist;
    testPlaylist.addSong("Keep Me", "Artist", 3, 10);
    testPlaylist.addSong("Delete Me", "Artist", 4, 10);
    testPlaylist.addSong("Keep Me Too", "Artist", 2, 50);

    assert(testPlaylist.removeSong("Delete Me") == true);
    assert(testPlaylist.removeSong("Ghost Song") == false);
}

void testFindSong() {
    LoopSet testPlaylist;

    testPlaylist.addSong("In Camera", "Yumi Zouma", 3, 24);
    testPlaylist.addSong("Mulholland", "Hope Tala, sky", 3, 44);

    assert(testPlaylist.findSong("In Camera") == true);
    assert(testPlaylist.findSong("Ghost Song") == false);
}

void testShufflePlaylist() {
    LoopSet testPlaylist;

    testPlaylist.addSong("A", "Artist", 1, 1);
    testPlaylist.addSong("B", "Artist", 1, 2);
    testPlaylist.addSong("C", "Artist", 1, 3);
    testPlaylist.addSong("D", "Artist", 1, 4);
    testPlaylist.addSong("E", "Artist", 1, 5);

    std::cout << "Before shuffle:\n";
    testPlaylist.displayPlaylist();

    testPlaylist.shufflePlaylist();

    std::cout << "After shuffle:\n";
    testPlaylist.displayPlaylist();
}

int main() {
    testAddSongs();
    testDisplayPlaylist();
    testPlayNavigation();
    testRemoveSong();
    testFindSong();
    testShufflePlaylist();

    std::cout << "All tests passed.\n";
    return 0;
}
