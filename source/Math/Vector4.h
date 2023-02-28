#pragma once
#include <glm/glm.hpp>
#include <string>

struct Vector4 {
private:
    glm::vec2 value_;
public:
    Vector4();
    Vector4(float x, float y, float z);
    
    float GetMagnitude();
    Vector4 Normalized();
    float GetSqrMagnitude();
    float x();
    float y();
    float z();
    void Normalize();
    void Set(float x, float y, float z);
    std::string ToString();
    
    // static
    static Vector4 Up();
    static Vector4 Down();
    static Vector4 Left();
    static Vector4 Right();
    static Vector4 Back();
    static Vector4 Forward();
    static Vector4 One();
    static Vector4 Zero();
    
    static float Angle(Vector4 a, Vector4 b);
    static Vector4 ClampMangitude(Vector4 v, float maxLength);
    static Vector4 Cross(Vector4 a, Vector4 b);
    static float Distance(Vector4 a, Vector4 b);
    static float Dot(Vector4 a, Vector4 b);
    static Vector4 Lerp(Vector4 a, Vector4 b, float t);
    static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);
    static Vector4 Max(Vector4 a, Vector4 b);
    static Vector4 Min(Vector4 a, Vector4 b);
    static Vector4 Normalize(Vector4 v);
    static Vector4 Project(Vector4 a, Vector4 b);
    static Vector4 ProjectOnPlane(Vector4 v, Vector4 n);
    static Vector4 Reflect(Vector4 v, Vector4 n);
    static Vector4 Scale(Vector4 a, Vector4 b);
    static float SignedAngle(Vector4 a, Vector4 b);
    static Vector4 Slerp(Vector4 a, Vector4 b, float t);
    static Vector4 SlerpUnclamped(Vector4 a, Vector4 b, Vector4 t);
    
    // operators
    float operator[](int index);
    Vector4 operator-(const Vector4& other);
    Vector4 operator+(const Vector4& other);
    Vector4 operator*(float c);
    Vector4 operator/(float c);
    bool operator==(const Vector4& other);
    bool operator!=(const Vector4& other);
};

