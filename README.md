<div align="center">
 <h1>💻 C Exercises 💻</h1>
 <p>Programming exercises in <strong>C</strong></p>

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=00599C&labelColor=fff&color=00599C)
![Arch](https://img.shields.io/badge/Arch-1793D1?logo=archlinux&logoColor=1793D1&labelColor=fff&color=1793D1)

</div>

## 🌟 Description

This repository contains **44 progressive programming exercises in C**, designed to develop an understanding of systems programming from scratch. It begins with the fundamentals of the language and progresses through data structures, algorithms, and file handling, culminating in C's strengths: low-level systems programming, concurrency, and networking. Practical examples include:

- Control flow, functions, recursion, and basic algorithmic problem-solving.
- Manual implementation of data structures with pointers (linked lists, stacks, queues, trees, hash tables, graphs).
- Search and sorting algorithms, graph traversal (`DFS/BFS`), and dynamic programming.
- File I/O operations (text, binary, CSV parsing).
- System programming: `fork`, `pipe`, `signal`, threads, and TCP sockets.

## 📂 Exercise Categories

| Category            | Exercises | Level | Description                                                                                                                                                                                   |
| ------------------- | --------- | ----- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Fundamentals**    | 8         | 🟢    | Core C syntax, control structures, functions, recursion, and basic algorithmic thinking. Build a solid foundation with calculators, converters, pattern generators, and text analysis tools.  |
| **Data Structures** | 12        | 🟡    | Data structures using pointers and dynamic memory allocation. Includes arrays, strings, matrices, linked lists (singly/doubly), stacks, queues, binary search trees, hash tables, and graphs. |
| **Algorithms**      | 10        | 🟡    | Classic algorithms for searching, sorting, graph traversal (DFS/BFS), dynamic programming, and optimization. Compare performance, visualize execution, and analyze computational complexity.  |
| **File Handling**   | 4         | 🟡    | Reading, writing, and processing text files, binary data, CSV analysis, and log file analysis for real-world data manipulation.                                                               |
| **Specialization**  | 10        | 🔴    | Programming showcasing C power: memory management, process control (fork), inter-process communication (pipes, signals), multi-threading (pthreads), and network programming (TCP sockets).   |

## 📋 Installation Requirements

- **Operating System**: Linux (Arch, Debian, Ubuntu, etc.) or WSL2 on Windows.
- **Architecture**: x86-64 (64-bit).
- **C Compiler GCC**: version 15.2.1 or higher.
- **GNU GDB**: version 16.3 or higher.

## 🚀 Execution Instructions

### 🖥️ Arch Linux/WSL (Recommended)

1. **Clone the repository**:
   ```bash
   git clone https://github.com/edavnix/c-systems-fundamentals.git
   ```
   > **Note**: When using Arch Linux natively, proceed to **Step 4**. For Windows environments, complete all steps to install and configure WSL Arch.
2. **Download and install WSL Arch** (PowerShell):
   ```bash
   wsl --install -d archlinux
   ```
3. **Restart the system** and access Arch Linux.
4. **Install GDB and compilation tools**:
   ```bash
   pacman -Syu
   pacman -S gdb base-devel
   ```
5. **Verify installation**:
   ```bash
   gcc --version    # e.g. gcc (GCC) 15.2.1 or higher
   gdb --version    # e.g. GNU gdb (GDB) 16.3 or higher
   uname -m         # e.g. x86_64
   ```
6. **Navigate to the exercises directory** (adjust path as needed):
   ```bash
    cd c-systems-fundamentals
   ```
7. **Execute exercises** use make run followed by the path to the file:
   ```bash
   make help                                                  # view available commands
   make run file=src/01_fundamentals/01_multi_calculator.c    # practical example
   ```

### 🌐 OneCompiler (No Installation Required)

Code execution without local installation:

1. Access **[OneCompiler - C](https://onecompiler.com/c)**.
2. Copy and paste the exercise code.
3. For exercises requiring input:
   - Navigate to the **STDIN** panel.
   - Enter values separated by a space.
4. Click **Run**.

> _Note: Online compilers may not support advanced OS concepts like `fork` or `pipe`._

## 📖 Official Documentation

Additional resources:

- **[C Reference](https://en.cppreference.com/w/c)** - Complete C language reference.
- **[Linux Man Pages](https://linux.die.net/man/)** - Reference for system calls.
- **[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)** - Excellent guide for sockets.

<div align="center">
 <br>
 <img
  src="https://img.shields.io/badge/Made%20with-C%20%26%20Dedication-00599C?style=for-the-badge"
  alt="Made with C"
 />
 <br><br>
 <p>⭐ <strong>Star this repository to show support</strong> ⭐</p>
</div>
