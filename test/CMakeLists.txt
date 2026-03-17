include_directories(../include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(polinoms-tests test_main.cpp ../src/Polinoms.cpp)
target_link_libraries(polinoms-tests PUBLIC gtest)

include(GoogleTest)
gtest_discover_tests(polinoms-tests)