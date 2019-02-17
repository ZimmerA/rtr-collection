#include "orbitCamera.h"
#include "glm/gtc/matrix_transform.hpp"

const float defaultAzimuth = 0.f;
const float defaultElevation = 50.f;
const glm::vec3 defaultLookAt{0, 0, 0};
const float defaultDistance = 150.f;
const float defaultSensitivity = 20.0f;
const float defaultScrollSpeed = 15;

OrbitCamera::OrbitCamera() noexcept
{
    azimuth = defaultAzimuth;
    elevation = defaultElevation;
    distance = defaultDistance;
    lookAtPoint = defaultLookAt;
    sensitivity = defaultSensitivity;
    scrollSpeed = defaultScrollSpeed;

    calc_position();
}

glm::mat4 OrbitCamera::get_view_matrix() const noexcept
{
    return viewMatrix;
}

void OrbitCamera::handleMouseMove(float deltaX, float deltaY)
{
    const float move_x = -deltaX * sensitivity;
    const float move_y = -deltaY * sensitivity;

    azimuth += glm::radians(move_x);
    elevation += glm::radians(move_y);

    azimuth = fmodf(azimuth, 360.0f);

    if (elevation > 179.0f)
        elevation = 179.0f;
    if (elevation < 1.0f)
        elevation = 1.0f;

    calc_position();
}

void OrbitCamera::handleMouseWheel(float scrollDelta)
{
    distance -= scrollDelta * scrollSpeed;

    if (distance <= 1.0f)
        distance = 1.0f;

    calc_position();
}

void OrbitCamera::movePivotPoint(float x, float y)
{
    const glm::mat4 lookAt = get_view_matrix();
    const glm::vec3 upVec(lookAt[0][1], lookAt[1][1], lookAt[2][1]);
    const glm::vec3 rightVec(lookAt[0][0], lookAt[1][0], lookAt[2][0]);

    lookAtPoint += upVec * y;
    lookAtPoint += rightVec * x;

    calc_position();
}

void OrbitCamera::resetPosition()
{
    lookAtPoint = defaultLookAt;
    azimuth = defaultAzimuth;
    elevation = defaultElevation;
    distance = defaultDistance;

    calc_position();
}

void OrbitCamera::calc_position()
{
    viewMatrix = glm::mat4(1);
    viewMatrix = translate(viewMatrix, lookAtPoint);
    viewMatrix = rotate(viewMatrix, glm::radians(azimuth), glm::vec3(0.f, 1.f, 0.f));
    viewMatrix = rotate(viewMatrix, glm::radians(elevation - 90.0f), glm::vec3(1.f, 0.f, 0.f));
    viewMatrix = translate(viewMatrix, glm::vec3(0, 0, distance));

    position = glm::vec3(viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2]);

    viewMatrix = inverse(viewMatrix);
}