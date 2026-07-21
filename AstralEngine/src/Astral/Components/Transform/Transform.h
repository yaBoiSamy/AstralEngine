#pragma once
#include "Astral/Components/Component.h"
#include <glm/gtc/quaternion.hpp>


namespace Astral {
	using namespace glm;

	class Transform : public AComponent {
	public:
		Transform(dvec3 init_pos = glm::dvec3(), dquat init_rot = glm::dquat(glm::dvec3()));

		dvec3 Forward() const;
		dvec3 Right() const;
		dvec3 Up() const;

		void LookAt(const dvec3& target);

		void Translate(const dvec3& displacement);
		void Rotate(const dquat& displacement);

		dvec3 position;
		dquat rotation;
	};
	
}

