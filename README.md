# 2D Graphics Editor in C

A simple, console-based 2D graphics editor written in C. The program uses a 2D character array as a grid canvas. Empty space is represented by underscores (`_`), and shapes are drawn onto the matrix using asterisks (`*`).

## 🚀 How it Works
* **The Canvas:** A fixed 2D grid matrix where rows represent the Y-axis and columns represent the X-axis.
* **Rendering:** When a shape function is called, the program calculates the correct coordinates and replaces the `_` characters with `*`.
* **Features:** Supports drawing lines, rectangles, triangles, and circles, along with options to modify, delete, or wipe the canvas clean.

## 📅 3-Day Development Plan
- [x] **Day 1 :** Set up the project structure, build the main menu loop, initialize the canvas, and implement all 4 core drawing functions (Line, Rectangle, Triangle, Circle).
- [ ] **Day 2:** Implement the object management layer (adding tracking for separate shapes to allow modifying and deleting specific objects).
- [ ] **Day 3:** Add edge-case validation (preventing array out-of-bounds crashes), code cleanups, and final submission testing.

## 💻 How to Run the Project
Compile the code using any standard C compiler (like GCC):

```bash
gcc main.c -o graphics_editor -lm
