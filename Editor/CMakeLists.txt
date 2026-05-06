# Editor
file(GLOB_RECURSE EDITOR_SRC *.cpp *.h)
add_library(Forgex_Editor SHARED ${EDITOR_SRC})
target_compile_definitions(Forgex_Editor PRIVATE EDITOR_DLL)

target_include_directories(Forgex_Editor INTERFACE Include)
target_link_libraries(Forgex_Editor PUBLIC Forgex_Engine)
target_link_libraries(Forgex_Editor PRIVATE ImGui)
set_module_properties(Forgex_Editor)