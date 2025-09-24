#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "shaders.h"


#define PI 3.14159265358979323846f

static const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec3 vColor;

out vec3 fragColor;

void main()
{
    gl_Position = vec4(vPosition, 0.0, 1.0);
    fragColor = vColor;
}
)";

static const char* fragmentShaderSource = R"(
#version 330 core
in vec3 fragColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(fragColor, 1.0);
}
)";

static GLuint compileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

static GLuint createShaderProgram() {
    GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int part2_main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "Task 2 Part 2 - Creative Shapes", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, 500, 500);
    GLuint shaderProgram = createShaderProgram();

    // 1. star
    std::vector<float> starVertices;
    std::vector<unsigned int> starIndices;

    float starCenterX = 0.0f, starCenterY = 0.6f;
    float outerRadius = 0.25f, innerRadius = 0.1f;
    int starPoints = 5;

    // Center vertex - bright yellow
    starVertices.insert(starVertices.end(), { starCenterX, starCenterY, 1.0f, 1.0f, 0.2f });

    for (int i = 0; i <= starPoints * 2; i++) {
        float angle = -PI / 2 + i * PI / starPoints; // Start from top
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        float x = starCenterX + radius * cos(angle);
        float y = starCenterY + radius * sin(angle);

        // Gradient from yellow to orange
        float red = 1.0f;
        float green = (i % 2 == 0) ? 0.6f : 1.0f;
        float blue = 0.0f;

        starVertices.insert(starVertices.end(), { x, y, red, green, blue });
    }

    for (int i = 1; i <= starPoints * 2; i++) {
        starIndices.insert(starIndices.end(), { 0, (unsigned int)i, (unsigned int)(i % (starPoints * 2) + 1) });
    }

    // 2. hexagon
    std::vector<float> hexVertices;
    std::vector<unsigned int> hexIndices;

    float hexCenterX = -0.5f, hexCenterY = 0.0f;
    float hexRadius = 0.2f;

    // Center vertex - purple
    hexVertices.insert(hexVertices.end(), { hexCenterX, hexCenterY, 0.5f, 0.0f, 0.8f });

    for (int i = 0; i <= 6; i++) {
        float angle = i * PI / 3;
        float x = hexCenterX + hexRadius * cos(angle);
        float y = hexCenterY + hexRadius * sin(angle);

        // Gradient from purple to pink
        float red = 0.5f + 0.4f * (float)i / 6;
        float green = 0.1f + 0.3f * (float)i / 6;
        float blue = 0.8f - 0.2f * (float)i / 6;

        hexVertices.insert(hexVertices.end(), { x, y, red, green, blue });
    }

    for (int i = 1; i <= 6; i++) {
        hexIndices.insert(hexIndices.end(), { 0, (unsigned int)i, (unsigned int)(i % 6 + 1) });
    }

    // 3. octagon
    std::vector<float> octVertices;
    std::vector<unsigned int> octIndices;

    float octCenterX = 0.5f, octCenterY = 0.0f;
    float octRadius = 0.18f;

    // Center vertex - cyan
    octVertices.insert(octVertices.end(), { octCenterX, octCenterY, 0.0f, 0.8f, 1.0f });

    for (int i = 0; i <= 8; i++) {
        float angle = i * PI / 4;
        float x = octCenterX + octRadius * cos(angle);
        float y = octCenterY + octRadius * sin(angle);

        // Gradient from cyan to blue
        float red = 0.0f;
        float green = 0.8f - 0.5f * (float)i / 8;
        float blue = 1.0f;

        octVertices.insert(octVertices.end(), { x, y, red, green, blue });
    }

    for (int i = 1; i <= 8; i++) {
        octIndices.insert(octIndices.end(), { 0, (unsigned int)i, (unsigned int)(i % 8 + 1) });
    }

    // 4. flower
    std::vector<float> flowerVertices;
    std::vector<unsigned int> flowerIndices;

    float flowerCenterX = 0.0f, flowerCenterY = -0.4f;
    float petalLength = 0.15f, petalWidth = 0.05f;
    int numPetals = 8;

    int vertexIndex = 0;
    for (int petal = 0; petal < numPetals; petal++) {
        float petalAngle = petal * 2.0f * PI / numPetals;

        float red = 0.5f + 0.5f * sin(petalAngle);
        float green = 0.5f + 0.5f * sin(petalAngle + 2.0f * PI / 3);
        float blue = 0.5f + 0.5f * sin(petalAngle + 4.0f * PI / 3);

        
        // Center point
        flowerVertices.insert(flowerVertices.end(), { flowerCenterX, flowerCenterY, red * 0.7f, green * 0.7f, blue * 0.7f });

        float tipX = flowerCenterX + petalLength * cos(petalAngle);
        float tipY = flowerCenterY + petalLength * sin(petalAngle);
        flowerVertices.insert(flowerVertices.end(), { tipX, tipY, red, green, blue });

        float sideAngle = petalAngle + PI / numPetals;
        float sideX = flowerCenterX + petalWidth * cos(sideAngle);
        float sideY = flowerCenterY + petalWidth * sin(sideAngle);
        flowerVertices.insert(flowerVertices.end(), { sideX, sideY, red, green, blue });

        flowerIndices.insert(flowerIndices.end(), {
            (unsigned int)vertexIndex,
            (unsigned int)(vertexIndex + 1),
            (unsigned int)(vertexIndex + 2)
            });
        vertexIndex += 3;
    }

    GLuint VAOs[4], VBOs[4], EBOs[4];
    glGenVertexArrays(4, VAOs);
    glGenBuffers(4, VBOs);
    glGenBuffers(4, EBOs);

    // star setup
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, starVertices.size() * sizeof(float), starVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, starIndices.size() * sizeof(unsigned int), starIndices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // hexagon setup
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, hexVertices.size() * sizeof(float), hexVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, hexIndices.size() * sizeof(unsigned int), hexIndices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // octagon setup
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, octVertices.size() * sizeof(float), octVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, octIndices.size() * sizeof(unsigned int), octIndices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // flower setup
    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, flowerVertices.size() * sizeof(float), flowerVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, flowerIndices.size() * sizeof(unsigned int), flowerIndices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.05f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Draw Star 
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, starIndices.size(), GL_UNSIGNED_INT, 0);

        // Draw Hexagon
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, hexIndices.size(), GL_UNSIGNED_INT, 0);

        // Draw Octagon
        glBindVertexArray(VAOs[2]);
        glDrawElements(GL_TRIANGLES, octIndices.size(), GL_UNSIGNED_INT, 0);

        // Draw Flower 
        glBindVertexArray(VAOs[3]);
        glDrawElements(GL_TRIANGLES, flowerIndices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(4, VAOs);
    glDeleteBuffers(4, VBOs);
    glDeleteBuffers(4, EBOs);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}