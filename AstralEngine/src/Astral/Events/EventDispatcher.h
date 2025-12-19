#pragma once
#include <Common.h>
#include <concepts>

#include "Astral/Events/Event.h"


namespace Astral {
	template<typename T>
	concept EventType = std::is_base_of_v<Event, T>;

	template<EventType EventT>
	class EventDispatcher {
		using EventCallback = std::function<void(EventT const&)>;

	public:
		static void Subscribe(EventCallback callback) {
			subscribers.push_back(callback);
		}

		static void Dispatch(EventT const& event) {
			for (EventCallback subscriber : subscribers) {
				subscriber(event);
			}
		}

	private:
		inline static std::vector<EventCallback> subscribers{};
	};
}

