#pragma once
#include "Astral/Model/Component.h"
#include <glm/gtc/quaternion.hpp>


namespace Astral {
	using namespace glm;

	class Transform : public AComponent {
	public:
		Transform(dvec3 init_pos = glm::dvec3(), dquat init_rot = glm::dquat(glm::dvec3()));

		virtual void OnOwnerChange() override;

		dvec3 Position() const;
		dquat Rotation() const;

		dvec3 GlobalPosition() const;
		dquat GlobalRotation() const;

		dvec3 Forward() const;
		dvec3 Right() const;
		dvec3 Up() const;

		void LookAt(const dvec3& target);

		void Translate(const dvec3& displacement);
		void Rotate(const dquat& displacement);

		mat4 ModelMatrix() const;

		dvec3 local_position;
		dquat local_rotation;

		dvec3 global_position;
		dquat global_rotation;
	};
	
}

