# FilesIO_Module
file(GLOB_RECURSE FILES_SRC *.cpp *.h)
add_library(FilesIO_Module SHARED ${FILES_SRC})
target_compile_definitions(FilesIO_Module PRIVATE FILES_DLL)

if(MSVC)
    target_compile_options(FilesIO_Module PRIVATE
        /experimental:external
        /external:anglebrackets
        /external:W0
    )
endif()

target_include_directories(FilesIO_Module INTERFACE Include)
target_include_directories(FilesIO_Module SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/ExternalLibraries/Nlohmann)
target_include_directories(FilesIO_Module SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/ExternalLibraries/STB_Image
    ${CMAKE_SOURCE_DIR}/ExternalLibraries/Tiny_obj_loader
)
set_module_properties(FilesIO_Module)