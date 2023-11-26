# Minimum required cmake version
cmake_minimum_required(VERSION 3.25) 
project(fast_server)

if(NOT UNIX) 
    message(FATAL_ERROR "It seems like your platform is not UNIX-like")
endif()

# Creating all project executables
add_executable(client "sources/clients.cpp")
add_executable(company "sources/company.cpp")

# Search for files and put them in the appropriate variables
file(GLOB ${PROJECT_NAME}_HEADERS "include/*.hpp" "include/*/*.hpp")
file(GLOB ${PROJECT_NAME}_SOURCES "sources/*.cpp" "sources/*/*.cpp")

# Creating a library using files from the specified variables
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES})

# Adding the include directory to the list of directories where header files for the ${PROJECT_NAME} library will be searched.
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# These lines ensure that when the project is built, the client and company executables 
# will be linked to the ${PROJECT_NAME} library, which allows them to use the functions and classes defined in this library.
target_link_libraries(client PRIVATE ${PROJECT_NAME})
target_link_libraries(company PRIVATE ${PROJECT_NAME})