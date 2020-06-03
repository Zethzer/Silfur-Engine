cmake_minimum_required(VERSION 3.11)
project(Silfur_Engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(Silfur/src)
include_directories(Silfur/vendor/glm/glm)
include_directories(Silfur/vendor/portable-snippets)
include_directories(Silfur/vendor/spdlog/include)
include_directories(Silfur/vendor/stb)
include_directories(Silfur/vendor/tinyobjloader)

add_executable(Silfur_Engine)
