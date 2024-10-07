#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include "hello_triangle.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// validation layers:
const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;
        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) return false;
    }
    return true;
}

void hello_triangle::initWindow() {
    glfwInit();
    // Tell GLFW not to use OpenGL.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // Tell GLFW that the window shouldn't be resizable.
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // Creating the window
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Hello", nullptr, nullptr);
}

void hello_triangle::initVulkan() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    // required on macOS
    std::vector<const char*> requiredExtensions;
    requiredExtensions.reserve(glfwExtensionCount);
    for(uint32_t i = 0; i < glfwExtensionCount; i++) {
        requiredExtensions.emplace_back(glfwExtensions[i]);
    }
    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    // validation layers
#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
    if (enableValidationLayers) {
        if (!checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
#pragma clang diagnostic pop
    // TODO define a callback function:
    // https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Validation_layers#page_Message-callback

    // creating the instance
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

void hello_triangle::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void hello_triangle::cleanup() {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}
