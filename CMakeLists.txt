cmake_minimum_required(VERSION 3.0.0)
project(trabalho VERSION 0.1.0)

add_compile_options(-Wall -Wextra -Werror)

include(CTest)
enable_testing()

add_executable(trabalho main.c aux.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
