#pragma once
#include <vulkan/vulkan_core.h>

namespace FFVk
{
    VkShaderModule CreateShaderModuleFromBinary(VkDevice& device, const char* fileName);
    VkShaderModule CreateShaderModuleFromText(VkDevice& device, const char* fileName);
}
