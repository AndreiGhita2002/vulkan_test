#ifndef VULKAN_TEST_HELLO_TRIANGLE_H
#define VULKAN_TEST_HELLO_TRIANGLE_H

/*
 * hello_triangle
 *
 * Basic vulkan program for drawing a triangle on screen.
 *
 * From this tutorial: https://vulkan-tutorial.com/
 */
class hello_triangle {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
private:
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkDevice device; // logical device
    VkQueue graphicsQueue;
    VkSurfaceKHR surface;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;
    const int MAX_FRAMES_IN_FLIGHT = 2;

    void initWindow();
    void initVulkan();
    void createVkInstance();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void setupDebugMessenger();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffer();
    void recordCommandBuffer(VkCommandBuffer cmdBuffer, uint32_t imageIndex);
    void createSyncObjects();
    void drawFrame();
    void mainLoop();
    void cleanup();
};


#endif //VULKAN_TEST_HELLO_TRIANGLE_H
