#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
public:
    Camera(GLFWwindow* window, float windowWidth, float windowHight,
     float pitch, float yaw, float sensitivity, float speed,
     const glm::vec3& position, const  glm::vec3& direction
    );

    static void cursorPosCallbackStatic(GLFWwindow* window, double xpos, double ypos);

    void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    void updatePosition(float deltaTime) noexcept;

    void setDirection(const glm::vec3& direction) noexcept;

    void setPosition(const glm::vec3& position) noexcept;

    void setSensitivity(float sensitivity) noexcept;

    void setSpeed(float speed) noexcept;

    glm::vec3 getDirection() const noexcept;

    glm::vec3 getPosition() const noexcept;

    float getSensitivity() const noexcept;

    float getSpeed() const noexcept;

    float getYaw() const noexcept;

    float getPitch() const noexcept;

    void cameraLog() const noexcept;

    ~Camera() = default;

private:
    GLFWwindow* window;
    float pitch;
    float yaw;
    float lastX;
    float lastY;
    bool firstMovement;
    float sensitivity;
    float speed;
    glm::vec3 direction;
    glm::vec3 position;
};

#endif