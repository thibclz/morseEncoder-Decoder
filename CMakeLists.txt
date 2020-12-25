cmake_minimum_required(VERSION 3.0.0)
project(morse_translate VERSION 0.1.0)


include_directories(include)

set(SOURCES src/fr_to_m.cpp src/write_wav.cpp include/fr_to_m.h include/write_wav.h)

add_executable(morse_translate main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
