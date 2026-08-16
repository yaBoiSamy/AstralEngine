#include "Common.h"
#include "Transform.h"
#include "Astral/Misc/Entity.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include <glm/fwd.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Astral::Components {

	Transform::Transform(
		dvec3 init_pos,
		dquat init_rot,
		dvec3 init_scale) :
		local_position(init_pos),
		local_rotation(init_rot),
	    local_scale(init_scale) {}

	void Transform::OnOwnerChange(Entity* prev_owner) {
		Transform& parent_tr = Owner()->Parent()->transform();
		Transform& prev_tr = prev_owner->transform();
		local_position = prev_tr.GlobalPosition() - parent_tr.GlobalPosition();
		local_rotation = glm::inverse(parent_tr.GlobalRotation()) * prev_tr.GlobalRotation();
		local_scale = prev_tr.GlobalScale() / parent_tr.GlobalScale();
	}

	dvec3 Transform::Position() const {
		return local_position;
	}

	dquat Transform::Rotation() const {
		return local_rotation;
	}

	dvec3 Transform::Scale() const {
		return local_scale;
	}

	dvec3 Transform::GlobalPosition() {
		Astral::Entity* parent = Owner()->Parent();
		if (parent) {
			Transform& parent_tr = parent->transform();
			return parent_tr.GlobalPosition() + parent_tr.GlobalRotation() * local_position;
		}
		return local_position;
	}

	dquat Transform::GlobalRotation() {
		Astral::Entity* parent = Owner()->Parent();
		if (parent) {
			Transform& parent_tr = parent->transform();
			return parent_tr.GlobalRotation() * local_rotation;
		}
		return local_rotation;
	}

	dvec3 Transform::GlobalScale() {
		Astral::Entity* parent = Owner()->Parent();
		if (parent) {
			Transform& parent_tr = parent->transform();
			return parent_tr.GlobalScale() * local_scale;
		}
		return local_scale;
	}

	dvec3 Transform::Forward() {
		return GlobalRotation() * dvec3(0, 0, -1);
	}

	dvec3 Transform::Right() {
		return GlobalRotation() * dvec3(1, 0, 0);
	}

	dvec3 Transform::Up() {
		return GlobalRotation() * dvec3(0, 1, 0);
	}

	void Transform::LookAt(const dvec3& target) {
		dvec3 direction = glm::normalize(target - local_position);
		Rotate(glm::rotation(Forward(), direction));
	}

	void Transform::Translate(const dvec3& displacement) {
		local_position += displacement;
	}

	void Transform::Rotate(const dquat& displacement) {
		local_rotation *= displacement;
	}

	void Transform::Scale(const dvec3& displacement) {
		local_scale *= displacement;
	}

	void Transform::UpdateRenderedWorldSpace() {
		Render::Renderer::ModelData modeldata = {
			ModelMatrix()
		};
		Render::Renderer::UpdateModelData(modeldata);
	}

	mat4 Transform::ModelMatrix() {
		return glm::translate(glm::mat4(1.0f), glm::vec3(GlobalPosition()))
			* glm::mat4_cast(glm::quat(GlobalRotation()))
			* glm::scale(glm::mat4(1.0f), glm::vec3(GlobalScale()));
	}
}