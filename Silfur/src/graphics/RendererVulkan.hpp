#pragma once

#ifndef __SILFUR_GRAPHICS_RENDERER_VULKAN_HPP__
#define __SILFUR_GRAPHICS_RENDERER_VULKAN_HPP__

#include "core/window/Window.hpp"
#include "graphics/vulkan/Instance.hpp"

#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include <optional>
#include <vector>
#include <array>

struct GLFWwindow;

namespace Silfur
{
    //////////////////////////////////////////
    //// Vertex Definition + Input layout ////
    //////////////////////////////////////////

    struct Vertex
    {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindingDescription()
        {
            VkVertexInputBindingDescription bindingDescription = {};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
        {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }

        bool operator==(const Vertex& p_Other) const
        {
            return (pos == p_Other.pos && color == p_Other.color && texCoord == p_Other.texCoord);
        }
    };

    struct UniformBufferObject
    {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> transferFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value()
                && presentFamily.has_value()
                && transferFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentMode;
    };

    class Renderer
    {
    public:
        Renderer(const Window& p_window, const std::string& p_appName,
            const Version& p_appVersion);
        ~Renderer();

        void drawFrame();
        void updateUniformBuffer(uint32_t p_CurrentImage);

    private:
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice p_device);

        void createInstance(const std::string& p_appName, const Version& p_appVersion);
        void selectPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice p_device);
        void createLogicalDevice();

        void createSwapChain();
        void createImageViews();
        void createFrameBuffers();
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice p_device);
        VkSurfaceFormatKHR selectSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& p_availableFormats);
        VkPresentModeKHR selectSwapPresentMode(const std::vector<VkPresentModeKHR>& p_availablePresentModes);
        VkExtent2D selectSwapExtent(const VkSurfaceCapabilitiesKHR& p_capabilities);
        void cleanUpSwapChain();
        void recreateSwapChain();

        void CreateSyncObjects();
        void transitionImageLayout(VkImage p_Image, VkFormat p_Format, VkImageLayout p_OldLayout,
            VkImageLayout p_NewLayout, uint32_t p_MipLevels);

        void createDescriptorPool();
        void createDescriptorSetLayout();
        void createDescriptorSets();

        VkShaderModule createShaderModule(const std::vector<char>& p_Code);

        void createRenderPass();

        void createGraphicsPipeline();
        
        void createCommandPools();
        void createCommandBuffers();
        VkCommandBuffer beginSingleTimeCommands(VkCommandPool p_CommandPool);
        void endSingleTimeCommands(VkQueue p_Queue, VkCommandPool p_CommandPool, VkCommandBuffer p_CommandBuffer);

        void createDepthResources();
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat p_Format);

        void createVertexBuffer();
        void createIndexBuffer();
        void createUniformBuffers();

        void createTextureImage();
        void createTextureImageView();
        void createTextureSampler();
        void generateMipMaps(VkImage p_Image, VkFormat p_ImageFormat, uint32_t p_Width, uint32_t p_Height, uint32_t p_MipLevels);

        void createColorResources(); // For Multisampling

        void createBuffer(VkDeviceSize p_Size, VkBufferUsageFlags p_Usage, VkMemoryPropertyFlags p_Properties,
            VkBuffer& p_Buffer, VkDeviceMemory& p_BufferMemory);
        void createImage(uint32_t p_Width, uint32_t p_Height, uint32_t p_MipLevels, VkSampleCountFlagBits p_numSamples,
            VkFormat p_Format, VkImageTiling p_Tiling, VkImageUsageFlags p_Usage, VkMemoryPropertyFlags p_Properties,
            VkImage& p_Image, VkDeviceMemory& p_ImageMemory);
        VkImageView createImageView(VkImage p_Image, VkFormat p_Format, VkImageAspectFlags p_AspectFlags, uint32_t p_MipLevels);
        void copyBuffer(VkBuffer p_SrcBuffer, VkBuffer p_DstBuffer, VkDeviceSize p_Size);
        void copyBufferToImage(VkBuffer p_Buffer, VkImage p_Image, uint32_t p_Width, uint32_t p_Height);
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        VkFormat findSupportedFormat(const std::vector<VkFormat>& p_Candidates, VkImageTiling p_Tiling,
            VkFormatFeatureFlags p_Features);
        VkSampleCountFlagBits getMaxUsableSampleCount();
        std::vector<char> readFile(const std::string& p_Filename);

        void loadModel();

        void OnWindowResized(Event& p_event);
    private:
        int m_MaxFramesInFlight = 3; // Triple buffering

        Window m_Window;

        std::vector<Vertex> m_Vertices {};
        std::vector<uint32_t> m_Indices {};

        bool m_FramebufferResized = false;

        // Vulkan resources
        static Vk::Instance s_Instance;
        VkSurfaceKHR m_Surface {};
        VkPhysicalDevice m_PhysicalDevice {};
        VkDevice m_Device {};

        VkSampleCountFlagBits m_MsaaSamples = VK_SAMPLE_COUNT_1_BIT;

        VkQueue m_GraphicsQueue {};
        VkQueue m_PresentQueue {};
        VkQueue m_TransferQueue {};

        VkSwapchainKHR m_SwapChain {};
        std::vector<VkImage> m_SwapChainImages {};
        VkFormat m_SwapChainImageFormat {};
        VkExtent2D m_SwapChainExtent {};
        std::vector<VkImageView> m_SwapChainImageViews {};
        std::vector<VkFramebuffer> m_SwapChainFramebuffers {};

        VkRenderPass m_RenderPass {};
        VkDescriptorSetLayout m_DescriptorSetLayout {};
        VkPipelineLayout m_PipelineLayout {};
        VkPipeline m_GraphicsPipeline {};

        VkDescriptorPool m_DescriptorPool {};
        std::vector<VkDescriptorSet> m_DescriptorSets {};

        VkCommandPool m_GraphicsCommandPool {};
        VkCommandPool m_TransferCommandPool {};
        std::vector<VkCommandBuffer> m_CommandBuffers {};

        VkImage m_DepthImage {};
        VkDeviceMemory m_DepthImageMemory {};
        VkImageView m_DepthImageView {};

        // For multisampling
        VkImage m_ColorImage {};
        VkDeviceMemory m_ColorImageMemory {};
        VkImageView m_ColorImageView {};

        VkBuffer m_VertexBuffer {};
        VkDeviceMemory m_VertexBufferMemory {};
        VkBuffer m_IndexBuffer {};
        VkDeviceMemory m_IndexBufferMemory {};

        std::vector<VkBuffer> m_UniformBuffers {};
        std::vector<VkDeviceMemory> m_UniformBuffersMemory {};

        uint32_t m_MipLevels {};
        VkImage m_TextureImage {};
        VkDeviceMemory m_TextureImageMemory {};
        VkImageView m_TextureImageView {};
        VkSampler m_TextureSampler {};

        std::vector<VkSemaphore> m_ImageAvailableSemaphore {};
        std::vector<VkSemaphore> m_RenderFinishedSemaphore {};
        std::vector<VkFence> m_inFlightFences {};
        std::vector<VkFence> m_ImagesInFlight {};
        size_t m_CurrentFrame {};
    };
}

// Extend std for hash Vertex type
namespace std
{
    template<>
    struct hash<Silfur::Vertex>
    {
        size_t operator()(Silfur::Vertex const& p_Vertex) const
        {
            return ((hash<glm::vec3>()(p_Vertex.pos) ^
                (hash<glm::vec3>()(p_Vertex.color) << 1)) >> 1) ^
                (hash<glm::vec2>()(p_Vertex.texCoord) << 1);
        }
    };
}

#endif // __SILFUR_GRAPHICS_RENDERER_VULKAN_HPP__
