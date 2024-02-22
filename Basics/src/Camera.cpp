#include "Camera.hpp"
#include "fmt/color.h"

Camera::Camera(GLFWwindow* window, float windowWidth, float windowHight, float pitch, float yaw, float sensitivity, float speed,  const glm::vec3& position, const glm::vec3& direction) 
    : window {window},firstMovement {true}, pitch {pitch}, yaw {yaw}, lastX {windowWidth / 2},
      lastY {windowHight / 2}, sensitivity {sensitivity}, speed {speed}, position {position}, direction {direction}
{
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, cursorPosCallbackStatic);
}


void Camera::updatePosition(float deltaTime)  noexcept
{
    glm::vec3 cameraPosition { this->getPosition() };
    glm::vec3 up { 0.0, 1.0f, 0.0f };

    // -------- WSAD movement --------
    if(glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPosition -=  this->speed * deltaTime * glm::normalize(glm::cross(this->direction, up));
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPosition +=  this->speed * deltaTime *  glm::normalize(glm::cross(this->direction, up));
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPosition += this->speed * deltaTime * this->direction;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPosition -= this->speed * deltaTime * this->direction;
    }

    this->setPosition(cameraPosition);
}


void Camera::setDirection(const glm::vec3 &newDirection) noexcept
{
    this->direction = newDirection;
}


void Camera::setPosition(const glm::vec3 &newPosition) noexcept
{
    this->position = newPosition;
}


void Camera::setSensitivity(float newSensitivity) noexcept
{
    if (newSensitivity < 0.01f)
    {
        fmt::print(fg(fmt::color::yellow), "Camera Sensitivity must be > 0!\n");

        this->sensitivity = 0.05f;

        return;
    }
    
    this->sensitivity = newSensitivity;
}


void Camera::setSpeed(float newSpeed) noexcept
{
    
    if (newSpeed < 0.01f)
    {
        fmt::print(fg(fmt::color::yellow), "Camera Speed must be > 0!\n");

        this->speed = 3.5f;

        return;
    }
    
    this->speed = newSpeed;
}


glm::vec3 Camera::getDirection() const noexcept
{
    return this->direction;
}


glm::vec3 Camera::getPosition() const noexcept
{
    return this->position;
}


float Camera::getSensitivity() const noexcept
{
    return this->sensitivity;
}


float Camera::getSpeed() const noexcept
{
    return this->speed;
}


void Camera::cursorPosCallbackStatic(GLFWwindow *window, double xpos, double ypos)
{
    Camera* camera { static_cast<Camera*>(glfwGetWindowUserPointer(window))};

    if (camera)
    {
        camera->cursorPosCallback(window, xpos, ypos);
    }
}


float Camera::getYaw() const noexcept
{
    return this->yaw;
}


float Camera::getPitch() const noexcept
{
    return this->pitch;
}


void Camera::cameraLog() const noexcept
{
    fmt::print(fg(fmt::color::yellow),
     "Camera position: [{}, {}, {}]\nCamera Yaw: [{}]\nCamera Pitch: [{}]\n\n",
      this->getPosition().x, this->getPosition().y, this->getPosition().z, this->getYaw(), this->getPitch());
}


void Camera::cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    fmt::print("{}\n", firstMovement);
    if (firstMovement)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMovement = false;
    }

    float xOffset { static_cast<float>((xpos - lastX) * sensitivity) };
    float yOffset { static_cast<float>((lastY - ypos) * sensitivity) };

    // fmt::print("xOffset: [{}]\nyOffset: [{}]\n\n", xOffset, yOffset);

    yaw += xOffset;
    pitch += yOffset;

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    if (pitch > 89.0f)
    {
        pitch = 89.0f; 
    }
    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    direction = glm::normalize(direction);
}