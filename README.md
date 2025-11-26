# 📚 Snazydeets

![C++](https://img.shields.io/badge/std-C%2B%2B20-blue?style=for-the-badge&logo=c%2B%2B)
![Build System](https://img.shields.io/badge/Build-CMake-orange?style=for-the-badge&logo=cmake)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey?style=for-the-badge&logo=linux)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

A comprehensive collection of data structure implementations using modern C++ techniques. This project focuses on clean code, modular design, and understanding the core mechanics of algorithms.

## 🚀 Features

* **Modular Architecture:** Each data structure is isolated with its own headers (`.hpp`), implementation (`.cpp`), and documentation.
* **Modern C++ Standards:** Built using C++20/23 features for efficiency and safety.
* **Cross-Platform:** Full support for Linux (GCC) and Windows (MSVC/MinGW) via CMake.
* **Visual Feedback:** Custom `console_colors` and `display()` implementation for distinct and readable terminal output.

## 📂 Project Structure

```text
.
├── console_colors/   # Utilities for colorized terminal output
├── graphs/           # Graph algorithms and traversal implementations
├── linked_lists/     # Singly, Doubly, and Circular linked lists
├── maps/             # Hash Maps and Dictionary implementations
├── trees/            # BST, AVL, and other tree structures
├── not_implemented/  # Placeholders for future structures
├── scrap/            # Experimental code and scratchpad
└── CMakeLists.txt    # Build configuration
```

### **Each module directory contains:**

  - *`*.hpp`*:     The core library/class definition.
  - *`main*.cpp`*: Implementation and testing logic.
  - *`*.md`:*      Detailed documentation and implementation details.
  - > **reference images** (Data Structures images collected from various sources).
---

## 🛠️ Installation & Build

### 🐧 Arch Linux (AUR)

If you are running Arch Linux, you can install this package directly from the AUR:

```bash
# Using yay
yay -S snazzydeets-git

# Using paru
paru -S snazzydeets-git
```

### 🐧 Linux (Manual Build)

Requirements: `git`, `cmake`, `gcc` (g++).

```bash
# 1. Clone the repository
git clone https://github.com/greatermonk/snazzydeets.git
cd snazzydeets

# 2. Generate build files
cmake -S . -B build

# 3. Compile
cmake --build build
```

### 🪟 Windows

Requirements: `CMake`, `Visual Studio` (or MinGW).

1.  Open PowerShell or Command Prompt in the project folder.
2.  Run the following commands:
    ```powershell
    cmake -S . -B build
    cmake --build build --config Release
    ```
3.  Executables will be generated in `build/Release/`.

-----

## 💻 Usage

After building, executables are generated for each module. You can run them directly to verify the data structures.

**Example:**

```bash
# From the build directory
./graphs_run
./linked_lists_run
```

## 🤝 Contributing

Contributions are welcome\!

1.  Fork the project.
2.  Create your feature branch (`git checkout -b feature/AmazingFeature`).
3.  Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4.  Push to the branch (`git push origin feature/AmazingFeature`).
5.  Open a Pull Request.

## 📄 License

Distributed under the APACHE License. See **[LICENSE](https://github.com/greatermonk/snazzydeets/blob/main/LICENSE)** for more information.
