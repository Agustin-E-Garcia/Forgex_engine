cmake_minimum_required(VERSION 3.20)
project(Forgex_Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Build/Bin)

# Find OpenGL properly
find_package(OpenGL REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Copy compile_commands.json to project root after generation
add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)

# Global includes and options
include_directories(Modules/Debug/Include)

# Helper function to set common properties for modules
function(set_module_properties target_name)
    set_target_properties(${target_name} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
    )
endfunction()

# Debug_Module
file(GLOB_RECURSE DEBUG_SRC Modules/Debug/*.cpp Modules/Debug/*.h)
add_library(Debug_Module SHARED ${DEBUG_SRC})
target_include_directories(Debug_Module PRIVATE ExternalLibraries/Spdlog/include)
target_compile_definitions(Debug_Module PRIVATE DEBUG_DLL)
set_module_properties(Debug_Module)

# Core_Module
file(GLOB_RECURSE CORE_SRC Modules/Core/*.cpp Modules/Core/*.h)
add_library(Core_Module SHARED ${CORE_SRC})
target_include_directories(Core_Module PRIVATE
    Modules/Graphics/Include
    Modules/Scene/Include
    Modules/Assets/Include
    Modules/Voxel/Include
    ExternalLibraries/GLM
    ExternalLibraries/EnTT
    ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/include
)
target_compile_definitions(Core_Module PRIVATE CORE_DLL)
target_link_libraries(Core_Module PRIVATE Graphics_Module Scene_Module Debug_Module Assets_Module Voxel_Module)
set_module_properties(Core_Module)

# Graphics_Module
file(GLOB_RECURSE GRAPHICS_SRC Modules/Graphics/*.cpp Modules/Graphics/*.h)
add_library(Graphics_Module SHARED ${GRAPHICS_SRC})
target_include_directories(Graphics_Module PRIVATE
    ExternalLibraries/GLM
    ExternalLibraries/GLEW/glew-2.1.0/include
    ExternalLibraries/GLFW/glfw-3.4.bin.WIN64/include
    ExternalLibraries/STB_Image
)
target_compile_definitions(Graphics_Module PRIVATE GRAPHICS_DLL)
target_link_libraries(Graphics_Module PRIVATE Debug_Module)

if(WIN32)
    target_link_libraries(Graphics_Module PRIVATE glew32 glfw3 opengl32)
else()
    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)
    target_link_libraries(Graphics_Module PRIVATE GLEW::GLEW glfw OpenGL::GL)
endif()

set_module_properties(Graphics_Module)

# Scene_Module
file(GLOB_RECURSE SCENE_SRC Modules/Scene/*.cpp Modules/Scene/*.h)
add_library(Scene_Module SHARED ${SCENE_SRC})
target_include_directories(Scene_Module PRIVATE
    ExternalLibraries/GLM 
    ExternalLibraries/EnTT
)
target_compile_definitions(Scene_Module PRIVATE SCENE_DLL)
target_link_libraries(Scene_Module PRIVATE Debug_Module)
set_module_properties(Scene_Module)

# Assets_Module
file(GLOB_RECURSE ASSETS_SRC Modules/Assets/*.cpp Modules/Assets/*.h)
add_library(Assets_Module SHARED ${ASSETS_SRC})
target_compile_definitions(Assets_Module PRIVATE ASSETS_DLL)
target_link_libraries(Assets_Module PRIVATE Debug_Module)
set_module_properties(Assets_Module)

# Voxel_Module
file(GLOB_RECURSE VOXEL_SRC Modules/Voxel/*.cpp Modules/Voxel/*.h)
add_library(Voxel_Module SHARED ${VOXEL_SRC})
target_include_directories(Voxel_Module PRIVATE ExternalLibraries/GLM ExternalLibraries/FastNoiseLite)
target_compile_definitions(Voxel_Module PRIVATE VOXEL_DLL)
target_link_libraries(Voxel_Module PRIVATE Debug_Module)
set_module_properties(Voxel_Module)

# Forgex_Editor
file(GLOB_RECURSE EDITOR_SRC Editor/*.cpp Editor/*.h)
add_executable(Forgex_Editor ${EDITOR_SRC})
target_include_directories(Forgex_Editor PRIVATE Modules/Core/Include ExternalLibraries/ImGui)
target_link_libraries(Forgex_Editor PRIVATE Core_Module Debug_Module ImGui)
set_target_properties(Forgex_Editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/Forgex_Editor/$<CONFIG>
)

# Only Windows needs DLL copy steps
if(WIN32)
    add_custom_command(TARGET Forgex_Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BUILD_OUTPUT_DIR}/Core_Module/$<CONFIG>/Core_Module.dll
            ${BUILD_OUTPUT_DIR}/Forgex_Editor/$<CONFIG>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${BUILD_OUTPUT_DIR}/Debug_Module/$<CONFIG>/Debug_Module.dll
            ${BUILD_OUTPUT_DIR}/Forgex_Editor/$<CONFIG>
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Editor/Resources
            ${BUILD_OUTPUT_DIR}/Forgex_Editor/$<CONFIG>/Resources
    )
else()
    # Just copy resources folder
    add_custom_command(TARGET Forgex_Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Editor/Resources
            ${BUILD_OUTPUT_DIR}/Forgex_Editor/$<CONFIG>/Resources
    )
endif()

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
set_target_properties(ImGui PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/ExternalLibraries/ImGui/bin
)
target_include_directories(ImGui PRIVATE ExternalLibraries/ImGui)

if(WIN32)
    target_link_libraries(ImGui PRIVATE opengl32)
else()
    target_link_libraries(ImGui PRIVATE OpenGL::GL)
endif()
