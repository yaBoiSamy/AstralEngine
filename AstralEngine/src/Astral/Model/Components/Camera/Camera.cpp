#include "Common.h"
#include "Camera.h"
#include "Astral/Model/Components/Transform/Transform.h"
#include <glm/gtc/quaternion.hpp>

namespace Astral {
	using namespace glm;
	
	Camera::Camera(
		double fov, 
		double aspect_ratio, 
		double near_plane, 
		double far_plane) :
		fov(fov),
		aspect_ratio(aspect_ratio),
		near_plane(near_plane),
		far_plane(far_plane) {
	}

	void Camera::SetPerspective(double fov, double aspect_ratio, double near_plane, double far_plane) {
		this->fov = fov;
		this->aspect_ratio = aspect_ratio;
		this->near_plane = near_plane;
		this->far_plane = far_plane;
	}
	
	mat4 Camera::ViewMatrix() {
		Transform& transform = owner->transform();
		mat4 rot = glm::mat4_cast(glm::conjugate(glm::quat(transform.Rotation())));
		mat4 trans = glm::translate(mat4(1.0), -glm::vec3(transform.Position()));
		return glm::inverse(trans * rot);
	}
	
	mat4 Camera::ProjectionMatrix() {
		return glm::perspective((float)fov, (float)aspect_ratio, (float)near_plane, (float)far_plane);
	}
}