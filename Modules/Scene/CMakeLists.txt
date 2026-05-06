# Scene_Module
file(GLOB_RECURSE SCENE_SRC *.cpp *.h)
add_library(Scene_Module SHARED ${SCENE_SRC})
target_compile_definitions(Scene_Module PRIVATE SCENE_DLL)

target_include_directories(Scene_Module INTERFACE Include)
target_link_libraries(Scene_Module PUBLIC Core_Module Assets_Module)
set_module_properties(Scene_Module)