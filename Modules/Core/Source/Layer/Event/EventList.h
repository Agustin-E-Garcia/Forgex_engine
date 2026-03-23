#pragma once
#include "Event.h"
#include <string>

namespace Forgex::Core::Layer::Event
{
	class WindowResizedEvent : public Event
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

	class WindowFocusChangedEvent : public Event
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

	class KeyPressedEvent : public Event
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

	class CharInputEvent : public Event
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

	class KeyReleasedEvent : public Event
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

	class MouseClickEvent : public Event
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

	class MouseWheelScrollEvent : public Event
	{
	public:
		MouseWheelScrollEvent(double x, double y) : m_XOffset(x), m_YOffset(y) {};
		EVENT_SET_TYPE(MouseWheel)
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

	class MousePositionEvent : public Event
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

    class MouseLockEvent : public Event
    {
    public:
        MouseLockEvent(bool lockState) : m_LockState(lockState) {}
        EVENT_SET_TYPE(MouseLock)
        EVENT_SET_CATEGORY(ApplicationEvent | LayerEvent)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseLockEvent: " << m_LockState;
            return ss.str();
        }

        inline bool GetState() { return m_LockState; }

    private:
        bool m_LockState;
    };
}
