project(module3)
cmake_minimum_required(VERSION 3.0)

add_executable(module3 module3.cxx Graph.cxx Stack.cxx)
set_property(TARGET module3 PROPERTY CXX_STANDARD 11)
target_compile_options(module3 PUBLIC "-g3" "-Wall")
