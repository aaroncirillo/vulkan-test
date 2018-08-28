#include "Renderer.h"

int main() {
    Renderer r;

    VkCommandPool commandPool;
    VkCommandPoolCreateInfo poolCreateInfo {};
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.queueFamilyIndex = r.getGraphicsFamilyIndex();
    poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    vkCreateCommandPool(r.getDevice(), &poolCreateInfo, nullptr, &commandPool);
    
    VkCommandBuffer commandBuffer;
    VkCommandBufferAllocateInfo commandBufferAllocateInfo {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = commandPool;
    commandBufferAllocateInfo.commandBufferCount = 1;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    vkAllocateCommandBuffers(r.getDevice(), &commandBufferAllocateInfo, &commandBuffer);
    VkCommandBufferBeginInfo beginInfo {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    vkBeginCommandBuffer(commandBuffer, &beginInfo);
    vkEndCommandBuffer(commandBuffer);
    VkSubmitInfo submitInfo {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    vkQueueSubmit(r.getQueue(), 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(r.getQueue());
    vkDestroyCommandPool(r.getDevice(), commandPool, nullptr);
    return 0;
}