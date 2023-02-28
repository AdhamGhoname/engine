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
    float magnitude = value_.length();
    return Vector2(value_.x / magnitude, value_.y / magnitude);
}

float Vector2::GetSqrMagnitude() {
    return
    value_.x * value_.x +
    value_.y * value_.y;
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

Vector2 Vector2::operator+(Vector2& other) {
    return Vector2(value_.x + other.x(), value_.y * other.y());
}

Vector2 Vector2::operator-(Vector2& other) {
    return Vector2(value_.x - other.x(), value_.y - other.y());
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

Vector2 Vector2::operator+=(Vector2& other) {
    Vector2 result = *this + other;
    this->Set(result.x(), result.y());
    return result;
}

bool Vector2::operator==(Vector2& other) {
    return value_.x == other.x() && value_.y == other.y();
}

bool Vector2::operator!=(Vector2& other) {
    return !(*this == other);
}

float Vector2::Angle(Vector2 a, Vector2 b) {
    float dot = Dot(a, b);
    float d = a.GetMagnitude() * b.GetMagnitude();
    dot /= d;
    return glm::acos(dot);
}

Vector2 Vector2::ClampMangitude(Vector2 v, float maxLength) {
    v /=
}
