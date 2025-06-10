#include "LoopSet.hpp"

int main() {
    LoopSet myPlaylist;
    
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

    myPlaylist.displayPlaylist();

    myPlaylist.playNext(); // should move forward to Mulholland
    myPlaylist.playNext(); // should move forward to Peaceful Place

    myPlaylist.playPrevious(); // should move backward to Mulholland
    myPlaylist.playPrevious(); // should move backward to In Camera
    myPlaylist.playPrevious(); // should move backward to Le Matin (tail)

    myPlaylist.removeSong("Bilgewater"); 
    myPlaylist.removeSong("Cosmic");
    myPlaylist.removeSong("Red Bottom Sky");

    myPlaylist.displayPlaylist(); // Bilgewater, Cosmic, and Red Bottom Sky should no longer appear

    myPlaylist.findSong("Hazey");
    myPlaylist.findSong("Le Matin");
    myPlaylist.findSong("Cosmic"); // removed in previous step, so shouldn't be found

    myPlaylist.shufflePlaylist();
    myPlaylist.displayPlaylist();

    return 0;
}
