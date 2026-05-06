# Voxel_Module
file(GLOB_RECURSE VOXEL_SRC *.cpp *.h)
add_library(Voxel_Module SHARED ${VOXEL_SRC})
target_compile_definitions(Voxel_Module PRIVATE VOXEL_DLL)

target_include_directories(Voxel_Module INTERFACE Include)
target_include_directories(Voxel_Module PRIVATE ${CMAKE_SOURCE_DIR}/ExternalLibraries/FastNoiseLite)
target_link_libraries(Voxel_Module PUBLIC Graphics_Module)
set_module_properties(Voxel_Module)