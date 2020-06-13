
cmake_minimum_required(VERSION 3.3...3.10)

project(travelling_salesman_problem
    VERSION     1.0
    DESCRIPTION "Travelling Salesman Problem"
    LANGUAGES   CXX)

add_executable(tsp_gen tsp_gen.cpp)
target_compile_features(tsp_gen PUBLIC cxx_std_17)
set_target_properties(tsp_gen PROPERTIES CXX_EXTENSIONS OFF)

add_executable(tsp_solver tsp_solver.cpp)
target_compile_features(tsp_solver PUBLIC cxx_std_17)
set_target_properties(tsp_solver PROPERTIES CXX_EXTENSIONS OFF)
