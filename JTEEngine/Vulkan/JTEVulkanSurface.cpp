#include "../JTEEngine.h"


namespace JTEEngine {

	namespace JTEVulkan {

		JTEVulkanSurface::JTEVulkanSurface() {}
		
		JTEVulkanSurface::JTEVulkanSurface(const JTEVulkanInstance& JVinstance, const JTEWindow& Jwindow) {
			this->m_JVinstance = JVinstance;
			this->m_JVwindow = Jwindow;
		}
		
		void JTEVulkanSurface::createVulkanSurface() {
			VkResult resultSurface = glfwCreateWindowSurface(this->m_JVinstance.getVulkanInstance(), this->m_JVwindow.getWindow(), nullptr, &m_Surface);
			if (resultSurface != VK_SUCCESS) { JTEUtilities::println("Vulkan Surface not created."); }
			else { JTEUtilities::println("Vulkan Surface created."); }
		}
		
		void JTEVulkanSurface::terminateVulkanSurface() {
			vkDestroySurfaceKHR(this->m_JVinstance.getVulkanInstance(), m_Surface, nullptr);
			JTEUtilities::println("Vulkan Surface terminated.");
		}
		
		VkSurfaceKHR JTEVulkanSurface::getVulkanSurface() {
			return m_Surface;
		}

	}

}