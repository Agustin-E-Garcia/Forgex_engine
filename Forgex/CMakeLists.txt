# Forgex_Executable
file(GLOB_RECURSE EXEC_SRC *.cpp *.h)
add_executable(Forgex_Exec ${EXEC_SRC})

target_link_libraries(Forgex_Exec PRIVATE Forgex_Editor)
set_target_properties(Forgex_Exec PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR}/Forgex/$<CONFIG>)
if(NOT MSVC)
    target_compile_options(Forgex_Exec PRIVATE -g)
endif()

if(WIN32)
    add_custom_command(TARGET Forgex_Exec POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Forgex_Exec>
            $<TARGET_FILE_DIR:Forgex_Exec>
        COMMAND_EXPAND_LISTS
    )
endif()
