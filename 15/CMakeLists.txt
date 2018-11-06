project(15)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

file(GLOB_RECURSE INCS "*.h")
add_executable(${PROJECT_NAME} ${SRC_LIST} ${INCS})
target_link_libraries(${PROJECT_NAME} pthread boost_system boost_thread)

