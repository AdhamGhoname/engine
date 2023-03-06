#include "Transform.h"
#include "../../Object.h"
#include <assert.h>

Transform::Transform(Object* object) {
	assert(object != NULL);
	object_ = object;
	parent_ = object->GetScene()->GetRootTransform();
	localPosition_ = Vector3::Zero();
	localRotation_ = Quaternion::Identity();
	localScale_ = Vector3::One();

	position_ = localPosition_;
	rotation_ = localRotation_;
	scale_ = localScale_;
	siblingIndex_ = 0;
	localToWorldMatrix_ = glm::mat4(1.0f);
	worldToLocalMatrix_ = glm::mat4(1.0f);
}

Transform::Transform(Object* object, Vector3 position) {
	assert(object != NULL);
	object_ = object;
	parent_ = object->GetScene()->GetRootTransform();
	localPosition_ = position;
	localRotation_ = Quaternion::Identity();
	localScale_ = Vector3::One();

	position_ = localPosition_;
	rotation_ = localRotation_;
	scale_ = localScale_;
	siblingIndex_ = 0;
	localToWorldMatrix_ = glm::mat4(1.0f);
	localToWorldMatrix_ = glm::translate(localToWorldMatrix_, position.GetGLMValue());
	worldToLocalMatrix_ = glm::inverse(localToWorldMatrix_);
}

Transform::Transform(Object* object, Vector3 position, Quaternion rotation) {
	assert(object != NULL);
	object_ = object;
	parent_ = object->GetScene()->GetRootTransform();
	localPosition_ = position;
	localRotation_ = rotation;
	localScale_ = Vector3::One();

	position_ = localPosition_;
	rotation_ = localRotation_;
	scale_ = localScale_;
	siblingIndex_ = 0;
	localToWorldMatrix_ = glm::translate(glm::mat4(1.0f), position.GetGLMValue()) * 
						rotation.GetTransformationMatrix();

	worldToLocalMatrix_ = glm::inverse(localToWorldMatrix_);
}

Transform::Transform(Object* object, Vector3 position, Quaternion rotation, Vector3 scale) {
	assert(object != NULL);
	object_ = object;
	parent_ = object->GetScene()->GetRootTransform();
	localPosition_ = position;
	localRotation_ = rotation;
	localScale_ = scale;

	position_ = localPosition_;
	rotation_ = localRotation_;
	scale_ = localScale_;
	siblingIndex_ = 0;
	localToWorldMatrix_ = glm::translate(glm::mat4(1.0f), position.GetGLMValue()) *
		rotation.GetTransformationMatrix() *
		glm::scale(glm::mat4(1.0f), scale.GetGLMValue());

	worldToLocalMatrix_ = glm::inverse(localToWorldMatrix_);
}

Transform::Transform(Object* object, Transform* parent) {
	assert(object != NULL);
	assert(parent != NULL);

	object_ = object;
	parent_ = parent;
	localPosition_ = Vector3::Zero();
	localRotation_ = Quaternion::Identity();
	localScale_ = Vector3::One();

	SetParent(parent);
}

Transform::Transform(Object* object, Transform* parent, Vector3 position) {
	assert(object != NULL);
	object_ = object;
	parent_ = parent;
	localPosition_ = position;
	localRotation_ = Quaternion::Identity();
	localScale_ = Vector3::One();

	SetParent(parent);
}

Transform::Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation) {
	assert(object != NULL);
	object_ = object;
	parent_ = parent;
	localPosition_ = position;
	localRotation_ = rotation;
	localScale_ = Vector3::One();

	SetParent(parent);
}

Transform::Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation, Vector3 scale) {
	assert(object != NULL);
	object_ = object;
	parent_ = parent;
	localPosition_ = position;
	localRotation_ = rotation;
	localScale_ = scale;

	SetParent(parent);
	worldToLocalMatrix_ = glm::inverse(localToWorldMatrix_);
}

Transform::~Transform() {
	SetParent(NULL);
	DetachChildren();
}

void Transform::RecomputeTransform() {
	glm::mat4 parentLToW = HasParent() ? parent_->GetLocalToWorldMatrix() : glm::mat4(1.0f);
	Quaternion parentRot = HasParent() ? parent_->GetRotation() : Quaternion::Identity();

	position_ = parentLToW * Vector4(localPosition_, 1.0f);
	rotation_ = localRotation_ * parentRot;
	scale_ = parentLToW * Vector4(localScale_, 0.0f);
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
	localPosition_ = parentWToL * Vector4(position_, 1.0f);
	Quaternion parentRot = HasParent() ? parent_->GetRotation() : Quaternion::Identity();
	localRotation_ = rotation_ * Quaternion::Inverse(parentRot);
	localScale_ = parentWToL * Vector4(scale_, 0.0f);
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
    if (IsChildOf(parent)) {
        return;
    }
    
    if (parent_ != NULL) {
        for (int i = siblingIndex_+1; i < parent_->GetChildCount(); i++) {
            parent_->children_[i]->siblingIndex_--;
        }
        parent->children_.erase(parent_->children_.begin() + siblingIndex_);
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
        GetChild(i)->SetParent(object_->GetScene()->GetRootTransform());
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
	delete temp;
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
