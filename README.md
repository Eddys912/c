<div align="center">
 <h1>💻 C Exercises 💻</h1>
 <p>Programming exercises in <strong>C</strong></p>

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=00599C&labelColor=fff&color=00599C)
![Arch](https://img.shields.io/badge/Arch-1793D1?logo=archlinux&logoColor=1793D1&labelColor=fff&color=1793D1)

</div>

## 🌟 Description

This repository contains programming exercises in **C**, covering fundamentals, low-level data structures, and operating system concepts. Practical examples include:

- Pointers, memory allocation (`malloc`, `free`), and pointer arithmetic.
- File I/O (text and binary).
- Data Structures implemented manually with pointers (Linked Lists, Stacks, Queues, Trees).
- Inter-Process Communication (IPC), Threads, and Sockets.

## 📂 Exercises

| #   | Exercise                | Level | Description                                           |
| --- | ----------------------- | ----- | ----------------------------------------------------- |
| 1   | **Pointers Basics**     | 🟢    | Memory introspection and data representation.         |
| 2   | **Pointer Arithmetic**  | 🟢    | Raw buffer parsing and manual offset navigation.      |
| 3   | **Dynamic Memory**      | 🟢    | Heap lifecycle management.                            |
| 4   | **Array Pointers**      | 🟢    | Multi-level dynamic structures and heap hierarchy.    |
| 5   | **Function Pointers**   | 🟡    | Callback implementation and decoupled execution flow. |
| 6   | **Void Pointers**       | 🟡    | Abstract data handling and generic programming.       |
| 7   | **String Manipulation** | 🟡    | Custom processing of character sequences in memory.   |
| 8   | **File Read**           | 🟡    | Extracting formatted information from external files. |
| 9   | **File Write**          | 🟡    | Persisting information into permanent text storage.   |
| 10  | **Binary Files**        | 🔴    | Direct machine-level data storage and retrieval.      |
| 11  | **Linked List**         | 🔴    | Dynamic and non-contiguous data organization.         |
| 12  | **Stack Array**         | 🔴    | LIFO (Last-In, First-Out) data flow management.       |
| 13  | **Queue Array**         | 🔴    | FIFO (First-In, First-Out) data buffer management.    |
| 14  | **Binary Tree**         | 🔴    | Hierarchical data sorting and optimized searching.    |
| 15  | **Fork Process**        | 🔴    | Task duplication and parallel execution control.      |
| 16  | **Pipe IPC**            | 🔴    | Unidirectional data flow between related processes.   |
| 17  | **Signal Handling**     | 🔴    | Interception of asynchronous system events.           |
| 18  | **Pthread Create**      | 🔴    | Concurrent execution within a single process.         |
| 19  | **Mutex Lock**          | 🔴    | Resource protection and race condition prevention.    |
| 20  | **TCP Socket**          | 🔴    | Bi-directional communication over a network.          |

## 📋 Installation Requirements

- **Operating System**: Linux (Arch, Debian, Ubuntu, etc.) or WSL2 on Windows.
- **Architecture**: x86-64 (64-bit).
- **C Compiler GCC**: version 15.2.1 or higher.
- **GNU GDB**: version 16.3 or higher.

## 🚀 Execution Instructions

### 🖥️ Arch Linux/WSL (Recommended)

1. **Clone the repository**:
   ```bash
   git clone https://github.com/edavsys/c-systems-fundamentals.git
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
   cd c-systems-fundamentals/exercises
   ```
7. **Execute exercises**:
   ```bash
   make run 01_pointer_basics
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
