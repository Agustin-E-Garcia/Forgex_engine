# Graphics_Module
file(GLOB_RECURSE GRAPHICS_SRC *.cpp *.h)
add_library(Graphics_Module SHARED ${GRAPHICS_SRC})
target_compile_definitions(Graphics_Module PRIVATE GRAPHICS_DLL)

target_include_directories(Graphics_Module INTERFACE Include)
target_link_libraries(Graphics_Module PRIVATE GLEW::GLEW glfw OpenGL::GL OpenGL::GLU)
target_link_libraries(Graphics_Module PUBLIC Core_Module Assets_Module)
set_module_properties(Graphics_Module)