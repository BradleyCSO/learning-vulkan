#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

/* Enable standard diagnostics layer provided by the Vulkan SDK */
const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false; // Disable validation layers if not being compiled in debug mode
#else
    const bool enableValidationLayers = true; // Enable validation layers if being compiled in debug mode
#endif

/* Checks if all the requested layers are available */
bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    /* Checks if all the layers in validationLayers exist in the availableLayers list */
    for (const char* layerName : validationLayers) {
        bool layerFound = false; // Initial declared value of false

        for (const auto &layerProperties: availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }
        return true;
}

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
    GLFWwindow* window; // Create pointer variable named window

    VkInstance instance; // Create VKInstance member to hold the handle to the instance

    /* Function calls */
    void initWindow() {
        glfwInit(); // Initialise GLFW library

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable resized windows

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
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

    void createInstance() {
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        /* Optional - Create VkApplicationInfo struct to fill information about the application */
        VkApplicationInfo appInfo{}; // Create appInfo struct
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        /* Essential - Tells the Vulkan driver which global extensions and validations to use */
        VkInstanceCreateInfo createInfo{}; // Create createInfo struct
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        /* GLFW - Interface with window system via a function that returns the extension(s) needed by passing to the struct */
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        /* Include validation layer names if they are enabled */
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        // Now have everything Vulkan needs to create an instance, so issue the vkCreateInstance call (no need to store the result)
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        };
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