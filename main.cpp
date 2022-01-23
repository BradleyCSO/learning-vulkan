#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

/* Class to store Vulkan objects as private class members and add functions to initiate each of them */
class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    /* Create pointer variable named window */
    GLFWwindow* window;

    /* Function calls */
    void initWindow() {
        glfwInit(); // Initialise GLFW library

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable resized windows

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }
    void initVulkan() {

    }
    /* Frame rendering */
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents(); /* Keep application running until either an error occurs or window is closed */
        }
    }
    /* Resource deallocation - Release resources that we've used */
    void cleanup() {
        glfwDestroyWindow(window); // Destroy used resource
        glfwTerminate(); // Terminate GLFW
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl; // Describe error. Common one might be a certain required extension is not supported
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}