#pragma once

namespace Astral {
	class Entity;
}

namespace Astral::Components {

	class AComponent {
	public:
		virtual ~AComponent() = 0;

		Entity* Owner();
		void SetOwner(Entity* owner);
		
	protected:
		virtual void OnOwnerChange(Entity* prev_owner);
		Entity* owner = nullptr;
	};


	// =================================================================================================================
	// ================================================ IMPLEMENTATIONS ================================================
	// =================================================================================================================

	inline AComponent::~AComponent() = default;

	inline Entity* AComponent::Owner() { 
		return owner; 
	}

	inline void AComponent::SetOwner(Entity* owner) {
		bool ownerchange = this->owner && owner;
		Entity* prev_owner = this->owner;
		this->owner = owner; 
		if (ownerchange)
			OnOwnerChange(prev_owner);
	}

	inline void AComponent::OnOwnerChange(Entity* prev_owner) {}
}