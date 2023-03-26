cmake_minimum_required(VERSION 3.13)

project(gRPC_TPPO VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(grpc)
add_subdirectory(fmt)

add_executable(server src/server/main.cpp)
target_link_libraries(server fmt grpc++ grpc++_reflection)

add_executable(client src/client/main.cpp)
target_link_libraries(client fmt grpc++ grpc++_reflection)
