#include "pch.h"
#include "JTEEngine/JTEEngine.h"


namespace JTEEngine {

	//===== Keys and Buttons =====//

	JTEboolean m_Keys[GLFW_KEY_LAST];
	JTEboolean m_MouseButtons[GLFW_MOUSE_BUTTON_LAST];
	JTEdouble m_MouseX, m_MouseY;

	//===== Constructors =====//

	JTEInput::JTEInput() {}

	//===== Private Public Functions =====//
	//(Meaning they shouldn't be used)

	GLFWkeyfun JTEInput::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		m_Keys[key] = action != GLFW_RELEASE;
		return GLFWkeyfun();
	}

	GLFWmousebuttonfun JTEInput::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		m_MouseButtons[button] = action != GLFW_RELEASE;
		return GLFWmousebuttonfun();
	}

	GLFWcursorposfun JTEInput::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
		m_MouseX = xPos;
		m_MouseY = yPos;
		return GLFWcursorposfun();
	}

	//===== Public Functions =====//

	JTEboolean JTEInput::keyDown(JTEuint key) {
		return m_Keys[key];
	}

	JTEboolean JTEInput::mouseButtonDown(JTEuint mouseButton) {
		return m_MouseButtons[mouseButton];
	}

	//===== Getters =====//

	JTEdouble JTEInput::getMouseX() {
		return m_MouseX;
	}

	JTEdouble JTEInput::getMouseY() {
		return m_MouseY;
	}

}