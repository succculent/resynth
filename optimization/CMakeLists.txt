#Written by elisabeth
# The minimum cmake version required to run this
cmake_minimum_required(VERSION 2.8)

# project's name
project(test)

#If you already have dlib downloaded
add_subdirectory(./dlib dlib_build)

#If you don't have dlib downloaded
#include(FetchContent)
#FetchContent_Declare(dlib
    #GIT_REPOSITORY https://github.com/davisking/dlib.git
    #GIT_TAG        v19.18
    #)
#FetchContent_MakeAvailable(dlib)

#The file we're generating (<executable name> <source file>)
add_executable(test ${PROJECT_SOURCE_DIR}/test.cpp)

#Tell cmake that our executable depends on dlib
target_link_libraries(test dlib::dlib)



