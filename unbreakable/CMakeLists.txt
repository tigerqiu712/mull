
set(unbreakable_sources unbreakable.cpp)
add_executable(unbreakable ${unbreakable_sources})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${MULL_SOURCE_DIR}/googletest/include")

target_link_libraries(unbreakable google-test)

mull_clone_target(unbreakable unbreakable-bitcode)
set_target_properties(unbreakable-bitcode PROPERTIES XCODE_ATTRIBUTE_CC "${MULL_CC}")
set_target_properties(unbreakable-bitcode PROPERTIES XCODE_ATTRIBUTE_CXX "${MULL_CXX}")

mull_clone_target(mull-driver mull-unbreakable-driver)

add_dependencies(mull-unbreakable-driver
  unbreakable-bitcode
  google-test-bitcode
)
