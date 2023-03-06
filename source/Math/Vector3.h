#pragma once
#include <glm/glm.hpp>
#include <string>
#include "MathCommons.h"
#include "Vector2.h"
#include "Vector4.h"


struct Vector3 {
private:
    glm::vec3 value_;
    Vector3(glm::vec3 value);
public:
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(Vector2 v, float z);
    Vector3(Vector4 v);
    
    float GetMagnitude();
    Vector3 Normalized();
    float GetSqrMagnitude();
    glm::vec3 GetGLMValue();

    float x();
    float y();
    float z();
    void Normalize();
    void Set(float x, float y, float z);
    void SetX(float x);
    void SetY(float x);
    void SetZ(float x);

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
    static Vector3 ClampMagnitude(Vector3 v, float maxLength);
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
    static Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);
    
    // operators
    float operator[](int index);
    Vector3 operator-(Vector3 other);
    Vector3 operator-(float other);
    Vector3 operator-=(Vector3 other);
    Vector3 operator+(Vector3 other);
    Vector3 operator+(float other);
    Vector3 operator+=(Vector3 other);
    Vector3 operator*(float c);
    Vector3 operator*=(float c);
    Vector3 operator/(float c);
    Vector3 operator/=(float c);
    bool operator==(Vector3 other);
    bool operator!=(Vector3 other);
};

Vector3 operator*(float b, Vector3 a);
Vector3 operator*(glm::mat3 m, Vector3 v);
Vector3 operator+(float b, Vector3 a);
Vector3 operator-(float b, Vector3 a);
Vector3 operator/(float b, Vector3 a);
