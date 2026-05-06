# Core_Module
file(GLOB_RECURSE CORE_SRC *.cpp *.h)
add_library(Core_Module SHARED ${CORE_SRC})
target_compile_definitions(Core_Module PRIVATE CORE_DLL)

target_include_directories(Core_Module INTERFACE Include)
target_include_directories(Core_Module PUBLIC ${CMAKE_SOURCE_DIR}/ExternalLibraries/EnTT ${CMAKE_SOURCE_DIR}/ExternalLibraries/GLM)
target_link_libraries(Core_Module PUBLIC Debug_Module FilesIO_Module)
set_module_properties(Core_Module)