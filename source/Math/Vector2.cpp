#include "Vector2.h"
#include <sstream>
#include <iomanip>

Vector2::Vector2() {
    value_ = glm::vec2(0.0f);
}

Vector2::Vector2(glm::vec2 value) {
    value_ = value;
}

Vector2::Vector2(float x, float y) {
    value_ = glm::vec2(x, y);
}

float Vector2::GetMagnitude() {
    return value_.length();
}

Vector2 Vector2::Normalized() {
    float magnitude = this->GetMagnitude();
    return Vector2(value_.x / magnitude, value_.y / magnitude);
}

float Vector2::GetSqrMagnitude() {
    return
    value_.x * value_.x +
    value_.y * value_.y;
}

glm::vec2 Vector2::GetGLMValue() {
    return value_;
}

float Vector2::x() {
    return value_.x;
}

float Vector2::y() {
    return value_.y;
}

void Vector2::Normalize() {
    value_ /= value_.length();
}

void Vector2::Set(float x, float y) {
    value_ = glm::vec2(x, y);
}

void Vector2::SetX(float x) {
    value_.x = x;
}

void Vector2::SetY(float y) {
    value_.y = y;
}

std::string Vector2::ToString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "(" << value_.x << ", " << value_.y << ")";
    return ss.str();
}

Vector2 Vector2::Up() {
    return Vector2(0, 1);
}

Vector2 Vector2::Down() {
    return Vector2(0, -1);
}

Vector2 Vector2::Left() {
    return Vector2(-1, 0);
}

Vector2 Vector2::Right() {
    return Vector2(1, 0);
}

Vector2 Vector2::Zero() {
    return Vector2(0, 0);
}

Vector2 Vector2::One() {
    return Vector2(1, 1);
}

float Vector2::operator[](int index) {
    switch (index) {
        case 0:
            return value_.x;
        case 1:
            return value_.y;
        default:
            return 0;
    }
}

Vector2 Vector2::operator*(float c) {
    return Vector2(value_.x * c, value_.y*c);
}

Vector2 Vector2::operator/(float c) {
    return Vector2(value_.x / c, value_.y / c);
}

Vector2 Vector2::operator+(Vector2 other) {
    return Vector2(value_.x + other.x(), value_.y * other.y());
}

Vector2 Vector2::operator-(Vector2 other) {
    return Vector2(value_.x - other.x(), value_.y - other.y());
}

Vector2 Vector2::operator+(float other) {
    return Vector2(value_.x + other, value_.y * other);
}

Vector2 Vector2::operator-(float other) {
    return Vector2(value_.x - other, value_.y - other);
}


Vector2 Vector2::operator*=(float c) {
    Vector2 result = *this * c;
    this->Set(result.x(), result.y());
    return result;
}

Vector2 Vector2::operator/=(float c) {
    Vector2 result = *this / c;
    this->Set(result.x(), result.y());
    return result;
}

Vector2 Vector2::operator+=(Vector2 other) {
    Vector2 result = *this + other;
    this->Set(result.x(), result.y());
    return result;
}

Vector2 Vector2::operator-=(Vector2 other) {
    Vector2 result = *this + other;
    this->Set(result.x(), result.y());
    return result;
}

Vector2 operator*(float b, Vector2 a) {
    return b * a;
}

Vector2 operator+(float b, Vector2 a) {
    return a + b;
}

Vector2 operator-(float b, Vector2 a) {
    Vector2 diff = a - b;
    return -1.0f * diff;
}

Vector2 operator/(float b, Vector2 a) {
    return Vector2(b / a.x(), b / a.y());
}

bool Vector2::operator==(Vector2 other) {
    return value_.x == other.x() && value_.y == other.y();
}

bool Vector2::operator!=(Vector2 other) {
    return !(*this == other);
}

float Vector2::Angle(Vector2 a, Vector2 b) {
    float dot = Dot(a, b);
    float d = a.GetMagnitude() * b.GetMagnitude();
    dot /= d;
    return glm::acos(dot);
}

Vector2 Vector2::ClampMagnitude(Vector2 v, float maxLength) {
    float length = glm::min(v.GetMagnitude(), maxLength);
    return v.Normalized() * length;
}

float Vector2::Distance(Vector2 a, Vector2 b) {
    return (a - b).GetMagnitude();
}

float Vector2::Dot(Vector2 a, Vector2 b) {
    return a.x() * b.x() + a.y() * b.y();
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t) {
    t = glm::clamp(t, 0.0f, 1.0f);
    return (1.0f - t) * a + t * b;
}

Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t) {
    return (1.0f - t) * a + t * b;
}

Vector2 Vector2::Min(Vector2 a, Vector2 b) {
    return glm::min(a.value_, b.value_);
}

Vector2 Vector2::Max(Vector2 a, Vector2 b) {
    return glm::max(a.value_, b.value_);
}

Vector2 Vector2::Perpendicular(Vector2 a) {
    return Vector2(-a.y(), a.x());
}

Vector2 Vector2::Reflect(Vector2 a, Vector2 n) {
    return glm::reflect(a.value_, n.value_);
}

Vector2 Vector2::Scale(Vector2 a, Vector2 b) {
    return Vector2(a.x() * b.x(), a.y() * b.y());
}

float Vector2::SignedAngle(Vector2 a, Vector2 b) {
    glm::vec2 c = glm::cross(glm::vec3(a.value_, 0.0f), glm::vec3(b.value_, 0.0f));
    return glm::asin(c.length() / (a.GetMagnitude() * b.GetMagnitude()));
}
