#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>

const std::vector<const char*> g_validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};
#ifdef _DEBUG
const bool g_enableValidationLayers = true;
#else
const bool g_enableValidationLayers = false;
#endif

struct Debug
{
	VkDebugUtilsMessengerEXT m_debugMessenger;

	//Create a function for the vkGetInstancePorcAddr for the callback
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	//Setup a structure of with debug messages/info
	static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void SetupDebugMessenger();

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	void DestroyDebugUtils();
};

//CALL IN  CREATE INSTANCE
/*
 *    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
		if (g_enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(g_validationLayers.size());
			createInfo.ppEnabledLayerNames = g_validationLayers.data();

			PopulateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
		{
			createInfo.enabledLayerCount = 0;

			createInfo.pNext = nullptr;
		}
 */
