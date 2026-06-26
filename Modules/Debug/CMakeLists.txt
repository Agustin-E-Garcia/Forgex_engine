# Debug_Module
file(GLOB_RECURSE DEBUG_SRC *.cpp *.h)
add_library(Debug_Module SHARED ${DEBUG_SRC})
target_compile_definitions(Debug_Module PRIVATE DEBUG_DLL)

target_include_directories(Debug_Module INTERFACE Include)
target_link_libraries(Debug_Module PUBLIC DataStructures_Module)
target_include_directories(Debug_Module PRIVATE ${CMAKE_SOURCE_DIR}/ExternalLibraries/Spdlog/include)
set_module_properties(Debug_Module)
