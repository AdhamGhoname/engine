#pragma once
#include <glm/glm.hpp>
#include <string>

struct Vector3 {
private:
    glm::vec2 value_;
public:
    Vector3();
    Vector3(float x, float y, float z);
    
    float GetMagnitude();
    Vector3 Normalized();
    float GetSqrMagnitude();
    float x();
    float y();
    float z();
    void Normalize();
    void Set(float x, float y, float z);
    std::string ToString();
    
    // static
    static Vector3 Up();
    static Vector3 Down();
    static Vector3 Left();
    static Vector3 Right();
    static Vector3 Back();
    static Vector3 Forward();
    static Vector3 One();
    static Vector3 Zero();
    
    static float Angle(Vector3 a, Vector3 b);
    static Vector3 ClampMangitude(Vector3 v, float maxLength);
    static Vector3 Cross(Vector3 a, Vector3 b);
    static float Distance(Vector3 a, Vector3 b);
    static float Dot(Vector3 a, Vector3 b);
    static Vector3 Lerp(Vector3 a, Vector3 b, float t);
    static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);
    static Vector3 Max(Vector3 a, Vector3 b);
    static Vector3 Min(Vector3 a, Vector3 b);
    static Vector3 Normalize(Vector3 v);
    static Vector3 Project(Vector3 a, Vector3 b);
    static Vector3 ProjectOnPlane(Vector3 v, Vector3 n);
    static Vector3 Reflect(Vector3 v, Vector3 n);
    static Vector3 Scale(Vector3 a, Vector3 b);
    static float SignedAngle(Vector3 a, Vector3 b);
    static Vector3 Slerp(Vector3 a, Vector3 b, float t);
    static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, Vector3 t);
    
    // operators
    float operator[](int index);
    Vector3 operator-(const Vector3& other);
    Vector3 operator+(const Vector3& other);
    Vector3 operator*(float c);
    Vector3 operator/(float c);
    bool operator==(const Vector3& other);
    bool operator!=(const Vector3& other);
};