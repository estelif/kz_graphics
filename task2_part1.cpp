#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "shaders.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

int part1_main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(500, 500, "Task 2 Part 1 - Correct Layout", NULL, NULL);
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

    int segments = 30;

    // 1. ellipse
    std::vector<float> ellipseVertices;
    std::vector<unsigned int> ellipseIndices;

    float ellipseCenterX = -0.5f, ellipseCenterY = 0.5f;
    float ellipseRadiusX = 0.2f, ellipseRadiusY = 0.12f; // 60% of radius

    ellipseVertices.insert(ellipseVertices.end(), { ellipseCenterX, ellipseCenterY, 1.0f, 0.0f, 0.0f });

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = ellipseCenterX + ellipseRadiusX * cos(angle);
        float y = ellipseCenterY + ellipseRadiusY * sin(angle);
        ellipseVertices.insert(ellipseVertices.end(), { x, y, 1.0f, 0.0f, 0.0f });
    }

    for (int i = 1; i <= segments; i++) {
        ellipseIndices.insert(ellipseIndices.end(), { 0, (unsigned int)i, (unsigned int)(i % segments + 1) });
    }

    // 2. triangle
    float triangleVertices[] = {
        // position      // colors
         0.0f,  0.7f,    1.0f, 0.0f, 0.0f,  
        -0.15f, 0.3f,    0.0f, 1.0f, 0.0f,  
         0.15f, 0.3f,    0.0f, 0.0f, 1.0f   
    };

    // 3. circle 
    std::vector<float> circleVertices;
    std::vector<unsigned int> circleIndices;

    float circleCenterX = 0.5f, circleCenterY = 0.5f;
    float circleRadius = 0.18f;

 
    circleVertices.insert(circleVertices.end(), { circleCenterX, circleCenterY, 0.5f, 0.0f, 0.0f });

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float x = circleCenterX + circleRadius * cos(angle);
        float y = circleCenterY + circleRadius * sin(angle);
        
        float red = 0.5f + 0.5f * sin(angle);
        circleVertices.insert(circleVertices.end(), { x, y, red, 0.0f, 0.0f });
    }

    for (int i = 1; i <= segments; i++) {
        circleIndices.insert(circleIndices.end(), { 0, (unsigned int)i, (unsigned int)(i % segments + 1) });
    }

    // 4. square
    std::vector<std::vector<float>> squareVertices;
    std::vector<unsigned int> squareIndices = { 0, 1, 2, 0, 2, 3 };

    float squareCenterX = 0.0f, squareCenterY = -0.25f;
    int numSquares = 6; // 6 squares total

    for (int layer = 0; layer < numSquares; layer++) {
        float size = 0.4f - layer * 0.06f; // decreasing size

        float color = (layer % 2 == 0) ? 1.0f : 0.0f; // white or black

        std::vector<float> vertices;
        // square corners using angle approach (pi/4, 3pi/4,etc)
        for (int i = 0; i < 4; i++) {
            float angle = M_PI / 4 + i * M_PI / 2;
            float x = squareCenterX + size * cos(angle);
            float y = squareCenterY + size * sin(angle);
            vertices.insert(vertices.end(), { x, y, color, color, color });
        }
        squareVertices.push_back(vertices);
    }

    GLuint VAOs[4], VBOs[4], EBOs[3];
    glGenVertexArrays(4, VAOs);
    glGenBuffers(4, VBOs);
    glGenBuffers(3, EBOs);
    //ellipse setup
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, ellipseVertices.size() * sizeof(float), ellipseVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ellipseIndices.size() * sizeof(unsigned int), ellipseIndices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //triangle setup
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //circle setup
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), circleVertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, circleIndices.size() * sizeof(unsigned int), circleIndices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //square setup
    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, squareIndices.size() * sizeof(unsigned int), squareIndices.data(), GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // drawing ellipse
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, ellipseIndices.size(), GL_UNSIGNED_INT, 0);

        // drawing triangle
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // drawing circle 
        glBindVertexArray(VAOs[2]);
        glDrawElements(GL_TRIANGLES, circleIndices.size(), GL_UNSIGNED_INT, 0);

        // drawing square
        glBindVertexArray(VAOs[3]);
        for (int i = 0; i < numSquares; i++) {
            glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
            glBufferData(GL_ARRAY_BUFFER, squareVertices[i].size() * sizeof(float), squareVertices[i].data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    glDeleteVertexArrays(4, VAOs);
    glDeleteBuffers(4, VBOs);
    glDeleteBuffers(3, EBOs);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}