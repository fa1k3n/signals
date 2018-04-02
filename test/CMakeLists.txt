find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    SET(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    SET(GOOGLETEST_DIR "${PROJECT_SOURCE_DIR}/external/googletest")
    message(STATUS "using google test at ${GOOGLETEST_DIR}")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    SET(GTestSrc ${GOOGLETEST_DIR}/googletest)
    SET(GMockSrc ${GOOGLETEST_DIR}/googlemock)
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${GTestSrc} ${GTestSrc}/include ${GMockSrc} ${GMockSrc}/include)

set(TESTCASES
    tst_signals.cpp
    ${GTestSrc}/src/gtest-all.cc
    ${GMockSrc}/src/gmock-all.cc)

add_executable(unittest EXCLUDE_FROM_ALL main.cpp ${TESTCASES})
add_test(unittest COMMAND unittest)
target_link_libraries(unittest Threads::Threads)

