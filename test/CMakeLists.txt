include_directories(${PROJECT_SOURCE_DIR}/leptSTL)
set(APP_SRC lept_test.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(leptstl_test ${APP_SRC})
