# Mandelbrot Set Fractal Renderer

This project is a simple Mandelbrot Set fractal renderer implemented in C++. It provides a visual representation of the famous Mandelbrot Set, allowing users to explore its intricate patterns and structures.

## Features

- Render high-resolution images of the Mandelbrot Set.
- Pan and zoom functionality to navigate and explore different regions of the fractal.
- Real-time rendering with smooth updates as the fractal is modified.
- Single-threaded implementation for simplicity and portability.

## Dependencies

- SDL2: Simple DirectMedia Layer library for window creation and rendering.
- C++17-compatible compiler.

## Getting Started

1. **Clone the repository:**
   
   ```
   git clone <repository_url>
   ```

2. **Build the project** using your preferred build system (e.g., CMake, Makefile, Visual Studio).

3. **Run the generated executable:**
   
   ```
   ./mandelbrot
   ```

4. **Use the following controls** to interact with the application:

   - **Mouse Movement:** Pan the fractal by moving the mouse.
   - **Mouse Wheel:** Zoom in or out of the fractal.
   - **Close Window:** Press the close button or use the system close event.

## Configuration

You can modify the configuration parameters directly in the `main.cpp` file.