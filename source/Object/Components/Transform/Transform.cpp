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
	if (!this->IsChildOf(parent)) {
		valid_ = false;
	}
	parent_ = parent;
	siblingIndex_ = parent->children_.size();
	parent->children_.push_back(this);
	RecomputeTransform();
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
	Vector3 newLocalPosition = worldToLocalMatrix_ * Vector4(position, 1.0f);
	SetLocalPosition(newLocalPosition);
}

Quaternion Transform::GetRotation() {
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

Vector3 Transform::GetScale() {
	if (!valid_) {
		RecomputeTransform();
	}
	return scale_;
}

Vector3 Transform::Forward() {
	if (!valid_) {
		RecomputeTransform();
	}
	return localToWorldMatrix_ * Vector3::Forward();
}

Vector3 Transform::Up() {
	if (!valid_) {
		RecomputeTransform();
	}
	return localToWorldMatrix_ * Vector3::Up();
}

Vector3 Transform::Right() {
	if (!valid_) {
		RecomputeTransform();
	}
	return localToWorldMatrix_ * Vector3::Right();
}

Vector3 Transform::GetEulerAngles() {
	if (!valid_) {
		RecomputeTransform();
	}
	return rotation_.GetEulerAngles();
}

Vector3 Transform::GetLocalEulerAngles() {
	if (!valid_) {
		RecomputeTransform();
	}
	return localRotation_.GetEulerAngles();
}

glm::mat4 Transform::GetLocalToWorldMatrix() {
	if (!valid_) {
		RecomputeTransform();
	}
}