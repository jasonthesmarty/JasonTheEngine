#include "../JTEEngine.h"


namespace JTEEngine {

	namespace JTEVulkan {

        JTEVulkanImageViews::JTEVulkanImageViews() {}

		JTEVulkanImageViews::JTEVulkanImageViews(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSwapchain& JVswapchain) {
            this->m_JVswapchain = JVswapchain;
            this->m_JVdevice = JVdevice;
		}

		void JTEVulkanImageViews::creatVulkanImageViews() {

            this->m_SwapChainImageViews.resize(this->m_JVswapchain.getVulkanSwapChainImages().size());
            for (size_t i = 0; i < this->m_JVswapchain.getVulkanSwapChainImages().size(); i++) {
                VkImageViewCreateInfo vkImageViewInfo{};

                vkImageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                vkImageViewInfo.image = this->m_JVswapchain.getVulkanSwapChainImages()[i];
                vkImageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                vkImageViewInfo.format = this->m_JVswapchain.getVulkanSwapChainImageFormat();
                vkImageViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                vkImageViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                vkImageViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                vkImageViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
                vkImageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                vkImageViewInfo.subresourceRange.baseMipLevel = 0;
                vkImageViewInfo.subresourceRange.levelCount = 1;
                vkImageViewInfo.subresourceRange.baseArrayLayer = 0;
                vkImageViewInfo.subresourceRange.layerCount = 1;

                if (vkCreateImageView(this->m_JVdevice.getVulkanLogicalDevice(), &vkImageViewInfo, nullptr, &this->m_SwapChainImageViews[i]) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create image views!");
                }
            }

            JTEUtilities::println("Vulkan Image Views created. (" + JTEUtilities::string(this->m_SwapChainImageViews.size()) + " Image Views created) ");
		}

		void JTEVulkanImageViews::terminateVulkanImageViews() {
            for (auto imageView : this->m_SwapChainImageViews) {
                vkDestroyImageView(this->m_JVdevice.getVulkanLogicalDevice(), imageView, nullptr);
            }

            JTEUtilities::println("Vulkan Image Views terminated. (" + JTEUtilities::string(this->m_SwapChainImageViews.size()) + " Image Views destroyed) ");
		}

		std::vector<VkImageView> JTEVulkanImageViews::getVulkanSwapChainImageViews() {
            return this->m_SwapChainImageViews;
		}

        void JTEVulkanImageViews::updateSwapchain(const JTEVulkanSwapchain& swpchain) {
            this->m_JVswapchain = swpchain;
        }

	}

}