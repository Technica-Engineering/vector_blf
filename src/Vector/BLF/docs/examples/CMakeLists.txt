include_directories(${PROJECT_SOURCE_DIR}/src)

if(OPTION_RUN_EXAMPLES)

  add_definitions(
    -DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
    -DCMAKE_CURRENT_BINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

  set(CMAKE_STATIC_LIBRARY_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")
  set(CMAKE_SHARED_LIBRARY_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")

  if(WIN32)
#    add_custom_target(Vector_DLL-Copy ALL
#      COMMAND ${CMAKE_COMMAND} -E copy_if_different
#      "${PROJECT_BINARY_DIR}/src/Vector/BLF/${CMAKE_BUILD_TYPE}/Vector_BLF.dll"
#      "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}"
#      COMMENT "Copy ${PROJECT_BINARY_DIR}/src/Vector/BLF/${CMAKE_BUILD_TYPE}/Vector_BLF.dll to ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
    add_custom_target(Vector_DLL-Copy ALL
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${PROJECT_BINARY_DIR}/src/Vector/BLF/Vector_BLF.dll"
      "${CMAKE_CURRENT_BINARY_DIR}"
      COMMENT "Copy ${PROJECT_BINARY_DIR}/src/Vector/BLF/Vector_BLF.dll to ${CMAKE_CURRENT_BINARY_DIR}")
  endif()

  add_executable(example_Parser Parser.cpp)

  target_link_libraries(example_Parser Vector_BLF)

endif()

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/Parser.cpp
  DESTINATION share/doc/Vector_BLF/examples)
