#include "Vector3.h"
#include <sstream>
#include <iomanip>


Vector3::Vector3() {
	value_ = glm::vec3(0.0f);
}

Vector3::Vector3(glm::vec3 value) {
	value_ = value;
}

Vector3::Vector3(float x, float y, float z) {
	value_ = glm::vec3(x, y, z);
}

Vector3::Vector3(Vector2 v, float z) {
	value_ = glm::vec3(v.x(), v.y(), z);
}

Vector3::Vector3(Vector4 v) {
	value_ = glm::vec3(v.GetGLMValue());
}

float Vector3::GetMagnitude() {
	return value_.length();
}

glm::vec3 Vector3::GetGLMValue() {
	return value_;
}

Vector3 Vector3::Normalized() {
	float magnitude = this->GetMagnitude();
	return Vector3(value_.x / magnitude, value_.y / magnitude, value_.z / magnitude);
}


float Vector3::GetSqrMagnitude() {
	return
		value_.x * value_.x +
		value_.y * value_.y +
		value_.z * value_.z;
}

float Vector3::x() {
	return value_.x;
}

float Vector3::y() {
	return value_.y;
}

float Vector3::z() {
	return value_.z;
}

void Vector3::Normalize() {
	float magnitude = this->GetMagnitude();
	this->Set(value_.x / magnitude, value_.y / magnitude, value_.z / magnitude);
}

void Vector3::Set(float x, float y, float z) {
	value_ = glm::vec3(x, y, z);
}

void Vector3::SetX(float x) {
	value_.x = x;
}

void Vector3::SetY(float y) {
	value_.y = y;
}

void Vector3::SetZ(float z) {
	value_.z = z;
}

std::string Vector3::ToString() {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);
	ss << "(" << value_.x << ", " << value_.y << ", " << value_.z << ")";
	return ss.str();
}

Vector3 Vector3::Up() {
	return Vector3(0, 1, 0);
}

Vector3 Vector3::Down() {
	return Vector3(0, -1, 0);
}

Vector3 Vector3::Left() {
	return Vector3(-1, 0, 0);
}

Vector3 Vector3::Right() {
	return Vector3(1, 0, 0);
}

Vector3 Vector3::Back() {
	return Vector3(0, 0, -1);
}

Vector3 Vector3::Forward() {
	return Vector3(0, 0, 1);
}

Vector3 Vector3::One() {
	return Vector3(1, 1, 1);
}

Vector3 Vector3::Zero() {
	return Vector3(0, 0, 0);
}

float Vector3::operator[](int index) {
	switch (index) {
	case 0:
		return value_.x;
	case 1:
		return value_.y;
	case 2:
		return value_.z;
	default:
		return 0.0f;
	}
}

Vector3 Vector3::operator-(Vector3 other) {
	return Vector3(this->x() - other.x(),
				   this->y() - other.y(),
				   this->z() - other.z());
}

Vector3 Vector3::operator-(float other) {
	return Vector3(this->x() - other,
				   this->y() - other,
				   this->z() - other);
}

Vector3 Vector3::operator-=(Vector3 other) {
	value_ = glm::vec3(value_.x - other.x(), value_.y - other.y(), value_.z - other.z());
	return Vector3(value_);
}

Vector3 Vector3::operator+(Vector3 other) {
	return Vector3(this->x() + other.x(),
		this->y() + other.y(),
		this->z() + other.z());
}

Vector3 Vector3::operator+(float other) {
	return Vector3(this->x() + other,
		this->y() + other,
		this->z() + other);
}

Vector3 Vector3::operator+=(Vector3 other) {
	value_ = glm::vec3(value_.x + other.x(), value_.y + other.y(), value_.z + other.z());
	return Vector3(value_);
}

Vector3 Vector3::operator*(float other) {
	return Vector3(this->x() * other,
		this->y() * other,
		this->z() * other);
}

Vector3 Vector3::operator*(Vector3 other) {
	return Vector3(this->x() * other.x(),
		this->y() * other.y(),
		this->z() * other.z());
}

Vector3 Vector3::operator*=(float other) {
	value_ = glm::vec3(value_.x * other, value_.y * other, value_.z * other);
	return Vector3(value_);
}

Vector3 Vector3::operator/(float other) {
	return Vector3(this->x() / other,
		this->y() / other,
		this->z() / other);
}

Vector3 Vector3::operator/=(float other) {
	value_ = glm::vec3(value_.x / other, value_.y / other, value_.z / other);
	return Vector3(value_);
}

bool Vector3::operator==(Vector3 other) {
	return value_ == other.value_;
}

bool Vector3::operator!=(Vector3 other) {
	return value_ != other.value_;
}

Vector3 operator*(float b, Vector3 a) {
	return a * b;
}

Vector3 operator*(glm::mat3 m, Vector3 v) {
	glm::vec3 res = m * v.GetGLMValue();
	return Vector3(res.x, res.y, res.z);
}

Vector3 operator+(float b, Vector3 a) {
	return a + b;
}

Vector3 operator-(float b, Vector3 a) {
	return -1.0f * (a - b);
}

Vector3 operator/(float b, Vector3 a) {
	return Vector3(b / a.x(), b / a.y(), b / a.z());
}

float Vector3::Angle(Vector3 a, Vector3 b) {
	return glm::acos(glm::dot(a.value_, b.value_) / (a.GetMagnitude() * b.GetMagnitude()));
}

Vector3 Vector3::ClampMagnitude(Vector3 v, float maxLength) {
	float length = glm::min(maxLength, v.GetMagnitude());
	return v.Normalized() * length;
}

Vector3 Vector3::Cross(Vector3 a, Vector3 b) {
	return Vector3(glm::cross(a.value_, b.value_));
}

float Vector3::Distance(Vector3 a, Vector3 b) {
	return (a - b).GetMagnitude();
}

float Vector3::Dot(Vector3 a, Vector3 b) {
	return glm::dot(a.value_, b.value_);
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t) {
	t = glm::clamp(t, 0.0f, 1.0f);
	return (1.0f - t) * a + t * b;
}

Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t) {
	return (1.0f - t) * a + t * b;
}

Vector3 Vector3::Max(Vector3 a, Vector3 b) {
	return Vector3(glm::max(a.value_, b.value_));
}

Vector3 Vector3::Min(Vector3 a, Vector3 b) {
	return Vector3(glm::min(a.value_, b.value_));
}

Vector3 Vector3::Normalize(Vector3 a) {
	return a.Normalized();
}

Vector3 Vector3::Project(Vector3 a, Vector3 b) {
	float b_mag = b.GetMagnitude();
	return (Dot(a, b) / (b_mag * b_mag)) * b;
}

Vector3 Vector3::ProjectOnPlane(Vector3 a, Vector3 n) {
	n = n.Normalized();
	return Cross(Cross(n, a), n);
}

Vector3 Vector3::Reflect(Vector3 a, Vector3 n) {
	return Vector3(glm::reflect(a.value_, n.value_));
}

Vector3 Vector3::Scale(Vector3 a, Vector3 b) {
	return Vector3(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
}

float Vector3::SignedAngle(Vector3 a, Vector3 b) {
	Vector3 c = Cross(a, b);
	return glm::asin(c.GetMagnitude() / (a.GetMagnitude() * b.GetMagnitude()));
}

Vector3 Vector3::Slerp(Vector3 a, Vector3 b, float t) {
	t = glm::clamp(t, 0.0f, 1.0f);
	return SlerpUnclamped(a, b, t);
}

Vector3 Vector3::SlerpUnclamped(Vector3 a, Vector3 b, float t) {
	float omega = Angle(a, b);
	if (omega == 0)
		return a;

	float sin_omega = glm::sin(omega);
	return (glm::sin((1.0f - t) * omega) / sin_omega) * a + (glm::sin(t * omega) / sin_omega) * b;
}
