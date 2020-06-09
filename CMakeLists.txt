cmake_minimum_required(VERSION 3.17)
project(SilfurEngine)

### Engine ###
add_subdirectory(Silfur)

### Examples ###
option(SILFUR_BUILD_EXAMPLES "Build examples" ON)
if (SILFUR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
#teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest251
#teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest250
#teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest231
#teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest230
#teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest221
#teeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeest220
### Shaders ###
# Fake target for compile the shaders with CMake
# Just add the line :
#     add_dependencies(MyTarget CompileShaders)
# in the CMakeLists.txt of your target. Don't forget to replace MyTarget

# Find glslc executable from Vulkan SDK
find_program(GLSLC_EXECUTABLE glslc HINTS "$ENV{VULKAN_SDK}/bin")
if (GLSLC_EXECUTABLE)
    message(STATUS "  - GLSLC executable: ${GLSLC_EXECUTABLE}")
else ()
    # GLSLC executable not found, send a warning

    set(GLSLC_EXECUTABLE "" CACHE PATH "Path to your GLSLC executable")
    message(WARNING "Warning: GLSLC executable not found. To compile shaders into SPIR-V, please specify its path manually.")
endif ()

# Shaders compilation
if (GLSLC_EXECUTABLE)
    set(SHADERS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

    # Recovering shaders
    file(
            GLOB_RECURSE
            SHADERS

            ${SHADERS_ROOT}/*.vert # Vertex shader
            ${SHADERS_ROOT}/*.tesc # Tesselation control shader
            ${SHADERS_ROOT}/*.tese # Tesselation evaluation shader
            ${SHADERS_ROOT}/*.geom # Geometry shader
            ${SHADERS_ROOT}/*.frag # Fragment shader
            ${SHADERS_ROOT}/*.comp # Compute shader
    )

    # Compiling all shaders found
    foreach (SHADER_INPUT_PATH ${SHADERS})
        # Stripping the path from the prepending folders, keeping the file's name
        get_filename_component(SHADER_FILENAME ${SHADER_INPUT_PATH} NAME)
        string(REPLACE "." ";" SHADER_FILE_PARTS ${SHADER_FILENAME})

        get_filename_component(SHADER_DIRECTORY ${SHADER_INPUT_PATH} DIRECTORY)
        if (WIN32)
            string(REPLACE "\\" "/" SHADER_DIRECTORY ${SHADER_DIRECTORY})
        endif()

        list(GET SHADER_FILE_PARTS 0 SHADER_NAME)
        list(GET SHADER_FILE_PARTS 1 SHADER_EXT)

        set(SHADER_OUTPUT_PATH "${SHADER_DIRECTORY}/${SHADER_NAME}.${SHADER_EXT}.spv")

        add_custom_command(
                OUTPUT "${SHADER_OUTPUT_PATH}"
                COMMAND ${GLSLC_EXECUTABLE} ${SHADER_INPUT_PATH} -o ${SHADER_OUTPUT_PATH}
                DEPENDS "${SHADER_INPUT_PATH}"
                WORKING_DIRECTORY "${SHADERS_ROOT}"
                COMMENT "Compiling shader ${SHADER_FILENAME} to SPIR-V"
                VERBATIM
        )

        set (SHADERS_COMP ${SHADERS_COMP} ${SHADER_OUTPUT_PATH})
    endforeach ()

    # Create custom target for shaders
    add_custom_target(CompileShaders ALL DEPENDS ${SHADERS_COMP})
endif ()
