#include "pch.h"
#include "JTEEngine/JTEEngine.h"


namespace JTEEngine {

	namespace JTEVulkan {

        JTEVulkanSemaphoreFence::JTEVulkanSemaphoreFence() {}

		JTEVulkanSemaphoreFence::JTEVulkanSemaphoreFence(const JTEVulkanLogicalDevice& JVdevice, JTEuint maxFramesInFlight) {
            this->m_JVdevice = JVdevice;

            this->m_MaxFramesInFlight = maxFramesInFlight;
		}

		void JTEVulkanSemaphoreFence::createVulkanSemaphoreFence() {
            this->m_ImageAvailableSemaphores.resize(this->m_MaxFramesInFlight);
            this->m_RenderFinishedSemaphores.resize(this->m_MaxFramesInFlight);
            this->m_InFlightFences.resize(this->m_MaxFramesInFlight);

            VkSemaphoreCreateInfo vkSemaphoreInfo{};
            vkSemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            VkFenceCreateInfo vkFenceInfo{};
            vkFenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
            vkFenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

            for (size_t i = 0; i < this->m_MaxFramesInFlight; i++) {
                VkResult semaphoreImageAvailable = vkCreateSemaphore(this->m_JVdevice.getVulkanLogicalDevice(), &vkSemaphoreInfo, nullptr, &this->m_ImageAvailableSemaphores[i]);
                VkResult semaphoreRenderFinished = vkCreateSemaphore(this->m_JVdevice.getVulkanLogicalDevice(), &vkSemaphoreInfo, nullptr, &this->m_RenderFinishedSemaphores[i]);
                VkResult fenceInFlight = vkCreateFence(this->m_JVdevice.getVulkanLogicalDevice(), &vkFenceInfo, nullptr, &this->m_InFlightFences[i]);

                if (semaphoreImageAvailable != VK_SUCCESS || semaphoreRenderFinished != VK_SUCCESS || fenceInFlight != VK_SUCCESS) {
                    throw std::runtime_error("failed to create synchronization objects for a frame!");
                }
            }

            JTEUtilities::println("Vulkan Semaphore and Fence created.");
		}

		void JTEVulkanSemaphoreFence::terminateVulkanSemaphoreFence() {
            for (size_t i = 0; i < this->m_MaxFramesInFlight; i++) {
                vkDestroySemaphore(this->m_JVdevice.getVulkanLogicalDevice(), this->m_RenderFinishedSemaphores[i], nullptr);
                vkDestroySemaphore(this->m_JVdevice.getVulkanLogicalDevice(), this->m_ImageAvailableSemaphores[i], nullptr);
                vkDestroyFence(this->m_JVdevice.getVulkanLogicalDevice(), this->m_InFlightFences[i], nullptr);
            }
            JTEUtilities::println("Vulkan Semaphore and Fence terminated.");
		}

        std::vector<VkSemaphore> JTEVulkanSemaphoreFence::getVulkanRenderFinishedSemaphore() {
            return this->m_RenderFinishedSemaphores;
        }

        std::vector<VkSemaphore> JTEVulkanSemaphoreFence::getVulkanImageAvailableSemaphore() {
            return this->m_ImageAvailableSemaphores;
        }

        std::vector<VkFence> JTEVulkanSemaphoreFence::getVulkanInFlightFence() {
            return this->m_InFlightFences;
        }

	}

}