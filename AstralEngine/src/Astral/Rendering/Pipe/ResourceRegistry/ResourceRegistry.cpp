#include "Common.h"
#include "ResourceRegistry.h"


namespace Astral::Render {

	ResourceHandle ResourceRegistry::AllocateHandle() {
		return static_cast<ResourceHandle>(current++);
	}

	void ResourceRegistry::AssignHandle(ResourceHandle handle, Box<IResource> resource) {
		registry.emplace(handle, std::move(resource));
	}

	IResource* ResourceRegistry::ResolveHandle(ResourceHandle handle) {
		AST_CORE_ASSERT(registry.contains(handle), "Unable to resolve mapping, handle {0} has not been assigned yet", static_cast<uint32_t>(handle));
		return registry.at(handle).get();
	}

	void ResourceRegistry::DeallocateResource(ResourceHandle handle) {
		AST_CORE_ASSERT(registry.contains(handle), "Unable to resolve mapping, handle {0} has not been assigned yet", static_cast<uint32_t>(handle));
		registry.erase(handle);
	}
}
