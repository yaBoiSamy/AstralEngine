#pragma once
#include "Astral/Components/Entity.h"
#include <glm/glm.hpp>


namespace Astral {
	using namespace glm;
	class Camera : AEntity {
	public:
		Camera(double fov, double aspect_ratio, double near_plane, double far_plane);

		void SetPerspective(double fov, double aspect_ratio, double near_plane, double far_plane);

		mat4 ViewMatrix();
		mat4 ProjectionMatrix();

	private:
		double fov;
		double aspect_ratio;
		double near_plane;
		double far_plane;
	};
}

