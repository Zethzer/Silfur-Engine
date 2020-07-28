### Silfur Engine ###
project(Silfur)

### Source files ###
FILE(GLOB_RECURSE SRC_FILES "src/*.cpp")

### Generate target ###
add_library(${PROJECT_NAME} ${SRC_FILES})

### Compile definitions and features ###
target_compile_definitions(${PROJECT_NAME} PRIVATE SF_CORE)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "Debug configuration")
    target_compile_definitions(${PROJECT_NAME} PUBLIC SF_CONFIG_DEBUG)
endif()

### Precompiled headers ###
target_precompile_headers(${PROJECT_NAME} PUBLIC "src/sfpch.hpp")

### Dependencies ###
# SDL2
if (WIN32)
    # Configure manually on Windows
    set(SDL2_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2")

    target_include_directories(${PROJECT_NAME} PUBLIC "${SDL2_PATH}/include")

    target_link_directories(${PROJECT_NAME} PUBLIC "${SDL2_PATH}/lib")

    if(MINGW)
        # MINGW SDL2 Dependencies in SHARED - Not use for the moment
        # set(SDL2_EXTRA_LINK_FLAGS "-lmingw32 -lSDL2main -lSDL2 -mwindows")

        # MINGW SDL2 dependencies in STATIC
        set(SDL2_EXTRA_LINK_FLAGS_STATIC "-lmingw32 -lSDL2main -lSDL2 -mwindows  -Wl,--no-undefined -Wl,--dynamicbase
        -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32
        -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc")

        target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_EXTRA_LINK_FLAGS_STATIC})
    else(MSVC)
        target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2)
    endif()
endif()

# Vulkan SDK
if (NOT VULKAN_SDK_ROOT)
    # Vulkan SDK path not set, trying to find it automatically

    find_package(Vulkan)

    if (VULKAN_FOUND)
        # find_package() found Vulkan
        message(STATUS "Vulkan found automatically")

        set(VULKAN_SDK_INCLUDE "${Vulkan_INCLUDE_DIRS}")
        set(VULKAN_SDK_LIB "${Vulkan_LIBRARIES}")
    endif()
endif()

if (NOT VULKAN_FOUND)
    # If not found automatically by find_package(), try another way
    message(STATUS "Vulkan not found automatically by find_package(), try manually")

    if (NOT VULKAN_SDK_ROOT AND WIN32)
        # If under Windows with the path not manually set, try to locate it from the environment variable
        set(VULKAN_SDK_ROOT "$ENV{VULKAN_SDK}")
    endif()

    if (VULKAN_SDK_ROOT)
        # SDK path has been defined

        if (WIN32)
            string(REPLACE "\\" "/" VULKAN_SDK_ROOT ${VULKAN_SDK_ROOT})
            set(VULKAN_SDK_INCLUDE "${VULKAN_SDK_ROOT}/Include")
            set(VULKAN_SDK_LIB "${VULKAN_SDK_ROOT}/Lib/vulkan-1.lib")
        endif()

        if (EXISTS "${VULKAN_SDK_INCLUDE}/vulkan/vulkan.h" AND EXISTS "${VULKAN_SDK_LIB}")
            set(VULKAN_FOUND ON)
        endif()
    endif()
endif()

if (VULKAN_FOUND)
    message(STATUS "Vulkan configuration :")
    if (VULKAN_SDK_ROOT)
        message(STATUS "  - Root path: ${VULKAN_SDK_ROOT}")
    endif()
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
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/stb")
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/tinyobjloader")
