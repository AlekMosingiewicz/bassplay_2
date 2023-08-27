add_executable(tests
        compiled_tests.cpp
        )
target_link_libraries(tests Play_lib)
target_link_libraries(tests bass)