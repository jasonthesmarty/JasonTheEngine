#include "pch.h"
#include "JTEEngine/JTEEngine.h"


namespace JTEEngine {

	//===== Constructors =====//

	JTEWindow::JTEWindow() {}

	JTEWindow::JTEWindow(JTEuint width, JTEuint height, JTEchars title) {
		this->m_Width = width;
		this->m_Height = height;
		this->m_Title = title;
	}

	//===== Public Functions =====//

	void JTEWindow::create() {
		if (!glfwInit()) { JTEUtilities::println("GLFW not initialized."); }

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, this->m_Title, nullptr, nullptr);

		glfwSetKeyCallback(this->m_Window, (GLFWkeyfun)JTEInput::keyboardCallback);
		glfwSetMouseButtonCallback(this->m_Window, (GLFWmousebuttonfun)JTEInput::mouseButtonCallback);
		glfwSetCursorPosCallback(this->m_Window, (GLFWcursorposfun)JTEInput::cursorPositionCallback);

		if (this->m_Window == 0) { JTEUtilities::println("GLFW window not created."); }

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);

		this->m_FramebufferResized = false;
	}

	void JTEWindow::update(JTEVulkanObjects& JVobjects) {
		glfwPollEvents();
	
		if (this->m_FramebufferResized) {
	
			vkDeviceWaitIdle(JVobjects.device.getVulkanLogicalDevice());
	
			JVobjects.framebuffers.terminateVulkanFramebuffers();
			JVobjects.imageviews.terminateVulkanImageViews();
			JVobjects.swapchain.terminateVulkanSwapchain();
		
			JVobjects.swapchain.createVulkanSwapchain();
			JVobjects.imageviews.updateSwapchain(JVobjects.swapchain);
			JVobjects.imageviews.creatVulkanImageViews();
			JVobjects.framebuffers.updateSwapchainAndImageViews(JVobjects.swapchain, JVobjects.imageviews);
			JVobjects.framebuffers.createVulkanFramebuffers();
	
			this->m_FramebufferResized = false;
		}
	}

	JTEboolean JTEWindow::close() {
		return glfwWindowShouldClose(this->m_Window);
	}

	void JTEWindow::terminate() {
		glfwDestroyWindow(this->m_Window);
		glfwTerminate();
	}

	void JTEWindow::clock(float* fps, float* milliseconds) {
		this->m_Frames++;

		this->m_CurrentTime = glfwGetTime();
		double deltaTime = this->m_CurrentTime - this->m_PreviousTime;

		if (deltaTime >= 1.0 / 30.0) {
			*fps = (float)((1.0f / deltaTime) * this->m_Frames);

			*milliseconds = (float)((deltaTime / this->m_Frames) * 1000);

			this->m_PreviousTime = this->m_CurrentTime;
			this->m_CurrentTime = glfwGetTime();
			this->m_Frames = 0;
		}
	}

	//===== Getters =====//

	GLFWwindow* JTEWindow::getWindow() {
		return this->m_Window;
	}

	std::array<JTEuint, 2> JTEWindow::getWindowDimensions() {
		JTEint width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		return { static_cast<JTEuint>(width), static_cast<JTEuint>(height) };
	}

	void JTEWindow::setTitle(std::string_view title) {
		glfwSetWindowTitle(m_Window, title.data());
	}

	//===== Setters =====//

	void JTEWindow::setDimensions(JTEuint width, JTEuint height) {
		glfwSetWindowSize(this->m_Window, width, height);
	}

	void JTEWindow::setOpacity(JTEuint opacity) {
		if (opacity > 255) {
			JTEUtilities::println("Opacity should not be bigger than 255. Over 255 will just mean it's at maximum opacity.");
			glfwTerminate();
			exit(3);
		}
		JTEfloat normalizedOpacity = static_cast<JTEfloat>(opacity) / 255;
		glfwSetWindowOpacity(m_Window, normalizedOpacity);
	}

	void JTEWindow::setPosition(JTEuint x, JTEuint y) {
		glfwSetWindowPos(this->m_Window, x, y);
	}

	//===== Private Functions =====//

	void JTEWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<JTEWindow*>(glfwGetWindowUserPointer(window));
		app->m_FramebufferResized = true;
	}

}