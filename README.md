# 🎵 LoopSet Playlist Manager

LoopSet is a C++ terminal-based playlist manager that uses a doubly linked list to store and manipulate songs. It supports adding, removing, shuffling, sorting, reversing, and playing tracks, while maintaining an intuitive looped navigation experience.

## 📁 Project Structure

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
```

## 🧰 Requirements

- [MSYS2](https://www.msys2.org/)
- C++11 compiler (provided by `g++` in MinGW64)
- MinGW 64-bit terminal (not MSYS shell)

## 🔧 Installation & Compilation

1. **Clone the repository:**

    ```bash
    git clone https://github.com/your-username/loopset.git
    cd loopset
    ```

2. **Open the correct terminal:**

   Launch **MSYS2 MinGW 64-bit** from your Start Menu. It will look like:

   ```
   yourname@yourpc MINGW64 ~
   ```

3. **Navigate to your project folder:**

   ```bash
   cd /c/Users/yourname/Documents/Projects/loopset
   ```

   *(Adjust the path based on where you cloned or saved the project.)*

4. **Compile the program:**

   ```bash
   g++ -std=c++11 -Iinclude src/*.cpp -o loopset.exe
   ```

   *(On some systems, you may need to use `g++` explicitly from your installed MinGW path or set it in your environment variables.)*

5. **Run it:**

   ```bash
   ./loopset.exe
   ```

## 🖥️ Features

- Add new songs with title, artist, and duration
- Display entire playlist
- Shuffle playlist randomly
- Sort by title, artist, or duration
- Reverse playlist order
- Play next/previous with looping navigation
- Case-insensitive search and removal
- Preserve current playing song during sort/shuffle/reverse
- Input validation and cancellation support

## 📝 Notes

- This app is written in modern C++ using a custom doubly linked list implementation.
- Input handling ensures invalid or blank inputs are gracefully managed.
- The menu updates in real time based on actions taken by the user.

