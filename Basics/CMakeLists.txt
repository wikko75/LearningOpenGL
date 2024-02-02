cmake_minimum_required(VERSION 3.15)

project(Basics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# fmt setup
find_package(fmt CONFIG REQUIRED)

# GLFW setup
find_package(glfw3 REQUIRED)

# GLEW setup
find_package(GLEW REQUIRED)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE inc)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")

    target_compile_options(${PROJECT_NAME} PRIVATE
        "-Wall" 
        "-Wuninitialized" 
        "-Wunused-variable" 
        "-Wshadow"
        "-O3" 
    )
    
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        fmt::fmt 
        GLEW::GLEW 
        glfw 
        GL
    )

else()
    
    target_compile_options(${PROJECT_NAME} PRIVATE "/W4")

    target_link_libraries(${PROJECT_NAME} PRIVATE 
        fmt::fmt 
        GLEW::GLEW 
        glfw
    )
endif()