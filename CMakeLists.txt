cmake_minimum_required(VERSION 3.28)
project(algorithms)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOLUTIONS src/**/solution.cpp)
foreach(file ${SOLUTIONS})
    get_filename_component(dir ${file} DIRECTORY)
    get_filename_component(problem_num ${dir} NAME)
    add_executable(problem_${problem_num} ${file})
endforeach()
