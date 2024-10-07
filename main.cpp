#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include "hello_triangle.h"


int hello_triangle_main() {
    hello_triangle app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int test_glfw() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";
    auto *pProperties = static_cast<VkExtensionProperties *>
    (malloc(extensionCount *sizeof(VkExtensionProperties)));
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, pProperties);
    for (int i = 0; i < extensionCount; ++i) {
        std::cout << pProperties[i].extensionName << ", ver:" << pProperties[i].specVersion << "\n";
    }
    free(pProperties);

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}

int main() {
//    return test_glfw();
    return hello_triangle_main();
}