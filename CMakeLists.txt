cmake_minimum_required(VERSION 3.20)
option(GENERATE_COMPILE_COMMANDS "Generates compile_commands.json and copies it to the project root" OFF)

project(Forgex)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Build/Bin)
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
        ARCHIVE_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/${target_name}/$<CONFIG>
    )
endfunction()

# ========================================================================================================#

# Debug_Module
file(GLOB_RECURSE DEBUG_SRC Modules/Debug/*.cpp Modules/Debug/*.h)
add_library(Debug_Module SHARED ${DEBUG_SRC})
target_compile_definitions(Debug_Module PRIVATE DEBUG_DLL)

target_include_directories(Debug_Module INTERFACE Modules/Debug/Include)
target_include_directories(Debug_Module PRIVATE ExternalLibraries/Spdlog/include)
set_module_properties(Debug_Module)

# Assets_Module
file(GLOB_RECURSE ASSETS_SRC Modules/Assets/*.cpp Modules/Assets/*.h)
add_library(Assets_Module SHARED ${ASSETS_SRC})
target_compile_definitions(Assets_Module PRIVATE ASSETS_DLL)

target_include_directories(Assets_Module INTERFACE Modules/Assets/Include)
target_include_directories(Assets_Module PRIVATE ExternalLibraries/STB_Image)
target_link_libraries(Assets_Module PUBLIC Debug_Module)
set_module_properties(Assets_Module)

# Core_Module
file(GLOB_RECURSE CORE_SRC Modules/Core/*.cpp Modules/Core/*.h)
add_library(Core_Module SHARED ${CORE_SRC})
target_compile_definitions(Core_Module PRIVATE CORE_DLL)

target_include_directories(Core_Module INTERFACE Modules/Core/Include)
target_include_directories(Core_Module PUBLIC ExternalLibraries/EnTT ExternalLibraries/GLM)
target_link_libraries(Core_Module PUBLIC Debug_Module Assets_Module)
set_module_properties(Core_Module)

# Graphics_Module
file(GLOB_RECURSE GRAPHICS_SRC Modules/Graphics/*.cpp Modules/Graphics/*.h)
add_library(Graphics_Module SHARED ${GRAPHICS_SRC})
target_compile_definitions(Graphics_Module PRIVATE GRAPHICS_DLL)

target_include_directories(Graphics_Module INTERFACE Modules/Graphics/Include)
target_link_libraries(Graphics_Module PRIVATE GLEW::GLEW glfw OpenGL::GL)
target_link_libraries(Graphics_Module PUBLIC Core_Module)
set_module_properties(Graphics_Module)

# Scene_Module
file(GLOB_RECURSE SCENE_SRC Modules/Scene/*.cpp Modules/Scene/*.h)
add_library(Scene_Module SHARED ${SCENE_SRC})
target_compile_definitions(Scene_Module PRIVATE SCENE_DLL)

target_include_directories(Scene_Module INTERFACE Modules/Scene/Include)
target_link_libraries(Scene_Module PUBLIC Core_Module)
set_module_properties(Scene_Module)


# Voxel_Module
file(GLOB_RECURSE VOXEL_SRC Modules/Voxel/*.cpp Modules/Voxel/*.h)
add_library(Voxel_Module SHARED ${VOXEL_SRC})
target_compile_definitions(Voxel_Module PRIVATE VOXEL_DLL)

target_include_directories(Voxel_Module INTERFACE Modules/Voxel/Include)
target_include_directories(Voxel_Module PRIVATE ExternalLibraries/FastNoiseLite)
target_link_libraries(Voxel_Module PUBLIC Core_Module)
set_module_properties(Voxel_Module)

# Engine
file(GLOB_RECURSE ENGINE_SRC Engine/*.cpp Engine/*.h)
add_library(Forgex_Engine SHARED ${ENGINE_SRC})
target_compile_definitions(Forgex_Engine PRIVATE ENGINE_DLL)

target_include_directories(Forgex_Engine INTERFACE Engine/Include)
target_link_libraries(Forgex_Engine PUBLIC Graphics_Module Scene_Module Voxel_Module Core_Module)
set_module_properties(Forgex_Engine)

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

# Editor
file(GLOB_RECURSE EDITOR_SRC Editor/*.cpp Editor/*.h)
add_library(Forgex_Editor SHARED ${EDITOR_SRC})
target_compile_definitions(Forgex_Editor PRIVATE EDITOR_DLL)

target_include_directories(Forgex_Editor INTERFACE Editor/Include)
target_link_libraries(Forgex_Editor PUBLIC Forgex_Engine)
target_link_libraries(Forgex_Editor PRIVATE ImGui)
set_module_properties(Forgex_Editor)

# Forgex_Executable
file(GLOB_RECURSE EXEC_SRC Forgex/*.cpp Forgex/*.h)
add_executable(Forgex_Exec ${EXEC_SRC})

target_link_libraries(Forgex_Exec PRIVATE Forgex_Editor)
set_target_properties(Forgex_Exec PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/Forgex/$<CONFIG>)
if(NOT MSVC)
    target_compile_options(Forgex_Exec PRIVATE -g)
endif()
