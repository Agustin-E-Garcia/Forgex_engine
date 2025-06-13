#pragma once
#include "Event.h"

namespace Forgex::Core 
{
	class CORE_API WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
		EVENT_SET_TYPE(WindowResized)
		EVENT_SET_CATEGORY(ApplicationEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: {" << m_Width << ", " << m_Height << "}";
			return ss.str();
		}

		unsigned int GetWidth() { return m_Width; }
		unsigned int GetHeight() { return m_Height; }

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		EVENT_SET_TYPE(WindowClose)
		EVENT_SET_CATEGORY(ApplicationEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent called";
			return ss.str();
		}
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API WindowFocusChangedEvent : public Event
	{
	public:
		WindowFocusChangedEvent(bool isFocused) : m_Focus(isFocused) {}
		EVENT_SET_TYPE(WindowFocusChanged)
		EVENT_SET_CATEGORY(ApplicationEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusChangedEvent called";
			return ss.str();
		}

		inline bool IsFocused() { return m_Focus; }

	private:
		bool m_Focus;
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(unsigned int keyCode, bool isRepeat, bool isPressed) : m_KeyCode(keyCode), m_IsRepeat(isRepeat), m_IsPressed(isPressed) {}
		EVENT_SET_TYPE(KeyPressed)
		EVENT_SET_CATEGORY(InputEvent | KeyboardEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: Key: " << m_KeyCode << " isRepeat: " << m_IsRepeat << " isPressed: " << m_IsPressed;
			return ss.str();
		}

		inline unsigned int GetKeyCode() { return m_KeyCode; }
		inline bool IsRepeat() { return m_IsRepeat; }
		inline bool IsPressed() { return m_IsPressed; }

	private:
		unsigned int m_KeyCode;
		bool m_IsRepeat;
		bool m_IsPressed;
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API CharInputEvent : public Event
	{
	public:
		CharInputEvent(unsigned int key) : m_Key(key) {}
		EVENT_SET_TYPE(CharInput)
		EVENT_SET_CATEGORY(InputEvent | KeyboardEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: Key: " << m_Key;
			return ss.str();
		}

		inline unsigned int GetKeyCode() { return m_Key; }

	private:
		unsigned int m_Key;
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(unsigned int keyCode) : m_KeyCode(keyCode) {}
		EVENT_SET_TYPE(KeyReleased)
		EVENT_SET_CATEGORY(InputEvent | KeyboardEvent)

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

	class CORE_API MouseClickEvent : public Event
	{
	public:
		MouseClickEvent(unsigned int button, bool isPressed) : m_Button(button), m_IsPressed(isPressed) {}
		EVENT_SET_TYPE(MouseClicked)
		EVENT_SET_CATEGORY(InputEvent | MouseButtonEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseClickedEvent: " << m_Button << " isPressed: " << m_IsPressed;
			return ss.str();
		}

		inline unsigned int GetButton() { return m_Button; }
		inline bool IsPressed() { return m_IsPressed; }

	private:
		unsigned int m_Button;
		bool m_IsPressed;
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API MouseUnclickEvent : public Event
	{
	public:
		MouseUnclickEvent(unsigned int button) : m_Button(button) {}
		EVENT_SET_TYPE(MouseUnclicked)
		EVENT_SET_CATEGORY(InputEvent | MouseButtonEvent)

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

	class CORE_API MouseWheelScrollEvent : public Event
	{
	public:
		MouseWheelScrollEvent(double x, double y) : m_XOffset(x), m_YOffset(y) {};
		EVENT_SET_TYPE(mouseWheel)
		EVENT_SET_CATEGORY(InputEvent | MouseEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseWheelScrollEvent: [" << m_XOffset << "], [" << m_YOffset << "]";
			return ss.str();
		}

		inline double GetXOffset() { return m_XOffset; }
		inline double GetYOffset() { return m_YOffset; }

	private:
		double m_XOffset;
		double m_YOffset;
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API MousePositionEvent : public Event
	{
	public:
		MousePositionEvent(double xPosition, double yPosition) : m_PositionX(xPosition), m_PositionY(yPosition) {}
		EVENT_SET_TYPE(MousePosition)
		EVENT_SET_CATEGORY(InputEvent | MouseEvent)

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePositionEvent: [" << m_PositionX << "], [" << m_PositionY << "]";
			return ss.str();
		}

		inline double GetPositionX() { return m_PositionX; }
		inline double GetPositionY() { return m_PositionY; }

	private:
		double m_PositionX;
		double m_PositionY;
	};

	/*---------------------------------------------------------------------------------------------------------*/

	class CORE_API ViewportResizeEvent : public Event
	{
	public:
		ViewportResizeEvent(float width, float height) : m_width(width), m_height(height) {}
		EVENT_SET_TYPE(ViewportResize)
		EVENT_SET_CATEGORY(LayerEvent)

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "ViewportResizeEvent: [" << m_width << "], [" << m_height << "]";
			return ss.str();
		}

		inline float GetWidth() { return m_width; }
		inline float GetHeight() { return m_height; }

	private:
		float m_width;
		float m_height;
	};
}
