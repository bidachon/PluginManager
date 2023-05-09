function(FetchGoogleTest)
    include(FetchContent)

    ## RKTODO:  Find the hash for the latest version of google test and update this
    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-v1.12.1
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endfunction()

function(AddGoogleTestDependency TEST)
    target_link_libraries(${TEST}
        GTest::gtest_main
        GTest::gmock_main
    )
endfunction()

function(AutoDiscoverTargetTests TEST)
    include(GoogleTest)
    gtest_discover_tests(${TEST})
endfunction()

