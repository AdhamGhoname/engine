#include "Vector4.h"
#include <sstream>
#include <iomanip>


Vector4::Vector4() {
	value_ = glm::vec4(0.0f);
}

Vector4::Vector4(glm::vec4 value) {
	value_ = value;
}

Vector4::Vector4(float x, float y, float z, float w) {
	value_ = glm::vec4(x, y, z, w);
}

Vector4::Vector4(Quaternion q) {
	value_ = Vector4(q.x(), q.y(), q.z(), q.w()).value_;
}

Vector4::Vector4(Vector2 v, float z, float w) {
	value_ = glm::vec4(v.x(), v.y(), z, w);
}

Vector4::Vector4(Vector3 v, float z) {
	value_ = glm::vec4(v.x(), v.y(), v.z(), z);
}


float Vector4::GetMagnitude() {
	return value_.length();
}

glm::vec4 Vector4::GetGLMValue() {
	return value_;
}

Vector4 Vector4::Normalized() {
	float magnitude = this->GetMagnitude();
	return Vector4(value_.x / magnitude, value_.y / magnitude, value_.z / magnitude, value_.w / magnitude);
}


float Vector4::GetSqrMagnitude() {
	return
		value_.x * value_.x +
		value_.y * value_.y +
		value_.z * value_.z +
		value_.w * value_.w;
}

float Vector4::x() {
	return value_.x;
}

float Vector4::y() {
	return value_.y;
}

float Vector4::z() {
	return value_.z;
}

float Vector4::w() {
	return value_.w;
}

void Vector4::Normalize() {
	float magnitude = this->GetMagnitude();
	this->Set(value_.x / magnitude, value_.y / magnitude, value_.z / magnitude, value_.w / magnitude);
}

void Vector4::Set(float x, float y, float z, float w) {
	value_ = glm::vec4(x, y, z, w);
}

void Vector4::SetX(float x) {
	value_.x = x;
}

void Vector4::SetY(float y) {
	value_.y = y;
}

void Vector4::SetZ(float z) {
	value_.z = z;
}

void Vector4::SetW(float w) {
	value_.w = w;
}

std::string Vector4::ToString() {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2);
	ss << "(" << value_.x << ", " << value_.y << ", " << value_.z << ")";
	return ss.str();
}

float Vector4::operator[](int index) {
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
		return 0.0f;
	}
}

Vector4 Vector4::operator-(Vector4 other) {
	return Vector4(this->x() - other.x(),
		this->y() - other.y(),
		this->z() - other.z(),
		this->w() - other.w());
}

Vector4 Vector4::operator-(float other) {
	return Vector4(this->x() - other,
		this->y() - other,
		this->z() - other,
		this->w() - other);
}

Vector4 Vector4::operator-=(Vector4 other) {
	value_ = glm::vec4(value_.x - other.x(), value_.y - other.y(), value_.z - other.z(), value_.w - other.w());
	return Vector4(value_);
}

Vector4 Vector4::operator+(Vector4 other) {
	return Vector4(this->x() + other.x(),
		this->y() + other.y(),
		this->z() + other.z(),
		this->w() + other.w());
}

Vector4 Vector4::operator+(float other) {
	return Vector4(this->x() + other,
		this->y() + other,
		this->z() + other,
		this->w() + other);
}

Vector4 Vector4::operator+=(Vector4 other) {
	value_ = glm::vec4(value_.x + other.x(), value_.y + other.y(), value_.z + other.z(), value_.w + other.w());
	return Vector4(value_);
}

Vector4 Vector4::operator*(float other) {
	return Vector4(this->x() * other,
		this->y() * other,
		this->z() * other,
		this->w() * other);
}

Vector4 Vector4::operator*=(float other) {
	value_ = glm::vec4(value_.x * other, value_.y * other, value_.z * other, value_.w * other);
	return Vector4(value_);
}

Vector4 Vector4::operator/(float other) {
	return Vector4(this->x() / other,
		this->y() / other,
		this->z() / other,
		this->w() / other);
}

Vector4 Vector4::operator/=(float other) {
	value_ = glm::vec4(value_.x / other, value_.y / other, value_.z / other, value_.w / other);
	return Vector4(value_);
}

bool Vector4::operator==(Vector4 other) {
	return value_ == other.value_;
}

bool Vector4::operator!=(Vector4 other) {
	return value_ != other.value_;
}

Vector4 operator*(float b, Vector4 a) {
	return a * b;
}

Vector4 operator*(glm::mat4 m, Vector4 v) {
	glm::vec4 res = m * v.GetGLMValue();
	return Vector4(res.x, res.y, res.z, res.w);
}

Vector4 operator+(float b, Vector4 a) {
	return a + b;
}

Vector4 operator-(float b, Vector4 a) {
	return -1.0f * (a - b);
}

Vector4 operator/(float b, Vector4 a) {
	return Vector4(b / a.x(), b / a.y(), b / a.z(), b / a.w());
}

float Vector4::Angle(Vector4 a, Vector4 b) {
	return glm::acos(glm::dot(a.value_, b.value_) / (a.GetMagnitude() * b.GetMagnitude()));
}

Vector4 Vector4::ClampMagnitude(Vector4 v, float maxLength) {
	float length = glm::min(maxLength, v.GetMagnitude());
	return v.Normalized() * length;
}

float Vector4::Distance(Vector4 a, Vector4 b) {
	return (a - b).GetMagnitude();
}

float Vector4::Dot(Vector4 a, Vector4 b) {
	return glm::dot(a.value_, b.value_);
}

Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t) {
	t = glm::clamp(t, 0.0f, 1.0f);
	return (1.0f - t) * a + t * b;
}

Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t) {
	return (1.0f - t) * a + t * b;
}

Vector4 Vector4::Max(Vector4 a, Vector4 b) {
	return Vector4(glm::max(a.value_, b.value_));
}

Vector4 Vector4::Min(Vector4 a, Vector4 b) {
	return Vector4(glm::min(a.value_, b.value_));
}

Vector4 Vector4::Normalize(Vector4 a) {
	return a.Normalized();
}

Vector4 Vector4::Project(Vector4 a, Vector4 b) {
	float b_mag = b.GetMagnitude();
	return (Dot(a, b) / (b_mag * b_mag)) * b;
}

Vector4 Vector4::Reflect(Vector4 a, Vector4 n) {
	return Vector4(glm::reflect(a.value_, n.value_));
}

Vector4 Vector4::Scale(Vector4 a, Vector4 b) {
	return Vector4(a.x() * b.x(), a.y() * b.y(), a.z() * b.z(), a.w() * b.w());
}

Vector4 Vector4::Slerp(Vector4 a, Vector4 b, float t) {
	t = glm::clamp(t, 0.0f, 1.0f);
	return SlerpUnclamped(a, b, t);
}

Vector4 Vector4::SlerpUnclamped(Vector4 a, Vector4 b, float t) {
	float omega = Angle(a, b);
	if (omega == 0)
		return a;

	float sin_omega = glm::sin(omega);
	return (glm::sin((1.0f - t) * omega) / sin_omega) * a + (glm::sin(t * omega) / sin_omega) * b;
}
