VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["GLFW"] = "%{wks.location}/vendor/GLFW/lib-vc2022"

-- Vulkan-related link sets
VulkanLinks = {}

VulkanLinks.Common =
{
    "vulkan-1",
}

VulkanLinks.Debug =
{
    "SPIRVd",
    "SPIRV-Toolsd",
    "SPIRV-Tools-diffd",
    "SPIRV-Tools-optd",
    "glslangd",
    "OSDependentd",
    "GenericCodeGend",
    "MachineIndependentd",
    "glslang-default-resource-limitsd",
}

VulkanLinks.Release =
{
    "SPIRV",
    "SPIRV-Tools",
    "SPIRV-Tools-diff",
    "SPIRV-Tools-opt",
    "glslang",
    "OSDependent",
    "GenericCodeGen",
    "MachineIndependent",
    "glslang-default-resource-limits",
}