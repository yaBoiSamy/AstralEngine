#pragma once
#include "Common.h"
#include "Component.h"
#include "Components/Transform/Transform.h"
#include <stack>


namespace Astral {

	class Entity {
	public:
		class ChildrenIterator {
		public:
			ChildrenIterator(
				std::unordered_map<std::string, ptr<Entity>>::iterator children_start,
				std::unordered_map<std::string, ptr<Entity>>::iterator children_end);

			bool Finished() const;

			Entity& operator*();

			ChildrenIterator& operator++();
			ChildrenIterator operator++(int);

			bool operator==(const ChildrenIterator& other) const;
			bool operator!=(const ChildrenIterator& other) const;

		private:
			std::unordered_map<std::string, ptr<Entity>>::iterator child_it;
			const std::unordered_map<std::string, ptr<Entity>>::iterator children_end;
		};


		class ChildrenRange {
		public:
			ChildrenRange(Entity& owner);
			ChildrenIterator begin();
			ChildrenIterator end();
		private:
			Entity& owner;
		};


		class DescendantIterator {
		public:
			DescendantIterator() = default;
			DescendantIterator(ChildrenIterator root_children);

			bool Finished() const;

			Entity& operator*();

			DescendantIterator& operator++();
			DescendantIterator operator++(int);

			bool operator==(const DescendantIterator& other) const;
			bool operator!=(const DescendantIterator& other) const;

		private:
			std::stack<ChildrenIterator> descendant_its;

			void Normalize();
		};


		class DescendantRange {
		public:
			DescendantRange(Entity& owner);
			DescendantIterator begin();
			DescendantIterator end();
		private:
			Entity& owner;
		};


		template <std::derived_from<AComponent> ComponentT>
		class ComponentIterator {
		public:
			ComponentIterator(
				std::vector<ptr<AComponent>>::iterator components_begin,
				std::vector<ptr<AComponent>>::iterator components_end);

			bool Finished() const;

			ComponentT& operator*();

			ComponentIterator& operator++();
			ComponentIterator operator++(int);

			bool operator==(const ComponentIterator& other) const;
			bool operator!=(const ComponentIterator& other) const;

		private:
			std::vector<ptr<AComponent>>::iterator component_it;
			const std::vector<ptr<AComponent>>::iterator components_end;

			void Filter();
		};


		template <std::derived_from<AComponent> ComponentT>
		class ComponentRange {
		public:
			ComponentRange(Entity& owner);
			ComponentIterator<ComponentT> begin();
			ComponentIterator<ComponentT> end();
		private:
			Entity& owner;
		};

	
	// Back into AEntity, nested types done
	public:
		Entity(std::string name = "Entity");

		Entity* Parent();
		Entity* Child(std::string child_name);

		void AddChild(ptr<Entity> child);
		void RemoveChild(std::string child_name);
		void AddComponent(ptr<AComponent> component);

		template <std::derived_from<AComponent> ComponentT>
		ComponentT* GetComponent();
		Transform& transform();


		ChildrenRange Children();
		DescendantRange Descendants();
		template <std::derived_from<AComponent> ComponentT>
		ComponentRange<ComponentT> Components();

	private:
		Entity* parent;
		std::string name;
		std::unordered_map<std::string, ptr<Entity>> children;
		std::vector<ptr<AComponent>> components;

		bool CheckNameCollision(std::string name);
		std::string GenerateDefaultName();

		ChildrenIterator BeginChildren();
		ChildrenIterator EndChildren();

		DescendantIterator BeginDescendants();
		DescendantIterator EndDescendants();

		template <std::derived_from<AComponent> ComponentT>
		ComponentIterator<ComponentT> BeginComponents();
		template <std::derived_from<AComponent> ComponentT>
		ComponentIterator<ComponentT> EndComponents();
	};




// =================================================================================================================
// ================================================ IMPLEMENTATIONS ================================================
// =================================================================================================================

	// =================================================================================================================
	// =========================================== ChildrenIterator ===================================================
	// =================================================================================================================

	inline Entity::ChildrenIterator::ChildrenIterator(
		std::unordered_map<std::string, ptr<Entity>>::iterator children_start,
		std::unordered_map<std::string, ptr<Entity>>::iterator children_end) :
		child_it(children_start),
		children_end(children_end) {}

	inline bool Entity::ChildrenIterator::Finished() const {
		return child_it == children_end;
	}

	inline Entity& Entity::ChildrenIterator::operator*() {
		return *child_it->second;
	}

	inline Entity::ChildrenIterator& Entity::ChildrenIterator::operator++() {
		++child_it;
		return *this;
	}

	inline Entity::ChildrenIterator Entity::ChildrenIterator::operator++(int) {
		Entity::ChildrenIterator copy = *this;
		++(*this);
		return copy;
	}

	inline bool Entity::ChildrenIterator::operator==(const ChildrenIterator& other) const {
		return child_it == other.child_it;
	}

	inline bool Entity::ChildrenIterator::operator!=(const ChildrenIterator& other) const {
		return !(*this == other);
	}


	// =================================================================================================================
	// ============================================= ChildrenRange ====================================================
	// =================================================================================================================

	inline Entity::ChildrenRange::ChildrenRange(Entity& owner) :
		owner(owner) {}

	inline Entity::ChildrenIterator Entity::ChildrenRange::begin() {
		return owner.BeginChildren();
	}

	inline Entity::ChildrenIterator Entity::ChildrenRange::end() {
		return owner.EndChildren();
	}


	// =================================================================================================================
	// =========================================== DescendantIterator =================================================
	// =================================================================================================================

	inline Entity::DescendantIterator::DescendantIterator(ChildrenIterator root_children) {
		descendant_its.push(root_children);
		Normalize();
	}

	inline bool Entity::DescendantIterator::Finished() const {
		return descendant_its.empty();
	}

	inline Entity& Entity::DescendantIterator::operator*() {
		return *descendant_its.top();
	}

	inline Entity::DescendantIterator& Entity::DescendantIterator::operator++() {
		assert(!descendant_its.empty());

		Entity& visited_descendant = *descendant_its.top();
		++descendant_its.top();
		descendant_its.push(visited_descendant.BeginChildren());
		Normalize();
		return *this;
	}

	inline Entity::DescendantIterator Entity::DescendantIterator::operator++(int) {
		Entity::DescendantIterator copy = *this;
		++(*this);
		return copy;
	}

	inline bool Entity::DescendantIterator::operator==(const DescendantIterator& other) const {
		if (Finished() || other.Finished())
			return Finished() && other.Finished();

		return descendant_its.top() == other.descendant_its.top();
	}

	inline bool Entity::DescendantIterator::operator!=(const DescendantIterator& other) const {
		return !(*this == other);
	}

	inline void Entity::DescendantIterator::Normalize() {
		while (!Finished() && descendant_its.top().Finished())
			descendant_its.pop();
	}


	// =================================================================================================================
	// ============================================= DescendantRange ==================================================
	// =================================================================================================================

	inline Entity::DescendantRange::DescendantRange(Entity& owner) :
		owner(owner) {}

	inline Entity::DescendantIterator Entity::DescendantRange::begin() {
		return owner.BeginDescendants();
	}

	inline Entity::DescendantIterator Entity::DescendantRange::end() {
		return owner.EndDescendants();
	}


	// =================================================================================================================
	// =========================================== ComponentIterator ==================================================
	// =================================================================================================================

	template <std::derived_from<AComponent> ComponentT>
	inline Entity::ComponentIterator<ComponentT>::ComponentIterator(
		std::vector<ptr<AComponent>>::iterator components_begin,
		std::vector<ptr<AComponent>>::iterator components_end) :
		component_it(components_begin),
		components_end(components_end) {
		Filter();
	}

	template <std::derived_from<AComponent> ComponentT>
	inline bool Entity::ComponentIterator<ComponentT>::Finished() const {
		return component_it == components_end;
	}

	template <std::derived_from<AComponent> ComponentT>
	inline ComponentT& Entity::ComponentIterator<ComponentT>::operator*() {
		return dynamic_cast<ComponentT&>(**component_it);
	}

	template <std::derived_from<AComponent> ComponentT>
	inline typename Entity::template ComponentIterator<ComponentT>&
		Entity::ComponentIterator<ComponentT>::operator++() {
		++component_it;
		Filter();
		return *this;
	}

	template <std::derived_from<AComponent> ComponentT>
	inline typename Entity::template ComponentIterator<ComponentT>
		Entity::ComponentIterator<ComponentT>::operator++(int) {
		auto copy = *this;
		++(*this);
		return copy;
	}

	template <std::derived_from<AComponent> ComponentT>
	inline bool Entity::ComponentIterator<ComponentT>::operator==(const ComponentIterator& other) const {
		return component_it == other.component_it;
	}

	template <std::derived_from<AComponent> ComponentT>
	inline bool Entity::ComponentIterator<ComponentT>::operator!=(const ComponentIterator& other) const {
		return !(*this == other);
	}

	template <std::derived_from<AComponent> ComponentT>
	inline void Entity::ComponentIterator<ComponentT>::Filter() {
		while (!Finished() && dynamic_cast<ComponentT*>(component_it->get()) == nullptr) {
			++component_it;
		}
	}


	// =================================================================================================================
	// ============================================= ComponentRange ===================================================
	// =================================================================================================================

	template <std::derived_from<AComponent> ComponentT>
	inline Entity::ComponentRange<ComponentT>::ComponentRange(Entity& owner) :
		owner(owner) {}

	template <std::derived_from<AComponent> ComponentT>
	inline typename Entity::template ComponentIterator<ComponentT>
		Entity::ComponentRange<ComponentT>::begin() {
		return owner.BeginComponents<ComponentT>();
	}

	template <std::derived_from<AComponent> ComponentT>
	inline typename Entity::template ComponentIterator<ComponentT>
		Entity::ComponentRange<ComponentT>::end() {
		return owner.EndComponents<ComponentT>();
	}


	// =================================================================================================================
	// ================================================= AEntity ======================================================
	// =================================================================================================================

	inline Entity::Entity(std::string name) :
		parent(nullptr),
		name(name) {
		components.push_back(std::make_unique<Transform>());
	}

	inline Entity* Entity::Parent() {
		return parent;
	}

	inline Entity* Entity::Child(std::string name) {
		auto it = children.find(name);

		if (it == children.end())
			return nullptr;

		return it->second.get();
	}

	inline void Entity::AddChild(ptr<Entity> child) {
		if (CheckNameCollision(child->name)) {
			AST_CORE_ERROR("Cannot make entity with name {0}, since a sibling entity has the same name. Aborting the operation.", child->name);
			return;
		}

		child->parent = this;
		children[child->name] = std::move(child);
	}

	inline void Entity::RemoveChild(std::string name) {
		children.erase(name);
	}

	inline void Entity::AddComponent(ptr<AComponent> component) {
		component->SetOwner(this);
		components.push_back(std::move(component));
	}

	template <std::derived_from<AComponent> ComponentT>
	inline ComponentT* Entity::GetComponent() {
		for (auto& component : Components<ComponentT>())
			return &component;

		return nullptr;
	}

	inline Transform& Entity::transform() {
		return *GetComponent<Transform>();
	}

	inline Entity::ChildrenRange Entity::Children() {
		return ChildrenRange(*this);
	}

	inline Entity::DescendantRange Entity::Descendants() {
		return DescendantRange(*this);
	}

	template <std::derived_from<AComponent> ComponentT>
	inline Entity::ComponentRange<ComponentT> Entity::Components() {
		return ComponentRange<ComponentT>(*this);
	}

	inline bool Entity::CheckNameCollision(std::string name) {
		return children.contains(name);
	}

	inline std::string Entity::GenerateDefaultName() {
		uint32_t attempts = 0;
		std::string name = "Entity";

		while (CheckNameCollision(name)) {
			name = "Entity (" + std::to_string(++attempts) + ")";
		}

		return name;
	}

	inline Entity::ChildrenIterator Entity::BeginChildren() {
		return ChildrenIterator(children.begin(), children.end());
	}

	inline Entity::ChildrenIterator Entity::EndChildren() {
		return ChildrenIterator(children.end(), children.end());
	}

	inline Entity::DescendantIterator Entity::BeginDescendants() {
		return DescendantIterator(BeginChildren());
	}

	inline Entity::DescendantIterator Entity::EndDescendants() {
		return DescendantIterator();
	}

	template <std::derived_from<AComponent> ComponentT>
	inline Entity::ComponentIterator<ComponentT> Entity::BeginComponents() {
		return ComponentIterator<ComponentT>(components.begin(), components.end());
	}

	template <std::derived_from<AComponent> ComponentT>
	inline Entity::ComponentIterator<ComponentT> Entity::EndComponents() {
		return ComponentIterator<ComponentT>(components.end(), components.end());
	}
}