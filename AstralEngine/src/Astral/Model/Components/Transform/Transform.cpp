#include "Common.h"
#include "Transform.h"
#include "Astral/Model/Entity.h"
#include <glm/fwd.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Astral {
	Transform::Transform(
		dvec3 init_pos,
		dquat init_rot) :
		local_position(init_pos),
		local_rotation(init_rot),
		global_position(init_pos),
		global_rotation(init_rot) {}

	void Transform::OnOwnerChange() {
		Transform& parent_tr = Owner()->Parent()->transform();
		global_position = parent_tr.global_position + local_position;
		global_rotation = parent_tr.global_rotation * local_rotation;
	}

	dvec3 Transform::Position() const {
		return local_position;
	}

	dquat Transform::Rotation() const {
		return local_rotation;
	}

	dvec3 Transform::GlobalPosition() const {
		return global_position;
	}

	dquat Transform::GlobalRotation() const {
		return global_rotation;
	}

	dvec3 Transform::Forward() const {
		return global_rotation * dvec3(0, 0, -1);
	}

	dvec3 Transform::Right() const {
		return global_rotation * dvec3(1, 0, 0);
	}

	dvec3 Transform::Up() const {
		return global_rotation * dvec3(0, 1, 0);
	}

	void Transform::LookAt(const dvec3& target) {
		dvec3 direction = glm::normalize(target - local_position);
		Rotate(glm::rotation(Forward(), direction));
	}

	void Transform::Translate(const dvec3& displacement) {
		for (Entity& descendant : Owner()->Descendants())
			descendant.transform().global_position += displacement;
	}

	void Transform::Rotate(const dquat& displacement) {
		for (Entity& descendant : Owner()->Descendants())
			descendant.transform().global_rotation *= displacement;
	}

	mat4 Transform::ModelMatrix() const {
		return glm::translate(glm::mat4(1.0f), glm::vec3(global_position)) * glm::mat4_cast(glm::quat(global_rotation));
	}
}