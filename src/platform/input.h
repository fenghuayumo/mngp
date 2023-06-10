#pragma once

#include "core/math/vec2.h"

#include "events/event.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "platform/key_codes.h"

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

namespace NerfShot
{
	class Event;

	class Input
	{
	public:
		static Input* GetInput() { return s_Input; }

		static void Create();
		static void Release() { delete s_Input; }

		bool GetKeyPressed(Key key)   const { return m_KeyPressed[int(key)]; }
		bool GetKeyHeld(Key key)      const { return m_KeyHeld[int(key)]; }
		bool GetMouseClicked(MouseKey key) const { return m_MouseClicked[int(key)]; }
		bool GetMouseHeld(MouseKey key)    const { return m_MouseHeld[int(key)]; }

		void SetKeyPressed(Key key, bool a) { m_KeyPressed[int(key)] = a; }
		void SetKeyHeld(Key key, bool a) { m_KeyHeld[int(key)] = a; }
		void SetMouseClicked(MouseKey key, bool a) { m_MouseClicked[int(key)] = a; }
		void SetMouseHeld(MouseKey key, bool a) { m_MouseHeld[int(key)] = a; }

		void SetMouseOnScreen(bool onScreen) { m_MouseOnScreen = onScreen; }
		bool GetMouseOnScreen() const { return m_MouseOnScreen; }

		void StoreMousePosition(int xpos, int ypos) { m_MousePosition = int2(xpos, ypos); }
		const int2& GetMousePosition() const { return m_MousePosition; }

		void SetWindowFocus(bool focus) { m_WindowFocus = focus; }
		bool GetWindowFocus() const { return m_WindowFocus; }

		void SetScrollOffset(float offset) { m_ScrollOffset = offset; }
		float GetScrollOffset() const { return m_ScrollOffset; }

		void Reset();
		void ResetPressed();
		void OnEvent(Event& e);

	protected:
		Input();
		virtual ~Input() = default;

		static Input* s_Input;

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);
		bool OnMouseReleased(MouseButtonReleasedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseEnter(MouseEnterEvent& e);

		bool m_KeyPressed[MAX_KEYS];
		bool m_KeyHeld[MAX_KEYS];

		bool m_MouseHeld[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];

		float m_ScrollOffset = 0.0f;

		bool m_MouseOnScreen;
		bool m_WindowFocus;

		int2 m_MousePosition;
	};
}
