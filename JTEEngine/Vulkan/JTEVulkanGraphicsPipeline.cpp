#include "../JTEEngine.h"


namespace JTEEngine {

	namespace JTEVulkan {

		JTEVulkanGraphicsPipeline::JTEVulkanGraphicsPipeline() {}

		JTEVulkanGraphicsPipeline::JTEVulkanGraphicsPipeline(const JTEVulkanLogicalDevice& JVdevice, const JTEVulkanRenderPass& JVrenderpass) {
            this->m_JVdevice = JVdevice;
            this->m_JVrenderpass = JVrenderpass;
		}

		void JTEVulkanGraphicsPipeline::createVulkanGraphicsPipeline() {
            JTEchars vertShaderCode =
                R"(
            #version 450

            layout(location = 0) in vec2 inPosition;
            layout(location = 1) in vec3 inColor;

            layout(location = 0) out vec3 fragColor;

            void main() {
                gl_Position = vec4(inPosition, 0.0, 1.0);
                fragColor = inColor;
            }
            )";

            JTEchars fragShaderCode =
                R"(
            #version 450

            layout(location = 0) in vec3 fragColor;

            layout(location = 0) out vec4 outColor;

            void main() {
                outColor = vec4(fragColor, 1.0);
            }
            )";

            VkShaderModule vertexShader = JTEVulkanUtils::createShaderModule(this->m_JVdevice.getVulkanLogicalDevice(), vertShaderCode, "Vertex Shader created.", "Vertex Shader not created.", shaderc_glsl_vertex_shader);
            VkShaderModule fragmentShader = JTEVulkanUtils::createShaderModule(this->m_JVdevice.getVulkanLogicalDevice(), fragShaderCode, "Fragment Shader created.", "Fragment Shader not created.", shaderc_glsl_fragment_shader);

            VkPipelineShaderStageCreateInfo vkVertexShaderStageInfo{};
            vkVertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            vkVertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
            vkVertexShaderStageInfo.module = vertexShader;
            vkVertexShaderStageInfo.pName = "main";

            VkPipelineShaderStageCreateInfo vkFragmentShaderStageInfo{};
            vkFragmentShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            vkFragmentShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            vkFragmentShaderStageInfo.module = fragmentShader;
            vkFragmentShaderStageInfo.pName = "main";

            VkPipelineShaderStageCreateInfo vkShaderStageInfo[] = { vkVertexShaderStageInfo, vkFragmentShaderStageInfo };

            VkPipelineVertexInputStateCreateInfo vkVertexInputStateInfo{};
            vkVertexInputStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            VkVertexInputBindingDescription bindingDescription = JTEVulkanUtils::Vertex::getBindingDescription();
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = JTEVulkanUtils::Vertex::getAttributeDescriptions();
            vkVertexInputStateInfo.vertexBindingDescriptionCount = 1;
            vkVertexInputStateInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
            vkVertexInputStateInfo.pVertexBindingDescriptions = &bindingDescription;
            vkVertexInputStateInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

            VkPipelineInputAssemblyStateCreateInfo vkInputAssemblyStateInfo{};
            vkInputAssemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            vkInputAssemblyStateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
            vkInputAssemblyStateInfo.primitiveRestartEnable = VK_FALSE;

            VkPipelineViewportStateCreateInfo vkViewportStateInfo{};
            vkViewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            vkViewportStateInfo.viewportCount = 1;
            vkViewportStateInfo.scissorCount = 1;

            VkPipelineRasterizationStateCreateInfo vkRasterizationStateInfo{};
            vkRasterizationStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
            vkRasterizationStateInfo.depthClampEnable = VK_FALSE;
            vkRasterizationStateInfo.rasterizerDiscardEnable = VK_FALSE;
            vkRasterizationStateInfo.polygonMode = VK_POLYGON_MODE_FILL;
            vkRasterizationStateInfo.lineWidth = 1.0f;
            vkRasterizationStateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
            vkRasterizationStateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
            vkRasterizationStateInfo.depthBiasEnable = VK_FALSE;

            VkPipelineMultisampleStateCreateInfo vkMultisampleStateInfo{};
            vkMultisampleStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            vkMultisampleStateInfo.sampleShadingEnable = VK_FALSE;
            vkMultisampleStateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

            VkPipelineColorBlendAttachmentState vkColorBlendAttachmentState{};
            vkColorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
            vkColorBlendAttachmentState.blendEnable = VK_FALSE;

            VkPipelineColorBlendStateCreateInfo vkColorBlendStateInfo{};
            vkColorBlendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
            vkColorBlendStateInfo.logicOpEnable = VK_FALSE;
            vkColorBlendStateInfo.logicOp = VK_LOGIC_OP_COPY;
            vkColorBlendStateInfo.attachmentCount = 1;
            vkColorBlendStateInfo.pAttachments = &vkColorBlendAttachmentState;
            vkColorBlendStateInfo.blendConstants[0] = 0.0f;
            vkColorBlendStateInfo.blendConstants[1] = 0.0f;
            vkColorBlendStateInfo.blendConstants[2] = 0.0f;
            vkColorBlendStateInfo.blendConstants[3] = 0.0f;

            std::vector<VkDynamicState> vkDynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

            VkPipelineDynamicStateCreateInfo vkDynamicStateInfo{};
            vkDynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
            vkDynamicStateInfo.dynamicStateCount = static_cast<JTEuint>(vkDynamicStates.size());
            vkDynamicStateInfo.pDynamicStates = vkDynamicStates.data();

            VkPipelineLayoutCreateInfo vkPipelineLayoutInfo{};
            vkPipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
            vkPipelineLayoutInfo.setLayoutCount = 0;
            vkPipelineLayoutInfo.pushConstantRangeCount = 0;

            VkResult layoutResult = vkCreatePipelineLayout(this->m_JVdevice.getVulkanLogicalDevice(), &vkPipelineLayoutInfo, nullptr, &this->m_PipelineLayout);
            if (layoutResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Graphics Pipeline Layout not created."); }
            else { JTEUtilities::println("Vulkan Graphics Pipeline Layout created."); }

            VkGraphicsPipelineCreateInfo vkGraphicsPipelineInfo{};
            vkGraphicsPipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
            vkGraphicsPipelineInfo.stageCount = 2;
            vkGraphicsPipelineInfo.pStages = vkShaderStageInfo;
            vkGraphicsPipelineInfo.pVertexInputState = &vkVertexInputStateInfo;
            vkGraphicsPipelineInfo.pInputAssemblyState = &vkInputAssemblyStateInfo;
            vkGraphicsPipelineInfo.pViewportState = &vkViewportStateInfo;
            vkGraphicsPipelineInfo.pRasterizationState = &vkRasterizationStateInfo;
            vkGraphicsPipelineInfo.pMultisampleState = &vkMultisampleStateInfo;
            vkGraphicsPipelineInfo.pColorBlendState = &vkColorBlendStateInfo;
            vkGraphicsPipelineInfo.pDynamicState = &vkDynamicStateInfo;
            vkGraphicsPipelineInfo.layout = this->m_PipelineLayout;
            vkGraphicsPipelineInfo.renderPass = this->m_JVrenderpass.getVulkanRenderPass();
            vkGraphicsPipelineInfo.subpass = 0;

            VkResult pipelineResult = vkCreateGraphicsPipelines(this->m_JVdevice.getVulkanLogicalDevice(), VK_NULL_HANDLE, 1, &vkGraphicsPipelineInfo, nullptr, &this->m_GraphicsPipeline);
            if (pipelineResult != VK_SUCCESS) { JTEUtilities::println("Vulkan Graphics Pipeline not created."); }
            else { JTEUtilities::println("Vulkan Graphics Pipeline created."); }

            vkDestroyShaderModule(this->m_JVdevice.getVulkanLogicalDevice(), vertexShader, nullptr);
            vkDestroyShaderModule(this->m_JVdevice.getVulkanLogicalDevice(), fragmentShader, nullptr);
		}

		void JTEVulkanGraphicsPipeline::terminateVulkanGraphicsPipeline() {
            vkDestroyPipeline(this->m_JVdevice.getVulkanLogicalDevice(), this->m_GraphicsPipeline, nullptr);
            JTEUtilities::println("Vulkan Graphics Pipeline terminated.");
            vkDestroyPipelineLayout(this->m_JVdevice.getVulkanLogicalDevice(), this->m_PipelineLayout, nullptr);
            JTEUtilities::println("Vulkan Graphics Pipeline Layout terminated.");
		}

		VkPipelineLayout JTEVulkanGraphicsPipeline::getVulkanPipelineLayout() {
            return this->m_PipelineLayout;
		}

		VkPipeline JTEVulkanGraphicsPipeline::getVulkanGraphicsPipeline() {
            return this->m_GraphicsPipeline;
		}

	}

}