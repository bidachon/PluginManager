function(FetchGoogleTest)
    include(FetchContent)

    ## RKTODO:  Find the hash for the latest version of google test and update this
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endfunction()

function(AddGoogleTestDependency TEST)
    target_link_libraries(${TEST}
        GTest::gtest_main
    )
endfunction()

function(AutoDiscoverTargetTests TEST)
    include(GoogleTest)
    gtest_discover_tests(${TEST})
endfunction()
