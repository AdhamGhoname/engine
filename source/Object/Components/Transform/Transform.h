#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "../../../Object/ObjectCommons.h"
#include "../../Component.h"
#include "../../../Math/MathCommons.h"
#include "../../../Math/Vector3.h"
#include "../../../Math/Vector4.h"
#include "../../../Math/Quaternion.h"


using namespace std;

class Transform : public Component {
private:
	Transform* parent_;
	vector<Transform*> children_;
    Vector3 localPosition_;
    Quaternion localRotation_;
    Vector3 localScale_;
    Vector3 position_;
    Quaternion rotation_;
    Vector3 scale_;
    unsigned int siblingIndex_;
    glm::mat4 localToWorldMatrix_;
    glm::mat4 worldToLocalMatrix_;

    void RecomputeTransform();
    void RecomputeLocalTransform();
    static void RecomputeSubtree(Transform* root);
public:
    Transform(Object* object);
    Transform(Object* object, Vector3 position);
    Transform(Object* object, Vector3 position, Quaternion rotation);
    Transform(Object* object, Vector3 position, Quaternion rotation, Vector3 scale);
    Transform(Object* object, Transform* parent);
    Transform(Object* object, Transform* parent, Vector3 position);
    Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation);
    Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation, Vector3 scale);
    ~Transform();

    // getters and setters
    Transform* GetParent();
    void SetParent(Transform* parent);
    Object* GetObject();
    unsigned int GetChildCount();
    Transform* GetChild(unsigned int index);
    Vector3 GetLocalPosition();
    void SetLocalPosition(Vector3 position);
    Quaternion GetLocalRotation();
    void SetLocalRotation(Quaternion rotation);
    Vector3 GetLocalScale();
    void SetLocalScale(Vector3 scale);
    Vector3 GetPosition();
    void SetPosition(Vector3 position);
    Quaternion GetRotation();
    void SetRotation(Quaternion rotation);
    Vector3 GetScale();
    std::string GetName();

    // utils
    Vector3 Forward();
    Vector3 Up();
    Vector3 Right();
    Vector3 GetEulerAngles();
    Vector3 GetLocalEulerAngles();
    glm::mat4 GetLocalToWorldMatrix();
    glm::mat4 GetWorldToLocalMatrix();

    void DetachChildren();
    Transform* FindChild(std::string name);
    unsigned int GetSiblingIndex();
    Vector3 TransfromDirection(Vector3 direction);
    Vector3 TransformVector(Vector3 vector);
    Vector3 InverseTransformDirection(Vector3 direction);
    Vector3 InverseTransformVector(Vector3 vector);
    bool IsChildOf(Transform* parent);
    bool HasParent();
    void LookAt(Vector3 position);
    void Rotate(Vector3 euler);
    void Rotate(float x, float y, float z);
    void RotateAround(Vector3 point, Vector3 axis, float angle);
    void SetAsFirstSibling();
    void SetAsLastSibling();
    void SetSiblingIndex(unsigned int index);
    void Translate(Vector3 delta);
    void TranslateLocal(Vector3 delta);
};
