#include "../JTEEngine.h"


namespace JTEEngine {

    //===== Constructor =====//
    
    JTERenderer::JTERenderer(JTEuint maxFramesInFlight) {
        this->m_MaxFramesInFlight = maxFramesInFlight;
    }
    
    //===== Public Functions =====//
    
    void JTERenderer::start(JTEVulkanObjects& JVObjects) {
        vkWaitForFences(JVObjects.device.getVulkanLogicalDevice(), 1, &JVObjects.semaphorefence.getVulkanInFlightFence()[currentFrame], VK_TRUE, UINT64_MAX);
        vkResetFences(JVObjects.device.getVulkanLogicalDevice(), 1, &JVObjects.semaphorefence.getVulkanInFlightFence()[currentFrame]);
        vkAcquireNextImageKHR(JVObjects.device.getVulkanLogicalDevice(), JVObjects.swapchain.getVulkanSwapchain(), UINT64_MAX, JVObjects.semaphorefence.getVulkanImageAvailableSemaphore()[currentFrame], VK_NULL_HANDLE, &imageIndex);
    
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
        if (vkBeginCommandBuffer(JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }
    
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = JVObjects.renderpass.getVulkanRenderPass();
        renderPassInfo.framebuffer = JVObjects.framebuffers.getVulkanSwapChainFramebuffers()[imageIndex];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = JVObjects.swapchain.getVulkanSwapChainExtent();
    
        VkClearValue clearColor = { {{0.75f, 0.5f, 1.0f, 1.0f}} };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;
    
        vkCmdBindPipeline(JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, JVObjects.graphicspipeline.getVulkanGraphicsPipeline());
    
        vkCmdBeginRenderPass(JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(JVObjects.swapchain.getVulkanSwapChainExtent().width);
        viewport.height = static_cast<float>(JVObjects.swapchain.getVulkanSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame], 0, 1, &viewport);
    
        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = JVObjects.swapchain.getVulkanSwapChainExtent();
        vkCmdSetScissor(JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame], 0, 1, &scissor);
    }
    
    void JTERenderer::end(JTEVulkanObjects& JVObjects) {
        vkCmdEndRenderPass(JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame]);
    
        if (vkEndCommandBuffer(JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
    
    void JTERenderer::submit(JTEVulkanObjects& JVObjects) {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    
        VkSemaphore waitSemaphores[] = { JVObjects.semaphorefence.getVulkanImageAvailableSemaphore()[currentFrame] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        VkCommandBuffer ccc = JVObjects.commandbuffers.getVulkanCommandBuffers()[currentFrame];
        submitInfo.pCommandBuffers = &ccc;
    
        VkSemaphore signalSemaphores[] = { JVObjects.semaphorefence.getVulkanRenderFinishedSemaphore()[currentFrame] };
    
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;
    
        if (vkQueueSubmit(JVObjects.device.getVulkanGraphicsQueue(), 1, &submitInfo, JVObjects.semaphorefence.getVulkanInFlightFence()[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }
    
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
    
        VkSwapchainKHR swapChains[] = { JVObjects.swapchain.getVulkanSwapchain() };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;
    
        vkQueuePresentKHR(JVObjects.device.getVulkanPresentQueue(), &presentInfo);
    
        currentFrame = (currentFrame + 1) % this->m_MaxFramesInFlight;
    
        vkDeviceWaitIdle(JVObjects.device.getVulkanLogicalDevice());
    }
    
    //===== Getters =====//
    
    JTEuint JTERenderer::getCurrentFrame() {
    
        return currentFrame;
    }

}