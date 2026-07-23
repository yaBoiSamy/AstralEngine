#pragma once

namespace Astral {
	class Entity;

	class AComponent {
	public:
		virtual ~AComponent() = 0;

		Entity* Owner();
		void SetOwner(Entity* owner);
		
	protected:
		virtual void OnOwnerChange();
		Entity* owner;
	};

	inline AComponent::~AComponent() = default;

	inline Entity* AComponent::Owner() { 
		return owner; 
	}

	inline void AComponent::SetOwner(Entity* owner) { 
		this->owner = owner; 
		OnOwnerChange();
	}

	inline void AComponent::OnOwnerChange() {}
}