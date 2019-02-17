#ifndef RTR_COLLECTION_ORBITCAMERA_H
#define RTR_COLLECTION_ORBITCAMERA_H

#include "glm/glm.hpp"

class OrbitCamera {
public:
    glm::vec3 position{};

    OrbitCamera() noexcept;

    glm::mat4 get_view_matrix() const noexcept;

    void handleMouseMove(float deltaX, float deltaY);

    void handleMouseWheel(float scrollDelta);

    void movePivotPoint(float x, float y);

    void resetPosition();

private:
    float azimuth;
    float elevation;
    float distance;
    float sensitivity;
    float scrollSpeed;
    glm::vec3 lookAtPoint{};
    glm::mat4 viewMatrix{};

    void calc_position();
};


#endif //RTR_COLLECTION_ORBITCAMERA_H
