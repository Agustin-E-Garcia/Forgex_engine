# Assets_Module
file(GLOB_RECURSE ASSETS_SRC *.cpp *.h)
add_library(Assets_Module SHARED ${ASSETS_SRC})
target_compile_definitions(Assets_Module PRIVATE ASSETS_DLL)

target_include_directories(Assets_Module INTERFACE Include)
target_link_libraries(Assets_Module PUBLIC Core_Module)
set_module_properties(Assets_Module)