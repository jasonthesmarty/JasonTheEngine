#include "pch.h"
#include "JTEEngine/JTEEngine.h"


namespace JTEEngine {

	namespace JTEVulkan {

        JTEVulkanFramebuffers::JTEVulkanFramebuffers() {}

		JTEVulkanFramebuffers::JTEVulkanFramebuffers(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSwapchain& JVswapchain, const JTEVulkanRenderPass& JVrenderpass, const JTEVulkanImageViews& JVimageviews) {
            this->m_JVdevice = JVdevice;
            this->m_JVswapchain = JVswapchain;
            this->m_JVrenderpass = JVrenderpass;
            this->m_JVimageviews = JVimageviews;
		}

		void JTEVulkanFramebuffers::createVulkanFramebuffers() {       
            this->m_SwapChainFramebuffers.resize(this->m_JVimageviews.getVulkanSwapChainImageViews().size());

            for (size_t i = 0; i < this->m_JVimageviews.getVulkanSwapChainImageViews().size(); i++) {
                VkImageView vkImageViewAttachment[] = { this->m_JVimageviews.getVulkanSwapChainImageViews()[i] };

                VkFramebufferCreateInfo vkFramebufferInfo{};
                vkFramebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                vkFramebufferInfo.renderPass = this->m_JVrenderpass.getVulkanRenderPass();
                vkFramebufferInfo.attachmentCount = 1;
                vkFramebufferInfo.pAttachments = vkImageViewAttachment;
                vkFramebufferInfo.width = this->m_JVswapchain.getVulkanSwapChainExtent().width;
                vkFramebufferInfo.height = this->m_JVswapchain.getVulkanSwapChainExtent().height;
                vkFramebufferInfo.layers = 1;

                VkResult framebufferResult = vkCreateFramebuffer(this->m_JVdevice.getVulkanLogicalDevice(), &vkFramebufferInfo, nullptr, &this->m_SwapChainFramebuffers[i]);
                if (framebufferResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Framebuffer not created."); }

            }

            JTEUtilities::println("Vulkan Framebuffer created.");
		}

		void JTEVulkanFramebuffers::terminateVulkanFramebuffers() {
            for (auto framebuffer : this->m_SwapChainFramebuffers) {
                vkDestroyFramebuffer(this->m_JVdevice.getVulkanLogicalDevice(), framebuffer, nullptr);
            }
            JTEUtilities::println("Vulkan Framebuffer terminated.");

		}
		std::vector<VkFramebuffer> JTEVulkanFramebuffers::getVulkanSwapChainFramebuffers() {
			return this->m_SwapChainFramebuffers;
		}

        void JTEVulkanFramebuffers::updateSwapchainAndImageViews(const JTEVulkanSwapchain& JVswapchain, const JTEVulkanImageViews& JVimageviews) {
            this->m_JVswapchain = JVswapchain;
            this->m_JVimageviews = JVimageviews;
        }

	}

}