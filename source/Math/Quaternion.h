#pragma once
#include <glm/gtx/quaternion.hpp>
#include "MathCommons.h"
#include "Vector4.h"
#include "Vector3.h"
#include <string>

struct Quaternion {
private:
    glm::quat value_ = glm::quat(glm::vec4(0.0f));
    Quaternion(glm::quat value);
public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(Vector4 v);
    glm::mat4 GetTransformationMatrix();
    Quaternion Normalized();
    Vector3 GetEulerAngles();
    float operator[](int index);
    float x();
    float y();
    float z();
    float w();
    void Set(float x, float y, float z, float w);
    void SetFromToRotation(Vector3 from, Vector3 to);
    void SetLookRotation(Vector3 forward, Vector3 up);
    Vector4 ToAngleAxis();
    std::string ToString();
    
    // static
    static Quaternion Euler(float x, float y, float z);
    static Quaternion Euler(Vector3 euler);
    static float Angle(Quaternion a, Quaternion b);
    static Quaternion AngleAxis(float angle, Vector3 axis);
    static float Dot(Quaternion a, Quaternion b);
    static Quaternion FromToRotation(Vector3 from, Vector3 to);
    static Quaternion LookRotation(Vector3 forward, Vector3 up);
    static Quaternion Inverse(Quaternion q);
    static Quaternion Lerp(Quaternion a, Quaternion b, float t);
    static Quaternion LerpUnclamped(Quaternion a, Quaternion b, float t);
    static Quaternion Normalize(Quaternion q);
    static Quaternion Slerp(Quaternion a, Quaternion b, float t);
    static Quaternion SlerpUnclamped(Quaternion a, Quaternion b, float t);
    static Quaternion Identity();

    // operators
    Quaternion operator*(Quaternion other);
    bool operator==(Quaternion other);
    bool operator!=(Quaternion other);
};

