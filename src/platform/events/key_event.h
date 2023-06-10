#pragma once

#include "event.h"
#include "platform/key_codes.h"
#include <sstream>
#include <spdlog/fmt/fmt.h>
namespace NerfShot
{
	class KeyEvent : public Event
	{
	public:
		inline Key GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(Key keycode)
			: m_KeyCode(keycode)
		{
		}

		Key m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(Key keycode, int repeatCount)
			: KeyEvent(keycode)
			, m_RepeatCount(repeatCount)
		{
		}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			return fmt::format("KeyPressedEvent: {0} ( {1} ) repeats", uint32_t(m_KeyCode), m_RepeatCount);
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class  KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(Key keycode)
			: KeyEvent(keycode)
		{
		}

		std::string ToString() const override
		{
			return fmt::format("KeyReleasedEvent: {0}", uint32_t(m_KeyCode));
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class  KeyTypedEvent : public KeyEvent
 	{
 	public:
		KeyTypedEvent(Key keycode, char character)
			: KeyEvent(keycode), Character(character)
		{
		}

		std::string ToString() const override
 		{
			return fmt::format("KeyPressedEvent: {0}", uint32_t(m_KeyCode));
 		}

  		EVENT_CLASS_TYPE(KeyTyped)
    
        char Character;

  	private:
 	};
}
