# OpenGL Graphics Program

## Program Description

This OpenGL program demonstrates basic 2D graphics rendering with multiple tasks showcasing different geometric shapes and rendering techniques. The program is built using modern OpenGL (3.3 Core Profile) with GLFW for window management and either GLAD or GLEW for OpenGL function loading.

## Program Structure

The program consists of four main tasks, each demonstrating different aspects of OpenGL programming:

1. **Task 1 Part 1**: Blue Square - Renders a simple blue square using element buffer objects (EBO)
2. **Task 1 Part 2**: Red Triangle - Renders a red triangle using vertex array objects (VAO)
3. **Task 2 Part 1**: Four Basic Shapes - Complex scene with ellipse, triangle, circle, and nested squares
4. **Task 2 Part 2**: Creative Shapes - Artistic scene with star, hexagon, octagon, and flower patterns

## File Structure

```
├── main.cpp           # Main entry point with task selection
├── shaders.h          # Shader utility header
├── shaders.cpp        # Shader compilation and program creation utilities
└── README.md          # This documentation
```

## How to Use

### Prerequisites

Ensure you have the following libraries installed:
- **GLFW3** - Window and input management
- **GLAD** or **GLEW** - OpenGL function loading
- **OpenGL 3.3** or higher support

### Running the Program

1. Open `main.cpp` in your editor
2. Locate the task selection section at the top of the file:
   ```cpp
   #define RUN_TRIANGLE
   //#define RUN_SQUARE
   //#define RUN_TASK2_PART1
   //#define RUN_TASK2_PART2
   ```
3. Comment out the current selection and uncomment the desired task:
   - `#define RUN_TRIANGLE` - Red triangle
   - `#define RUN_SQUARE` - Blue square  
   - `#define RUN_TASK2_PART1` - Four shapes layout
   - `#define RUN_TASK2_PART2` - Creative artistic shapes

4. Compile and run the program using your preferred build system

### Controls

- **ESC** or **Close Window** - Exit the program
- The program runs in a continuous render loop until closed

## Tested Operating Systems

This program has been designed to work on:

- **Windows 10/11** - Primary development platform

### System Requirements

- **Graphics Card**: Any GPU with OpenGL 3.3+ support
- **RAM**: Minimal (< 100MB)
- **Display**: Any resolution (program creates 500x500 window)

## Visual Output

### Task 1 - Basic Shapes
- **Blue Square**: Solid blue square centered on dark teal background
- **Red Triangle**: Solid red triangle centered on dark teal background

### Task 2 Part 1 - Complex Layout
- **Top Left**: Red ellipse (flattened circle)
- **Top Center**: Multi-colored triangle (red, green, blue vertices)
- **Top Right**: Red circle with gradient coloring
- **Bottom Center**: Nested squares alternating white/black (6 layers)

### Task 2 Part 2 - Creative Artistic Shapes
- **Top**: 5-pointed star with yellow to orange gradient
- **Left**: Purple to pink gradient hexagon
- **Right**: Cyan to blue gradient octagon  
- **Bottom**: Multi-colored flower with 8 rainbow petals

## Technical Features

- **Modern OpenGL**: Uses OpenGL 3.3 Core Profile
- **Efficient Rendering**: Vertex Array Objects (VAO) for state management
- **Buffer Objects**: VBO and EBO for vertex data storage
- **Custom Shaders**: Vertex and fragment shaders for rendering
- **Color Interpolation**: Smooth color gradients using vertex colors
- **Geometric Algorithms**: Mathematical generation of circles, polygons, and stars

## Troubleshooting

### Common Issues

1. **Black Screen**: Check if OpenGL drivers are properly installed
2. **Compilation Errors**: Ensure all required libraries (GLFW, GLAD/GLEW) are linked
3. **Window Not Opening**: Verify graphics drivers support OpenGL 3.3+

### Debug Information

The program outputs error messages to console for:
- GLFW initialization failures
- OpenGL context creation issues
- Shader compilation errors
- OpenGL function loading problems
