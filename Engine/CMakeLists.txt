# Engine
file(GLOB_RECURSE ENGINE_SRC *.cpp *.h)
add_library(Forgex_Engine SHARED ${ENGINE_SRC})
target_compile_definitions(Forgex_Engine PRIVATE ENGINE_DLL)

target_include_directories(Forgex_Engine INTERFACE Include)
target_link_libraries(Forgex_Engine PUBLIC Graphics_Module Scene_Module Voxel_Module)
target_link_libraries(Forgex_Engine PUBLIC Core_Module)
set_module_properties(Forgex_Engine)