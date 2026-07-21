#include "Common.h"
#include "Transform.h"
#include <glm/fwd.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Astral {
	Transform::Transform(
		dvec3 init_pos,
		dquat init_rot) :
		position(init_pos),
		rotation(init_rot) {}

	dvec3 Transform::Forward() const {
		return rotation * dvec3(0, 0, -1);
	}

	dvec3 Transform::Right() const {
		return rotation * dvec3(1, 0, 0);
	}

	dvec3 Transform::Up() const {
		return rotation * dvec3(0, 1, 0);
	}

	void Transform::LookAt(const dvec3& target) {
		dvec3 direction = glm::normalize(target - position);
		rotation = glm::rotation(dvec3(0, 0, -1), direction);
	}

	void Transform::Translate(const dvec3& displacement) {
		position += displacement;
	}

	void Transform::Rotate(const dquat& displacement) {
		rotation *= displacement;
	}
}