#pragma once
#include "Common.h"
#include "Astral/Rendering/Backend/API.h"


namespace Astral::Render {

	using ResourceHandle = uint32_t;

	class ResourceRegistry {
	public:
		ResourceHandle AllocateHandle();
		void AssignHandle(ResourceHandle handle, Box<IResource> resource);
		IResource* ResolveHandle(ResourceHandle handle);
		void DeallocateResource(ResourceHandle handle);

	private:
		uint32_t current = 1;
		std::unordered_map<ResourceHandle, Box<IResource>> registry;
	};
}
