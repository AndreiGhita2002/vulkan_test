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

    void initWindow();
    void initVulkan();
    void createVkInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void setupDebugMessenger();
    void mainLoop();
    void cleanup();
};


#endif //VULKAN_TEST_HELLO_TRIANGLE_H
