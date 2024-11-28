#pragma once
#include "Event.h"
/*TEMP*/
#include "../SceneGraph/Scene.h"

class ENGINE_API WindowResizedEvent : public Event
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

class ENGINE_API WindowCloseEvent : public Event
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

class ENGINE_API WindowFocusChangedEvent : public Event
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

class ENGINE_API KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(unsigned int keyCode, bool isRepeat) : m_KeyCode(keyCode), m_IsRepeat(isRepeat) {}
	EVENT_SET_TYPE(KeyPressed)
	EVENT_SET_CATEGORY(InputEvent | KeyboardEvent)

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

class ENGINE_API CharInputEvent : public Event
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

class ENGINE_API KeyReleasedEvent : public Event
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

class ENGINE_API MouseClickEvent : public Event
{
public:
	MouseClickEvent(unsigned int button) : m_Button(button) {}
	EVENT_SET_TYPE(MouseClicked)
	EVENT_SET_CATEGORY(InputEvent | MouseButtonEvent)

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

class ENGINE_API MouseWheelScrollEvent : public Event 
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

class ENGINE_API MousePositionEvent : public Event
{
public:
	MousePositionEvent(float xPosition, float yPosition) : m_PositionX(xPosition), m_PositionY(yPosition) {}
	EVENT_SET_TYPE(MousePosition)
	EVENT_SET_CATEGORY(InputEvent | MouseEvent)

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

/*---------------------------------------------------------------------------------------------------------*/

class ENGINE_API SceneChangeEvent : public Event 
{
public:
	SceneChangeEvent(Scene* scene) : m_Scene(scene) {}
	EVENT_SET_TYPE(SceneChange)
	EVENT_SET_CATEGORY(LayerEvent)

	std::string ToString() const override 
	{
		std::stringstream ss;
		ss << "SceneChangedEvent: {" << m_Scene->GetName() << "}";
		return ss.str();
	}

	inline Scene* GetScene() { return m_Scene; }

private:
	Scene* m_Scene;
};