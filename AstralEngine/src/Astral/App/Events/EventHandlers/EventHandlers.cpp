#include "Common.h"
#include "EventHandlers.h"

namespace Astral::App {

	EventBroadcaster::SubscriptionToken::SubscriptionToken(EventBroadcaster* subject, const EventListener* subscriber) : subject(subject), subscriber(subscriber) {}

	EventBroadcaster::SubscriptionToken::~SubscriptionToken() {
		if (!subject || !subscriber)
			return;  // temporary object from move constructor is calling destructor
		subject->Unsubscribe(subscriber);
	}

	EventBroadcaster::SubscriptionToken::SubscriptionToken(SubscriptionToken&& other) noexcept : subject(other.subject), subscriber(other.subscriber) {
		other.subject = nullptr;
		other.subscriber = nullptr;
	}

	EventBroadcaster::SubscriptionToken EventBroadcaster::Subscribe(EventListener* subscriber) {
		subscribers.push_back(subscriber);
		return SubscriptionToken(this, subscriber);
	}

	EventBroadcaster::~EventBroadcaster() {
		for (EventListener* subscriber : subscribers) {
			subscriber->UnsubscribeTo(*this);
		}
	}

	void EventBroadcaster::Unsubscribe(const EventListener* subscriber) {
		std::erase(subscribers, subscriber);
	}

	bool EventBroadcaster::Broadcast(const Event& event) {
		bool consumed = false;
		for (EventListener* subscriber : subscribers) {
			consumed |= event.Dispatch(*subscriber);
			if (consumed)
				return true;
		}
		return false;
	}

	void EventListener::SubscribeTo(EventBroadcaster& subject) {
		tokens.push_back(subject.Subscribe(this));
	}

	void EventListener::UnsubscribeTo(EventBroadcaster& subject) {
		std::erase_if(tokens, [&subject](const EventBroadcaster::SubscriptionToken& token) {
			return token.subject == &subject;
			});
	}
}