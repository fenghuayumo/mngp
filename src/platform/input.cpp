#include "input.h"
#include "platform/platform.h"

namespace NerfShot
{
	Input* Input::s_Input;

	void Input::Create()
	{
		s_Input = new Input();
	}

	Input::Input()
		: m_WindowFocus(true)
	{
		Reset();
	}

	void Input::Reset()
	{
		Platform::MemorySet(m_KeyHeld, 0, MAX_KEYS);
		Platform::MemorySet(m_KeyPressed, 0, MAX_KEYS);
		Platform::MemorySet(m_MouseClicked, 0, MAX_BUTTONS);
		Platform::MemorySet(m_MouseHeld, 0, MAX_BUTTONS);

		m_MouseOnScreen = true;
		m_WindowFocus = true;
		m_ScrollOffset = 0.0f;
	}

	void Input::ResetPressed()
	{
		Platform::MemorySet(m_KeyPressed, 0, MAX_KEYS);
		Platform::MemorySet(m_MouseClicked, 0, MAX_BUTTONS);
		m_ScrollOffset = 0;
	}

	void Input::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(NRS_BIND_EVENT_FN(Input::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(NRS_BIND_EVENT_FN(Input::OnKeyReleased));
		dispatcher.Dispatch<MouseButtonPressedEvent>(NRS_BIND_EVENT_FN(Input::OnMousePressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(NRS_BIND_EVENT_FN(Input::OnMouseReleased));
		dispatcher.Dispatch<MouseScrolledEvent>(NRS_BIND_EVENT_FN(Input::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(NRS_BIND_EVENT_FN(Input::OnMouseMoved));
		dispatcher.Dispatch<MouseEnterEvent>(NRS_BIND_EVENT_FN(Input::OnMouseEnter));
	}

	bool Input::OnKeyPressed(KeyPressedEvent& e)
	{
		SetKeyPressed(Key(e.GetKeyCode()), e.GetRepeatCount() < 1);
		SetKeyHeld(Key(e.GetKeyCode()), true);
		return false;
	}

	bool Input::OnKeyReleased(KeyReleasedEvent& e)
	{
		SetKeyPressed(Key(e.GetKeyCode()), false);
		SetKeyHeld(Key(e.GetKeyCode()), false);
		return false;
	}

	bool Input::OnMousePressed(MouseButtonPressedEvent& e)
	{
		SetMouseClicked(MouseKey(e.GetMouseButton()), true);
		SetMouseHeld(MouseKey(e.GetMouseButton()), true);
		return false;
	}

	bool Input::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
		SetMouseClicked(MouseKey(e.GetMouseButton()), false);
		SetMouseHeld(MouseKey(e.GetMouseButton()), false);
		return false;
	}

	bool Input::OnMouseScrolled(MouseScrolledEvent& e)
	{
		SetScrollOffset(e.GetYOffset());
		return false;
	}

	bool Input::OnMouseMoved(MouseMovedEvent& e)
	{
		StoreMousePosition((int)e.GetX(), (int)e.GetY());
		return false;
	}

	bool Input::OnMouseEnter(MouseEnterEvent& e)
	{
		SetMouseOnScreen(e.GetEntered());
		return false;
	}
}
