### Silfur Engine ###
project(Silfur)

### Source files ###
FILE(GLOB_RECURSE SRC_FILES "src/*.cpp")

### Generate target ###
add_library(${PROJECT_NAME} ${SRC_FILES})

### Compile definitions and features ###
target_compile_definitions(${PROJECT_NAME} PUBLIC SF_CORE)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

### Precompiled headers ###
target_precompile_headers(${PROJECT_NAME} PUBLIC "src/sfpch.hpp")

### Dependencies ###
# GLFW
add_subdirectory(vendor/GLFW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw "${GLFW_LIBRARIES}")

# Vulkan SDK
if (NOT VULKAN_SDK_ROOT)
    # Vulkan SDK path not set, trying to find it automatically

    find_package(Vulkan)

    if (VULKAN_FOUND)
        # find_package() found Vulkan
        message(STATUS "Vulkan found automatically")

        set(VULKAN_SDK_INCLUDE "${Vulkan_INCLUDE_DIRS}")
        set(VULKAN_SDK_LIB "${Vulkan_LIBRARIES}")
    endif ()
endif ()

if (NOT VULKAN_FOUND)
    # If not found automatically by find_package(), try another way
    message(STATUS "Vulkan not found automatically by find_package(), try manually")

    if (NOT VULKAN_SDK_ROOT AND WIN32)
        # If under Windows with the path not manually set, try to locate it from the environment variable
        set(VULKAN_SDK_ROOT "$ENV{VULKAN_SDK}")
    endif ()

    if (VULKAN_SDK_ROOT)
        # SDK path has been defined

        if (WIN32)
            string(REPLACE "\\" "/" VULKAN_SDK_ROOT ${VULKAN_SDK_ROOT})
            set(VULKAN_SDK_INCLUDE "${VULKAN_SDK_ROOT}/Include")
            set(VULKAN_SDK_LIB "${VULKAN_SDK_ROOT}/Lib/vulkan-1.lib")
        endif ()

        if (EXISTS "${VULKAN_SDK_INCLUDE}/vulkan/vulkan.h" AND EXISTS "${VULKAN_SDK_LIB}")
            set(VULKAN_FOUND ON)
        endif ()
    endif ()
endif ()

if (VULKAN_FOUND)
    message(STATUS "Vulkan configuration :")
    if (VULKAN_SDK_ROOT)
        message(STATUS "  - Root path: ${VULKAN_SDK_ROOT}")
    endif ()
    message(STATUS "  - Include: ${VULKAN_SDK_INCLUDE}")
    message(STATUS "  - Library: ${VULKAN_SDK_LIB}")

    # Including & linking the Vulkan SDK

    target_include_directories(${PROJECT_NAME} PUBLIC "${VULKAN_SDK_INCLUDE}")
    target_link_libraries(${PROJECT_NAME} PUBLIC "${VULKAN_SDK_LIB}")
endif()

# Stb
target_sources(${PROJECT_NAME} PRIVATE "vendor/stb/stb_image.cpp")

### Includes ###
target_include_directories(${PROJECT_NAME} PUBLIC "src")
target_include_directories(${PROJECT_NAME} PUBLIC "vendor/portable-snippets")
target_include_directories(${PROJECT_NAME} PUBLIC "vendor/spdlog/include")
target_include_directories(${PROJECT_NAME} PUBLIC "vendor/glm")
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/GLFW/include")
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/stb")
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/tinyobjloader")
