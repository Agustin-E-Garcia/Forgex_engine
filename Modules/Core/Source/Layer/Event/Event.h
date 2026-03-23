#pragma once
#include <functional>
#include <map>
#include <sstream>
#include <cstdint>

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

namespace Forgex::Core::Layer::Event
{
	enum EventType : uint8_t
	{
		WindowResized, WindowFocusChanged,
		KeyPressed, KeyReleased, CharInput,
		MouseClicked, MousePosition, MouseWheel, MouseLock
	};

	enum EventCategory
	{
		None = 0,
		ApplicationEvent = (1 << 0),
		InputEvent = (1 << 1),
		KeyboardEvent = (1 << 2),
		MouseEvent = (1 << 3),
		MouseButtonEvent = (1 << 4),
		LayerEvent = (1 << 5),
	};

#define EVENT_SET_TYPE(x) 	static EventType GetStaticType() { return EventType::x; }\
							inline EventType GetEventType() const override { return GetStaticType(); }\
							inline bool IsEventType(EventType type) const override { return type == GetStaticType(); }

#define EVENT_SET_CATEGORY(x) virtual int GetCategoryFlags() const override { return EventCategory::x; }

	// Event base class
	class Event
	{
		friend class EventDispatcher;
	public:
		bool m_Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual bool IsEventType(EventType type) const = 0;
		virtual std::string ToString() const = 0;

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
	};

	// Event Dispatcher
	class EventDispatcher
	{
		template<typename T>
		using HandleEventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		~EventDispatcher() {}

		template<typename T>
		bool Dispatch(HandleEventFn<T> func)
		{
			if (m_Event.IsEventType(T::GetStaticType()))
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
