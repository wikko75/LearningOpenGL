#ifndef UTILS_HPP
#define UTILS_HPP
#include <GLFW/glfw3.h>

void initLog() noexcept;

void shaderStatusLogger(GLuint shader);

void programStatusLogger(GLuint program);

void proccessInput(GLFWwindow* window) noexcept;

void windowFramebufferSizeCallback(GLFWwindow* window, int width, int height);


#endif