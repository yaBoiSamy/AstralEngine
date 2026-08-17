#pragma once
#include <glm/gtc/quaternion.hpp>
#include "Astral/Components/Component.h"
#include "Astral/Rendering/Command/Command.h"


namespace Astral::Components {
	using namespace glm;
	using namespace Astral;

	class Transform : public AComponent {
	public:
		Transform(
			dvec3 init_pos = glm::dvec3(), 
			dquat init_rot = glm::dquat(glm::dvec3()),
			dvec3 init_scale = glm::dvec3(1.0f));

		virtual void OnOwnerChange(Entity* prev_owner) override;

		dvec3 Position() const;
		dquat Rotation() const;
		dvec3 Scale() const;

		dvec3 GlobalPosition();
		dquat GlobalRotation();
		dvec3 GlobalScale();

		dvec3 Forward();
		dvec3 Right();
		dvec3 Up();

		void LookAt(const dvec3& target);

		void Translate(const dvec3& displacement);
		void Rotate(const dquat& displacement);
		void Scale(const dvec3& displacement);

		Render::ModelData RenderedWorldSpace();

		dvec3 local_position;
		dquat local_rotation;
		dvec3 local_scale;

	private:
		mat4 ModelMatrix();
	};
	
}

