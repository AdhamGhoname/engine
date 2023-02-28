#include "Quaternion.h"

Quaternion::Quaternion() {
    value_ = glm::quat(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
}

Quaternion::Quaternion(float x, float y, float z, float w) {
    value_ = glm::quat(glm::vec4(x, y, z, w));
}

Quaternion::Quaternion(glm::quat value) {
    value_ = value;
}

Quaternion Quaternion::Euler(float x, float y, float z) {
    return Quaternion(glm::quat(glm::vec3(x, y, z)));
}
    