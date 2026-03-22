#include "FFVulkan/Vulkan.h"

#include "FFCore/Core/Assert.h"
#include "FFCore/Core/Types.h"

void FFVk::Vulkan::InitVulkan()
{
   // constexpr vk::ApplicationInfo appInfo
   // {
   //     .pApplicationName   = "FF Engine",
   //     .applicationVersion = VK_MAKE_VERSION( 1, 0, 0 ),
   //     .pEngineName        = "FF Engine",
   //     .engineVersion      = VK_MAKE_VERSION( 1, 0, 0 ),
   //     .apiVersion         = vk::ApiVersion14
   // };

    // Get the required instance extensions from GLFW.
    u32 glfwExtensionCount = 0;
    auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // Check if the required GLFW extensions are supported by the Vulkan implementation.
    auto extensionProperties = _context.enumerateInstanceExtensionProperties();
    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        if (std::ranges::none_of(extensionProperties,
                                 [glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
                                 { return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
        {
            ASSERT_NO_ENTRY("Required GLFW extension not supported: %s", std::string(glfwExtensions[i]))
        }
    }
}
