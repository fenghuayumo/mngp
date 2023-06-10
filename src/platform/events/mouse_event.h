#pragma once
#include "Event.h"

#include <sstream>
namespace NerfShot
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			return fmt::format("MouseMovedEvent: {0} , {1}", m_MouseX, m_MouseY);
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};


	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			return fmt::format("MouseScrolledEvent: {0} , {1}", GetXOffset(), GetYOffset());
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline MouseKey GetMouseButton() const
		{
			return m_Button;
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(MouseKey button)
			: m_Button(button)
		{
		}

		MouseKey m_Button;
	};

	class  MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseKey button)
			: MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			return fmt::format("MouseButtonPressedEvent: {0} ", m_Button);
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseKey button)
			: MouseButtonEvent(button)
		{
		}

		std::string ToString() const override
		{
			return fmt::format("MouseButtonReleasedEvent: {0} ", m_Button);
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};

	class MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent(bool enter) : m_Entered(enter) {}

		std::string ToString() const override
		{
			return fmt::format("MouseEnterEvent: {0} ", m_Entered);
		}

		EVENT_CLASS_TYPE(MouseEntered)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		inline bool GetEntered() const { return m_Entered; }

	protected:

		bool m_Entered;

	};

}