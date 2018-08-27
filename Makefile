VULKAN_SDK_PATH = /home/aaron/vulkan_sdk/1.1.82.1/x86_64
CXXFLAGS = -std=c++11 -I$(VULKAN_SDK_PATH)/include
#LDFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan
LDFLAGS = -lvulkan
CXX_DEBUG_FLAGS = $(CXXFLAGS) -DENABLE_DEBUG
SRC_FILES = src/main.cpp src/Renderer.cpp src/ErrorUtils.cpp

all: src/main.cpp
	g++ $(CXXFLAGS) -o bin/vulkan $(SRC_FILES) $(LDFLAGS) -O3

debug: src/main.cpp
	g++ $(CXX_DEBUG_FLAGS) -o bin/vulkan $(SRC_FILES) $(LDFLAGS) -ggdb

.PHONY: test clean

test: clean debug
	./bin/vulkan

clean:
	rm -f bin/*
