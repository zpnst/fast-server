cmake_minimum_required(VERSION 3.25)
project(fast_server)

if(NOT UNIX)
    message(FATAL_ERROR "It seems like your platform is not UNIX-like")
endif()

add_executable(client "sources/clients.cpp")
add_executable(company "sources/company.cpp")

file(GLOB ${PROJECT_NAME}_HEADERS "include/*.hpp" "include/*/*.hpp")
file(GLOB ${PROJECT_NAME}_SOURCES "sources/*.cpp" "sources/*/*.cpp")

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(client PRIVATE ${PROJECT_NAME})
target_link_libraries(company PRIVATE ${PROJECT_NAME})