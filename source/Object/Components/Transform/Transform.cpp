#include "Transform.h"
#include "../../Object.h"
#include "../../../Scene/Scene.h"
#include <assert.h>

Transform::Transform(Object* object) : Component(object) {
	init(object);
}

Transform::Transform(Object* object, Vector3 position) : Component(object) {
	init(object, position);
}

Transform::Transform(Object* object, Vector3 position, Quaternion rotation) : Component(object) {
	init(object, position, rotation);
}

Transform::Transform(Object* object, Vector3 position, Quaternion rotation, Vector3 scale) : Component(object) {
	init(object, position, rotation, scale);
}

Transform::Transform(Object* object, Transform* parent) : Component(object) {
	init(object, parent);
}

Transform::Transform(Object* object, Transform* parent, Vector3 position) : Component(object) {
	init(object, parent, position);
}

Transform::Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation) : Component(object) {
	init(object, parent, position, rotation);
}

Transform::Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation, Vector3 scale) : Component(object) {
	init(object, parent, position, rotation, scale);
}

void Transform::init(Object* object) {
	init(object, object->GetScene()->GetRootTransform(), Vector3::Zero(), Quaternion::Identity(), Vector3::One());
}

void Transform::init(Object* object, Vector3 position) {
	init(object, object->GetScene()->GetRootTransform(), position, Quaternion::Identity(), Vector3::One());
}

void Transform::init(Object* object, Vector3 position, Quaternion rotation) {
	init(object, object->GetScene()->GetRootTransform(), position, rotation, Vector3::One());
}

void Transform::init(Object* object, Vector3 position, Quaternion rotation, Vector3 scale) {
	init(object, object->GetScene()->GetRootTransform(), position, rotation, scale);
}

void Transform::init(Object* object, Transform* parent) {
	init(object, parent, Vector3::Zero(), Quaternion::Identity(), Vector3::One());
}

void Transform::init(Object* object, Transform* parent, Vector3 position) {
	init(object, parent, position, Quaternion::Identity(), Vector3::One());
}

void Transform::init(Object* object, Transform* parent, Vector3 position, Quaternion rotation) {
	init(object, parent, position, rotation, Vector3::One());
}

void Transform::init(Object* object, Transform* parent, Vector3 position, Quaternion rotation, Vector3 scale) {
	assert(object != NULL);
	position_ = position;
	rotation_ = rotation;
	scale_ = scale;

	localToWorldMatrix_ = glm::mat4(1.0f);
	worldToLocalMatrix_ = glm::mat4(1.0f);

	parent_ = NULL;

	RecomputeLocalTransform();
	SetParent(parent);
}

Transform::~Transform() {
	DetachChildren();
	SetParent(NULL);
}

void Transform::RecomputeTransform() {
	glm::mat4 parentLToW = HasParent() ? parent_->GetLocalToWorldMatrix() : glm::mat4(1.0f);
	Quaternion parentRot = HasParent() ? parent_->GetRotation() : Quaternion::Identity();
	Vector3 parentScale = HasParent() ? parent_->GetScale() : Vector3::One();

	position_ = parentLToW * Vector4(localPosition_, 1.0f);
	rotation_ = localRotation_ * parentRot;
	scale_ = parentScale * localScale_;
	localToWorldMatrix_ =
		parentLToW *
		glm::translate(glm::mat4(1.0f), localPosition_.GetGLMValue()) *
		localRotation_.GetTransformationMatrix() *
		glm::scale(glm::mat4(1.0f), localScale_.GetGLMValue());
	worldToLocalMatrix_ = glm::inverse(localToWorldMatrix_);
}

void Transform::RecomputeLocalTransform() {
	glm::mat4 parentWToL = HasParent() ? parent_->GetWorldToLocalMatrix() : glm::mat4(1.0f);
	glm::mat4 parentLToW = HasParent() ? parent_->GetLocalToWorldMatrix() : glm::mat4(1.0f);
	Quaternion parentRot = HasParent() ? parent_->GetRotation() : Quaternion::Identity();
	Vector3 parentScale = HasParent() ? parent_->GetScale() : Vector3::One();

	localPosition_ = parentWToL * Vector4(position_, 1.0f);
	localRotation_ = rotation_ * Quaternion::Inverse(parentRot);
	localScale_ = (1.0f / parentScale) * scale_;
	localToWorldMatrix_ =
		parentLToW *
		glm::translate(glm::mat4(1.0f), localPosition_.GetGLMValue()) *
		localRotation_.GetTransformationMatrix() *
		glm::scale(glm::mat4(1.0f), localScale_.GetGLMValue());
	worldToLocalMatrix_ = glm::inverse(localToWorldMatrix_);
}

void Transform::RecomputeSubtree(Transform* root) {
	root->RecomputeTransform();
	for (auto child : root->children_) {
		Transform::RecomputeSubtree(child);
	}
}

Transform* Transform::GetParent() {
	return this->parent_;
}

void Transform::SetParent(Transform* parent) {
    if (parent != NULL && IsChildOf(parent)) {
        return;
    }
    
    if (parent_ != NULL) {
        for (int i = siblingIndex_+1; i < parent_->GetChildCount(); i++) {
            parent_->children_[i]->siblingIndex_--;
        }
        parent_->children_.erase(parent_->children_.begin() + siblingIndex_);
    }
    
    parent_ = parent;
    if (parent == NULL) {
        siblingIndex_ = 0;
    }
    else {
        siblingIndex_ = (unsigned int)parent->children_.size();
        parent->children_.push_back(this);
    }
	RecomputeLocalTransform();
}

Object* Transform::GetObject() {
	return object_;
}

unsigned int Transform::GetChildCount() {
	return (unsigned int)children_.size();
}

Transform* Transform::GetChild(unsigned int index) {
	assert(index < children_.size());
    return children_[index];
}

Vector3 Transform::GetLocalPosition() {
	return localPosition_;
}

void Transform::SetLocalPosition(Vector3 position) {
	localPosition_ = position;
	RecomputeSubtree(this);
}

Quaternion Transform::GetLocalRotation() {
	return localRotation_;
}

void Transform::SetLocalRotation(Quaternion rotation) {
	localRotation_ = rotation;
	RecomputeSubtree(this);
}

Vector3 Transform::GetLocalScale() {
	return localScale_;
}

void Transform::SetLocalScale(Vector3 scale) {
	localScale_ = scale;
	RecomputeSubtree(this);
}

Vector3 Transform::GetPosition() {
	return position_;
}

void Transform::SetPosition(Vector3 position) {
    glm::mat4 parentWToL = HasParent() ? parent_->GetWorldToLocalMatrix() : glm::mat4(1.0f);
	Vector3 newLocalPosition = parentWToL * Vector4(position, 1.0f);
	SetLocalPosition(newLocalPosition);
}

Quaternion Transform::GetRotation() {
	return rotation_;
}

void Transform::SetRotation(Quaternion rotation) {
	Quaternion parentRot = HasParent() ? parent_->GetRotation() : Quaternion::Identity();
	Quaternion newLocalRotation = rotation * Quaternion::Inverse(parentRot);
	SetLocalRotation(newLocalRotation);
}

Vector3 Transform::GetScale() {
	return scale_;
}

std::string Transform::GetName() {
    return object_->GetName();
}

Vector3 Transform::Forward() {
	return localToWorldMatrix_ * Vector4(Vector3::Forward(), 0.0f);
}

Vector3 Transform::Up() {
	return localToWorldMatrix_ * Vector4(Vector3::Up(), 0.0f);
}

Vector3 Transform::Right() {
	return localToWorldMatrix_ * Vector4(Vector3::Right(), 0.0f);
}

Vector3 Transform::GetEulerAngles() {
	return rotation_.GetEulerAngles();
}

Vector3 Transform::GetLocalEulerAngles() {
	return localRotation_.GetEulerAngles();
}

glm::mat4 Transform::GetLocalToWorldMatrix() {
    return localToWorldMatrix_;
}

glm::mat4 Transform::GetWorldToLocalMatrix() {
    return worldToLocalMatrix_;
}

void Transform::DetachChildren() {
    for (int i = 0; i < GetChildCount(); i++) {
        GetChild(i)->SetParent(parent_);
    }
}

Transform* Transform::FindChild(std::string name) {
    for (int i = 0; i < GetChildCount(); i++) {
        if (GetChild(i)->GetName() == name) {
            return GetChild(i);
        }
    }
    return NULL;
}

unsigned int Transform::GetSiblingIndex() {
    return siblingIndex_;
}

Vector3 Transform::TransfromDirection(Vector3 direction) {
    return GetLocalToWorldMatrix() * Vector4(direction, 0.0f);
}

Vector3 Transform::TransformVector(Vector3 vector) {
    return GetLocalToWorldMatrix() * Vector4(vector, 1.0f);
}

Vector3 Transform::InverseTransformDirection(Vector3 direction) {
    return GetWorldToLocalMatrix() * Vector4(direction, 0.0f);
}

Vector3 Transform::InverseTransformVector(Vector3 vector) {
    return GetWorldToLocalMatrix() * Vector4(vector, 1.0f);
}

bool Transform::IsChildOf(Transform *parent) {
    return parent == parent_;
}

bool Transform::HasParent() {
    return parent_ != NULL;
}

void Transform::LookAt(Vector3 position) {
    SetLocalRotation(Quaternion::LookRotation(position - position_, Vector3::Up()));
}

void Transform::Rotate(Vector3 euler) {
    Vector3 currentEuler = GetEulerAngles();
    SetLocalRotation(Quaternion::Euler(currentEuler + euler));
}

void Transform::Rotate(float x, float y, float z) {
    Rotate(Vector3(x, y, z));
}

void Transform::RotateAround(Vector3 point, Vector3 axis, float angle) {
	Object* temp = new Object(object_->GetScene(), point);
	Transform* parent = parent_;
	SetParent(temp->GetTransform());
	temp->GetTransform()->SetRotation(Quaternion::AngleAxis(angle, axis));
	SetParent(parent);
}

void Transform::SetAsFirstSibling() {
	for (int i = 0; i < siblingIndex_; i++) {
		unsigned int siblingIndex = parent_->GetChild(i)->GetSiblingIndex();
		parent_->GetChild(i)->siblingIndex_ = siblingIndex + 1;
	}
	parent_->children_.erase(parent_->children_.begin() + siblingIndex_);
	parent_->children_.insert(parent_->children_.begin(), this);
}

void Transform::SetAsLastSibling() {
	for (int i = siblingIndex_ + 1; i < parent_->GetChildCount(); i++) {
		unsigned int siblingIndex = parent_->GetChild(i)->GetSiblingIndex();
		parent_->GetChild(i)->siblingIndex_ = siblingIndex - 1;
	}
	parent_->children_.erase(parent_->children_.begin() + siblingIndex_);
	parent_->children_.insert(parent_->children_.end(), this);
}

void Transform::SetSiblingIndex(unsigned int index) {
	assert(index < parent_->GetChildCount());
	parent_->children_.erase(parent_->children_.begin() + siblingIndex_);
	parent_->children_.insert(parent_->children_.begin() + index, this);
	for (int i = 0; i < parent_->GetChildCount(); i++) {
		parent_->GetChild(i)->siblingIndex_ = i;
	}
}

void Transform::Translate(Vector3 delta) {
	SetPosition(position_ + delta);
}

void Transform::TranslateLocal(Vector3 delta) {
	SetLocalPosition(localPosition_ + delta);
}
