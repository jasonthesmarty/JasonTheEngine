#include "../JTEEngine.h"


namespace JTEEngine {

	namespace JTEVulkan {

		JTEVulkanCommandBuffers::JTEVulkanCommandBuffers() {}

		JTEVulkanCommandBuffers::JTEVulkanCommandBuffers(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanSurface& JVsurface, JTEuint maxFramesInFlight) {
            this->m_JVdevice = JVdevice;
            this->m_JVsurface = JVsurface;

            this->m_MaxFramesInFlight = maxFramesInFlight;
		}

		void JTEVulkanCommandBuffers::createVulkanCommandBuffers() {
            //<===== Creating Command Pool =====>//

            JTEVulkanUtils::QueueFamilyIndices queueFamilyIndices = JTEVulkanUtils::findQueueFamilies(this->m_JVdevice.getVulkanPhysicalDevice(), this->m_JVsurface.getVulkanSurface());

            VkCommandPoolCreateInfo poolInfo{};
            poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

            VkResult poolResult = vkCreateCommandPool(this->m_JVdevice.getVulkanLogicalDevice(), &poolInfo, nullptr, &this->m_CommandPool);
            if (poolResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Command Pool not created."); }
            else { JTEUtilities::println("Vulkan Command Pool created."); }

            //<===== Creating Command Buffers =====>//

            this->m_CommandBuffers.resize(this->m_MaxFramesInFlight);
            VkCommandBufferAllocateInfo allocInfo{};
            allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            allocInfo.commandPool = this->m_CommandPool;
            allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            allocInfo.commandBufferCount = (JTEuint)this->m_CommandBuffers.size();

            VkResult buffersResult = vkAllocateCommandBuffers(this->m_JVdevice.getVulkanLogicalDevice(), &allocInfo, this->m_CommandBuffers.data());
            if (buffersResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Command Buffers not created."); }
            else { JTEUtilities::println("Vulkan Command Buffers created."); }
		}

		void JTEVulkanCommandBuffers::terminateVulkanCommandBuffers() {
            vkDestroyCommandPool(this->m_JVdevice.getVulkanLogicalDevice(), this->m_CommandPool, nullptr);
            JTEUtilities::println("Vulkan Command Pool terminated.");
		}

		VkCommandPool JTEVulkanCommandBuffers::getVulkanCommandPool() {
            return this->m_CommandPool;
		}

		std::vector<VkCommandBuffer> JTEVulkanCommandBuffers::getVulkanCommandBuffers() {
            return this->m_CommandBuffers;
		}

	}

}