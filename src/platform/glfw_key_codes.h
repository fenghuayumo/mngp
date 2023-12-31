#pragma once
#include "core/base_type.h"

#include "platform/key_codes.h"
#include <GLFW/glfw3.h>
#include <map>
namespace NerfShot
{
	namespace GLFWKeyCodes
	{
		static Key GLFWToNeoxRayKeyboardKey(uint32 glfwKey)
		{
			static std::map<uint32, Key> keyMap =
				{
					{GLFW_KEY_A, Key::A},
					{GLFW_KEY_B, Key::B},
					{GLFW_KEY_C, Key::C},
					{GLFW_KEY_D, Key::D},
					{GLFW_KEY_E, Key::E},
					{GLFW_KEY_F, Key::F},
					{GLFW_KEY_G, Key::G},
					{GLFW_KEY_H, Key::H},
					{GLFW_KEY_I, Key::I},
					{GLFW_KEY_J, Key::J},
					{GLFW_KEY_K, Key::K},
					{GLFW_KEY_L, Key::L},
					{GLFW_KEY_M, Key::M},
					{GLFW_KEY_N, Key::N},
					{GLFW_KEY_O, Key::O},
					{GLFW_KEY_P, Key::P},
					{GLFW_KEY_Q, Key::Q},
					{GLFW_KEY_R, Key::R},
					{GLFW_KEY_S, Key::S},
					{GLFW_KEY_T, Key::T},
					{GLFW_KEY_U, Key::U},
					{GLFW_KEY_V, Key::V},
					{GLFW_KEY_W, Key::W},
					{GLFW_KEY_X, Key::X},
					{GLFW_KEY_Y, Key::Y},
					{GLFW_KEY_Z, Key::Z},

					{GLFW_KEY_0, Key::D0},
					{GLFW_KEY_1, Key::D1},
					{GLFW_KEY_2, Key::D2},
					{GLFW_KEY_3, Key::D3},
					{GLFW_KEY_4, Key::D4},
					{GLFW_KEY_5, Key::D5},
					{GLFW_KEY_6, Key::D6},
					{GLFW_KEY_7, Key::D7},
					{GLFW_KEY_8, Key::D8},
				{GLFW_KEY_9, Key::D9},
				
				{GLFW_KEY_F1, Key::F1},
				{GLFW_KEY_F2, Key::F2},
				{GLFW_KEY_F3, Key::F3},
				{GLFW_KEY_F4, Key::F4},
				{GLFW_KEY_F5, Key::F5},
				{GLFW_KEY_F6, Key::F6},
				{GLFW_KEY_F7, Key::F7},
				{GLFW_KEY_F8, Key::F8},
				{GLFW_KEY_F9, Key::F9},
				{GLFW_KEY_F10, Key::F10},
				{GLFW_KEY_F11, Key::F11},
				{GLFW_KEY_F12, Key::F12},

					{GLFW_KEY_MINUS, Key::Minus},
					{GLFW_KEY_DELETE, Key::Delete},
					{GLFW_KEY_SPACE, Key::Space},
					{GLFW_KEY_LEFT, Key::Left},
					{GLFW_KEY_RIGHT, Key::Right},
					{GLFW_KEY_UP, Key::Up},
					{GLFW_KEY_DOWN, Key::Down},
					{GLFW_KEY_LEFT_SHIFT, Key::LeftShift},
					{GLFW_KEY_RIGHT_SHIFT, Key::RightShift},
					{GLFW_KEY_ESCAPE, Key::Escape},
					{GLFW_KEY_KP_ADD, Key::A},
					{GLFW_KEY_COMMA, Key::Comma},
					{GLFW_KEY_BACKSPACE, Key::Backspace},
					{GLFW_KEY_ENTER, Key::Enter},
					{GLFW_KEY_LEFT_SUPER, Key::LeftSuper},
					{GLFW_KEY_RIGHT_SUPER, Key::RightSuper},
					{GLFW_KEY_LEFT_ALT, Key::LeftAlt},
					{GLFW_KEY_RIGHT_ALT, Key::RightAlt},
					{GLFW_KEY_LEFT_CONTROL, Key::LeftControl},
					{GLFW_KEY_RIGHT_CONTROL, Key::RightControl}};

 			return keyMap[glfwKey];
		}

		static MouseKey GLFWToLumosMouseKey(uint32 glfwKey)
		{

			static std::map<uint32, MouseKey> keyMap =
				{
					{GLFW_MOUSE_BUTTON_LEFT, MouseKey::ButtonLeft},
					{GLFW_MOUSE_BUTTON_RIGHT, MouseKey::ButtonRight},
					{GLFW_MOUSE_BUTTON_MIDDLE, MouseKey::ButtonMiddle}};

			return keyMap[glfwKey];
		}
	}
}
