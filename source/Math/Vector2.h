#pragma once
#include <glm/glm.hpp>
#include <string>

struct Vector2 {
private:
    glm::vec2 value_;
    Vector2(glm::vec2 value);
public:
    Vector2();
    Vector2(float x, float y);
    
    float GetMagnitude();
    Vector2 Normalized();
    float GetSqrMagnitude();
    glm::vec2 GetGLMValue();
    float x();
    float y();
    void Normalize();
    void Set(float x, float y);
    void SetX(float x);
    void SetY(float y);
    std::string ToString();
    
    // static
    static Vector2 Up();
    static Vector2 Down();
    static Vector2 Left();
    static Vector2 Right();
    static Vector2 One();
    static Vector2 Zero();
    
    static float Angle(Vector2 a, Vector2 b);
    static Vector2 ClampMagnitude(Vector2 v, float maxLength);
    static float Distance(Vector2 a, Vector2 b);
    static float Dot(Vector2 a, Vector2 b);
    static Vector2 Lerp(Vector2 a, Vector2 b, float t);
    static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);
    static Vector2 Max(Vector2 a, Vector2 b);
    static Vector2 Min(Vector2 a, Vector2 b);
    static Vector2 Perpendicular(Vector2 v);
    static Vector2 Reflect(Vector2 v, Vector2 n);
    static Vector2 Scale(Vector2 a, Vector2 b);
    static float SignedAngle(Vector2 a, Vector2 b);
    
    // operators
    float operator[](int index);
    Vector2 operator-(Vector2& other);
    Vector2 operator-(float other);
    Vector2 operator-=(Vector2& other);
    Vector2 operator+(Vector2& other);
    Vector2 operator+(float other);
    Vector2 operator+=(Vector2& other);
    Vector2 operator*(float c);
    Vector2 operator*=(float c);
    Vector2 operator/(float c);
    Vector2 operator/=(float c);
    bool operator==(Vector2& other);
    bool operator!=(Vector2& other);
};

Vector2 operator*(float b, Vector2& a);
Vector2 operator+(float b, Vector2& a);
Vector2 operator-(float b, Vector2& a);
Vector2 operator/(float b, Vector2& a);