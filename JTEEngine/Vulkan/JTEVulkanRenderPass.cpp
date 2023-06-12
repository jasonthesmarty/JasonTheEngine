#include "pch.h"
#include "JTEEngine/JTEEngine.h"

namespace JTEEngine {

	namespace JTEVulkan {

        JTEVulkanRenderPass::JTEVulkanRenderPass() {}

		JTEVulkanRenderPass::JTEVulkanRenderPass(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSwapchain& JVswapchain) {
            this->m_JVdevice = JVdevice;
            this->m_JVswapchain = JVswapchain;
		}

		void JTEVulkanRenderPass::createVulkanRenderPass() {
            VkAttachmentDescription vkAttachmentDesc{};
            vkAttachmentDesc.format = this->m_JVswapchain.getVulkanSwapChainImageFormat();
            vkAttachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
            vkAttachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            vkAttachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
            vkAttachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            vkAttachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            vkAttachmentDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            vkAttachmentDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

            VkAttachmentReference vkAttachmentRef{};
            vkAttachmentRef.attachment = 0;
            vkAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

            VkSubpassDescription vkSubpassDesc{};
            vkSubpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            vkSubpassDesc.colorAttachmentCount = 1;
            vkSubpassDesc.pColorAttachments = &vkAttachmentRef;

            VkSubpassDependency vkSubpassDepend{};
            vkSubpassDepend.srcSubpass = VK_SUBPASS_EXTERNAL;
            vkSubpassDepend.dstSubpass = 0;
            vkSubpassDepend.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            vkSubpassDepend.srcAccessMask = 0;
            vkSubpassDepend.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            vkSubpassDepend.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

            VkRenderPassCreateInfo vkRenderPassInfo{};
            vkRenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            vkRenderPassInfo.attachmentCount = 1;
            vkRenderPassInfo.pAttachments = &vkAttachmentDesc;
            vkRenderPassInfo.subpassCount = 1;
            vkRenderPassInfo.pSubpasses = &vkSubpassDesc;
            vkRenderPassInfo.dependencyCount = 1;
            vkRenderPassInfo.pDependencies = &vkSubpassDepend;

            VkResult renderPassResult = vkCreateRenderPass(this->m_JVdevice.getVulkanLogicalDevice(), &vkRenderPassInfo, nullptr, &this->m_RenderPass);
            if (renderPassResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Render Pass not created."); }
            else { JTEUtilities::println("Vulkan Render Pass created."); }
		}

		void JTEVulkanRenderPass::terminateVulkanRenderPass() {
            vkDestroyRenderPass(this->m_JVdevice.getVulkanLogicalDevice(), this->m_RenderPass, nullptr);
            JTEUtilities::println("Vulkan Render Pass terminated.");
		}

		VkRenderPass JTEVulkanRenderPass::getVulkanRenderPass() {
			return this->m_RenderPass;
		}

	}

}