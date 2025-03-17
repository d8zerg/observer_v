cmake_minimum_required(VERSION 3.20)

project(observer_v LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(observer_v src/main.cpp)

include(GNUInstallDirs)
install(TARGETS observer_v
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)