cmake_minimum_required(VERSION 3.21)
project(DesignPatterns)

set(CMAKE_CXX_STANDARD 14)

add_executable(Factory factory.cpp)
add_executable(AbstractFactory abstract_factory.cpp)
add_executable(Builder builder.cpp)