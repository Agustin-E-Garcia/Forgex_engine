cmake_minimum_required(VERSION 3.20)
option(GENERATE_COMPILE_COMMANDS "Generates compile_commands.json and copies it to the project root" OFF)

project(Forgex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Build/Bin)
set(LIBS_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Build/Libs)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find OpenGL properly
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

if(MSVC)
    add_compile_options(/utf-8)
endif()

if(GENERATE_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    # Copy compile_commands.json to project root after generation if it exists
    add_custom_target(copy_compile_commands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_SOURCE_DIR}/compile_commands.json
        COMMENT "Copying compile_commands.json if it exists"
    )
endif()

# Helper function to set common properties for modules
function(set_module_properties target_name)
    set_target_properties(${target_name} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${LIBS_OUTPUT_DIR}/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
    )
endfunction()

# ========================================================================================================#

# ImGui
file(GLOB IMGUI_SRC
    ExternalLibraries/ImGui/*.cpp
    ExternalLibraries/ImGui/*.h
    ExternalLibraries/ImGui/backends/imgui_impl_opengl3.cpp
    ExternalLibraries/ImGui/backends/imgui_impl_opengl3.h
    ExternalLibraries/ImGui/misc/cpp/imgui_stdlib.cpp
    ExternalLibraries/ImGui/misc/cpp/imgui_stdlib.h
)
add_library(ImGui STATIC ${IMGUI_SRC})
set_target_properties(ImGui PROPERTIES POSITION_INDEPENDENT_CODE ON ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/ExternalLibraries/ImGui/bin)

target_include_directories(ImGui PRIVATE ExternalLibraries/ImGui)
target_include_directories(ImGui INTERFACE ExternalLibraries/ImGui)
target_link_libraries(ImGui PRIVATE OpenGL::GL)

add_subdirectory(Modules/Debug)
add_subdirectory(Modules/FilesIO)
add_subdirectory(Modules/Core)
add_subdirectory(Modules/Assets)
add_subdirectory(Modules/Graphics)
add_subdirectory(Modules/Scene)
add_subdirectory(Modules/Voxel)
add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Forgex)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Forgex/Resources
        ${BUILD_OUTPUT_DIR}/Forgex/$<CONFIG>/Resources
    COMMENT "Copying Resources to output directory"
)