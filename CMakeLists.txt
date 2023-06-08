cmake_minimum_required(VERSION 3.13)

project(gRPC_TPPO VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

#add_subdirectory(fmt)

add_executable(server src/server/main.cpp
        src/protoFiles/chatBot.grpc.pb.h
        src/protoFiles/chatBot.grpc.pb.cc
        src/protoFiles/chatBot.pb.h
        src/protoFiles/chatBot.pb.cc
        )
target_link_libraries(server PUBLIC gRPC::grpc++ gRPC::grpc++_reflection)

add_executable(client src/client/main.cpp
        src/protoFiles/chatBot.grpc.pb.h
        src/protoFiles/chatBot.grpc.pb.cc
        src/protoFiles/chatBot.pb.h
        src/protoFiles/chatBot.pb.cc
        )
target_link_libraries(client PUBLIC gRPC::grpc++ gRPC::grpc++_reflection)
