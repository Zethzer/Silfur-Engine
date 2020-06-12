# Sandbox example
project(Sandbox)

# Sources files
FILE(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Shaders
add_dependencies(${PROJECT_NAME} CompileShaders)

# Dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC Silfur)

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC "src")