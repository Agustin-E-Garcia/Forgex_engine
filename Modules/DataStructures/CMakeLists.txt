# DataStructures_Module
file(GLOB_RECURSE DATASTRUCTURES_SRC *.cpp *.h)
add_library(DataStructures_Module SHARED ${DATASTRUCTURES_SRC})
target_compile_definitions(DataStructures_Module PRIVATE DATASTRUCTURES_DLL)

target_include_directories(DataStructures_Module INTERFACE Include)
set_module_properties(DataStructures_Module)
