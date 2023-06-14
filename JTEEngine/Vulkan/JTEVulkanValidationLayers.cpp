#include "../JTEEngine.h"


namespace JTEEngine {
	
	namespace JTEVulkan {

		JTEVulkanValidationLayers::JTEVulkanValidationLayers() {}

		JTEVulkanValidationLayers::JTEVulkanValidationLayers(const JTEVulkanInstance& JVinstance, JTEboolean enableValidationLayers) {
            this->m_JVinstance = JVinstance;

			this->m_EnableValidationLayers = enableValidationLayers;
		}

		void JTEVulkanValidationLayers::createVulkanValidationLayers() {
			if (!this->m_EnableValidationLayers) return;

			VkDebugUtilsMessengerCreateInfoEXT createInfo;
			JTEVulkanUtils::populateDebugMessengerCreateInfo(createInfo);

			VkResult debugResult = JTEVulkanUtils::CreateDebugUtilsMessengerEXT(this->m_JVinstance.getVulkanInstance(), &createInfo, nullptr, &m_DebugMessenger);
			if (debugResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Validation Layers not created."); }
			else { JTEUtilities::println("Vulkan Validation Layers created."); }
		} 

		void JTEVulkanValidationLayers::terminateVulkanValidationLayers() {
			JTEVulkanUtils::DestroyDebugUtilsMessengerEXT(this->m_JVinstance.getVulkanInstance(), m_DebugMessenger, nullptr);
			JTEUtilities::println("Vulkan Validation Layers terminated.");
		}

	}

}