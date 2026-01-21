cmake_minimum_required(VERSION 3.10)
project(Strassen-algorithm)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    main.cpp
    Collector.cpp
    Consumer.cpp
    matrix.cpp
)

set(HEADERS
    matrix.h
    Producer.h
    Consumer.h
    Collector.h
    Task.h
    BlockingQueue.h
)
find_package(Threads REQUIRED)
add_executable(Strassen ${SOURCES})
target_link_libraries(Strassen Threads::Threads)
