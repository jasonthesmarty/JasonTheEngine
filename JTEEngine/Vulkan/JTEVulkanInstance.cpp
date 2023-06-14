#include "../JTEEngine.h"


namespace JTEEngine {

    namespace JTEVulkan {

        JTEVulkanInstance::JTEVulkanInstance() {}

        JTEVulkanInstance::JTEVulkanInstance(JTEchars applicationName, JTEint majorVersion, JTEint minorVersion, JTEint patch, JTEboolean enableValidationLayers) {
            this->m_Instance = VK_NULL_HANDLE;

            this->m_ApplicationName = applicationName;
            this->m_MajorVersion = majorVersion;
            this->m_MinorVersion = minorVersion;
            this->m_Patch = patch;

            this->m_EnableValidationLayers = enableValidationLayers;
        }

        void JTEVulkanInstance::createVulkanInstance() {
            if (this->m_EnableValidationLayers && !JTEVulkanUtils::checkValidationLayerSupport()) {
                JTEUtilities::println("Validation Layers not avaiable.");
            }

            VkApplicationInfo vkAppInfo{};
            vkAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            vkAppInfo.pApplicationName = this->m_ApplicationName;
            vkAppInfo.applicationVersion = VK_MAKE_VERSION(this->m_MajorVersion, this->m_MinorVersion, this->m_Patch);
            vkAppInfo.pEngineName = "JasonTheEngine";
            vkAppInfo.engineVersion = VK_MAKE_VERSION(JTE_MAJOR_VERSION, JTE_MINOR_VERSION, JTE_PATCH_VERSION);
            vkAppInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo vkInstanceInfo{};
            vkInstanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            vkInstanceInfo.pApplicationInfo = &vkAppInfo;
            std::vector<JTEchars> extensions = JTEVulkanUtils::getRequiredExtensions(this->m_EnableValidationLayers);
            vkInstanceInfo.enabledExtensionCount = static_cast<JTEuint>(extensions.size());
            vkInstanceInfo.ppEnabledExtensionNames = extensions.data();

            VkDebugUtilsMessengerCreateInfoEXT vkDebugMessengerCreateInfo{};

            if (this->m_EnableValidationLayers) {
                vkInstanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                vkInstanceInfo.ppEnabledLayerNames = validationLayers.data();
                JTEVulkanUtils::populateDebugMessengerCreateInfo(vkDebugMessengerCreateInfo);
                vkInstanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&vkDebugMessengerCreateInfo;
            }
            else {
                vkInstanceInfo.enabledLayerCount = 0;
                vkInstanceInfo.pNext = nullptr;
            }

            VkResult resultInstance = vkCreateInstance(&vkInstanceInfo, nullptr, &m_Instance);
            if (resultInstance != VK_SUCCESS) { JTEUtilities::println("Vulkan Instance not created."); }
            else { JTEUtilities::println("Vulkan Instance created."); }
        }

        void JTEVulkanInstance::terminateVulkanInstance() {
            vkDestroyInstance(m_Instance, nullptr);
            JTEUtilities::println("Vulkan Instance terminated.");
        }

        VkInstance JTEVulkanInstance::getVulkanInstance() {
            return m_Instance;
        }

    }

}