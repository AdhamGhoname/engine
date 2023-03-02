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

Quaternion::Quaternion(Vector4 v) {
    value_ = glm::quat(v.GetGLMValue());
}

Quaternion Quaternion::Euler(float x, float y, float z) {
    return Quaternion(glm::quat(glm::vec3(x, y, z)));
}

glm::mat4 Quaternion::GetTransformationMatrix() {
    return glm::mat4_cast(value_);
}

Quaternion Quaternion::Normalized() {
    return Quaternion(glm::normalize(value_));
}

Vector3 Quaternion::GetEulerAngles() {
    glm::vec3 angles = glm::eulerAngles(value_);
    return Vector3(angles.x, angles.y, angles.z);
}

float Quaternion::x() {
    return value_.x;
}

float Quaternion::y() {
    return value_.y;
}

float Quaternion::z() {
    return value_.z;
}

float Quaternion::w() {
    return value_.w;
}

void Quaternion::Set(float x, float y, float z, float w) {
    value_ = glm::quat(w, x, y, z);
}

void Quaternion::SetFromToRotation(Vector3 from, Vector3 to) {
    Vector3 axis = Vector3::Cross(from, to).Normalized();
    float angle = Vector3::Angle(from, to);
    value_ = glm::angleAxis(angle, glm::vec3(axis.x(), axis.y(), axis.z()));
}

void Quaternion::SetLookRotation(Vector3 forward, Vector3 up) {
    glm::mat4 mat = glm::lookAt(glm::vec3(0.0f), forward.GetGLMValue(), up.GetGLMValue());
}

Vector4 Quaternion::ToAngleAxis() {
    float angle = glm::angle(value_);
    glm::vec3 axis = glm::axis(value_);
    return Vector4(glm::angle(value_), axis.x, axis.y, axis.z);
}

std::string Quaternion::ToString() {
    return Vector4(*this).ToString();
}

float Quaternion::operator[](int index) {
    switch (index) {
    case 0:
        return value_.x;
    case 1:
        return value_.y;
    case 2:
        return value_.z;
    case 3:
        return value_.w;
    default:
        return 0;
    }
}

Quaternion Quaternion::operator*(Quaternion other) {
    return Quaternion(value_ * other.value_);
}

bool Quaternion::operator==(Quaternion other) {
    return value_ == other.value_;
}

bool Quaternion::operator!=(Quaternion other) {
    return value_ != other.value_;
}

Quaternion Quaternion::Euler(Vector3 euler) {
    return Quaternion(glm::quat(euler.GetGLMValue()));
}

Quaternion Quaternion::AngleAxis(float angle, Vector3 axis) {
    return Quaternion(glm::angleAxis(angle, axis.GetGLMValue()));
}

float Quaternion::Dot(Quaternion a, Quaternion b) {
    return glm::dot(a.value_, b.value_);
}

Quaternion Quaternion::FromToRotation(Vector3 from, Vector3 to) {
    Quaternion ans;
    ans.SetFromToRotation(from, to);
    return ans;
}

Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 up) {
    Quaternion q;
    q.SetLookRotation(forward, up);
    return q;
}

Quaternion Quaternion::Inverse(Quaternion q) {
    return Quaternion(glm::inverse(q.value_));
}

Quaternion Quaternion::LerpUnclamped(Quaternion a, Quaternion b, float t) {
    return Quaternion(Vector4::LerpUnclamped(a, b, t));
}

Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t) {
    t = glm::clamp(t, 0.0f, 1.0f);
    return LerpUnclamped(a, b, t);
}

Quaternion Quaternion::Normalize(Quaternion q) {
    return Quaternion(glm::normalize(q.value_));
}

Quaternion Quaternion::SlerpUnclamped(Quaternion a, Quaternion b, float t) {
    return Quaternion(Vector4::SlerpUnclamped(a, b, t));
}

Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, float t) {
    t = glm::clamp(t, 0.0f, 1.0f);
    return SlerpUnclamped(a, b, t);
}

Quaternion Quaternion::Identity() {
    return Quaternion(glm::quat(glm::vec3(0.0f)));
}
