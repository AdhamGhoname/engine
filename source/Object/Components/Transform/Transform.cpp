#include "Transform.h"
#include <assert.h>

Transform::Transform(Object* object) {
	assert(object != NULL);
	object_ = object;
	parent_ = NULL;
	localPosition_ = Vector3::Zero();
	localRotation_ = Quaternion::Identity();
	localScale_ = Vector3::One();

	position_ = localPosition_;
	rotation_ = localRotation_;
	scale_ = localScale_;
	siblingIndex_ = 0;
	localToWorldMatrix_ = glm::mat4(1.0f);
	worldToLocalMatrix_ = glm::mat4(1.0f);
	valid_ = true;
}

Transform::Transform(Object* object, Vector3 position) {
	assert(object != NULL);
	object_ = object;
	parent_ = NULL;
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
	valid_ = true;
}

Transform::Transform(Object* object, Vector3 position, Quaternion rotation) {
	assert(object != NULL);
	object_ = object;
	parent_ = NULL;
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
	valid_ = true;
}

Transform::Transform(Object* object, Vector3 position, Quaternion rotation, Vector3 scale) {
	assert(object != NULL);
	object_ = object;
	parent_ = NULL;
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
	valid_ = true;
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
	valid_ = true;
}

Transform::Transform(Object* object, Transform* parent, Vector3 position) {
	assert(object != NULL);
	object_ = object;
	parent_ = NULL;
	localPosition_ = position;
	localRotation_ = Quaternion::Identity();
	localScale_ = Vector3::One();

	SetParent(parent);
	valid_ = true;
}

Transform::Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation) {
	assert(object != NULL);
	object_ = object;
	parent_ = NULL;
	localPosition_ = position;
	localRotation_ = rotation;
	localScale_ = Vector3::One();

	SetParent(parent);
	valid_ = true;
}

Transform::Transform(Object* object, Transform* parent, Vector3 position, Quaternion rotation, Vector3 scale) {
	assert(object != NULL);
	object_ = object;
	parent_ = NULL;
	localPosition_ = position;
	localRotation_ = rotation;
	localScale_ = scale;

	SetParent(parent);
	worldToLocalMatrix_ = glm::inverse(localToWorldMatrix_);
	valid_ = true;
}


Transform* Transform::GetParent() {
	return this->parent_;
}

void Transform::SetParent(Transform* parent) {
	if (!this->IsChildOf(parent)) {
		valid_ = false;
	}
	parent_ = parent;
}

Object* Transform::GetObject() {
	return object_;
}

unsigned int Transform::GetChildCount() {
	return children_.size();
}

Transform* Transform::GetChild(unsigned int index) {
	assert(index <= children_.size());
}

Vector3 Transform::GetLocalPosition() {
	return localPosition_;
}

void Transform::SetLocalPosition(Vector3 position) {
	localPosition_ = position;
	RecomputeTransform();
}

Quaternion Transform::GetLocalRotation() {
	return localRotation_;
}

void Transform::SetLocalRotation(Quaternion rotation) {
	localRotation_ = rotation;
	RecomputeTransform();
}

Vector3 Transform::GetLocalScale() {
	return localScale_;
}

void Transform::SetLocalScale(Vector3 scale) {
	localScale_ = scale;
	RecomputeTransform();
}

Vector3 Transform::GetPosition() {
	if (!valid_) {
		RecomputeTransform();
	}
	return position_;
}

void Transform::SetPosition(Vector3 position) {
	if (!valid_) {
		RecomputeTransform();
	}
	Vector3 newLocalPosition = worldToLocalMatrix_ * Vector4(position, 1.0f);
	SetLocalPosition(newLocalPosition);
}

Quaternion Transform::GetRotation() {
	if (!valid_) {
		RecomputeTransform();
	}
	return rotation_;
}

void Transform::SetRotation(Quaternion rotation) {
	if (!valid_) {
		RecomputeTransform();
	}
	Quaternion parentRot = HasParent() ? parent_->GetRotation() : Quaternion::Identity();
	Quaternion newLocalRotation = rotation * Quaternion::Inverse(parentRot);
	SetLocalRotation(newLocalRotation);
}