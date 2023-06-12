#include "pch.h"
#include "JTEEngine/JTEEngine.h"


namespace JTEEngine {

    //===== Constructor =====// 
    
    JTEQuad::JTEQuad(JTEuint x, JTEuint y, JTEuint width, JTEuint height, std::array<JTEfloat, 4> color, JTEWindow& JWindow, JTEVulkanObjects& JVObjects, JTERenderer& JVRender) {
        this->m_X = static_cast<JTEfloat>(x);
        this->m_Y = static_cast<JTEfloat>(y);
        this->m_Width = static_cast<JTEfloat>(width);
        this->m_Height = static_cast<JTEfloat>(height);
    
        this->JWindow = JWindow;
        this->JRenderer = JVRender;
    
        this->m_Colors[0] = (float)color[0] / 255;
        this->m_Colors[1] = (float)color[1] / 255;
        this->m_Colors[2] = (float)color[2] / 255;
    
        std::array<JTEuint, 2> winSize = JWindow.getWindowDimensions();
    
        this->m_HalfWidth = (float)winSize[0] / 2;
        this->m_HalfHeight = (float)winSize[1] / 2;
    
        JTEfloat X = (1 - (this->m_X / this->m_HalfWidth)) * -1;
        JTEfloat Y = (1 - (this->m_Y / this->m_HalfHeight));
    
        JTEfloat WIDTH = (this->m_Width / this->m_HalfWidth);
        JTEfloat HEIGHT = (this->m_Height / this->m_HalfHeight);
    
        std::array<JTEfloat, 20> vertices = {
            X, Y,                   m_Colors[0], m_Colors[1], m_Colors[2],
            X + WIDTH, Y,           m_Colors[0], m_Colors[1], m_Colors[2],
            X + WIDTH, Y - HEIGHT,  m_Colors[0], m_Colors[1], m_Colors[2],
            X ,Y - HEIGHT,          m_Colors[0], m_Colors[1], m_Colors[2]
        };
        std::array<uint16_t, 6> indices = {
            0, 1, 3, 3, 1, 2
        };
    
        this->m_Vertices = vertices;
        this->m_Indices = indices;
    
        this->m_BufferSizeV = sizeof(this->m_Vertices[0]) * this->m_Vertices.size();
        this->m_BufferSizeI = sizeof(this->m_Indices[0]) * this->m_Indices.size();
    
        //===== Creating Vertex Buffer =====//
    
        JTEVulkan::JTEVulkanUtils::createBuffer(this->m_BufferSizeV, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, this->m_VertexBuffer, this->m_VertexBufferMemory, JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanPhysicalDevice());
        JTEVulkan::JTEVulkanUtils::createBuffer(this->m_BufferSizeV, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, this->m_StagingBufferV, this->m_StagingBufferMemoryV, JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanPhysicalDevice());
    
        //===== Creating Index Buffer =====//
    
        JTEVulkan::JTEVulkanUtils::createBuffer(this->m_BufferSizeI, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, this->m_IndexBuffer, this->m_IndexBufferMemory, JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanPhysicalDevice());
        JTEVulkan::JTEVulkanUtils::createBuffer(this->m_BufferSizeI, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, this->m_StagingBufferI, this->m_StagingBufferMemoryI, JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanPhysicalDevice());
        
        //===== Loading Vertex Buffer =====//
    
        void* dataV;
        vkMapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryV, 0, this->m_BufferSizeV, 0, &dataV);
        memcpy(dataV, vertices.data(), (size_t)this->m_BufferSizeV);
        vkUnmapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryV);
        JTEVulkan::JTEVulkanUtils::copyBuffer(this->m_StagingBufferV, this->m_VertexBuffer, this->m_BufferSizeV, JVObjects.commandbuffers.getVulkanCommandPool(), JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanGraphicsQueue());
    
        //===== Loading Index Buffer =====//
    
        void* dataI;
        vkMapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryI, 0, this->m_BufferSizeI, 0, &dataI);
        memcpy(dataI, this->m_Indices.data(), (size_t)this->m_BufferSizeI);
        vkUnmapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryI);
        JTEVulkan::JTEVulkanUtils::copyBuffer(this->m_StagingBufferI, this->m_IndexBuffer, this->m_BufferSizeI, JVObjects.commandbuffers.getVulkanCommandPool(), JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanGraphicsQueue());
    }
    
    //===== Public Functions =====//
    
    void JTEQuad::update(JTEVulkanObjects& JVObjects) {
        bool changed = false;
    
        JTEfloat X = (1 - (static_cast<JTEfloat>(this->m_X) / this->m_HalfWidth)) * -1;
        JTEfloat Y = (1 - ((float)this->m_Y / this->m_HalfHeight));
    
        JTEfloat WIDTH = (this->m_Width / this->m_HalfWidth);
        JTEfloat HEIGHT = (this->m_Height / this->m_HalfHeight);
    
        std::array<JTEfloat, 20> vertices = {
            X, Y,                   m_Colors[0], m_Colors[1], m_Colors[2],
            X + WIDTH, Y,           m_Colors[0], m_Colors[1], m_Colors[2],
            X + WIDTH, Y - HEIGHT,  m_Colors[0], m_Colors[1], m_Colors[2],
            X ,Y - HEIGHT,          m_Colors[0], m_Colors[1], m_Colors[2]
        };
        std::array<uint16_t, 6> indices = {
            0, 1, 3, 3, 1, 2
        };
    
        changed = std::equal(this->m_Vertices.begin(), this->m_Vertices.end(), vertices.begin());
    
        if (!changed) {  
            this->m_Vertices = vertices;
            changed = true;
    
            //===== Updating Vertex Buffer =====//
    
            void* dataV;
            vkMapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryV, 0, this->m_BufferSizeV, 0, &dataV);
            memcpy(dataV, vertices.data(), (size_t)this->m_BufferSizeV);
            vkUnmapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryV);
            JTEVulkan::JTEVulkanUtils::copyBuffer(this->m_StagingBufferV, this->m_VertexBuffer, this->m_BufferSizeV, JVObjects.commandbuffers.getVulkanCommandPool(), JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanGraphicsQueue());
    
    
            //===== Updating Index Buffer =====//
    
            void* dataI;
            vkMapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryI, 0, this->m_BufferSizeI, 0, &dataI);
            memcpy(dataI, this->m_Indices.data(), (size_t)this->m_BufferSizeI);
            vkUnmapMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryI);
            JTEVulkan::JTEVulkanUtils::copyBuffer(this->m_StagingBufferI, this->m_IndexBuffer, this->m_BufferSizeI, JVObjects.commandbuffers.getVulkanCommandPool(), JVObjects.device.getVulkanLogicalDevice(), JVObjects.device.getVulkanGraphicsQueue());
        }
    }
    
    void JTEQuad::render(JTEVulkanObjects& JVObjects, JTERenderer& render) {
        VkBuffer vertexBuffers[] = { m_VertexBuffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(JVObjects.commandbuffers.getVulkanCommandBuffers()[render.getCurrentFrame()], 0, 1, &this->m_VertexBuffer, offsets);
        vkCmdBindIndexBuffer(JVObjects.commandbuffers.getVulkanCommandBuffers()[render.getCurrentFrame()], this->m_IndexBuffer, 0, VK_INDEX_TYPE_UINT16);
        vkCmdDrawIndexed(JVObjects.commandbuffers.getVulkanCommandBuffers()[render.getCurrentFrame()], static_cast<JTEuint>(this->m_Indices.size()), 1, 0, 0, 0);
    }
    
    void JTEQuad::erase(JTEVulkanObjects& JVObjects) {
        vkDestroyBuffer(JVObjects.device.getVulkanLogicalDevice(), this->m_IndexBuffer, nullptr);
        vkFreeMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_IndexBufferMemory, nullptr);
        vkDestroyBuffer(JVObjects.device.getVulkanLogicalDevice(), this->m_VertexBuffer, nullptr);
        vkFreeMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_VertexBufferMemory, nullptr);
    
        vkDestroyBuffer(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferI, nullptr);
        vkFreeMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryI, nullptr);
        vkDestroyBuffer(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferV, nullptr);
        vkFreeMemory(JVObjects.device.getVulkanLogicalDevice(), this->m_StagingBufferMemoryV, nullptr);
    }
    
    //===== Getters =====//

    JTEint JTEQuad::getX() {
        return static_cast<JTEint>(this->m_X);
    }

    JTEint JTEQuad::getY() {
        return static_cast<JTEint>(this->m_Y);
    }

    JTEint JTEQuad::getWidth() {
        return static_cast<JTEint>(this->m_Width);
    }

    JTEint JTEQuad::getHeight() {
        return static_cast<JTEint>(this->m_Height);
    }
    
    //===== Setters =====//
    
    void JTEQuad::setX(JTEint x) {
        this->m_X = static_cast<JTEfloat>(x);
    }
    
    void JTEQuad::setY(JTEint y) {
        this->m_Y = static_cast<JTEfloat>(y);
    }
    
    void JTEQuad::setWidth(JTEint width) {
        this->m_Width = static_cast<JTEfloat>(width);
    }
    
    void JTEQuad::setHeight(JTEint height) {
        this->m_Height = static_cast<JTEfloat>(height);
    }

}