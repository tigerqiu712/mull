
set(unbreakable_sources unbreakable.cpp)
add_executable(unbreakable ${unbreakable_sources})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${MULL_SOURCE_DIR}/googletest/include")

target_link_libraries(unbreakable google-test)
