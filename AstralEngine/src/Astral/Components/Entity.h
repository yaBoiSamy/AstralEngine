#pragma once
#include "Common.h"
#include "Astral/Components/Component.h"
#include <stack>


namespace Astral {
	class AEntity {
	public:
		class ChildrenIterator {
		public:
			ChildrenIterator(
				std::unordered_map<std::string, ptr<AEntity>>::iterator children_start,
				std::unordered_map<std::string, ptr<AEntity>>::iterator children_end);

			bool Finished() const;

			AEntity& operator*();

			ChildrenIterator& operator++();
			ChildrenIterator operator++(int);

			bool operator==(const ChildrenIterator& other) const;
			bool operator!=(const ChildrenIterator& other) const;

		private:
			std::unordered_map<std::string, ptr<AEntity>>::iterator child_it;
			const std::unordered_map<std::string, ptr<AEntity>>::iterator children_end;
		};


		class ChildrenRange {
		public:
			ChildrenRange(AEntity& owner);
			ChildrenIterator begin();
			ChildrenIterator end();
		private:
			AEntity& owner;
		};


		class DescendantIterator {
		public:
			DescendantIterator() = default;
			DescendantIterator(ChildrenIterator root_children);

			bool Finished() const;

			AEntity& operator*();

			DescendantIterator& operator++();
			DescendantIterator operator++(int);

			bool operator==(const DescendantIterator& other) const;
			bool operator!=(const DescendantIterator& other) const;

		private:
			std::stack<ChildrenIterator> descendant_its;

			void VisitDescendant(ChildrenIterator descendant_children_it);
		};


		class DescendantRange {
		public:
			DescendantRange(AEntity& owner);
			DescendantIterator begin();
			DescendantIterator end();
		private:
			AEntity& owner;
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
			ComponentRange(AEntity& owner);
			ComponentIterator<ComponentT> begin();
			ComponentIterator<ComponentT> end();
		private:
			AEntity& owner;
		};

	
	// Back into AEntity, nested types done
	public:
		AEntity(std::string name = "Entity");

		AEntity* Parent();
		AEntity* Child(std::string child_name);

		void AddChild(ptr<AEntity> child);
		void RemoveChild(std::string child_name);
		void AddComponent(ptr<AComponent> component);

		template <std::derived_from<AComponent> ComponentT>
		ComponentT* GetComponent();


		ChildrenRange Children();
		DescendantRange Descendants();
		template <std::derived_from<AComponent> ComponentT>
		ComponentRange<ComponentT> Components();

	private:
		AEntity* parent;
		std::string name;
		std::unordered_map<std::string, ptr<AEntity>> children;
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

	AEntity::ChildrenIterator::ChildrenIterator(
		std::unordered_map<std::string, ptr<AEntity>>::iterator children_start,
		std::unordered_map<std::string, ptr<AEntity>>::iterator children_end) :
		child_it(children_start),
		children_end(children_end) {}

	bool AEntity::ChildrenIterator::Finished() const {
		return child_it == children_end;
	}

	AEntity& AEntity::ChildrenIterator::operator*() {
		return *child_it->second;
	}

	AEntity::ChildrenIterator& AEntity::ChildrenIterator::operator++() {
		++child_it;
		return *this;
	}

	AEntity::ChildrenIterator AEntity::ChildrenIterator::operator++(int) {
		AEntity::ChildrenIterator copy = *this;
		++(*this);
		return copy;
	}

	bool AEntity::ChildrenIterator::operator==(const ChildrenIterator& other) const {
		return child_it == other.child_it;
	}

	bool AEntity::ChildrenIterator::operator!=(const ChildrenIterator& other) const {
		return !(*this == other);
	}


	// =================================================================================================================
	// ============================================= ChildrenRange ====================================================
	// =================================================================================================================

	AEntity::ChildrenRange::ChildrenRange(AEntity& owner) :
		owner(owner) {}

	AEntity::ChildrenIterator AEntity::ChildrenRange::begin() {
		return owner.BeginChildren();
	}

	AEntity::ChildrenIterator AEntity::ChildrenRange::end() {
		return owner.EndChildren();
	}


	// =================================================================================================================
	// =========================================== DescendantIterator =================================================
	// =================================================================================================================

	AEntity::DescendantIterator::DescendantIterator(ChildrenIterator root_children) {
		VisitDescendant(root_children);
	}

	bool AEntity::DescendantIterator::Finished() const {
		return descendant_its.empty();
	}

	AEntity& AEntity::DescendantIterator::operator*() {
		return *descendant_its.top();
	}

	AEntity::DescendantIterator& AEntity::DescendantIterator::operator++() {
		assert(!descendant_its.empty());

		if (!descendant_its.top().Finished()) {
			AEntity& visited_descendant = *descendant_its.top();
			++descendant_its.top();
			VisitDescendant(visited_descendant.BeginChildren());
			return *this;
		}

		descendant_its.pop();
		return ++ * this;
	}

	AEntity::DescendantIterator AEntity::DescendantIterator::operator++(int) {
		AEntity::DescendantIterator copy = *this;
		++(*this);
		return copy;
	}

	bool AEntity::DescendantIterator::operator==(const DescendantIterator& other) const {
		if (Finished() || other.Finished())
			return Finished() && other.Finished();

		return descendant_its.top() == other.descendant_its.top();
	}

	bool AEntity::DescendantIterator::operator!=(const DescendantIterator& other) const {
		return !(*this == other);
	}

	void AEntity::DescendantIterator::VisitDescendant(ChildrenIterator descendant_children_it) {
		descendant_its.push(descendant_children_it);

		if (descendant_its.top().Finished())
			descendant_its.pop();
	}


	// =================================================================================================================
	// ============================================= DescendantRange ==================================================
	// =================================================================================================================

	AEntity::DescendantRange::DescendantRange(AEntity& owner) :
		owner(owner) {}

	AEntity::DescendantIterator AEntity::DescendantRange::begin() {
		return owner.BeginDescendants();
	}

	AEntity::DescendantIterator AEntity::DescendantRange::end() {
		return owner.EndDescendants();
	}


	// =================================================================================================================
	// =========================================== ComponentIterator ==================================================
	// =================================================================================================================

	template <std::derived_from<AComponent> ComponentT>
	AEntity::ComponentIterator<ComponentT>::ComponentIterator(
		std::vector<ptr<AComponent>>::iterator components_begin,
		std::vector<ptr<AComponent>>::iterator components_end) :
		component_it(components_begin),
		components_end(components_end) {
		Filter();
	}

	template <std::derived_from<AComponent> ComponentT>
	bool AEntity::ComponentIterator<ComponentT>::Finished() const {
		return component_it == components_end;
	}

	template <std::derived_from<AComponent> ComponentT>
	ComponentT& AEntity::ComponentIterator<ComponentT>::operator*() {
		return dynamic_cast<ComponentT&>(**component_it);
	}

	template <std::derived_from<AComponent> ComponentT>
	typename AEntity::template ComponentIterator<ComponentT>&
		AEntity::ComponentIterator<ComponentT>::operator++() {
		++component_it;
		Filter();
		return *this;
	}

	template <std::derived_from<AComponent> ComponentT>
	typename AEntity::template ComponentIterator<ComponentT>
		AEntity::ComponentIterator<ComponentT>::operator++(int) {
		auto copy = *this;
		++(*this);
		return copy;
	}

	template <std::derived_from<AComponent> ComponentT>
	bool AEntity::ComponentIterator<ComponentT>::operator==(const ComponentIterator& other) const {
		return component_it == other.component_it;
	}

	template <std::derived_from<AComponent> ComponentT>
	bool AEntity::ComponentIterator<ComponentT>::operator!=(const ComponentIterator& other) const {
		return !(*this == other);
	}

	template <std::derived_from<AComponent> ComponentT>
	void AEntity::ComponentIterator<ComponentT>::Filter() {
		while (!Finished() && dynamic_cast<ComponentT*>(component_it->get()) == nullptr) {
			++component_it;
		}
	}


	// =================================================================================================================
	// ============================================= ComponentRange ===================================================
	// =================================================================================================================

	template <std::derived_from<AComponent> ComponentT>
	AEntity::ComponentRange<ComponentT>::ComponentRange(AEntity& owner) :
		owner(owner) {}

	template <std::derived_from<AComponent> ComponentT>
	typename AEntity::template ComponentIterator<ComponentT>
		AEntity::ComponentRange<ComponentT>::begin() {
		return owner.BeginComponents<ComponentT>();
	}

	template <std::derived_from<AComponent> ComponentT>
	typename AEntity::template ComponentIterator<ComponentT>
		AEntity::ComponentRange<ComponentT>::end() {
		return owner.EndComponents<ComponentT>();
	}


	// =================================================================================================================
	// ================================================= AEntity ======================================================
	// =================================================================================================================

	AEntity::AEntity(std::string name) :
		parent(nullptr),
		name(name) {}

	AEntity* AEntity::Parent() {
		return parent;
	}

	AEntity* AEntity::Child(std::string name) {
		auto it = children.find(name);

		if (it == children.end())
			return nullptr;

		return it->second.get();
	}

	void AEntity::AddChild(ptr<AEntity> child) {
		if (CheckNameCollision(child->name)) {
			AST_CORE_ERROR("Cannot make entity with name {0}, since a sibling entity has the same name. Aborting the operation.", child->name);
			return;
		}

		child->parent = this;
		children[child->name] = std::move(child);
	}

	void AEntity::RemoveChild(std::string name) {
		children.erase(name);
	}

	void AEntity::AddComponent(ptr<AComponent> component) {
		components.push_back(std::move(component));
	}

	template <std::derived_from<AComponent> ComponentT>
	ComponentT* AEntity::GetComponent() {
		for (auto& component : Components<ComponentT>())
			return &component;

		return nullptr;
	}

	AEntity::ChildrenRange AEntity::Children() {
		return ChildrenRange(*this);
	}

	AEntity::DescendantRange AEntity::Descendants() {
		return DescendantRange(*this);
	}

	template <std::derived_from<AComponent> ComponentT>
	AEntity::ComponentRange<ComponentT> AEntity::Components() {
		return ComponentRange<ComponentT>(*this);
	}

	bool AEntity::CheckNameCollision(std::string name) {
		return children.contains(name);
	}

	std::string AEntity::GenerateDefaultName() {
		uint32_t attempts = 0;
		std::string name = "Entity";

		while (CheckNameCollision(name)) {
			name = "Entity (" + std::to_string(++attempts) + ")";
		}

		return name;
	}

	AEntity::ChildrenIterator AEntity::BeginChildren() {
		return ChildrenIterator(children.begin(), children.end());
	}

	AEntity::ChildrenIterator AEntity::EndChildren() {
		return ChildrenIterator(children.end(), children.end());
	}

	AEntity::DescendantIterator AEntity::BeginDescendants() {
		return DescendantIterator(BeginChildren());
	}

	AEntity::DescendantIterator AEntity::EndDescendants() {
		return DescendantIterator();
	}

	template <std::derived_from<AComponent> ComponentT>
	AEntity::ComponentIterator<ComponentT> AEntity::BeginComponents() {
		return ComponentIterator<ComponentT>(components.begin(), components.end());
	}

	template <std::derived_from<AComponent> ComponentT>
	AEntity::ComponentIterator<ComponentT> AEntity::EndComponents() {
		return ComponentIterator<ComponentT>(components.end(), components.end());
	}
}