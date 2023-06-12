#include "pch.h"
#include "JTEEngine/JTEEngine.h"


namespace JTEEngine {
       
    namespace JTEVulkan {

        JTEVulkanLogicalDevice::JTEVulkanLogicalDevice() {}

        JTEVulkanLogicalDevice::JTEVulkanLogicalDevice(const JTEVulkanInstance& JVinstance, const JTEVulkanSurface& JVsurface, JTEboolean enableValidationLayers) {
            this->m_JVinstance = JVinstance;
            this->m_JVsurface = JVsurface;

            this->m_EnableValidationLayers = enableValidationLayers;
        }

        void JTEVulkanLogicalDevice::createVulkanLogicalDevice() {
            //<===== Picking Physical Device =====>//

            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(this->m_JVinstance.getVulkanInstance(), &deviceCount, nullptr);

            if (deviceCount == 0) {
                throw std::runtime_error("No GPUs support Vulkan on this device.");
            }

            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(this->m_JVinstance.getVulkanInstance(), &deviceCount, devices.data());
            for (const auto& device : devices) {
                if (JTEVulkanUtils::isDeviceSuitable(device, this->m_JVsurface.getVulkanSurface())) {
                    this->m_PhysicalDevice = device;
                    JTEUtilities::println("Vulkan Physical Deivce choosen.");
                    break;
                }
            }

            if (this->m_PhysicalDevice == VK_NULL_HANDLE) {
                JTEUtilities::println("Vulkan Physical Deivce not choosen.");
            }

            //<===== Creating Logical Device =====>//

            JTEVulkanUtils::QueueFamilyIndices indices = JTEVulkanUtils::findQueueFamilies(this->m_PhysicalDevice, this->m_JVsurface.getVulkanSurface());

            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            std::set<JTEuint> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

            float queuePriority = 1.0f;
            for (uint32_t queueFamily : uniqueQueueFamilies) {
                VkDeviceQueueCreateInfo vkQueueInfo{};
                vkQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                vkQueueInfo.queueFamilyIndex = queueFamily;
                vkQueueInfo.queueCount = 1;
                vkQueueInfo.pQueuePriorities = &queuePriority;
                queueCreateInfos.push_back(vkQueueInfo);
            }

            VkPhysicalDeviceFeatures deviceFeatures{};

            VkDeviceCreateInfo vkDeviceInfo{};
            vkDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            vkDeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
            vkDeviceInfo.pQueueCreateInfos = queueCreateInfos.data();
            vkDeviceInfo.pEnabledFeatures = &deviceFeatures;
            vkDeviceInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
            vkDeviceInfo.ppEnabledExtensionNames = deviceExtensions.data();

            if (this->m_EnableValidationLayers) {
                vkDeviceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                vkDeviceInfo.ppEnabledLayerNames = validationLayers.data();
            }
            else {
                vkDeviceInfo.enabledLayerCount = 0;
            }

            VkResult resultDevice = vkCreateDevice(this->m_PhysicalDevice, &vkDeviceInfo, nullptr, &this->m_LogicalDevice);
            if (resultDevice != VK_SUCCESS) { JTEUtilities::println("Vulkan Logical Device not created."); }
            else { JTEUtilities::println("Vulkan Logical Device created."); }

            vkGetDeviceQueue(this->m_LogicalDevice, indices.graphicsFamily.value(), 0, &this->m_GraphicsQueue);
            vkGetDeviceQueue(this->m_LogicalDevice, indices.presentFamily.value(), 0, &this->m_PresentQueue);
        }

        void JTEVulkanLogicalDevice::terminateVulkanLogicalDevice() {
            vkDestroyDevice(this->m_LogicalDevice, nullptr);
            JTEUtilities::println("Vulkan Logical Device terminated.");
        }

        VkPhysicalDevice JTEVulkanLogicalDevice::getVulkanPhysicalDevice() {
            return this->m_PhysicalDevice;
        }

        VkDevice JTEVulkanLogicalDevice::getVulkanLogicalDevice() {
            return this->m_LogicalDevice;
        }

        VkQueue JTEVulkanLogicalDevice::getVulkanGraphicsQueue() {
            return this->m_GraphicsQueue;
        }

        VkQueue JTEVulkanLogicalDevice::getVulkanPresentQueue() {
            return this->m_PresentQueue;
        }

    }

}