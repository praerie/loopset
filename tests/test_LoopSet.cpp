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


int main() {
    testAddSongs();
    testDisplayPlaylist();
    testPlayNavigation();
    testRemoveSong();
    testFindSong();

    std::cout << "All tests passed.\n";
    return 0;
}
