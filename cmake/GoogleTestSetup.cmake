function(FetchGoogleTest)
    include(FetchContent)

    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG b796f7d # release-v1.13.1
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endfunction()

function(AddGoogleTestDependency TEST)
    message(VERBOSE "AddGoogleTestDependency: ${TEST}")
    target_link_libraries(${TEST} PRIVATE
        GTest::gtest_main
        GTest::gmock_main
    )
endfunction()

function(AutoDiscoverTargetTests TEST)
    message(VERBOSE "AutoDiscoverTargetTests: ${TEST}")
    include(GoogleTest)
    gtest_discover_tests(${TEST})
endfunction()

