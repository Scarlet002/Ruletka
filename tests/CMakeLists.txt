file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(RuletkaTESTS ${TEST_SOURCES})

target_link_libraries(RuletkaTESTS
    PRIVATE
        RuletkaLib
        GTest::gtest
        GTest::gtest_main
)

target_include_directories(RuletkaTESTS PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/unit
    ${CMAKE_CURRENT_SOURCE_DIR}/integration
)

include(GoogleTest)
gtest_discover_tests(RuletkaTESTS
    DISCOVERY_MODE PRE_TEST
    DISCOVERY_TIMEOUT 30
)