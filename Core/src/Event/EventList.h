#pragma once
#include "Event.h"

class ENGINE_API WindowResizedEvent : public Event
{
public:
	WindowResizedEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
	EVENT_SET_TYPE(WindowResized)
	EVENT_SET_CATEGORY(EventCategory::ApplicationEvent)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizedEvent: {" << m_Width << ", " << m_Height << "}";
		return ss.str();
	}

private:
	unsigned int m_Width;
	unsigned int m_Height;
};

/*---------------------------------------------------------------------------------------------------------*/

class ENGINE_API WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}
	EVENT_SET_TYPE(WindowClose)
	EVENT_SET_CATEGORY(EventCategory::ApplicationEvent)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowCloseEvent called";
		return ss.str();
	}
};

/*---------------------------------------------------------------------------------------------------------*/

class ENGINE_API KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(unsigned int keyCode, bool isRepeat) : m_KeyCode(keyCode), m_IsRepeat(isRepeat) {}
	EVENT_SET_TYPE(KeyPressed)
	EVENT_SET_CATEGORY(EventCategory::InputEvent | EventCategory::KeyboardEvent)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: Key: " << m_KeyCode << " isRepeat: " << m_IsRepeat;
		return ss.str();
	}

	inline unsigned int GetKeyCode() { return m_KeyCode; }
	inline bool IsRepeat() { return m_IsRepeat; }

private:
	unsigned int m_KeyCode;
	bool m_IsRepeat;
};

/*---------------------------------------------------------------------------------------------------------*/

class ENGINE_API KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(unsigned int keyCode) : m_KeyCode(keyCode) {}
	EVENT_SET_TYPE(KeyReleased)
	EVENT_SET_CATEGORY(EventCategory::InputEvent | EventCategory::KeyboardEvent)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: Key: " << m_KeyCode;
		return ss.str();
	}

	inline unsigned int GetKeyCode() { return m_KeyCode; }

private:
	unsigned int m_KeyCode;
};

/*---------------------------------------------------------------------------------------------------------*/

class ENGINE_API MouseClickEvent : public Event
{
public:
	MouseClickEvent(unsigned int button) : m_Button(button) {}
	EVENT_SET_TYPE(MouseClicked)
	EVENT_SET_CATEGORY(EventCategory::InputEvent | EventCategory::MouseButtonEvent)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseClickedEvent: " << m_Button;
		return ss.str();
	}

	inline unsigned int GetButton() { return m_Button; }

private:
	unsigned int m_Button;
};

/*---------------------------------------------------------------------------------------------------------*/

class ENGINE_API MouseUnclickEvent : public Event
{
public:
	MouseUnclickEvent(unsigned int button) : m_Button(button) {}
	EVENT_SET_TYPE(MouseUnclicked)
	EVENT_SET_CATEGORY(EventCategory::InputEvent | EventCategory::MouseButtonEvent)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseUnclickEvent: " << m_Button;
		return ss.str();
	}

	inline unsigned int GetButton() { return m_Button; }

private:
	unsigned int m_Button;
};

/*---------------------------------------------------------------------------------------------------------*/

class ENGINE_API MousePositionEvent : public Event
{
public:
	MousePositionEvent(float xPosition, float yPosition) : m_PositionX(xPosition), m_PositionY(yPosition) {}
	EVENT_SET_TYPE(MousePosition)
	EVENT_SET_CATEGORY(EventCategory::InputEvent | EventCategory::MouseEvent)

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousePositionEvent: {" << m_PositionX << ", " << m_PositionY << "}";
		return ss.str();
	}

	inline float GetPositionX() { return m_PositionX; }
	inline float GetPositionY() { return m_PositionY; }

private:
	float m_PositionX;
	float m_PositionY;
};