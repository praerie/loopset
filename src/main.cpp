#include "Spinlist.hpp"

int main() {
    Spinlist myPlaylist;
    
    myPlaylist.addSong("In Camera", "Yumi Zouma", 3.24);
    myPlaylist.addSong("Mulholland", "Hope Tala, sky", 3.44); // handles multiple artists in one string
    myPlaylist.addSong("Peaceful Place", "Leon Bridges", 4.15);
    myPlaylist.addSong("Bilgewater", "Brown Bird", 3.55);
    myPlaylist.addSong("ENTROPY", "Daniel Caesar", 4.21);
    myPlaylist.addSong("Cosmic", "Amber Mark", 4.35);
    myPlaylist.addSong("Red Bottom Sky", "Yung Lean", 5.03);
    myPlaylist.addSong("Hazey", "Glass Animals", 4.26);
    myPlaylist.addSong("Nothing Better", "The Postal Service", 3.47);
    myPlaylist.addSong("Le Matin", "Yann Tiersen", 1.59);

    return 0;
}
