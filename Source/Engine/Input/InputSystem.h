#pragma once
#include <vector>
#include <array>
#include "Core/Math/Vector2.h"
#include <SDL2-2.28.0/include/SDL.h>

namespace max
{
	class InputSystem
	{
	public:
		// keyboard
		InputSystem() = default;
		~InputSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		bool GetKeyDown(uint32_t key) const { return m_keyboardState[key]; }
		bool GetKeyDownOnce(uint32_t button) { return (m_keyboardState[button] && !m_prevKeyboardState[button]); }
		bool GetKeyUpOnce(uint32_t button) { return (!m_keyboardState[button] && m_prevKeyboardState[button]); }
		bool GetPreviousKeyDown(uint32_t key) const { return m_prevKeyboardState[key]; }

		// mouse
		const max::Vector2& GetMousePosition() const { return m_mousePosition; }
		bool GetMouseButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetMouseButtonDownOnce(uint32_t button) { return (m_mouseButtonState[button] && !m_prevMouseButtonState[button]); }
		bool GetMouseButtonUpOnce(uint32_t button) { return (!m_mouseButtonState[button] && m_prevMouseButtonState[button]); }
		bool GetMousePreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }
	private:
		//Keyboard
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;

		//Mouse
		max::Vector2 m_mousePosition;
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern InputSystem g_inputSystem;
}