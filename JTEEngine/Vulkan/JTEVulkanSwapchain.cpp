#include "../JTEEngine.h"


namespace JTEEngine {

	namespace JTEVulkan {

        JTEVulkanSwapchain::JTEVulkanSwapchain() {}

		JTEVulkanSwapchain::JTEVulkanSwapchain(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSurface& JVsurface, const JTEWindow& Jwindow) {
            this->m_JVdevice = JVdevice;
            this->m_JVsurface = JVsurface;
            this->m_JVwindow = Jwindow;
		}

		void JTEVulkanSwapchain::createVulkanSwapchain() {
            JTEVulkanUtils::SwapChainSupportDetails swapChainSupport = JTEVulkanUtils::querySwapChainSupport(this->m_JVdevice.getVulkanPhysicalDevice(), this->m_JVsurface.getVulkanSurface());
            VkSurfaceFormatKHR surfaceFormat = JTEVulkanUtils::chooseSwapSurfaceFormat(swapChainSupport.formats);
            VkPresentModeKHR presentMode = JTEVulkanUtils::chooseSwapPresentMode(swapChainSupport.presentModes);
            VkExtent2D extent = JTEVulkanUtils::chooseSwapExtent(swapChainSupport.capabilities, this->m_JVwindow.getWindow());

            uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
            if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
                imageCount = swapChainSupport.capabilities.maxImageCount;
            }

            VkSwapchainCreateInfoKHR vkSwapchainInfo{};
            vkSwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            vkSwapchainInfo.surface = this->m_JVsurface.getVulkanSurface();
            vkSwapchainInfo.minImageCount = imageCount;
            vkSwapchainInfo.imageFormat = surfaceFormat.format;
            vkSwapchainInfo.imageColorSpace = surfaceFormat.colorSpace;
            vkSwapchainInfo.imageExtent = extent;
            vkSwapchainInfo.imageArrayLayers = 1;
            vkSwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            JTEVulkanUtils::QueueFamilyIndices indices = JTEVulkanUtils::findQueueFamilies(this->m_JVdevice.getVulkanPhysicalDevice(), this->m_JVsurface.getVulkanSurface());
            uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

            if (indices.graphicsFamily != indices.presentFamily) {
                vkSwapchainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                vkSwapchainInfo.queueFamilyIndexCount = 2;
                vkSwapchainInfo.pQueueFamilyIndices = queueFamilyIndices;
            }
            else {
                vkSwapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            }

            vkSwapchainInfo.preTransform = swapChainSupport.capabilities.currentTransform;
            vkSwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            vkSwapchainInfo.presentMode = presentMode;
            vkSwapchainInfo.clipped = VK_TRUE;

            VkResult swapChainResult = vkCreateSwapchainKHR(this->m_JVdevice.getVulkanLogicalDevice(), &vkSwapchainInfo, nullptr, &this->m_Swapchain);
            if (swapChainResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Swapchain not created."); }
            else { JTEUtilities::println("Vulkan Swapchain created."); }

            vkGetSwapchainImagesKHR(this->m_JVdevice.getVulkanLogicalDevice(), this->m_Swapchain, &imageCount, nullptr);
            this->m_SwapChainImages.resize(imageCount);
            vkGetSwapchainImagesKHR(this->m_JVdevice.getVulkanLogicalDevice(), this->m_Swapchain, &imageCount, this->m_SwapChainImages.data());

            this->m_SwapChainImageFormat = surfaceFormat.format;
            this->m_SwapChainExtent = extent;
		}

		void JTEVulkanSwapchain::terminateVulkanSwapchain() {
            vkDestroySwapchainKHR(this->m_JVdevice.getVulkanLogicalDevice(), this->m_Swapchain, nullptr);
            JTEUtilities::println("Vulkan Swapchain terminated.");
		}

		VkSwapchainKHR JTEVulkanSwapchain::getVulkanSwapchain() {
			return this->m_Swapchain;
		}

		std::vector<VkImage> JTEVulkanSwapchain::getVulkanSwapChainImages() {
			return this->m_SwapChainImages;
		}

		VkExtent2D JTEVulkanSwapchain::getVulkanSwapChainExtent() {
			return this->m_SwapChainExtent;
		}

        VkFormat JTEVulkanSwapchain::getVulkanSwapChainImageFormat() {
            return this->m_SwapChainImageFormat;
        }

	}

}