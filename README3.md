# LoopSet Playlist Manager

LoopSet is a C++ console application that allows users to manage a music playlist using a doubly linked list. Features include adding, removing, playing, finding, sorting, shuffling, and reversing songs in the playlist.

## Features

- Add new songs with title, artist, and duration
- Remove songs by title
- Play next and previous songs in loop
- Find a song and choose to play or remove it
- Shuffle or sort playlist by title, artist, or duration
- Reverse the playlist order
- Handles user input robustly with validation

## Installation

1. Clone the repository:

```bash
git clone https://github.com/your-username/loopset.git
cd loopset
```

2. Make sure you have a C++ compiler installed (e.g., `g++`).

3. Compile the project:

```bash
g++ -std=c++11 -Iinclude src/*.cpp -o loopset.exe
```

> On some systems, you may need to use `g++` explicitly from your installed MinGW path or set it in your environment variables.

4. Run the program:

```bash
./loopset.exe
```

## File Structure

```
loopset/
├── include/
│   ├── LoopSet.hpp
│   ├── Node.hpp
│   ├── Song.hpp
│   └── utils.hpp
├── src/
│   ├── main.cpp
│   ├── LoopSet.cpp
│   ├── Node.cpp
│   ├── Song.cpp
│   └── utils.cpp
└── README.md
```

## Notes

- All user input is validated
- Songs are managed using a custom doubly linked list
- Console output shows the currently playing song and highlights it in the display
