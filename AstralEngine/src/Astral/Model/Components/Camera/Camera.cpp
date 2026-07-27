#include "Common.h"
#include "Camera.h"
#include "Astral/Model/Components/Transform/Transform.h"
#include "Astral/Rendering/Renderer/Renderer.h"
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>

namespace Astral {
	using namespace glm;
	
	Camera::Camera(
		double fov,
		double near_plane, 
		double far_plane) :
		fov(fov),
		near_plane(near_plane),
		far_plane(far_plane) {}

	void Camera::SetPerspective(double fov, double near_plane, double far_plane) {
		this->fov = fov;
		this->near_plane = near_plane;
		this->far_plane = far_plane;
	}
	
	mat4 Camera::ViewMatrix() {
		AST_CORE_ASSERT(owner, "Camera component used before being attached");
		Transform& transform = owner->transform();
		mat4 rot = glm::mat4_cast(glm::conjugate(glm::quat(transform.GlobalRotation())));
		mat4 trans = glm::translate(mat4(1.0), -glm::vec3(transform.GlobalPosition()));
		return rot * trans;
	}
	
	mat4 Camera::ProjectionMatrix() {
		int fbx, fby;
		glfwGetFramebufferSize(glfwGetCurrentContext(), &fbx, &fby);
		return glm::perspective((float)fov, (float)fbx / (float)fby, (float)near_plane, (float)far_plane);
	}

	void Camera::UpdateRenderedPOV() {
		Renderer::CameraData camdata = {
			ViewMatrix(),
			ProjectionMatrix()
		};
		Renderer::UpdateCameraData(camdata);
	}
}