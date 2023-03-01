#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Quaternion.h"


struct Vector4 {
private:
    glm::vec4 value_;
    Vector4(glm::vec4 value);
public:
    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(Quaternion q);
    Vector4(Vector3 v, float w);
    Vector4(Vector2 v, float z, float w);

    float GetMagnitude();
    Vector4 Normalized();
    float GetSqrMagnitude();
    glm::vec4 GetGLMValue();

    float x();
    float y();
    float z();
    float w();
    void Normalize();
    void Set(float x, float y, float z, float w);
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
    void SetW(float w);
    std::string ToString();
    
    // static
    
    static float Angle(Vector4 a, Vector4 b);
    static Vector4 ClampMagnitude(Vector4 v, float maxLength);
    static float Distance(Vector4 a, Vector4 b);
    static float Dot(Vector4 a, Vector4 b);
    static Vector4 Lerp(Vector4 a, Vector4 b, float t);
    static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);
    static Vector4 Max(Vector4 a, Vector4 b);
    static Vector4 Min(Vector4 a, Vector4 b);
    static Vector4 Normalize(Vector4 v);
    static Vector4 Project(Vector4 a, Vector4 b);
    static Vector4 Reflect(Vector4 v, Vector4 n);
    static Vector4 Scale(Vector4 a, Vector4 b);
    static Vector4 Slerp(Vector4 a, Vector4 b, float t);
    static Vector4 SlerpUnclamped(Vector4 a, Vector4 b, float t);
    
    // operators
    float operator[](int index);
    Vector4 operator-(Vector4& other);
    Vector4 operator-(float other);
    Vector4 operator-=(Vector4& other);
    Vector4 operator+(Vector4& other);
    Vector4 operator+(float other);
    Vector4 operator+=(Vector4& other);
    Vector4 operator*(float c);
    Vector4 operator*=(float c);
    Vector4 operator/(float c);
    Vector4 operator/=(float c);
    bool operator==(Vector4& other);
    bool operator!=(Vector4& other);
};

Vector4 operator*(float b, Vector4& a);
Vector4 operator*(glm::mat4 m, Vector4& v);
Vector4 operator+(float b, Vector4& a);
Vector4 operator-(float b, Vector4& a);
Vector4 operator/(float b, Vector4& a);