Перед началом работы нужно инициализировать сабмодули (это не обязательно, не нужно в общем):

`` git submodule update --init --recursive ``

Необходимо установить grpc и protobuf в систему (например vcpkg), можно собрать самому, гайды:

- gRPC https://github.com/grpc/grpc/blob/master/BUILDING.md#build-from-source
- protobuf https://github.com/protocolbuffers/protobuf/blob/main/src/README.md

Генерация прото файлов:

``protoc -I ./src/protoFiles \
--cpp_out=:./src/protoFiles \
./src/protoFiles/chatBot.proto``

``protoc -I ./src/protoFiles \
--grpc_out=./src/protoFiles --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
./src/protoFiles/chatBot.proto``
