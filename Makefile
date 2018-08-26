VULKAN_SDK_PATH = /home/aaron/vulkan_sdk/1.1.82.1/x86_64
CFLAGS = -std=c++11 -I$(VULKAN_SDK_PATH)/include
#LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
LDFLAGS = -lvulkan

all: src/main.cpp
	g++ $(CFLAGS) -o vulkan src/main.cpp src/Renderer.cpp $(LDFLAGS) -ggdb

.PHONY: test clean

test: all
	./vulkan

clean:
	rm -f vulkan
